#pragma once
#include "doof_runtime.hpp"
#include <spawn.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <cerrno>
#include <cstring>
extern char **environ;

// macOS pipe ownership only. Protocol and all debugger behavior live in Doof.
// Each pump is bounded; neither pipe reads nor writes block the AppKit thread.
class DebugTransport {
    pid_t child_ = -1;
    int input_ = -1, output_ = -1, error_ = -1;
    std::string pending_, failure_;
    static void closeFd(int& fd) { if (fd >= 0) ::close(fd); fd = -1; }
    static void nonblocking(int fd) {
        fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
        fcntl(fd, F_SETFD, FD_CLOEXEC);
        fcntl(fd, F_SETNOSIGPIPE, 1);
    }
public:
    static doof::Result<std::shared_ptr<DebugTransport>, std::string> start(
        const std::string& command, const std::shared_ptr<std::vector<std::string>>& arguments) {
        auto p = std::make_shared<DebugTransport>();
        int in[2] = {-1,-1}, out[2] = {-1,-1}, err[2] = {-1,-1};
        if (pipe(in) || pipe(out) || pipe(err)) {
            for (int* pair : {in, out, err}) { closeFd(pair[0]); closeFd(pair[1]); }
            return doof::Failure<std::string>{"Cannot create debugger pipes"};
        }
        posix_spawn_file_actions_t actions;
        posix_spawn_file_actions_init(&actions);
        posix_spawn_file_actions_adddup2(&actions, in[0], STDIN_FILENO);
        posix_spawn_file_actions_adddup2(&actions, out[1], STDOUT_FILENO);
        posix_spawn_file_actions_adddup2(&actions, err[1], STDERR_FILENO);
        for (int fd : {in[0],in[1],out[0],out[1],err[0],err[1]})
            posix_spawn_file_actions_addclose(&actions, fd);
        posix_spawnattr_t attr;
        posix_spawnattr_init(&attr);
        posix_spawnattr_setflags(&attr, POSIX_SPAWN_SETPGROUP | POSIX_SPAWN_CLOEXEC_DEFAULT);
        posix_spawnattr_setpgroup(&attr, 0);
        std::vector<char*> argv{const_cast<char*>(command.c_str())};
        for (const auto& arg : *arguments) argv.push_back(const_cast<char*>(arg.c_str()));
        argv.push_back(nullptr);
        int status = posix_spawn(&p->child_, command.c_str(), &actions, &attr, argv.data(), environ);
        posix_spawn_file_actions_destroy(&actions);
        posix_spawnattr_destroy(&attr);
        closeFd(in[0]); closeFd(out[1]); closeFd(err[1]);
        if (status) {
            closeFd(in[1]); closeFd(out[0]); closeFd(err[0]);
            p->child_ = -1;
            return doof::Failure<std::string>{std::string("Cannot start LLDB-DAP: ") + strerror(status)};
        }
        p->input_ = in[1]; p->output_ = out[0]; p->error_ = err[0];
        nonblocking(p->input_); nonblocking(p->output_); nonblocking(p->error_);
        return doof::Success<std::shared_ptr<DebugTransport>>{p};
    }
    doof::Result<void,std::string> send(const std::string& text) {
        if (input_ < 0) return doof::Failure<std::string>{"Debugger pipe is closed"};
        if (pending_.size() + text.size() > 8 * 1024 * 1024)
            return doof::Failure<std::string>{"Debugger write queue exceeded 8 MiB"};
        pending_ += text;
        flush();
        if (!failure_.empty()) return doof::Failure<std::string>{failure_};
        return doof::Success<void>{};
    }
    void flush() {
        if (input_ < 0 || pending_.empty()) return;
        auto n = write(input_, pending_.data(), std::min<size_t>(pending_.size(),65536));
        if (n > 0) pending_.erase(0, static_cast<size_t>(n));
        else if (n < 0 && errno != EAGAIN && errno != EINTR) {
            failure_ = std::string("Debugger write failed: ") + strerror(errno); closeFd(input_);
        }
    }
    std::shared_ptr<std::vector<uint8_t>> read(bool stderrStream) {
        int& fd = stderrStream ? error_ : output_;
        auto bytes = std::make_shared<std::vector<uint8_t>>();
        if (fd < 0) return bytes;
        bytes->resize(65536);
        auto n = ::read(fd, bytes->data(), bytes->size());
        if (n > 0) bytes->resize(n);
        else {
            bytes->clear();
            if (n == 0) closeFd(fd);
            else if (errno != EAGAIN && errno != EINTR) {
                failure_ = std::string("Debugger read failed: ") + strerror(errno); closeFd(fd);
            }
        }
        return bytes;
    }
    bool running() {
        if (child_ <= 0) return false;
        int status = 0;
        auto result = waitpid(child_, &status, WNOHANG);
        if (result == child_ || (result < 0 && errno == ECHILD)) { child_ = -1; return false; }
        return true;
    }
    bool stdoutOpen() { return output_ >= 0; }
    std::string error() { return failure_; }
    void close() {
        closeFd(input_); closeFd(output_); closeFd(error_);
        if (child_ > 0) {
            // This group belongs exclusively to this spawned adapter.
            kill(-child_, SIGKILL);
            int status = 0;
            while (waitpid(child_, &status, 0) < 0 && errno == EINTR) {}
            child_ = -1;
        }
    }
    ~DebugTransport() { close(); }
};

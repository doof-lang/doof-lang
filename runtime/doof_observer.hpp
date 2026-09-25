#pragma once
// Included inside namespace doof after the metrics primitives.

// ============================================================================
// Observer — authenticated loopback HTTP diagnostics
// ============================================================================

namespace observe {

#if defined(_WIN32)
using socket_handle = SOCKET;
using socket_length = int;
inline constexpr socket_handle invalid_socket = INVALID_SOCKET;
inline void close_socket(socket_handle value) { closesocket(value); }
inline bool initialize_sockets() {
    WSADATA data{};
    return WSAStartup(MAKEWORD(2, 2), &data) == 0;
}
#else
using socket_handle = int;
using socket_length = socklen_t;
inline constexpr socket_handle invalid_socket = -1;
inline void close_socket(socket_handle value) { ::close(value); }
inline bool initialize_sockets() { return true; }
#endif

inline std::once_flag server_once;
inline std::string server_url;
inline std::string session_id;
inline std::atomic<int> active_clients{0};
inline std::atomic<bool> running{false};
inline socket_handle listener = invalid_socket;
inline socket_handle listener_v6 = invalid_socket;
inline std::thread listener_thread;
inline std::thread listener_v6_thread;
inline std::thread metric_flush_thread;
inline std::mutex clients_mutex;
inline std::condition_variable clients_finished;

struct Event {
    uint64_t id;
    std::string type;
    std::string data;
};

inline std::mutex events_mutex;
inline std::condition_variable events_changed;
inline std::deque<Event> events;
inline uint64_t next_event_id = 1;
inline std::size_t retained_event_bytes = 0;
inline constexpr std::size_t maximum_retained_event_bytes = 8 * 1024 * 1024;
inline std::mutex pending_metrics_mutex;
inline std::unordered_map<std::string, int64_t> pending_metrics;

inline std::size_t event_retention() {
    static const std::size_t value = [] {
        const char* text = std::getenv("DOOF_OBSERVE_RETAIN_EVENTS");
        if (text == nullptr || *text == '\0') return std::size_t{10000};
        char* end = nullptr;
        const auto parsed = std::strtoull(text, &end, 10);
        return end != text && *end == '\0' && parsed > 0
            ? static_cast<std::size_t>(std::min<unsigned long long>(parsed, 100000ULL))
            : std::size_t{10000};
    }();
    return value;
}

inline void publish_event(const std::string& type, const std::string& data) {
    if (data.size() > 65536) return;
    {
        std::lock_guard<std::mutex> lock(events_mutex);
        events.push_back(Event{next_event_id++, type, data});
        retained_event_bytes += type.size() + data.size();
        while (events.size() > event_retention() || retained_event_bytes > maximum_retained_event_bytes) {
            retained_event_bytes -= events.front().type.size() + events.front().data.size();
            events.pop_front();
        }
    }
    events_changed.notify_all();
}

inline std::string html_escape(const std::string& value) {
    std::string result;
    result.reserve(value.size());
    for (const char character : value) {
        switch (character) {
            case '&': result += "&amp;"; break;
            case '<': result += "&lt;"; break;
            case '>': result += "&gt;"; break;
            case '"': result += "&quot;"; break;
            case '\'': result += "&#39;"; break;
            default: result += character; break;
        }
    }
    return result;
}

inline std::string json_escape(const std::string& value) {
    std::ostringstream result;
    for (const unsigned char character : value) {
        switch (character) {
            case '"': result << "\\\""; break;
            case '\\': result << "\\\\"; break;
            case '\b': result << "\\b"; break;
            case '\f': result << "\\f"; break;
            case '\n': result << "\\n"; break;
            case '\r': result << "\\r"; break;
            case '\t': result << "\\t"; break;
            default:
                if (character < 0x20) {
                    result << "\\u" << std::hex << std::setw(4) << std::setfill('0')
                           << static_cast<int>(character) << std::dec;
                } else {
                    result << character;
                }
        }
    }
    return result.str();
}

inline void publish_metric(const std::string& name, int64_t value) {
    std::lock_guard<std::mutex> lock(pending_metrics_mutex);
    pending_metrics[name] = value;
}

inline void flush_metric_events() {
    std::unordered_map<std::string, int64_t> changed;
    {
        std::lock_guard<std::mutex> lock(pending_metrics_mutex);
        changed.swap(pending_metrics);
    }
    if (changed.empty()) return;
    std::vector<std::pair<std::string, int64_t>> ordered(changed.begin(), changed.end());
    std::sort(ordered.begin(), ordered.end());
    std::ostringstream result;
    result << "{\"metrics\":[";
    bool first = true;
    for (const auto& item : ordered) {
        if (!first) result << ',';
        first = false;
        result << "{\"name\":\"" << json_escape(item.first) << "\",\"value\":" << item.second << '}';
    }
    result << "]}";
    publish_event("metrics", result.str());
}

inline std::string snapshot_json() {
    const auto snapshot = metrics::snapshot_pairs();
    std::vector<Event> retained_logs;
    uint64_t latest_event_id = 0;
    {
        std::lock_guard<std::mutex> lock(events_mutex);
        latest_event_id = next_event_id - 1;
        for (const auto& event : events) if (event.type == "log") retained_logs.push_back(event);
    }
    std::ostringstream result;
    result << "{\"version\":1,\"session\":\"" << json_escape(session_id)
           << "\",\"lastEventId\":" << latest_event_id
           << ",\"capabilities\":[\"metrics\",\"logs\",\"classLifecycle\",\"sse\"],\"metrics\":[";
    bool first = true;
    for (const auto& item : snapshot) {
        if (!first) result << ',';
        first = false;
        result << "{\"name\":\"" << json_escape(item.first) << "\",\"value\":" << item.second << '}';
    }
    result << "],\"logs\":[";
    first = true;
    for (const auto& event : retained_logs) {
        if (!first) result << ',';
        first = false;
        result << "{\"id\":" << event.id << ",\"entry\":" << event.data << '}';
    }
    result << "]}";
    return result.str();
}

inline std::string dashboard_html() {
    const auto snapshot = metrics::snapshot_pairs();
    std::ostringstream result;
    result << "<!doctype html><html lang=\"en\"><head><meta charset=\"utf-8\">"
              "<meta name=\"viewport\" content=\"width=device-width,initial-scale=1\">"
              "<meta http-equiv=\"refresh\" content=\"1\"><title>Doof Observe</title>"
              "<style>body{font:15px system-ui,sans-serif;margin:0;background:#101218;color:#e8eaf0}"
              "main{max-width:960px;margin:auto;padding:32px}h1{font-size:24px}"
              "table{width:100%;border-collapse:collapse;background:#181c24;border-radius:8px;overflow:hidden}"
              "th,td{padding:10px 14px;text-align:left;border-bottom:1px solid #2a3040}"
              "th{color:#9fa8bd}td:last-child{text-align:right;font-variant-numeric:tabular-nums}"
              "p{color:#9fa8bd}</style></head><body><main><h1>Doof Observe</h1>"
              "<p>Process-local metrics · refreshes every second</p><table><thead><tr>"
              "<th>Metric</th><th>Value</th></tr></thead><tbody>";
    if (snapshot.empty()) {
        result << "<tr><td colspan=\"2\">No metrics recorded yet</td></tr>";
    } else {
        for (const auto& item : snapshot) {
            result << "<tr><td>" << html_escape(item.first) << "</td><td>" << item.second << "</td></tr>";
        }
    }
    result << "</tbody></table></main></body></html>";
    return result.str();
}

inline std::string response(
    int status,
    const std::string& reason,
    const std::string& content_type,
    const std::string& body,
    const std::string& extra_headers = "") {
    std::ostringstream result;
    result << "HTTP/1.1 " << status << ' ' << reason << "\r\n"
           << "Content-Type: " << content_type << "\r\n"
           << "Content-Length: " << body.size() << "\r\n"
           << "Cache-Control: no-store\r\n"
           << "X-Content-Type-Options: nosniff\r\n"
           << "Referrer-Policy: no-referrer\r\n"
           << extra_headers
           << "Connection: close\r\n\r\n" << body;
    return result.str();
}

inline bool send_all(socket_handle client, const std::string& value) {
    std::size_t sent = 0;
    while (sent < value.size()) {
        const auto remaining = value.size() - sent;
        const auto chunk = static_cast<int>(std::min<std::size_t>(remaining, 16384));
#if defined(_WIN32) || !defined(MSG_NOSIGNAL)
        const auto count = ::send(client, value.data() + sent, chunk, 0);
#else
        const auto count = ::send(client, value.data() + sent, chunk, MSG_NOSIGNAL);
#endif
        if (count <= 0) return false;
        sent += static_cast<std::size_t>(count);
    }
    return true;
}

inline void configure_client_timeout(socket_handle client) {
#if defined(_WIN32)
    const DWORD timeout = 2000;
    setsockopt(client, SOL_SOCKET, SO_SNDTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
    setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, reinterpret_cast<const char*>(&timeout), sizeof(timeout));
#else
    timeval timeout{};
    timeout.tv_sec = 2;
    setsockopt(client, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
    setsockopt(client, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#if defined(SO_NOSIGPIPE)
    int enabled = 1;
    setsockopt(client, SOL_SOCKET, SO_NOSIGPIPE, &enabled, sizeof(enabled));
#endif
#endif
}

inline std::string content_type_for(const std::string& path) {
    if (path.size() >= 5 && path.substr(path.size() - 5) == ".html") return "text/html; charset=utf-8";
    if (path.size() >= 4 && path.substr(path.size() - 4) == ".css") return "text/css; charset=utf-8";
    if (path.size() >= 3 && path.substr(path.size() - 3) == ".js") return "text/javascript; charset=utf-8";
    if (path.size() >= 5 && path.substr(path.size() - 5) == ".json") return "application/json; charset=utf-8";
    if (path.size() >= 4 && path.substr(path.size() - 4) == ".svg") return "image/svg+xml";
    if (path.size() >= 4 && path.substr(path.size() - 4) == ".png") return "image/png";
    return "application/octet-stream";
}

inline bool safe_asset_path(const std::string& path) {
    return !path.empty() && path.front() != '/' && path.find("..") == std::string::npos &&
        path.find('\\') == std::string::npos && path.find('%') == std::string::npos &&
        path.find('\0') == std::string::npos;
}

inline std::optional<std::string> read_ui_asset(const std::string& relative_path) {
    const char* root = std::getenv("DOOF_OBSERVE_UI_ROOT");
    if (root == nullptr || *root == '\0' || !safe_asset_path(relative_path)) return std::nullopt;
    std::error_code error;
    const auto root_path = std::filesystem::weakly_canonical(root, error);
    if (error) return std::nullopt;
    const auto file_path = std::filesystem::weakly_canonical(root_path / relative_path, error);
    if (error) return std::nullopt;
    const auto relative = file_path.lexically_relative(root_path);
    if (relative.empty() || relative.generic_string().find("..") == 0 || relative.is_absolute() ||
        !std::filesystem::is_regular_file(file_path, error) || error) return std::nullopt;
    std::ifstream input(file_path, std::ios::binary);
    if (!input) return std::nullopt;
    std::ostringstream content;
    std::array<char, 16384> buffer{};
    std::size_t size = 0;
    while (input) {
        input.read(buffer.data(), static_cast<std::streamsize>(buffer.size()));
        const auto count = input.gcount();
        if (count <= 0) break;
        size += static_cast<std::size_t>(count);
        if (size > 1024 * 1024) return std::nullopt;
        content.write(buffer.data(), count);
    }
    return content.str();
}

inline uint64_t parse_last_event_id(const std::string& request) {
    const std::string header = "Last-Event-ID:";
    const auto start = request.find(header);
    if (start == std::string::npos) return 0;
    const auto value_start = request.find_first_not_of(" \t", start + header.size());
    if (value_start == std::string::npos) return 0;
    const auto end = request.find("\r\n", value_start);
    const auto text = request.substr(value_start, end - value_start);
    char* parsed_end = nullptr;
    const auto value = std::strtoull(text.c_str(), &parsed_end, 10);
    return parsed_end != text.c_str() && *parsed_end == '\0' ? value : 0;
}

inline uint64_t parse_after_query(const std::string& query) {
    if (query.find("after=") != 0) return 0;
    const auto text = query.substr(6);
    if (text.empty()) return 0;
    char* parsed_end = nullptr;
    const auto value = std::strtoull(text.c_str(), &parsed_end, 10);
    return parsed_end != text.c_str() && *parsed_end == '\0' ? value : 0;
}

inline std::string render_sse_event(const Event& event) {
    return "id: " + std::to_string(event.id) + "\nevent: " + event.type + "\ndata: " + event.data + "\n\n";
}

inline void serve_events(socket_handle client, uint64_t last_id) {
    const std::string headers =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/event-stream\r\n"
        "Cache-Control: no-store\r\n"
        "X-Content-Type-Options: nosniff\r\n"
        "Connection: keep-alive\r\n\r\n"
        "retry: 1000\n\n";
    if (!send_all(client, headers)) return;
    const std::string hello = "event: hello\ndata: {\"version\":1,\"session\":\"" +
        json_escape(session_id) + "\",\"capabilities\":[\"metrics\",\"logs\",\"classLifecycle\"]}\n\n";
    if (!send_all(client, hello)) return;
    for (;;) {
        std::vector<Event> pending;
        bool gap = false;
        {
            std::unique_lock<std::mutex> lock(events_mutex);
            if (!events.empty() && last_id != 0 && last_id + 1 < events.front().id) gap = true;
            for (const auto& event : events) if (event.id > last_id) pending.push_back(event);
            if (pending.empty() && !gap) {
                if (!running.load()) return;
                if (events_changed.wait_for(lock, std::chrono::seconds(15)) == std::cv_status::timeout) {
                    lock.unlock();
                    if (!send_all(client, ": keepalive\n\n")) return;
                    continue;
                }
                continue;
            }
        }
        if (gap) {
            if (!send_all(client, "event: gap\ndata: {\"reason\":\"retention\"}\n\n")) return;
            last_id = 0;
        }
        for (const auto& event : pending) {
            if (!send_all(client, render_sse_event(event))) return;
            last_id = event.id;
        }
        if (!running.load()) return;
    }
}

inline void serve_client(socket_handle client, const std::string& token) {
    std::array<char, 2048> buffer{};
    std::string request;
    while (request.find("\r\n\r\n") == std::string::npos && request.size() <= 8192) {
        const auto count = ::recv(client, buffer.data(), static_cast<int>(buffer.size()), 0);
        if (count <= 0) return;
        request.append(buffer.data(), static_cast<std::size_t>(count));
    }
    if (request.size() > 8192) {
        send_all(client, response(413, "Content Too Large", "text/plain; charset=utf-8", "request headers too large\n"));
        return;
    }
    const auto line_end = request.find("\r\n");
    const auto first_line = request.substr(0, line_end);
    const auto first_space = first_line.find(' ');
    const auto second_space = first_space == std::string::npos ? std::string::npos : first_line.find(' ', first_space + 1);
    if (first_space == std::string::npos || second_space == std::string::npos) {
        send_all(client, response(400, "Bad Request", "text/plain; charset=utf-8", "bad request\n"));
        return;
    }
    const auto method = first_line.substr(0, first_space);
    const auto target = first_line.substr(first_space + 1, second_space - first_space - 1);
    const auto query_start = target.find('?');
    const auto path = target.substr(0, query_start);
    const auto query = query_start == std::string::npos ? std::string{} : target.substr(query_start + 1);
    if (method != "GET") {
        send_all(client, response(405, "Method Not Allowed", "text/plain; charset=utf-8", "method not allowed\n", "Allow: GET\r\n"));
        return;
    }
    const auto root = "/" + token + "/";
    if (path == root) {
        const auto custom = read_ui_asset("index.html");
        send_all(client, response(
            200, "OK", "text/html; charset=utf-8", custom.has_value() ? *custom : dashboard_html(),
            custom.has_value()
                ? "Content-Security-Policy: default-src 'none'; script-src 'self'; style-src 'self'; connect-src 'self'; img-src 'self'; base-uri 'none'; frame-ancestors 'none'\r\n"
                : "Content-Security-Policy: default-src 'none'; style-src 'unsafe-inline'; base-uri 'none'; frame-ancestors 'none'\r\n"));
    } else if (path == root + "api/v1/snapshot") {
        send_all(client, response(200, "OK", "application/json; charset=utf-8", snapshot_json()));
    } else if (path == root + "api/v1/metrics/prometheus") {
        send_all(client, response(200, "OK", "text/plain; version=0.0.4; charset=utf-8", metrics::snapshot_prometheus()));
    } else if (path == root + "api/v1/events") {
        const auto header_id = parse_last_event_id(request);
        serve_events(client, header_id != 0 ? header_id : parse_after_query(query));
    } else if (path.size() > root.size() && path.substr(0, root.size()) == root) {
        const auto relative = path.substr(root.size());
        const auto asset = read_ui_asset(relative);
        if (asset.has_value()) {
            send_all(client, response(
                200, "OK", content_type_for(relative), *asset,
                "Content-Security-Policy: default-src 'none'; script-src 'self'; style-src 'self'; connect-src 'self'; img-src 'self'; base-uri 'none'; frame-ancestors 'none'\r\n"));
        } else {
            send_all(client, response(404, "Not Found", "text/plain; charset=utf-8", "not found\n"));
        }
    } else {
        send_all(client, response(404, "Not Found", "text/plain; charset=utf-8", "not found\n"));
    }
}

inline int requested_port() {
    const char* value = std::getenv("DOOF_OBSERVE_PORT");
    if (value == nullptr || *value == '\0') return 0;
    char* end = nullptr;
    const long parsed = std::strtol(value, &end, 10);
    return end != value && *end == '\0' && parsed >= 0 && parsed <= 65535 ? static_cast<int>(parsed) : 0;
}

inline std::string random_token() {
    static constexpr char hexadecimal[] = "0123456789abcdef";
    std::random_device random;
    std::string result(32, '0');
    for (auto& character : result) character = hexadecimal[random() & 15U];
    return result;
}

inline void publish_url_file(const std::string& url) {
    const char* path = std::getenv("DOOF_OBSERVE_URL_FILE");
    if (path == nullptr || *path == '\0') return;
#if defined(_WIN32)
    std::ofstream output(path, std::ios::binary | std::ios::trunc);
    if (output) output << url << '\n';
    if (!output) std::cerr << "warning: doof observe could not write its URL discovery file\n";
#else
    const int file = ::open(path, O_WRONLY | O_CREAT | O_TRUNC | O_NOFOLLOW, 0600);
    if (file < 0) {
        std::cerr << "warning: doof observe could not write its URL discovery file\n";
        return;
    }
    const std::string content = url + "\n";
    const auto count = ::write(file, content.data(), content.size());
    ::close(file);
    if (count != static_cast<ssize_t>(content.size())) {
        std::cerr << "warning: doof observe could not finish its URL discovery file\n";
    }
#endif
}

inline void open_browser(const std::string& url) {
    const char* disabled = std::getenv("DOOF_OBSERVE_NO_OPEN");
    if (disabled != nullptr && std::string(disabled) == "1") return;
    std::thread([url] {
#if defined(_WIN32)
        const std::string command = "start \"\" \"" + url + "\"";
#elif defined(__APPLE__)
        const std::string command = "open \"" + url + "\"";
#else
        const std::string command = "xdg-open \"" + url + "\" >/dev/null 2>&1";
#endif
        (void)std::system(command.c_str());
    }).detach();
}

inline void accept_clients(socket_handle server, const std::string& token) {
    while (running.load()) {
        sockaddr_storage client_address{};
        socket_length client_size = sizeof(client_address);
        const auto client = ::accept(server, reinterpret_cast<sockaddr*>(&client_address), &client_size);
        if (client == invalid_socket) {
            if (!running.load()) break;
            continue;
        }
        configure_client_timeout(client);
        if (active_clients.fetch_add(1) >= 16) {
            active_clients.fetch_sub(1);
            send_all(client, response(503, "Service Unavailable", "text/plain; charset=utf-8", "too many clients\n"));
            close_socket(client);
            continue;
        }
        std::thread([client, token] {
            serve_client(client, token);
            close_socket(client);
            active_clients.fetch_sub(1);
            clients_finished.notify_all();
        }).detach();
    }
}

inline void stop_server() {
    publish_event("shutdown", "{\"reason\":\"process-exit\"}");
    running.store(false);
    events_changed.notify_all();
    if (listener != invalid_socket) {
#if defined(_WIN32)
        ::shutdown(listener, SD_BOTH);
#else
        ::shutdown(listener, SHUT_RDWR);
#endif
        close_socket(listener);
        listener = invalid_socket;
    }
    if (listener_v6 != invalid_socket) {
#if defined(_WIN32)
        ::shutdown(listener_v6, SD_BOTH);
#else
        ::shutdown(listener_v6, SHUT_RDWR);
#endif
        close_socket(listener_v6);
        listener_v6 = invalid_socket;
    }
    if (listener_thread.joinable()) listener_thread.join();
    if (listener_v6_thread.joinable()) listener_v6_thread.join();
    if (metric_flush_thread.joinable()) metric_flush_thread.join();
    std::unique_lock<std::mutex> lock(clients_mutex);
    clients_finished.wait(lock, [] { return active_clients.load() == 0; });
}

inline const std::string& start_server() {
    std::call_once(server_once, [] {
        if (!initialize_sockets()) {
            std::cerr << "warning: doof observe could not initialize sockets\n";
            return;
        }
        const auto server = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (server == invalid_socket) {
            std::cerr << "warning: doof observe could not create its loopback socket\n";
            return;
        }
        int enabled = 1;
#if defined(_WIN32)
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&enabled), sizeof(enabled));
#else
        setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &enabled, sizeof(enabled));
#endif
        sockaddr_in address{};
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
        address.sin_port = htons(static_cast<uint16_t>(requested_port()));
        if (::bind(server, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0 || ::listen(server, 16) != 0) {
            close_socket(server);
            std::cerr << "warning: doof observe could not bind its loopback socket\n";
            return;
        }
        socket_length address_size = sizeof(address);
        if (::getsockname(server, reinterpret_cast<sockaddr*>(&address), &address_size) != 0) {
            close_socket(server);
            std::cerr << "warning: doof observe could not determine its loopback port\n";
            return;
        }
        const auto token = random_token();
        session_id = token.substr(0, 12);
        server_url = "http://127.0.0.1:" + std::to_string(ntohs(address.sin_port)) + "/" + token + "/";
        listener = server;
        const auto ipv6 = ::socket(AF_INET6, SOCK_STREAM, IPPROTO_TCP);
        if (ipv6 != invalid_socket) {
            int ipv6_only = 1;
#if defined(_WIN32)
            const auto option = reinterpret_cast<const char*>(&ipv6_only);
#else
            const auto option = &ipv6_only;
#endif
            setsockopt(ipv6, IPPROTO_IPV6, IPV6_V6ONLY, option, sizeof(ipv6_only));
            sockaddr_in6 ipv6_address{};
            ipv6_address.sin6_family = AF_INET6;
            ipv6_address.sin6_addr = in6addr_loopback;
            ipv6_address.sin6_port = address.sin_port;
            if (::bind(ipv6, reinterpret_cast<sockaddr*>(&ipv6_address), sizeof(ipv6_address)) == 0 &&
                ::listen(ipv6, 16) == 0) {
                listener_v6 = ipv6;
            } else {
                close_socket(ipv6);
            }
        }
        running.store(true);
        std::atexit(stop_server);
        std::cout << "DOOF_OBSERVE_URL=" << server_url << std::endl;
        publish_url_file(server_url);
        metric_flush_thread = std::thread([] {
            while (running.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                flush_metric_events();
            }
        });
        listener_thread = std::thread([server, token] { accept_clients(server, token); });
        if (listener_v6 != invalid_socket) {
            listener_v6_thread = std::thread([ipv6 = listener_v6, token] { accept_clients(ipv6, token); });
        }
        open_browser(server_url);
    });
    if (server_url.empty()) throw std::runtime_error("doof observe could not start its local HTTP server");
    return server_url;
}

} // namespace observe

#!/usr/bin/env python3

import errno
import os
import pty
import select
import signal
import sys
import time


def fail(message: str, output: bytes) -> None:
    sys.stderr.write(message + "\n")
    sys.stderr.buffer.write(output)
    if output and not output.endswith(b"\n"):
        sys.stderr.write("\n")
    raise SystemExit(1)


def main() -> None:
    if len(sys.argv) != 4:
        raise SystemExit("usage: interactive-run.test.py <doof> <fixture> <stdlib-root>")

    compiler, fixture, stdlib_root = map(os.path.abspath, sys.argv[1:])
    child_pid, terminal_fd = pty.fork()
    if child_pid == 0:
        os.chdir(fixture)
        environment = os.environ.copy()
        environment["DOOF_STDLIB_ROOT"] = stdlib_root
        os.execve(compiler, [compiler, "run", fixture], environment)

    output = bytearray()
    input_sent = False
    status = None
    deadline = time.monotonic() + 30

    try:
        while time.monotonic() < deadline:
            readable, _, _ = select.select([terminal_fd], [], [], 0.1)
            if readable:
                try:
                    chunk = os.read(terminal_fd, 4096)
                except OSError as error:
                    if error.errno != errno.EIO:
                        raise
                    chunk = b""
                output.extend(chunk)
                if not input_sent and b"Enter value:" in output:
                    os.write(terminal_fd, b"hello\n")
                    input_sent = True

            waited_pid, waited_status = os.waitpid(child_pid, os.WNOHANG)
            if waited_pid == child_pid:
                status = waited_status
                break
    finally:
        os.close(terminal_fd)
        if status is None:
            try:
                os.kill(child_pid, signal.SIGKILL)
            except ProcessLookupError:
                pass
            _, status = os.waitpid(child_pid, 0)

    captured = bytes(output)
    if not input_sent:
        fail("interactive doof run never displayed its prompt", captured)
    if not os.WIFEXITED(status) or os.WEXITSTATUS(status) != 0:
        fail("interactive doof run did not exit successfully", captured)
    if b"received: hello" not in captured:
        fail("interactive doof run did not receive the entered line", captured)

    print("Interactive doof run test passed")


if __name__ == "__main__":
    main()

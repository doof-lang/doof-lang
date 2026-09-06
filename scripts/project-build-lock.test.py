#!/usr/bin/env python3
"""POSIX process regression: python3 scripts/project-build-lock.test.py <compiler>."""
import fcntl
import json
import os
from pathlib import Path
import subprocess
import sys
import tempfile
import time


def eventually(predicate, message, timeout=30):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if predicate():
            return
        time.sleep(0.05)
    raise AssertionError(message() if callable(message) else message)


def main():
    compiler = str(Path(sys.argv[1]).resolve())
    repo = Path(__file__).resolve().parent.parent
    env = dict(os.environ, DOOF_STDLIB_ROOT=str(repo.parent / "doof-stdlib"),
               DOOF_RUNTIME_HEADER=str(repo / "runtime/doof_runtime.h"))
    children = []
    with tempfile.TemporaryDirectory(prefix="doof-build-lock-") as temporary:
        root = Path(temporary)
        project = root / "project"
        project.mkdir()
        (project / "doof.json").write_text(json.dumps({"name": "lock-test", "build": {"entry": "main.do"}}))
        (project / "main.do").write_text("function main(): none {}\n")
        ready, release = project / "ready", project / "release"
        (project / "main.test.do").write_text(
            'import { exists, writeText } from "std/fs"\n'
            'import { Duration, Thread } from "std/time"\n'
            'export function testWait(): none {\n'
            f'  try! writeText({json.dumps(str(ready))}, "ready")\n'
            f'  for attempt of 0..<3000 {{ if exists({json.dumps(str(release))}) {{ return }}\n'
            '    Thread.sleep(Duration.ofMillis(10L)) }\n'
            '  panic("release timed out")\n}\n')
        release.touch()
        (project / "build").mkdir()
        lock_path = project / "build/.doof.lock"

        def start(label, *args):
            log = root / (label + ".log")
            with log.open("w") as output:
                child = subprocess.Popen([compiler, *map(str, args)], env=env, stdout=output, stderr=subprocess.STDOUT)
            children.append(child)
            return child, log

        def waiting(child, log):
            eventually(lambda: "Waiting for project build lock:" in log.read_text(), log.read_text)
            assert child.poll() is None, log.read_text()

        def passed(child, log):
            assert child.wait(timeout=120) == 0, log.read_text()

        try:
            with lock_path.open("w") as holder:
                fcntl.flock(holder, fcntl.LOCK_EX)
                build, build_log = start("build", "build", project, "-o", root / "build-output")
                test, test_log = start("test", "test", project, "-o", root / "test-output")
                waiting(build, build_log)
                waiting(test, test_log)
                assert not (root / "build-output").exists()
                assert not (root / "test-output").exists()
                listed, listed_log = start("list", "test", project, "--list")
                passed(listed, listed_log)
                other = root / "other"
                other.mkdir()
                (other / "main.do").write_text("function main(): none {}\n")
                independent, independent_log = start("independent", "check", other / "main.do")
                passed(independent, independent_log)
                build.terminate()
                build.wait(timeout=10)
                assert test.poll() is None
            passed(test, test_log)
            # The test command itself must retain ownership during worker execution.
            ready.unlink()
            release.unlink()
            test, test_log = start("holding-test", "test", project, "-o", root / "test-output")
            eventually(ready.exists, "test worker did not start", timeout=120)
            build, build_log = start("queued-build", "build", project, "-o", root / "build-output")
            waiting(build, build_log)
            release.touch()
            passed(test, test_log)
            passed(build, build_log)
            # A long-running program must not keep the completed build locked.
            ready.unlink()
            release.unlink()
            (project / "main.do").write_text(
                (project / "main.test.do").read_text().replace(
                    "export function testWait()", "function main()"))
            running, running_log = start("run", "run", project, "-o", root / "build-output")
            eventually(ready.exists, "program did not start", timeout=120)
            check, check_log = start("check-during-run", "check", project)
            passed(check, check_log)
            assert running.poll() is None, running_log.read_text()
            release.touch()
            passed(running, running_log)
            assert lock_path.exists(), "lock file must remain stable"
            with lock_path.open("r+") as handle:
                fcntl.flock(handle, fcntl.LOCK_EX | fcntl.LOCK_NB)
            print("Project build/test queue tests passed")
        finally:
            release.touch()
            for child in children:
                if child.poll() is None:
                    child.terminate()
                    child.wait(timeout=10)


if __name__ == "__main__":
    main()

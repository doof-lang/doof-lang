import { Assert } from "std/assert"
import { join } from "std/string"
import { execute, path, setting, text, write } from "./common"
import { runtimeCompile, runtimeEnvironment, threadSanitizerFlags, threadSanitizerOptions } from "./verify"

import { TemporaryDirectory } from "./test-support"

export function testRuntimeCompilePlacesFlagsBeforeSource(): none {
  Assert.equal(join(runtimeCompile(["-O0"], "a.cpp", "a").cloneReadonly(), " "), "-std=c++17 -pthread -O0 a.cpp -o a")
  Assert.equal(join(runtimeCompile(threadSanitizerFlags(), "a.cpp", "a", "-DDOOF_OBSERVE=1").cloneReadonly(), " "),
    "-std=c++17 -pthread -O1 -g -fsanitize=thread -DDOOF_OBSERVE=1 a.cpp -o a")
}
export function testRuntimeEnvironmentSetsSanitizerOptionsOnlyWhenRequested(): none {
  Assert.isFalse(runtimeEnvironment("").has("TSAN_OPTIONS"))
  Assert.equal(runtimeEnvironment(threadSanitizerOptions).get("TSAN_OPTIONS")!, "halt_on_error=1")
}
// Proves the sanitizer gate fails on a race rather than silently linking an
// uninstrumented binary. Only the repository gate compiles native fixtures.
export function testRepositoryNativeThreadSanitizerRejectsRace(): none {
  if setting("DOOF_REPOSITORY_TEST_ROOT") == "" { return }
  temp := TemporaryDirectory()!
  source := path(temp.root, "race.cpp"); binary := path(temp.root, "race")
  write(source, "#include <thread>\nint shared;\nint main() { std::thread a([] { ++shared; }); std::thread b([] { ++shared; }); a.join(); b.join(); }\n")!
  built := execute("c++", runtimeCompile(threadSanitizerFlags(), source, binary))!
  Assert.equal(built.exitCode, 0)
  raced := execute(binary, [], runtimeEnvironment(threadSanitizerOptions))!
  Assert.isTrue(raced.exitCode != 0)
  Assert.stringContains(text(raced.stdout), "ThreadSanitizer: data race")
  temp.close()
}

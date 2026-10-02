import { setting, stdlibDirectory, path, erase, makeDirectory } from "./common"
import { commandOutputChecks, interactiveCheck, projectLockChecks } from "./process-checks"

// Only the repository gate enables real subprocess regressions; ordinary tool
// unit-test development remains fast. Fixture builds use independent projects.
export function testRepositoryNativeCommandOutputContract(): none {
  root := setting("DOOF_REPOSITORY_TEST_ROOT"); compiler := setting("DOOF_REPOSITORY_TEST_COMPILER")
  if root == "" || compiler == "" { return }
  stdlib := stdlibDirectory(root)!
  commandOutputChecks(compiler, path(root, "tests/release-fixtures"), path(root, "build/command-output-check"), stdlib)!
}
export function testRepositoryNativeInteractiveInput(): none {
  root := setting("DOOF_REPOSITORY_TEST_ROOT"); compiler := setting("DOOF_REPOSITORY_TEST_COMPILER")
  if root == "" || compiler == "" { return }
  stdlib := stdlibDirectory(root)!
  interactiveCheck(compiler, path(root, "tests/release-fixtures/interactive-run"), stdlib)!
}
export function testRepositoryNativeProjectBuildQueue(): none {
  root := setting("DOOF_REPOSITORY_TEST_ROOT"); compiler := setting("DOOF_REPOSITORY_TEST_COMPILER")
  if root == "" || compiler == "" { return }
  stdlib := stdlibDirectory(root)!
  projectLockChecks(root, compiler, stdlib)!
}

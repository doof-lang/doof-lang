import { uuidV4 } from "std/crypto"
import { tempDirectory } from "std/path"
import { path, makeDirectory, erase } from "./common"
export class TemporaryDirectory {
  root: string
  static constructor(): Result<TemporaryDirectory, string> {
    root := path(tempDirectory(), "doof-repository-" + uuidV4())
    try makeDirectory(root)
    return Success(TemporaryDirectory { root })
  }
  function close(): none { _ := erase(root) else {} }
}

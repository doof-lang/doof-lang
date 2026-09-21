import { formatJsonValue } from "std/json"
import { Assert } from "std/assert"

export function testVendorManifestShape(): none {
  value := formatJsonValue({
    "schemaVersion": 1,
    "dependencies": [
      {
        "name": "example",
        "kind": "archive",
        "url": "https://example.invalid/example.tar.gz",
        "destination": "vendor/example",
        "sha256": "abc",
        "stripComponents": 1,
        "copyFiles": [{ "source": "a", "destination": "b" }]
      }
    ]
  })
  Assert.equal(value.contains("vendor/example"), true)
}

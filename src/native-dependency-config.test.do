import { Assert } from "std/assert"
import { parseJsonValue } from "std/json"
import { parseOptionalPkgConfigPackages } from "./native-dependency-config"

function parse(source: string): Result<none, string> {
  object := parseJsonValue(source)! as SerialObject else { panic("expected object") }
  try parseOptionalPkgConfigPackages(object, "/app/doof.json", "/app", "build.native")
  return Success()
}

export function testOptionalNativeConfigParsesPackageLocalProbe(): none {
  object := parseJsonValue(`{
    "optionalPkgConfigPackages": [{"name":"libcrypto","define":"RSA_EVP",
      "probeSource":"./native/openssl-probe.cpp","minimumVersion":"3.0"}]
  }`)! as SerialObject else { panic("expected object") }
  packages := parseOptionalPkgConfigPackages(object, "/app/doof.json", "/app", "build.native")!
  Assert.equal(packages[0].name, "libcrypto")
  Assert.equal(packages[0].define, "RSA_EVP")
  Assert.equal(packages[0].probeSource, "/app/native/openssl-probe.cpp")
  Assert.equal(packages[0].minimumVersion, "3.0")
  Assert.equal(parseOptionalPkgConfigPackages({}, "/app/doof.json", "/app", "build.native")!.length, 0)
}

export function testOptionalNativeConfigRejectsInvalidFieldsWithContext(): none {
  for source of [
    `{"optionalPkgConfigPackages":{}}`,
    `{"optionalPkgConfigPackages":[4]}`,
    `{"optionalPkgConfigPackages":[{}]}`,
    `{"optionalPkgConfigPackages":[{"name":"-bad","define":"OK","probeSource":"probe.cpp"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto >= 3","define":"OK","probeSource":"probe.cpp"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"OK=1","probeSource":"probe.cpp"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"4BAD","probeSource":"probe.cpp"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"OK","probeSource":"../probe.cpp"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"OK","probeSource":"probe.c"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"OK","probeSource":"probe.cpp","minimumVersion":"3..0"}]}`,
    `{"optionalPkgConfigPackages":[{"name":"libcrypto","define":"OK","probeSource":"probe.cpp","minimumVersion":3}]}`,
  ] {
    result := parse(source)
    _ := result else error {
      Assert.stringContains(error, "/app/doof.json")
      Assert.stringContains(error, "build.native.optionalPkgConfigPackages")
      continue
    }
    panic("expected invalid optional dependency rejection")
  }
}

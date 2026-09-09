// Build scripts replace only these constants in an isolated source checkout.
// Direct source builds are deliberately uncacheable: their identity is unknown.
export readonly compilerVersion = "0.1.0-dev.unstamped"
export readonly compilerVersionStamped = false

export function versionCacheIdentity(version: string, stamped: bool): string {
  return if stamped && version != "" then version else ""
}

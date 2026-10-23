// Invalid: private declarations are file-local, so an export list cannot publish them.
// expect-error: 5:10 Cannot export private declaration 'helper'; private declarations are file-local
private function helper(): int => 1

export { helper }

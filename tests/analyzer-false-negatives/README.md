# Analyzer false-negative samples

Each `.do` file in this directory is intentionally invalid according to the
language specification and must be rejected by `doof check` with exactly the
diagnostics it declares. Keep the samples independent so a regression in one
checker rule does not hide the status of the others.

A sample starts with a comment describing the rule, followed by one
`expect-error` comment per expected error, in reported order:

```doof
// Invalid: break is only valid inside a loop.
// expect-error: 4:5 Break is only valid inside a loop
function main(): none {
    break
}
```

`./scripts/test.sh` (or `tools/run.sh corpus-test` on its own) fails when a
sample is accepted, when its reported errors differ from the declared spans
and messages (including extra cascading errors), or when `doof emit` writes
output for it. Focused unit coverage still lives beside the checker.

Line numbers count the comment lines, so add or remove `expect-error` comments
before reading spans from `doof check` output.

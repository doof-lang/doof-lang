# Analyzer false-negative samples

Each `.do` file in this directory is intentionally invalid according to the
language specification and must be rejected by `doof check` with an error
diagnostic. Keep the samples independent so a regression in one checker rule
does not hide the status of the others.

These are command-level regression inputs; focused unit coverage lives beside
the checker. To survey them:

```sh
failed=0
for sample in tests/analyzer-false-negatives/*.do; do
  if build/doof check "$sample"; then
    echo "unexpectedly accepted: $sample"
    failed=1
  fi
done
exit "$failed"
```

An accepted sample is a regression in the rule described by its leading
comment.

function main(): none {
  let pairs = ""
  for let i = 0, j = 10; i < j; i += 1, j -= 1 {
    pairs = pairs + "${i}:${j} "
  }
  assert(pairs == "0:10 1:9 2:8 3:7 4:6 ", "both variables advance")

  let completed = false
  for let i = 0, limit: long = 3; i < limit; i += 1 { } then { completed = true }
  assert(completed, "then runs on normal completion")

  let skipped = 0
  outer: for let i = 0, j = 0; i < 4; i += 1, j += 2 {
    if i == 1 { continue outer }
    if j > 4 { break outer }
    skipped += i
  }
  assert(skipped == 2, "labeled continue and break")

  let total = 0
  for let i = 0, step = 2; i < 6; i += step {
    add := (): none => { total += i * step }
    add()
  }
  assert(total == 12, "lambdas capture both loop variables")

  for let i = 0, j = 1; i < 1; i += 1 { }
  for let i = 7, j = 8; i < 8; i += 1 { assert(i + j == 15, "names reusable after the loop") }
}

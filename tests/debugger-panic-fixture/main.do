function explicitPanic(): none {
  let local = 73
  panic("fixture panic")
}

function boundsPanic(): none {
  values: int[] := [1]
  println(values[9])
}

function caughtPanic(): none {
  result := catchPanic((): none => { panic("caught panic") })
  println("recovered from panic")
}

function main(arguments: string[]): none {
  if arguments[0] == "bounds" { boundsPanic(); return }
  if arguments[0] == "caught" { caughtPanic(); return }
  explicitPanic()
}

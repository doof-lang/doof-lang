import { env } from "std/os"
let debuggerGlobal = 73
function main(arguments: string[]): none {
  let count = 41
  count += 1
  println(count)
  for argument of arguments { println(argument) }
  println(try! env("DOOF_DEBUG_FIXTURE_ENV"))
  println(debuggerGlobal)
}


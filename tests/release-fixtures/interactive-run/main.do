import { prompt } from "std/console"

function main(): int {
  answer := prompt("Enter value:") else error {
    println("prompt failed: " + error.message)
    return 1
  }
  println("received: " + answer)
  return 0
}

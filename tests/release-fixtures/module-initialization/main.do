import { snapshot } from "./b"

function main(): int {
  if snapshot() != "ready!:4:0:0" {
    return 1
  }
  return 0
}

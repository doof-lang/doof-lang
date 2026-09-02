import { HttpRequest } from "std/http"

function main(): int {
  request := HttpRequest { method: "GET", url: "https://example.invalid/" }
  return if request.method == "GET" then 0 else 1
}

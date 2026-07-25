let observed = 0
println("script:" + string(arguments.length))
observed = arguments.length

function observedCount(): int => observed

function main(arguments: string[]): int {
  return if observedCount() == arguments.length then 0 else 7
}

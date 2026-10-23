// Invalid: a native entry script with top-level statements cannot export declarations.
// expect-error: 5:8 Native script entry modules cannot export declarations
println("starting")

export function helper(): int => 1

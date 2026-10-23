// Invalid: the entry point must not be exported.
// expect-error: 3:8 'main' must not be exported; remove 'export' from the entry point
export function main(): none {
    println("hello")
}

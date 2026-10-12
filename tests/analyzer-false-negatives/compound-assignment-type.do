// Invalid: string cannot be added and assigned to an int binding.
// expect-error: 5:5 Operator '+' is not defined for int and string
function main(): none {
    let count = 1
    count += "two"
    println(count)
}

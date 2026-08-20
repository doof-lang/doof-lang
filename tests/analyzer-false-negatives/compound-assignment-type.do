// Invalid: string cannot be added and assigned to an int binding.
function main(): none {
    let count = 1
    count += "two"
    println(count)
}

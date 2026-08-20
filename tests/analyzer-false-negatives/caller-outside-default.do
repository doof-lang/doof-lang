// Invalid: @caller is only valid as a parameter or class-field default value.
function main(): none {
    location := @caller
    println(location.line)
}

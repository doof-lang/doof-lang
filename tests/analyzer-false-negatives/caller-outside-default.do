// Invalid: @caller is only valid as a parameter or class-field default value.
// expect-error: 4:17 @caller is only valid as a parameter or class-field default value
function main(): none {
    location := @caller
    println(location.line)
}

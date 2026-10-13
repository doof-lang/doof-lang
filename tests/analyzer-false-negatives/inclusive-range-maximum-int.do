// Invalid: an inclusive range cannot end at the maximum int.
// expect-error: 4:17 Inclusive range ".." cannot end at the maximum int (2147483647); its exclusive upper bound would overflow
function main(): none {
    for i of 0..2147483647 {
        println(i)
    }
}

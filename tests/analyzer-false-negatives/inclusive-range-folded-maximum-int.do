// Invalid: the inclusive range overflow check applies to constant-folded upper bounds too.
// expect-error: 4:22 Inclusive range ".." cannot end at the maximum int (2147483647); its exclusive upper bound would overflow
function main(): none {
    for index of 0..(2147483646 + 1) {
        println(index)
    }
}

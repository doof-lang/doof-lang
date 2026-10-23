// Invalid: metadata is not available on generic classes.
// expect-error: 8:17 Metadata is not available on generic type "Box"
class Box<T> {
    value: T
}

function main(): none {
    metadata := Box<int>.metadata
}

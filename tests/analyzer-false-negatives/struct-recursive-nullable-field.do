// Invalid: a struct is stored inline, so it cannot contain itself even through a nullable field.
// expect-error: 5:5 Struct "Node" cannot contain itself by value through field "next"; use a class or a collection to add indirection
struct Node {
    value: int
    next: Node | none
}

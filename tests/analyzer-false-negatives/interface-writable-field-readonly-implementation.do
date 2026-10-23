// Invalid: an immutable implementation field cannot satisfy a writable interface field.
// expect-error: 7:24 Class "Fixed" does not satisfy interface "Named"
interface Named {
    let name: string
}

class Fixed implements Named {
    name: string = "fixed"
}

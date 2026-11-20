// Invalid: inclusion has no override rule, so two inclusions may not supply
// the same field name.
// expect-error: 8:5 Field "id" is already included from "A" (line 7); remove one inclusion or rename the field
struct A { id: int }
struct B { id: int }
class C {
    ...A
    ...B
}
function main(): none {}

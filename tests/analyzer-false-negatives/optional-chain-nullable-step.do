// Invalid: a step after '?.' short-circuits only when it reads a present value; a nullable field still needs '?.' or '!.'.
// expect-error: 6:10 Cannot access member "name" on possibly-none value of type "Box | none"; use '?.', '!.', or narrow it first
class Box { name: string = "box" }
class Holder { maybeBox: Box | none = none }
function name(holder: Holder | none): string | none {
  return holder?.maybeBox.name
}

// Invalid: parentheses end an optional chain, so the step after them reads a possibly-none value.
// expect-error: 6:11 Cannot access member "name" on possibly-none value of type "Box | none"; use '?.', '!.', or narrow it first
class Box { name: string = "box" }
class Holder { box: Box = Box {} }
function name(holder: Holder | none): string | none {
  return (holder?.box).name
}

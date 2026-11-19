// Invalid: a step that short-circuits with an earlier '?.' cannot be assigned.
// expect-error: 6:3 An optional chain cannot be used as an assignment target; '.name' short-circuits with an earlier '?.'
class Box { let name: string = "box" }
class Holder { box: Box = Box {} }
function rename(holder: Holder | none): none {
  holder?.box.name = "renamed"
}

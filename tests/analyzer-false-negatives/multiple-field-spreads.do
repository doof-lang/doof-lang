// Invalid: a construction or object literal takes at most one field spread.
// expect-error: 7:32 Named construction supports only one field spread
class Point { x: int; y: int }

readonly a = Point { x: 1, y: 2 }
readonly b = Point { x: 3, y: 4 }
readonly mixed = Point { ...a, ...b }

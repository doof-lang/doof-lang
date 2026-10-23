// Invalid: byte arithmetic promotes to int, so a T: byte | int sum cannot return T.
// expect-error: 3:54 Cannot return int from function returning T
function add<T: byte | int>(left: T, right: T): T => left + right

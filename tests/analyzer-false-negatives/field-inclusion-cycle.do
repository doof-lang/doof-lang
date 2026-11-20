// Invalid: inclusion expands transitively, so it cannot be cyclic.
// expect-error: 4:14 Inclusion cycle: "Token" includes "Pos", which includes "Token"
struct Token { ...Pos }
struct Pos { ...Token; line: int }
function main(): none {}

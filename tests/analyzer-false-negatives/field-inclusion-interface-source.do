// Invalid: only class and struct declarations own fields to include.
// expect-error: 4:32 Cannot include "Spanned": only class and struct fields can be included
interface Spanned { line: int }
class Token { text: string; ...Spanned }
function main(): none {}

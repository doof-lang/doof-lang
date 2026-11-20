// Invalid: a private field is not part of its class's API, so a declaration
// cannot copy it by including the class.
// expect-error: 9:5 Cannot include "Session": it declares private field "secret"
class Session {
    id: int
    private secret: string = ""
}
class Audit {
    ...Session
    at: long
}
function main(): none {}

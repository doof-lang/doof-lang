// Invalid: imports are module-level declarations.
// expect-error: 4:5 Import declarations are only valid at module level
function main(): none {
    import { Helper } from "./helper"
}

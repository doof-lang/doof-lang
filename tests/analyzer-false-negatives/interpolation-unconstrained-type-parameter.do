// Invalid: an unconstrained type parameter has no implicit string representation.
// expect-error: 3:52 Type "T" cannot be used in string interpolation
function describe<T>(value: T): string => `value=${value}`

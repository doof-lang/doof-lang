// Invalid: an unknown local annotation is reported once.
// expect-error: 4:8 Unknown type 'Missing'
function main(): none {
    x: Missing := 1
}

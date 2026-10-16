// Invalid: instances of an immutable class can cross into another domain and be
// released there, so its destructor must be isolated.
// expect-error: 8:9 Destructor of immutable class "Noisy" must be isolated because its instances can cross domains: accesses mutable module binding "counter"
let counter: int[] = []

class Noisy {
    destructor {
        counter.push(1)
    }
}

function main(): none {
    noisy := Noisy {}
}

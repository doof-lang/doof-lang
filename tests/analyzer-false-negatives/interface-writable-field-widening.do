// Invalid: a writable interface field requires an identical implementation field type,
// because writes through the interface would store a double into an int field.
// expect-error: 8:24 Class "Meter" does not satisfy interface "Gauge"
interface Gauge {
    let value: double
}

class Meter implements Gauge {
    let value: int = 0
}

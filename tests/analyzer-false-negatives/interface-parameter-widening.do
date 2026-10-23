// Invalid: interface method parameter types must match exactly; only return types are covariant.
// expect-error: 7:28 Class "IntScaler" does not satisfy interface "Scaler"
interface Scaler {
    scale(factor: double): double
}

class IntScaler implements Scaler {
    scale(factor: int): double => 1.0
}

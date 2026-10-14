// A generic implementor contributes one arm per instantiation.
export class Boxed<T> { kind: "boxed"; value: T; area(): double => 1.0 }

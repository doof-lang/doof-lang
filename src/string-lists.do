// Ordered string lists that behave as insertion-ordered sets.
//
// Emitters accumulate includes, namespaces, captures, and build inputs in
// first-seen order; that order is part of the generated output.

/** Appends `value` unless the list already holds it. */
export function addUnique(values: string[], value: string): none {
  if !values.contains(value) { values.push(value) }
}

/** Appends each of `additions` that the list does not already hold, in order. */
export function addAllUnique(values: string[], additions: string[]): none {
  for value of additions { addUnique(values, value) }
}

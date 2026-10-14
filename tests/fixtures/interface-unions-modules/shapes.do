// The interface lives apart from every implementor and every holder.
export interface Shape { area(): double }

// Only non-generic classes implement Tagged, so it supports JSON.
export interface Tagged { label(): string }

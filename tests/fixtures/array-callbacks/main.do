class Item { name: string; price: double }
struct Point { x: int; y: int }

function label(value: int): string => "#" + string(value)
function weighted(acc: double, it: int): double => acc + it * 0.5
function main(): int {
  items := [1, 2, 3, 4]

  // Result types: explicit, declared on the lambda, contextual, inferred.
  explicit := items.map<double>(=> it + 3)
  declared := items.map((it): double => it + 3)
  contextual: double[] := items.map(=> it + 3)
  inferred := items.map(=> it * 2)
  if explicit[0] / 2 != 2.0 || declared[1] / 2 != 2.5 || contextual[2] / 2 != 3.0 || inferred[3] != 8 { return 1 }

  // `index` binds by name, in any order, or through the parameterless form.
  if items.map((index) => index)[3] != 3 { return 2 }
  if items.map((index, it) => it * index)[3] != 12 { return 3 }
  if items.map(=> it * index)[2] != 6 { return 4 }
  if items.filter(=> index % 2 == 0).length != 2 { return 5 }
  if !items.some(=> it == index + 1) || !items.every((index) => index < 4) { return 6 }

  // Named functions may omit `index`.
  if items.map(label)[0] != "#1" || items.reduce(0.0, weighted) != 5.0 { return 7 }

  // Accumulators.
  if items.reduce(0, => acc + it) != 10 { return 8 }
  if items.reduce<double>(0, (acc, it, index) => acc + it * index * 0.5) != 10.0 { return 9 }
  if items.reduceRight("", => acc + string(it)) != "4321" { return 10 }
  if items.reduceRight("", (acc, index) => acc + string(index)) != "3210" { return 11 }

  // find in each absence carrier.
  if (items.find(=> it > 2) ?? -1) != 3 || (items.find(=> it > 20) ?? -1) != -1 { return 12 }
  shop := [Item { name: "b", price: 2.0 }, Item { name: "a", price: 1.0 }]
  if (shop.find(=> it.price < 1.5)?.name ?? "none") != "a" || shop.find(=> it.price > 5.0) != none { return 13 }
  points := [Point { x: 1, y: 2 }, Point { x: 3, y: 4 }]
  if (points.find(=> it.x == 3)?.y ?? 0) != 4 || points.find(=> it.x == 9) != none { return 14 }
  let mixed: (int | string)[] = [1, "two", 3]
  if mixed.find(=> index == 1) == none || mixed.find(=> index == 7) != none { return 15 }

  // forEach and in-place sort.
  let sum = 0
  items.forEach(=> sum += it * index)
  items.forEach() { sum += 1 }
  if sum != 24 { return 16 }
  let sorted = [3, 1, 2, 1]
  sorted.sort(=> a - b)
  if sorted[0] != 1 || sorted[1] != 1 || sorted[2] != 2 || sorted[3] != 3 { return 17 }
  let byName = [Item { name: "b", price: 1.0 }, Item { name: "a", price: 2.0 }]
  byName.sort((a, b) => if a.name < b.name then -1 else if a.name > b.name then 1 else 0)
  if byName[0].name != "a" { return 18 }

  // Readonly arrays keep mutability through map and filter.
  frozen: readonly int[] := [5, 6]
  doubled: readonly int[] := frozen.map(=> it * 2)
  if doubled[1] != 12 || frozen.reduce(0, => acc + it) != 11 { return 19 }
  return 0
}

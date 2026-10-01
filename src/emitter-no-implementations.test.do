import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

function emitted(source: string): string {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  return result.emission!.modules[0].header + result.emission!.modules[0].source
}

export function testImplementationlessInterfacesLowerToThePlaceholder(): none {
  output := emitted("interface Shape { name: string\narea(): double }\nfunction area(shape: Shape): double => shape.area()\nfunction name(shape: Shape): string => shape.name")
  Assert.stringContains(output, "using Shape = std::variant<doof::NoImplementations>;")
  Assert.stringContains(output, "(static_cast<void>(shape), doof::no_implementations<double>(\"Shape\"))")
  Assert.stringContains(output, "(static_cast<void>(shape), doof::no_implementations<std::string>(\"Shape\"))")
  Assert.equal(output.contains("std::visit"), false)
}

export function testUninstantiatedGenericImplementersCountAsNone(): none {
  output := emitted("interface Labelled { label(): string }\nclass Tagged<T> implements Labelled { value: T\nlabel(): string => \"t\" }\nfunction label(item: Labelled): string => item.label()")
  Assert.stringContains(output, "using Labelled = std::variant<doof::NoImplementations>;")
  Assert.stringContains(output, "doof::no_implementations<std::string>(\"Labelled\")")
}

export function testImplementedInterfacesStillVisitTheirClasses(): none {
  output := emitted("interface Shape { area(): double }\nclass Square implements Shape { side: double\narea(): double => side * side }\nfunction area(shape: Shape): double => shape.area()\nfunction main(): none { println(string(area(Square { side: 2.0 }))) }")
  Assert.stringContains(output, "using Shape = std::variant<std::shared_ptr<Square>>;")
  Assert.stringContains(output, "std::visit(")
  Assert.equal(output.contains("no_implementations"), false)
}

export function testAssignmentsAndDestructuringUseTheFieldType(): none {
  output := emitted("interface Shape { let scale: double\nname: string }\nfunction grow(shape: Shape): none { shape.scale = 2.0 }\nfunction name(shape: Shape): string { { name } := shape\nreturn name }")
  Assert.stringContains(output, "doof::no_implementations<double&>(\"Shape\")")
  Assert.stringContains(output, "doof::no_implementations<std::string>(\"Shape\")")
}

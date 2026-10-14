import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { ClassDeclaration, InterfaceDeclaration, Program } from "./ast"
import { createChecker } from "./checker"
import {
  canGenerateInterfaceJsonSerialization, canGenerateJsonDeserialization, canGenerateJsonSerialization, interfaceJsonDiscriminator, interfaceJsonSerializationBlocker, isGeneratedJsonType,
  objectUnionJsonDecodeBlocker, objectUnionJsonDiscriminator, objectUnionJsonMembers,
} from "./json-semantics"
import { InterfaceType, PrimitiveType, ResolvedType, SourceFile, UnionResolvedType } from "./semantic"

class CheckedInterfaces {
  programs: Program[]
  interfaces: InterfaceDeclaration[]
}

function checkedInterfaces(source: string): CheckedInterfaces {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  Assert.equal(analysis.diagnostics.length, 0)
  checked := createChecker(analysis, "/main.do").check("/main.do")
  for diagnostic of checked.diagnostics { println(diagnostic.message) }
  Assert.equal(checked.diagnostics.length, 0)
  let programs: Program[] = []
  let interfaces: InterfaceDeclaration[] = []
  for module of analysis.modules {
    programs.push(module.program)
    for statement of module.program.statements {
      case statement {
        interface_: InterfaceDeclaration -> { interfaces.push(interface_) }
        _ -> { }
      }
    }
  }
  return CheckedInterfaces { programs, interfaces }
}

function named(checked: CheckedInterfaces, name: string): InterfaceDeclaration {
  for interface_ of checked.interfaces { if interface_.name == name { return interface_ } }
  panic("missing interface " + name)
}

function interfaceType(declaration: InterfaceDeclaration): InterfaceType {
  return InterfaceType { name: declaration.name, symbol: declaration.resolvedSymbol! }
}

export function testInterfaceSerializationNeedsEveryImplementation(): none {
  checked := checkedInterfaces(
    "interface Pet { speak(): string }\n" +
    "class Dog implements Pet { name: string\nspeak(): string => name }\n" +
    "class Robot implements Pet { onSpeak: (): string\nspeak(): string => onSpeak() }\n" +
    "interface Shape { area(): int }\n" +
    "class Square implements Shape { side: int\narea(): int => side * side }\n" +
    "interface Ghost { haunt(): int }",
  )
  Assert.equal(interfaceJsonSerializationBlocker(named(checked, "Pet"), checked.programs), "Robot")
  Assert.isFalse(canGenerateInterfaceJsonSerialization(named(checked, "Pet"), checked.programs))
  // Encoding needs no discriminator; decoding does.
  Assert.isTrue(canGenerateInterfaceJsonSerialization(named(checked, "Shape"), checked.programs))
  Assert.isTrue(interfaceJsonDiscriminator(named(checked, "Shape"), checked.programs) == none)
  Assert.isFalse(isGeneratedJsonType(interfaceType(named(checked, "Shape")), checked.programs))
  // No value of an implementationless interface exists, so both directions are vacuous.
  Assert.isTrue(canGenerateInterfaceJsonSerialization(named(checked, "Ghost"), checked.programs))
  Assert.isTrue(isGeneratedJsonType(interfaceType(named(checked, "Ghost")), checked.programs))
}

export function testRecursiveInterfacesTerminate(): none {
  checked := checkedInterfaces(
    "interface Node { weight(): int }\n" +
    "class Leaf implements Node { kind: \"leaf\"\nvalue: int\nweight(): int => value }\n" +
    "class Branch implements Node { kind: \"branch\"\nchildren: Node[]\nnext: Node | none = none\nweight(): int => children.length }",
  )
  node := named(checked, "Node")
  Assert.isTrue(canGenerateInterfaceJsonSerialization(node, checked.programs))
  Assert.isTrue(isGeneratedJsonType(interfaceType(node), checked.programs))
  discriminator := interfaceJsonDiscriminator(node, checked.programs)!
  Assert.equal(discriminator.fieldName, "kind")
  Assert.equal(discriminator.entries.length, 2)
}

export function testGenericInterfacesAreNotJsonTypes(): none {
  checked := checkedInterfaces(
    "interface Box<T> { get(): T }\n" +
    "class IntBox implements Box<int> { kind: \"int\"\nvalue: int\nget(): int => value }",
  )
  box := named(checked, "Box")
  Assert.isFalse(canGenerateInterfaceJsonSerialization(box, checked.programs))
}

function ownerClass(checked: CheckedInterfaces, name: string): ClassDeclaration {
  for program of checked.programs {
    for statement of program.statements {
      case statement {
        class_: ClassDeclaration -> { if class_.name == name { return class_ } }
        _ -> { }
      }
    }
  }
  panic("missing class " + name)
}

function fieldType(checked: CheckedInterfaces, owner: string, field: string): ResolvedType {
  for candidate of ownerClass(checked, owner).fields {
    if candidate.names.contains(field) { return candidate.resolvedType! }
  }
  panic("missing field " + owner + "." + field)
}

export function testObjectUnionsDecodeThroughOneFlattenedDiscriminator(): none {
  checked := checkedInterfaces(
    "interface Shape { area(): double }\n" +
    "interface Named { name(): string }\n" +
    "class Circle implements Shape { kind: \"circle\"\nradius: double\narea(): double => radius }\n" +
    "class Badge implements Shape, Named { kind: \"badge\"\narea(): double => 1.0\nname(): string => \"b\" }\n" +
    "class Tag implements Named { kind: \"tag\"\ntext: string\nname(): string => text }\n" +
    "class Note { kind: \"note\"\ntext: string }\n" +
    "class Holder { both: Shape | Named | none = none\nmixed: Circle | Note\noverlap: Shape | Circle }",
  )
  both := fieldType(checked, "Holder", "both")
  Assert.equal(objectUnionJsonMembers(both)!.length, 2)
  // Badge reaches the union through both interfaces but is one candidate.
  discriminator := objectUnionJsonDiscriminator(both, checked.programs)!
  Assert.equal(discriminator.fieldName, "kind")
  Assert.equal(discriminator.entries.length, 3)
  Assert.equal(objectUnionJsonDiscriminator(fieldType(checked, "Holder", "overlap"), checked.programs)!.entries.length, 2)
  Assert.isTrue(isGeneratedJsonType(fieldType(checked, "Holder", "mixed"), checked.programs))
  Assert.isTrue(canGenerateJsonDeserialization(ownerClass(checked, "Holder"), checked.programs))
  Assert.equal(objectUnionJsonDecodeBlocker(ownerClass(checked, "Holder"), checked.programs), none)
}

export function testObjectUnionsWithoutADiscriminatorOnlyEncode(): none {
  checked := checkedInterfaces(
    "class Circle { radius: double }\n" +
    "class Note { text: string }\n" +
    "class Loose { pick: Circle | Note }",
  )
  pick := fieldType(checked, "Loose", "pick")
  Assert.equal(objectUnionJsonDiscriminator(pick, checked.programs), none)
  Assert.isTrue(canGenerateJsonSerialization(ownerClass(checked, "Loose"), checked.programs))
  Assert.isFalse(canGenerateJsonDeserialization(ownerClass(checked, "Loose"), checked.programs))
  Assert.stringContains(objectUnionJsonDecodeBlocker(ownerClass(checked, "Loose"), checked.programs)!, "field \"pick\" has union type \"Circle | Note\"")
}

export function testOnlyClassAndInterfaceUnionsAreObjectUnions(): none {
  integer := PrimitiveType { name: "int" }
  Assert.equal(objectUnionJsonMembers(UnionResolvedType { types: [integer, PrimitiveType { name: "string" }] }), none)
  checked := checkedInterfaces("class Circle { kind: \"c\" }\nclass Holder { single: Circle | none = none }")
  // One member with none stays a nullable value, not an object union.
  Assert.equal(objectUnionJsonMembers(fieldType(checked, "Holder", "single")), none)
}

export function testRecursiveObjectUnionsTerminate(): none {
  checked := checkedInterfaces(
    "class Leaf { kind: \"leaf\"\nvalue: int }\n" +
    "class Branch { kind: \"branch\"\nchildren: (Leaf | Branch)[] }",
  )
  Assert.isTrue(canGenerateJsonDeserialization(ownerClass(checked, "Branch"), checked.programs))
  Assert.isTrue(canGenerateJsonSerialization(ownerClass(checked, "Branch"), checked.programs))
}

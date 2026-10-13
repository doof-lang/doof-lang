import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { InterfaceDeclaration, Program } from "./ast"
import { createChecker } from "./checker"
import {
  canGenerateInterfaceJsonSerialization, interfaceJsonDiscriminator, interfaceJsonSerializationBlocker, isGeneratedJsonType,
} from "./json-semantics"
import { InterfaceType, SourceFile } from "./semantic"

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

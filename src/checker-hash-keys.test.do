import { Assert } from "std/assert"
import { createAnalyzer } from "./analyzer"
import { createChecker } from "./checker"
import { SourceFile } from "./semantic"

function keyMessages(source: string): string[] {
  analysis := createAnalyzer([SourceFile { path: "/main.do", source }]).analyze("/main.do")
  for diagnostic of analysis.diagnostics { println(diagnostic.message) }
  Assert.equal(analysis.diagnostics.length, 0)
  let messages: string[] = []
  for diagnostic of createChecker(analysis, "/main.do").check("/main.do").diagnostics {
    if !diagnostic.message.contains("is not supported") { println(diagnostic.message) }
    messages.push(diagnostic.message)
  }
  return messages
}

export function testAcceptsScalarEnumIdentityAndCompositeKeys(): none {
  Assert.equal(keyMessages(
    "enum Suit { Spades, Hearts }\nclass Node {}\ninterface Named { name: string }\nclass Person { name: string }\n" +
    "struct Point { x: int\nlabel: string | none }\nstruct Edge { start: Point\nend: Node }\nstruct Box<T> { value: T }\n" +
    "function use(a: Set<byte>, b: Set<Suit>, c: Set<Node>, d: Set<Named>, e: Set<Point>, f: Set<Edge>, g: Set<Box<Suit>>,\n" +
    "  h: Set<Tuple<int, Point, Node>>, i: Set<int | string>, j: Set<string | none>, k: Set<Node | none>, l: Set<Tuple<Suit, Point | none>>): none {}",
  ).length, 0)
}

export function testRejectsFloatingPointAtAnyDepth(): none {
  messages := keyMessages(
    "struct Inner { ratio: double }\nstruct Outer { inner: Inner }\nstruct Box<T> { value: T }\n" +
    "function use(a: Set<double>, b: Set<Tuple<int, float>>, c: Set<int | float>, d: Set<Outer>, e: Set<Box<float>>, f: Set<double | none>): none {}",
  )
  Assert.equal(messages.length, 6)
  Assert.stringContains(messages[0], "Set element type \"double\" is not supported; Map keys and Set elements may be")
  Assert.stringContains(messages[1], "Set element type \"(int, float)\" is not supported (contains \"float\")")
  Assert.stringContains(messages[2], "Set element type \"int | float\" is not supported (contains \"float\")")
  Assert.stringContains(messages[3], "Set element type \"Outer\" is not supported (field \"ratio\" of \"Inner\" has type \"double\")")
  Assert.stringContains(messages[4], "Set element type \"Box<float>\" is not supported (field \"value\" of \"Box<float>\" has type \"float\")")
  Assert.stringContains(messages[5], "Set element type \"double | none\" is not supported (contains \"double\")")
}

export function testRejectsReferenceKeyedCollectionsCallbacksAndWeakKeys(): none {
  messages := keyMessages(
    "class Node {}\nstruct Holder { items: int[] }\n" +
    "function use(a: Map<int[], int>, b: Map<Map<string, int>, int>, c: Map<(): int, int>, d: Map<Holder, int>, e: Map<weak Node, int>, f: Map<none, int>): none {}",
  )
  Assert.equal(messages.length, 6)
  Assert.stringContains(messages[0], "Map key type \"int[]\" is not supported;")
  Assert.stringContains(messages[1], "Map key type \"Map<string, int>\" is not supported;")
  Assert.stringContains(messages[2], "is not supported;")
  Assert.stringContains(messages[3], "Map key type \"Holder\" is not supported (field \"items\" of \"Holder\" has type \"int[]\")")
  Assert.stringContains(messages[4], "Map key type \"weak Node\" is not supported;")
  Assert.stringContains(messages[5], "Map key type \"none\" is not supported;")
}

export function testDefersTypeParameterKeysAndChecksInferredLiterals(): none {
  Assert.equal(keyMessages("struct Box<T> { value: T }\nfunction index<K>(keys: K[]): Map<Box<K>, int> => {}").length, 0)
  inferred := keyMessages("struct Point { x: int\ny: int }\nvalues: Set := [(1, 2.5)]\npoints: Map := { (Point { x: 1, y: 2 }): \"a\" }")
  Assert.equal(inferred.length, 1)
  Assert.stringContains(inferred[0], "Set element type \"(int, double)\" is not supported (contains \"double\")")
}

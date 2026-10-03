import { Assert } from "std/assert"
import { compile } from "./compiler"
import { SourceFile } from "./semantic"

function emitMain(source: string): string {
  result := compile([SourceFile { path: "/main.do", source }], "/main.do")
  for diagnostic of result.diagnostics { println(diagnostic.message) }
  Assert.equal(result.diagnostics.length, 0)
  return result.emission!.modules[0].source
}

readonly shapes = "function top(scale: int = 2): string => \"top\" + string(scale)\n" +
  "class Sq { static unit(scale: int = 2): string => \"sq\" + string(scale)\ntag: string = \"t\"\nname(scale: int): string => tag + string(scale) }\n" +
  "struct Pt { x: int\nshifted(by: int): int => x + by }\n" +
  "function apply(g: (scale: int): string): string => g(7)\n"

export function testFunctionAndStaticMethodReferencesBecomeCallbacks(): none {
  source := emitMain(shapes + "function main(): none { a := top\nf := Sq.unit\nh := if true then top else Sq.unit\nprintln(a(1) + f(5) + h(2)) }")
  Assert.stringContains(source, "const auto a = doof::callback<std::string(int32_t)>(top);")
  Assert.stringContains(source, "const auto f = doof::callback<std::string(int32_t)>(Sq::unit);")
  Assert.stringContains(source, "doof::callback<std::string(int32_t)>(top) : doof::callback<std::string(int32_t)>(Sq::unit)")
  Assert.stringContains(source, "a.call(1)")
}

export function testBoundMethodReferencesCaptureTheirReceiver(): none {
  source := emitMain(shapes + "function main(): none { s := Sq {}\np := Pt { x: 1 }\nm := s.name\nk := p.shifted\nprintln(m(1) + apply(s.name) + string(k(2))) }")
  Assert.stringContains(source, "const auto m = doof::callback<std::string(int32_t)>([_self = s](auto&&... _args) -> std::string { return _self->name(std::forward<decltype(_args)>(_args)...); });")
  Assert.stringContains(source, "[_self = p](auto&&... _args) mutable -> int32_t { return _self.shifted(")
  Assert.stringContains(source, "apply(doof::callback<std::string(int32_t)>([_self = s]")
}

export function testImplicitMethodReferencesInsideClasses(): none {
  source := emitMain(shapes + "class Holder { tag: string = \"h\"\nlabel(scale: int): string => tag\nstatic make(scale: int): string => \"m\"\n" +
    "bound(): string => apply(label)\nstatic statics(): string => apply(make) }\nfunction main(): none { println(Holder {}.bound() + Holder.statics()) }")
  Assert.stringContains(source, "apply(doof::callback<std::string(int32_t)>([_self = this->shared_from_this()](auto&&... _args) -> std::string { return _self->label(")
  Assert.stringContains(source, "apply(doof::callback<std::string(int32_t)>(make))")
}

export function testDirectCallsKeepTheirCalleeForm(): none {
  source := emitMain(shapes + "function main(): none { s := Sq {}\nprintln(top(1) + Sq.unit(2) + s.name(3)) }")
  Assert.stringContains(source, "top(1)")
  Assert.stringContains(source, "Sq::unit(2)")
  Assert.stringContains(source, "s->name(3)")
  Assert.stringNotContains(source, "(top)")
  Assert.stringNotContains(source, "_self")
}

export function testInterfaceReceiverReferencesDispatchThroughTheVariant(): none {
  source := emitMain("interface Named { label(): string }\nclass A { label(): string => \"a\" }\nclass B { label(): string => \"b\" }\n" +
    "function main(): none { n: Named := A {}\nf := n.label\nprintln(f()) }")
  Assert.stringContains(source, "doof::callback<std::string()>([_self = n](auto&&... _args) -> std::string { return std::visit([&](auto&& _obj) -> std::string { return _obj->label(std::forward<decltype(_args)>(_args)...); }, _self); })")
}

export function testGenericReferencesNameTheirConcreteInstantiation(): none {
  source := emitMain("function identity<T>(value: T): T => value\nfunction apply(g: (value: int): int): int => g(4)\n" +
    "class Box { wrap<T>(value: T): T[] => [value]\nstatic make<T>(value: T): T[] => [value] }\n" +
    "function main(): none { println(apply(identity))\nb := Box {}\nlet w: (value: int): int[] = b.wrap\nlet m: (value: string): string[] = Box.make\nprintln(w(1).length + m(\"x\").length) }")
  Assert.stringContains(source, "apply(doof::callback<int32_t(int32_t)>(identity__int))")
  Assert.stringContains(source, "return _self->wrap__int(std::forward<decltype(_args)>(_args)...); })")
  Assert.stringContains(source, "(Box::make__string)")
}

export function testOptionalAndWeakReceiversBindTheUnwrappedReceiver(): none {
  source := emitMain("class Sq { name(scale: int): string => \"s\" }\n" +
    "function main(): none { s: Sq | none := Sq {}\nstrong := Sq {}\nw: weak Sq := strong\nm := s?.name\nk := w?.name\nf := w!.name\nprintln(m!(1) + k!(2) + f(3)) }")
  Assert.stringContains(source, "[_self = _optional_receiver_")
  Assert.stringContains(source, "[_self = _weak_value_")
  Assert.stringNotContains(source, "->name;")
}

export function testUnionReceiverReferencesDispatchThroughTheVariant(): none {
  source := emitMain("class A { label(): string => \"a\" }\nclass B { label(): string => \"b\" }\n" +
    "function main(): none { u: A | B := B {}\nl := u.label\nprintln(l()) }")
  Assert.stringContains(source, "[_self = u](auto&&... _args) -> std::string { return std::visit(")
}

export function testGenericReferenceInsideArrayMapUsesTheElementInstantiation(): none {
  source := emitMain("function identity<T>(value: T): T => value\nfunction main(): none { items := [1, 2]\nout := items.map(identity)\nprintln(out[0]) }")
  Assert.stringContains(source, "doof::array_map(items, doof::callback<int32_t(int32_t)>(identity__int)")
}

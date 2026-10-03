function main(): none {
  assert("foo bar".replace("foo", "baz") == "baz bar", "replace a match")
  assert("a-b-c".replace("-", "+") == "a+b-c", "replace only the first occurrence")
  assert("a-b-c".replaceAll("-", "+") == "a+b+c", "replaceAll still replaces every occurrence")
  assert("hello".replace("x", "y") == "hello", "no match")
  assert("hello".replace("", "y") == "hello", "empty search")
  assert("".replace("a", "b") == "", "empty receiver")
  assert("aaa".replace("a", "aa") == "aaaa", "replacement containing the search")
  assert("one two".replace("two", "") == "one ", "empty replacement")
  assert("café café".replace("é", "e") == "cafe café", "UTF-8 search")
  assert("ab".replace{oldValue: "a", newValue: "x"} == "xb", "named arguments")
}

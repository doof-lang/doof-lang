class Animal {
  name: string
}

class Question {
  text: string
  let yes: Knowledge
  let no: Knowledge
}

type Knowledge = Animal | Question

function initial(): Knowledge {
  return {
    text: "Does it swim",
    yes: { name: "fish" },
    no: { name: "bird" },
  }
}

function main(): int {
  knowledge := initial()
  return case knowledge {
    _: Animal -> 1,
    _: Question -> 2,
  }
}

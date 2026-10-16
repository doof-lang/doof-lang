// Invalid: a native class is opaque to the checker, so it may cross actor
// boundaries only when declared `import isolated class`. BlobBuilder is a
// mutable buffer that both domains could otherwise write concurrently.
// expect-error: 17:5 Actor method parameter "builder" of type "BlobBuilder" cannot cross actor boundary for "Actor<Writer>": native class "BlobBuilder" is not declared "import isolated class"
// expect-error: 18:27 Async block capture "builder" of type "BlobBuilder" cannot cross to the worker: native class "BlobBuilder" is not declared "import isolated class"
import { BlobBuilder } from "std/blob"

class Writer {
    fill(builder: BlobBuilder): none {
        builder.writeZeroes(1024L)
    }
}

function main(): none {
    builder := BlobBuilder()
    writer := Actor<Writer>()
    writer.fill(builder)
    task := async { yield builder.length() }
    println(task.get()!)
}

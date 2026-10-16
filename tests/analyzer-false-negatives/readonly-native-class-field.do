// Invalid: readonly fields must be deeply immutable, and a native class is
// mutable unless it is declared `import isolated class`.
// expect-error: 7:5 Readonly field "Packet.builder" must be deeply immutable: native class "BlobBuilder" is not declared "import isolated class"
import { BlobBuilder } from "std/blob"

class Packet {
    readonly builder: BlobBuilder
}

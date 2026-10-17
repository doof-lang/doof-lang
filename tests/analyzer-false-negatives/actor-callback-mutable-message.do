// Invalid: a channel's message type is carried by native code without
// appearing in any field, so every type argument of a crossing class must be
// boundary-safe. Otherwise the actor could send a mutable array to the root
// and keep mutating it.
// expect-error: 22:5 Actor method parameter "sender" of type "ChannelSender<int[]>" cannot cross actor boundary for "Actor<Producer>": type argument "T" cannot cross actor boundaries: array type "int[]" is mutable
import { ChannelSender, createChannel } from "std/event"

class Producer {
    start(sender: ChannelSender<int[]>): none {
        values := [1]
        _ := sender.send(values) else {}
        for index of 0..<100 {
            values.push(index)
        }
    }
}

function main(): none {
    (sender, receiver) := createChannel<int[]>()
    receiver.onMessage((values: int[]): none => println(values.length))
    producer := Actor<Producer>()
    producer.start(sender)
}

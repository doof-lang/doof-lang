import { Assert } from "std/assert"
import { lastSseId, observedUrl } from "./observe-checks"

export function testObservedUrlSelectsSessionLine(): none {
  Assert.equal(try! observedUrl("ready\nDOOF_OBSERVE_URL=http://127.0.0.1:1234/token/\n"),
    "http://127.0.0.1:1234/token/")
  Assert.isTrue(observedUrl("DOOF_OBSERVE_URL=\n").isFailure())
}

export function testLastSseIdUsesLatestRetainedEvent(): none {
  Assert.equal(try! lastSseId("event: hello\n\nid: 4\nevent: log\n\nid: 7\nevent: metrics\n"), "7")
  Assert.isTrue(lastSseId("event: hello\n").isFailure())
}

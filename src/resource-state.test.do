import { Assert } from "std/assert"
import {
  MaterializedResource, ResourceState, findMaterializedResource, materializedResourceIsCurrent,
  parseResourceState, renderResourceState,
} from "./resource-state"

function sampleResource(): MaterializedResource {
  return MaterializedResource {
    sourcePath: "/project/assets/logo.png",
    outputPath: "/project/build/assets/logo.png",
    sourceSize: 10L,
    sourceModifiedNanos: 20L,
    outputSize: 10L,
    outputModifiedNanos: 30L,
  }
}

export function testResourceStateRoundTripsAndFindsFiles(): none {
  parsed := parseResourceState(renderResourceState(ResourceState { files: [sampleResource()] }))
  Assert.equal(parsed != none, true)
  found := findMaterializedResource(parsed!, "/project/assets/logo.png", "/project/build/assets/logo.png")
  Assert.equal(found != none, true)
  Assert.equal(found!.sourceSize, 10L)
  Assert.equal(parseResourceState("not json"), none)
  Assert.equal(parseResourceState("{\"version\":99}"), none)
}

export function testResourceMetadataInvalidatesSourceAndOutputChanges(): none {
  resource := sampleResource()
  Assert.equal(materializedResourceIsCurrent(resource, 10L, 20L, 10L, 30L), true)
  Assert.equal(materializedResourceIsCurrent(resource, 11L, 20L, 10L, 30L), false)
  Assert.equal(materializedResourceIsCurrent(resource, 10L, 21L, 10L, 30L), false)
  Assert.equal(materializedResourceIsCurrent(resource, 10L, 20L, 11L, 30L), false)
  Assert.equal(materializedResourceIsCurrent(resource, 10L, 20L, 10L, 31L), false)
  Assert.equal(materializedResourceIsCurrent(none, 10L, 20L, 10L, 30L), false)
}

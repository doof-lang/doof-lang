import { Image, ImageEncodeOptions, ImageFormat, PixelBytes } from "std/image"

function main(): int {
  pixels := readonly [byte(255), byte(0), byte(0), byte(255), byte(0), byte(255), byte(0), byte(255)]
  image := try! Image.fromPixelBytes(PixelBytes(2, 1, pixels))
  encoded := try! image.saveBlob(ImageFormat.WebP, ImageEncodeOptions { lossless: true })
  if encoded.length < 12 { return 1 }
  if encoded[0] != byte(82) || encoded[1] != byte(73) || encoded[2] != byte(70) || encoded[3] != byte(70) {
    return 2
  }
  return 0
}

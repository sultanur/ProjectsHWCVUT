package MainTest

import Image.Images.ImmutableImage
import Image.Pixels.GrayPixels
import org.scalatest.FunSuite

import scala.collection.mutable.ArrayBuffer

class ImmutableImageTest extends FunSuite {
  test ("Wrong imageWidth Test") {
    var pixelRow = new ArrayBuffer[GrayPixels](0)
    var pixel = new GrayPixels(0x00000000)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0A0B0C0D)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0E0F0C0D)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0F0F0A0A)
    pixelRow.addOne(pixel)


    var ImageArray = new ArrayBuffer[Array[GrayPixels]](0)
    ImageArray.addOne(pixelRow.toArray)
    ImageArray.addOne(pixelRow.toArray)
    var error = ""
    try {
      var imageTest = new ImmutableImage(ImageArray.toArray, imageW = 5, imageH = 2)
    } catch {
      case e: Throwable => error = e.getMessage
    }
    assert (error == "Wrong imageWidth in PixelGrid")

  }

  test ("Image Test") {
    var pixelRow = new ArrayBuffer[GrayPixels](0)
    var pixel = new GrayPixels(0x00000000)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0AFAFAFA)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0E0F0C0D)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0F0F0A0A)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0xFFFFAAAA)
    pixelRow.addOne(pixel)

    var ImageArray = new ArrayBuffer[Array[GrayPixels]](0)
    ImageArray.addOne(pixelRow.toArray)
    ImageArray.addOne(pixelRow.toArray)

    var imageTest = new ImmutableImage(ImageArray.toArray, imageW = 5, imageH = 2)

    for (h <- 0 until imageTest.Height) {
      for (w <- 0 until imageTest.Width) {
        assert(imageTest.getPixel(h)(w) == pixelRow(w))
      }
    }
  }
}
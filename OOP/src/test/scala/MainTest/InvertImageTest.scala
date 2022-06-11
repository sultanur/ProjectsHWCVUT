package MainTest

import Filters.FiltersOnPixels.InvertImage
import Image.Images.ImmutableImage
import Image.Pixels.GrayPixels
import org.scalatest.FunSuite
import CommandArguments.filter

import scala.collection.mutable.ArrayBuffer

class InvertImageTest extends FunSuite {
  test("Invert Image Test") {
    var pixelRow = new ArrayBuffer[GrayPixels](0)
    var pixel = new GrayPixels(0x0F00A0B0)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0AAAFAAA)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0E0E0E0D)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0x0F0F0A0A)
    pixelRow.addOne(pixel)
    pixel = new GrayPixels(0xBBBBAAAA)
    pixelRow.addOne(pixel)

    var ImageArray = new ArrayBuffer[Array[GrayPixels]](0)
    ImageArray.addOne(pixelRow.toArray)
    ImageArray.addOne(pixelRow.toArray)

    var imageTest = new ImmutableImage(ImageArray.toArray, imageW = 5, imageH = 2)
    var testingGrid = ImageArray.toArray

    var InvertImage = new InvertImage
    var InvertedImage = filter.apply(imageTest, InvertImage)


    var pixelRow1 = new ArrayBuffer[GrayPixels](0)
    var pixel1 = new GrayPixels(255 - 0x0F00A0B0)
    pixelRow1.addOne(pixel)
    pixel1 = new GrayPixels(255 - 0x0AAAFAAA)
    pixelRow1.addOne(pixel)
    pixel1 = new GrayPixels(255 - 0x0E0E0E0D)
    pixelRow1.addOne(pixel)
    pixel1 = new GrayPixels(255 - 0x0F0F0A0A)
    pixelRow1.addOne(pixel)
    pixel1 = new GrayPixels(255 - 0xBBBBAAAA)
    pixelRow1.addOne(pixel)

    var ImageArray1 = new ArrayBuffer[Array[GrayPixels]](0)
    ImageArray1.addOne(pixelRow.toArray)
    ImageArray1.addOne(pixelRow.toArray)

    var imageTest1 = new ImmutableImage(ImageArray.toArray, imageW = 5, imageH = 2)
    var testingGrid1 = ImageArray.toArray
    //var invertedImageGrid1 = new ArrayBuffer[Array[GrayPixels]]
    var InvertImage1 = new InvertImage
    var InvertedImage1 = filter.apply(imageTest, InvertImage1)

    assert(InvertedImage == InvertedImage1)
  }

}


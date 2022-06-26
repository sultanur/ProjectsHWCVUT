package MainTest

import CommandArguments.Flip
import Filters.FlipImage
import Image.Images.ImmutableImage
import Image.Pixels.GrayPixels
import ImageLoader.Importers.ImageFileLoader
import org.scalatest.FunSuite

import scala.collection.mutable.ArrayBuffer

class FlipImageTest extends FunSuite{
  test ("Flip image test") {
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
    var testingGrid = ImageArray.toArray
    for (w <- 0 until imageTest.Width) {
      for (h <- 0 until imageTest.Height) {
        var tmp = testingGrid(imageTest.Height - h - 1)(w)
        testingGrid(h)(w) = tmp
      }
    }

        var flipImage = new FlipImage
        var testingGrid1 = flipImage.applyFlipX(imageTest)


          for ( h <- 0 until imageTest.Height){
            for ( w <- 0 until imageTest.Width) {
            assert(testingGrid1(h)(w) == testingGrid(h)(w))
          }
        }

      }

  test("Flip Image Test on x direction  ") {
    val loader = new ImageFileLoader("src/test/south_park.png")
    val imageTest = loader.loadImage()
    val argument = new Flip("x")
    var error = ""
    try {
      argument.apply(imageTest)
    }catch {
      case c: Throwable =>error = c.getMessage
    }
    assert(error == "")
  }
  test("Flip Image Test on y direction  ") {
    val loader = new ImageFileLoader("src/test/south_park.png")
    val imageTest = loader.loadImage()
    val argument = new Flip("y")
    var error = ""
    try {
      argument.apply(imageTest)
    }catch {
      case c: Throwable =>error = c.getMessage
    }
    assert(error == "")
  }
  test("Flip Image Test on wrong direction  ") {
    val loader = new ImageFileLoader("src/test/south_park.png")
    val imageTest = loader.loadImage()
    val argument = new Flip("a")
    var error = ""
    try {
      argument.apply(imageTest)
    }catch {
      case c: Throwable =>error = c.getMessage
    }
    assert(error == "Invalid direction")
  }

}

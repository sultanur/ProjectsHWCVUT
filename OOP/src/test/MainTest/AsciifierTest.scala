package MainTest

import Asciifier.Asciifier
import Image.Images.ImmutableImage
import Image.Pixels.GrayPixels
import ImageLoader.Importers.ImageFileLoader
import org.scalatest.FunSuite

import scala.collection.mutable.ArrayBuffer

class AsciifierTest extends FunSuite {
  test("Asciifier Test of Image") {
    val loader = new ImageFileLoader("src/test/south_park.png")
    val asciiaArt = new Asciifier
    var asciifiedImage1 = ""
    val asciiChars: String = " .:-=+*#%@*".reverse
    val imageTest1 = loader.loadImage()
    for (h <- 0 until imageTest1.Height) {
      for (w <- 0 until imageTest1.Width) {
        asciifiedImage1 += asciiaArt.asciiChars((imageTest1.getPixel(h)(w).pixel / (255.0 / (asciiChars.length - 1))).toInt)
      }
      asciifiedImage1 += "\n"
    }

   var  ascifiedImage2 = asciiaArt.AsciiImageCreation(imageTest1)
    assert(asciifiedImage1 == ascifiedImage2)
  }

  test("Asciifier Test of created Image") {
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

    var imageTest2 = new ImmutableImage(ImageArray.toArray, imageW = 5, imageH = 2)
    //var testingGrid = ImageArray.toArray
    val asciifier = new Asciifier
    val asciifiedImage3 =  asciifier.AsciiImageCreation(imageTest2)

    val asciiChars1: String = " .:-=+*#%@*".reverse
    var ascifiedImage4 = ""
    for (h <- 0 until imageTest2.Height) {
      for (w <- 0 until imageTest2.Width) {
       ascifiedImage4 += asciifier.asciiChars((imageTest2.getPixel(h)(w).pixel / (255.0 / (asciiChars1.length - 1))).toInt)
      }
      ascifiedImage4 += "\n"
    }


    assert(asciifiedImage3 == ascifiedImage4)


  }
}
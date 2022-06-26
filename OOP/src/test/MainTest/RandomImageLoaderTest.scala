package MainTest

import ImageLoader.Importers.{ImageFileLoader, RandomImageLoader}
import org.scalatest.FunSuite

class RandomImageLoaderTest extends FunSuite {
  test("Random Image Loader Test") {
    val loader = new RandomImageLoader("src/test/GeneratedRandomTestImage.png")
    val randomImage = loader.loadImage()
  }


    test("Testing case:image == null"){
      val loader = new ImageFileLoader("src/test/nonExisting.jpeg")
      var error = ""
      try {
        val imageTest = loader.loadImage()
      } catch {
        case c: Throwable => error = c.getMessage
      }
      assert (error == "Can't read input file!")
    }

}

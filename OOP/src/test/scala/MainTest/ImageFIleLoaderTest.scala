package MainTest

import ImageLoader.Importers.ImageFileLoader
import org.scalatest.FunSuite

class ImageFIleLoaderTest extends FunSuite{
 test("Image File Loader Test") {
  val loader = new ImageFileLoader("src/test/south_park.png")
  val imageTest = loader.loadImage()


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

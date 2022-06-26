package MainTest

import Image.Pixels.GrayPixels
import org.scalatest.FunSuite

class GrayPixelTest extends FunSuite{
  test("Gray Pixel Test") {
  var grayP = new GrayPixels(0xFFFFFFFF)
  assert (grayP.pixel  == 255)
  }
  test("Gray Pixel_Negative value Test") {
    var grayP = new GrayPixels(-0xFFFFFFFF)
    assert (grayP.pixel  == 0)
  }
}

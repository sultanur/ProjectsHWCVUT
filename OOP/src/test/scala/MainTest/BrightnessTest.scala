package MainTest

import Filters.FiltersOnPixels.BrightnessImage
import Image.Pixels.GrayPixels
import org.scalatest.FunSuite

class BrightnessTest extends FunSuite {
  test("Brightness of Image Test (0)") {
    var grayPixel = new GrayPixels(0)
    val brightness = new BrightnessImage( 0 )
    brightness.filter(grayPixel)
    assert(grayPixel.pixel == 0)
  }

    test("Brightness of Image Test (100)") {
      var grayPixel = new GrayPixels(0)
      val brightness = new BrightnessImage( 100 )
      brightness.filter(grayPixel)
      assert(grayPixel.pixel == 100)
    }
  test("Brightness of Image Test (-100)") {
    var grayPixel = new GrayPixels(0)
    val brightness = new BrightnessImage( -100 )
    brightness.filter(grayPixel)
    assert(grayPixel.pixel == 0)
  }

  test("Brightness of Image Test (-1567890000)") {
    var grayPixel = new GrayPixels(0)
    val brightness = new BrightnessImage( 156789000 )
    brightness.filter(grayPixel)
    assert(grayPixel.pixel == 255)
  }

}

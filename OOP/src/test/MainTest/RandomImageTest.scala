package MainTest

import Image.Images.RandomImage
import org.scalatest.FunSuite

class RandomImageTest extends FunSuite {
  test("Random Image Test") {
    val randomImage = new RandomImage("src/test/RandomTestImage.png")
    val randomTestImage = randomImage.generateImage()

  }
}


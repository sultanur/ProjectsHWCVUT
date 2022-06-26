package Filters

import Image.Images.ImmutableImage
import Image.Pixels.GrayPixels


class FlipImage()  {

  def applyFlipX(image: ImmutableImage): Array[Array[GrayPixels]] = {
    val grid = image.pixelGrid
    for (x <- 0 until image.Width) {
      for (y <- 0 until image.Height/2) {
        var tmp = grid(image.Height-y-1)(x)
        grid(image.Height-y-1)(x) = grid(y)(x)
        grid(y)(x) = tmp
      }
    }
    grid
  }

  def applyFlipY(image: ImmutableImage): Array[Array[GrayPixels]] = {
    val grid = image.pixelGrid
    for (y <- 0 until image.Height) {
      for (x <- 0 until image.Width/2) {
        val tmp = grid(y)(image.Width-x-1)
        grid(y)(image.Width-x-1) = grid(y)(x)
        grid(y)(x) = tmp
      }
    }
    grid
  }

}

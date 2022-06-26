package ImageLoader

import Image.Pixels.GrayPixels
import java.awt.image.BufferedImage
import scala.collection.mutable.ArrayBuffer

object ImageReader {

  def fillPixelGrid(image: BufferedImage): (Array[Array[GrayPixels]], Int, Int) = {
    val ImageArray = ArrayBuffer[Array[GrayPixels]]()
    val height = image.getHeight
    val width = image.getWidth
    for (col <- 0 until height) {
      val pixelRow = ArrayBuffer[GrayPixels]()
      for (row <- 0 until width) {
        pixelRow.addOne(new GrayPixels(image.getRGB(row, col)))
      }
      ImageArray.addOne(pixelRow.toArray)
    }
    (ImageArray.toArray, width, height)
  }


  def resize(src: BufferedImage): BufferedImage = {
    val resizedWidth = 70
    val resizedHeight = 50
    val image: BufferedImage = new BufferedImage(resizedWidth, resizedHeight, BufferedImage.TYPE_INT_RGB)
    for (w <- 0 until resizedWidth) {
      for (h <- 0 until resizedHeight) {
        val color: Int = src.getRGB(w * src.getWidth / resizedWidth, h * src.getHeight / resizedHeight)
        image.setRGB(w, h, color)
      }
    }
    image
  }
}

package Image.Images

import java.awt.image.BufferedImage
import javax.imageio.ImageIO
import java.io.File

class RandomImage (pathName:String) {

  def generateImage(): File = {
    val randomValue = new scala.util.Random(300) //min size
    val width: Int = randomValue.nextInt(500) //max size
    val height: Int = randomValue.nextInt(500) //max size
    val generatedImage: BufferedImage = new BufferedImage(width, height, BufferedImage.TYPE_INT_ARGB)
    val imageFile: File = new File(pathName)
    if (pathName.takeRight(3) != "png")
      throw new IllegalArgumentException ("Random generated image can be saved only in \"png\" format")
    for (h <- 40 until height) {
      for (w <- 20 until width) {
        val a = (Math.random * 256).toInt //alpha
        val r = (Math.random * 256).toInt //red
        val g = (Math.random * 256).toInt //green
        val b = (Math.random * 256).toInt //blue
        val col = (a << 24) | (r << 16) | (g << 8) | b //pixel
        generatedImage.setRGB(w, h, col)
      }
    }
    if (!new File(pathName).exists()) {
      new File(pathName).mkdir()
    }
    ImageIO.write(generatedImage, "png", imageFile)
    imageFile
  }
}


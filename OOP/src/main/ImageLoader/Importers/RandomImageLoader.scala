package ImageLoader.Importers

import Image.Images.{ImmutableImage, RandomImage}
import ImageLoader.ImageReader

import java.io.File
import javax.imageio.ImageIO


class RandomImageLoader (pathName: String) extends ImageLoaderModule {

   def loadImage(): ImmutableImage = {
    val randomImage = new RandomImage(pathName)
    val randImageFile = randomImage.generateImage()
    val image = ImageIO.read(randImageFile)
    if (image == null) {
      throw new IllegalArgumentException("Can't read input file!")
    }
    val resizedImage = ImageReader.resize(image)
    val (pixelGrid, imageHeight, imageWidth) = ImageReader.fillPixelGrid(resizedImage)
    new ImmutableImage(pixelGrid, imageHeight, imageWidth)
  }
}


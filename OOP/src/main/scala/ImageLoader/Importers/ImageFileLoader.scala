package ImageLoader.Importers

import Image.Images.ImmutableImage
import ImageLoader.ImageReader

import java.io.File
import javax.imageio.ImageIO

class ImageFileLoader(filePath: String) extends ImageLoaderModule {
    def loadImage(): ImmutableImage = {
    val image = ImageIO.read(new File(filePath))
    if (image == null) {
      throw new IllegalArgumentException("Can't read input file!")
    }
    val resizedImage = ImageReader.resize(image)
    val (pixelGrid, imageWidth, imageHeight )  = ImageReader.fillPixelGrid(resizedImage)
    new ImmutableImage(pixelGrid, imageWidth, imageHeight )
  }
}

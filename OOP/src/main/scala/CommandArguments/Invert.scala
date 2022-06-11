package CommandArguments

import Filters.FiltersOnPixels.InvertImage
import Image.Images.ImmutableImage

class Invert extends CommandArguments {
  override def apply(image: ImmutableImage): Unit = {
    var invertImage = new InvertImage()
    filter.apply(image, invertImage)
  }
}

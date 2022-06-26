package CommandArguments

import Filters.FiltersOnPixels.{BrightnessImage, FilterOnPixels}
import Image.Images.ImmutableImage

class Brightness (value: Int) extends  CommandArguments {
  override def apply(image: ImmutableImage): Unit = {
    var brighteness = new BrightnessImage(value)
    filter.apply(image, brighteness)
  }
}
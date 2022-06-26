package CommandArguments

import Filters.FiltersOnPixels.FilterOnPixels
import Image.Images.ImmutableImage

object filter {
  def apply(image: ImmutableImage, filterOnPixels: FilterOnPixels): Unit = {
    for (h <- 0 until image.Height) {
      for (w <- 0 until image.Width) {
        filterOnPixels.filter(image.pixelGrid(h)(w))
      }
    }
  }

}

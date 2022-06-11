package ImageLoader.Importers

import Image.Images.ImmutableImage

trait ImageLoaderModule {
  def loadImage(): ImmutableImage
}

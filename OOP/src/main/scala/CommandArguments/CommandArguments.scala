package CommandArguments

import Image.Images.ImmutableImage

trait CommandArguments  {
  def apply (argument: ImmutableImage):Unit
}

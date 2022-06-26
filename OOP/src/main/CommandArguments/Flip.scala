package CommandArguments

import Filters.FlipImage
import Image.Images.ImmutableImage

class Flip (direction: String) extends CommandArguments {
  override def apply(image: ImmutableImage): Unit = {
    if (direction != "x" & direction != "y"){
      throw new IllegalArgumentException ("Invalid direction")
    }
    val flip = new FlipImage
    direction match {
      case "x" => flip.applyFlipX(image)
      case "y" => flip.applyFlipY(image)
      case _ => throw new IllegalArgumentException("Wrong direction")
    }
  }
}


package CommandArguments

import Asciifier.Asciifier
import Image.Images.ImmutableImage
import ImageLoader.Exporters.ExportToConsole

class OutputToConsole extends CommandArguments {
  override def apply(input: ImmutableImage): Unit = {
    val asciifier = new Asciifier
    val AsciiImage = asciifier.AsciiImageCreation(input)
    val toConsole = new ExportToConsole
    toConsole.writeImageTo(AsciiImage)
  }
}

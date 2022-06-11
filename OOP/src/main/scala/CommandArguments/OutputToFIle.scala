package CommandArguments
import Asciifier.Asciifier
import Image.Images.ImmutableImage
import ImageLoader.Exporters.ExportToFile

class OutputToFIle (fileAddress: String) extends CommandArguments {
  override def apply(image: ImmutableImage): Unit = {
    val asciifier = new Asciifier
    val asciiImage = asciifier.AsciiImageCreation(image)
    val write = new ExportToFile(fileAddress)
    write.writeImageTo(asciiImage)
  }
}

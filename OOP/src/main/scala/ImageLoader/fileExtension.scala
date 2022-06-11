package ImageLoader

object fileExtension {
  def isValid(filename: String): Boolean = {
    val suffix = filename.takeRight(3)
    suffix match {
      case "txt" | "jpg" | "png" | "gif" =>
        true
      case _ =>
        throw new IllegalArgumentException("Doesn't support this file format")
    }
  }
}

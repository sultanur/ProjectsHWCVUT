package Asciifier

import Image.Images.ImmutableImage

class Asciifier(var asciiChars: String = " .:-=+*#%@*".reverse){

  def AsciiImageCreation(image: ImmutableImage): String = {
    var asciifiedImage: String = ""
    //var asciiChars: String = " .:-=+*#%@*".reverse
        for (h <- 0 until image.Height) {
          for (w <- 0 until image.Width) {
            asciifiedImage += asciiChars ((image.getPixel(h)(w).pixel / (255.0 / (asciiChars.length -1 ))).toInt)
      }
      asciifiedImage += "\n"
    }
    asciifiedImage
  }
}
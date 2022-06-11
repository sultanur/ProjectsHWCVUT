package Image.Pixels

class GrayPixels extends  Pixel {
  private var _grayPixel: Int = 0

  def toGrayScale (red: Int, green: Int, blue: Int): Int =
    (0.3 * red + 0.59 * green + 0.11 * blue).toInt

  def this(pixel:Int) = {
    this()
    val red = (pixel & 0xFF0000) >> 16
    val green = (pixel & 0xFF00) >> 8
    val blue = pixel & 0xFF
    _grayPixel = toGrayScale(red, green, blue)
  }

  //getters, setters
  def pixel: Int =  _grayPixel
  def pixel_= (newPixel:Int):Unit = {
    this._grayPixel = newPixel
  }

}



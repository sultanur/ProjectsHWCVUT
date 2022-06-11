package Image.Pixels

class RGBPixels extends Pixel {
  private var _RGBPixel:Int = 0

  def this(pixel:Int)= {
    this()
    this._RGBPixel = pixel
  }

  def pixel: Int = _RGBPixel
  def pixel_=(p: Int): Unit = {
    this._RGBPixel = p
  }
}


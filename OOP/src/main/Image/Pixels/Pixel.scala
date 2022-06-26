package Image.Pixels

trait Pixel {
  def pixel: Int

  def pixel_=(newPixel: Int): Unit
}

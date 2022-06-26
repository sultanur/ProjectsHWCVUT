package Image.Images

import Image.Pixels.{GrayPixels, Pixel}

class ImmutableImage {

  private var _Width = 0
  private var _Height = 0
  private var _pixelsGrid: Array[Array[GrayPixels]] = new Array[Array[GrayPixels]](0)

  def this(pixelGrid: Array[Array[GrayPixels]], imageW: Int, imageH: Int ) = {
    this()
    if (imageH <= 0 | imageW <= 0)
      throw new IllegalArgumentException("Dimension of image cannot be less or equal than 0")
    if (pixelGrid.length == 0)
      throw new IllegalArgumentException("The length of image cannot be equal 0 ")

    if (pixelGrid.length != imageH)
      throw new IllegalArgumentException("Wrong imageHeight in PixelGrid ")

    if (pixelGrid(0).length != imageW)
      throw new IllegalArgumentException("Wrong imageWidth in PixelGrid")

    this._Width = imageW
    this._Height = imageH
    this._pixelsGrid = pixelGrid
  }

  def printGrid {
    for (row <- this._pixelsGrid) {
      for (cell <- row) {
        print(cell.pixel)
        print(" ")
      }
      println()
    }
  }

  //Getter and setters
  def Width: Int = this._Width
  def Width_=(imageW: Int): Unit = {
    this._Width = imageW
  }

  def pixelGrid: Array[Array[GrayPixels]] = this._pixelsGrid
  def pixelsGrid_= (newPixelGrid: Array[Array[GrayPixels]]):Unit =
    this._pixelsGrid = newPixelGrid

  def Height: Int = this._Height
  def Height_=(imageH: Int): Unit = {
    this._Height = imageH
  }

   def getPixel(h: Int)(w: Int): Pixel = {
      this._pixelsGrid(h)(w)
    }
  def setPixels(h:Int)(w:Int) (col:GrayPixels):Array[Array[GrayPixels]] = {
    this._pixelsGrid(h)(w) = col
    this._pixelsGrid
  }
}










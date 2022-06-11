package Filters.FiltersOnPixels

import Image.Pixels.GrayPixels


class BrightnessImage(var brightness: Int) extends  FilterOnPixels {
  override def filter(grayPixel: GrayPixels): Unit = {
    var bright = grayPixel.pixel + brightness
    if (bright > 255 ) bright = 255
    if (bright < 0 ) bright = 0
    grayPixel.pixel = bright
  }
}


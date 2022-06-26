package Filters.FiltersOnPixels

import Image.Pixels.GrayPixels

class InvertImage extends FilterOnPixels {
  override def filter(grayPixel: GrayPixels): Unit = {
    grayPixel.pixel =  255 - grayPixel.pixel
  }
}

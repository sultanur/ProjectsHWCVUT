package Filters.FiltersOnPixels

import Image.Pixels.GrayPixels


trait FilterOnPixels {
  def filter(grayPixel: GrayPixels): Unit

}

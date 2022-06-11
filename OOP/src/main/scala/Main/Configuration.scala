package Main

import CommandArguments._
import ImageLoader.Importers.{ImageFileLoader, ImageLoaderModule, RandomImageLoader}
import ImageLoader.fileExtension

import scala.annotation.tailrec
import scala.collection.mutable.ListBuffer

object Configuration {
  var imageFileLoader = new ImageFileLoader("")
  var randomImageLoader = new RandomImageLoader("")

  def parsingImage(args: List[String]): ImageLoaderModule = {
    if (args.isEmpty & (args.contains("--image") & args.contains("--image-random"))) {
      printUsage()
      throw new IllegalArgumentException("Check the Usage hint, not allowed to  provide more than one image")
    }
    args match {
      case "--image" :: filePath :: tail => {
        if (fileExtension.isValid(filePath)) {
          imageFileLoader = new ImageFileLoader(filePath)
        }
        if (containsMoreImages(tail))
          throw new IllegalArgumentException("You can process only one image")
        imageFileLoader
      }
      case "--image-random" :: imagePath :: tail => {
        if (fileExtension.isValid(imagePath)) {
          randomImageLoader = new RandomImageLoader(imagePath)
        }
        if (containsMoreImages(tail))
          throw new IllegalArgumentException("You can process only one image")
        randomImageLoader
      }
    }
  }

  def parsingCommands(args: List[String]): ListBuffer[CommandArguments] = {
    var filters: ListBuffer[CommandArguments] = new ListBuffer[CommandArguments]()
    this.parsingCommands(filters, args)
  }

  @tailrec
  def parsingCommands(filters: ListBuffer[CommandArguments], args: List[String]): ListBuffer[CommandArguments] = {
    args match {
      case Nil => filters
      case "--output-file" :: fileAddress :: tail =>
        parsingCommands(filters.addOne(new OutputToFIle(fileAddress)), tail)
      case "--output-console" :: tail =>
        parsingCommands(filters.addOne(new OutputToConsole), tail)
      case "--rotate" :: number :: tail =>
        parsingCommands(filters.addOne(new Rotate(number.toInt)), tail)
      case "--scale" :: number :: tail =>
        parsingCommands(filters.addOne(new Scale(number.toDouble)), tail)
      case "--invert" :: tail =>
        parsingCommands(filters.addOne(new Invert), tail)
      case "--flip" :: direction :: tail =>
        parsingCommands(filters.addOne(new Flip(direction)), tail)
      case "--brightness" :: value :: tail =>
        parsingCommands(filters.addOne(new Brightness(value.toInt)), tail)
      case "--font-aspect-ratio" :: aspect :: ratio :: tail =>
        filters.addOne(new FontAspect(aspect.toInt, ratio.toInt))
        parsingCommands(tail)
    }
  }
  def printUsage(): Unit = {
    val hint: String =
      """
    Usage: run --image <path>                Absolute or relative file path
               or
               --image-random                Creates random image
               --output-file <path>          Writing the result  to the file
               --output-console <>           Printing the result to the console

               optional arguments:
               [--rotate] <degrees>          Degrees parameter can be: +90, 90 (same as +90), -180, …
               [--invert] <>                 Inverts the greyscale value of the pixes
               [--flip]  <x> or <y>          Flips the image on “y” or “x” axes
               [--brightness] <how-much>     How-much parameter can be: +1, 1 (same as +1), -5, …
               etc.
    Example of input in sbt console:"run --image ../images/test-image.jpg --rotate +90 --scale 0.25 --invert --output-console
  """
    println(hint)
  }

  def containsMoreImages(list: List[String]): Boolean = {
    var found: Boolean = false
    for (element <- list) {
      if (element.takeRight(3).contains("png") | element.takeRight(3).contains("jpg") | element.takeRight(3).contains("gif"))
        found = true
      else found = false
    }
    if (found) true else false
  }
}

package MainTest

import Asciifier.Asciifier
import CommandArguments.{Brightness, CommandArguments, Flip, Invert}
import ImageLoader.Importers.{ImageFileLoader, RandomImageLoader}
import Main.Configuration
import org.scalatest.FunSuite

import scala.collection.mutable.ListBuffer

class ConfigurationTest extends FunSuite {

  test("Configuration Test") {
    val FileLoader = new ImageFileLoader("src/test/south_park.png")
    val asciifier = new Asciifier
    val imageTest1 = FileLoader.loadImage()
    val arguments1 = new ListBuffer[CommandArguments]()
    arguments1.addOne(new Brightness(100))
    arguments1.addOne(new Flip("x"))
    arguments1.addOne(new Invert)
    for (filters1 <- arguments1) {
      filters1.apply(imageTest1)
    }

    val args: List[String] = List(
      "--image", "src/test/south_park.png",
      "--brightness", "100" ,
      "--flip", "x",
      "--invert")

    val argLoader = args.take(2)
    val imageLoader = Configuration.parsingImage(argLoader)
    val imageTest2 = imageLoader.loadImage()

    val commands = args.drop(2)
    val arguments2 = Configuration.parsingCommands(commands)
    for (filter2 <- arguments2)
      filter2.apply(imageTest2)

    assert(asciifier.AsciiImageCreation(imageTest1) == asciifier.AsciiImageCreation(imageTest2))

  }
  test("Configuration Test2") {
    val FileLoader = new ImageFileLoader("src/test/south_park.png")
    val asciifier = new Asciifier
    val imageTest1 = FileLoader.loadImage()
    val arguments1 = new ListBuffer[CommandArguments]()
    arguments1.addOne(new Brightness(30))
    arguments1.addOne(new Flip("y"))
    arguments1.addOne(new Invert)
    for (filters1 <- arguments1) {
      filters1.apply(imageTest1)
    }

    val args: List[String] = List(
      "--image", "src/test/south_park.png",
      "--brightness", "30" ,
      "--flip", "y",
      "--invert")

    val argLoader = args.take(2)
    val imageLoader = Configuration.parsingImage(argLoader)
    val imageTest2 = imageLoader.loadImage()

    val commands = args.drop(2)
    val arguments2 = Configuration.parsingCommands(commands)
    for (filter2 <- arguments2)
      filter2.apply(imageTest2)

    assert(asciifier.AsciiImageCreation(imageTest1) == asciifier.AsciiImageCreation(imageTest2))

  }

  test("Random Image Loader Test") {
    val randomImageloader = new RandomImageLoader("src/test/RandomImage.png")
    val randImageTest1 = randomImageloader.loadImage()
    val asciifier = new Asciifier
    val arguments1 = new ListBuffer[CommandArguments]()
    arguments1.addOne(new Brightness(50))
    arguments1.addOne(new Flip("y"))
    arguments1.addOne(new Invert)
    for (filters1 <- arguments1) {
      filters1.apply(randImageTest1)
    }

    val args: List[String] = List(
      "--image-random", "src/test/RandomImage.png",
      "--flip", "y",
      "--invert",
      "--brightness", "50")

    val argLoader2 = args.take(2)
    val imageLoader2 = Configuration.parsingImage(argLoader2)
    val randImageTest2 = imageLoader2.loadImage()

    val commands = args.drop(2)
    val arguments2 = Configuration.parsingCommands(commands)
    for (filter2 <- arguments2)
      filter2.apply(randImageTest2)

  }

    test("Configuration_Testing file extension") {
      val args: List[String] = List(
        "--image", "testingImage.jpeg",
        "--brightness", "30")

      val argLoader = args.take(2)
      //val imageLoader = Configuration.parsingImage(argLoader)
      var error1 = ""
      try {
        val imageLoader = Configuration.parsingImage(argLoader)
      } catch {
        case c: Throwable => error1 = c.getMessage
      }


     //assert(error == ("Doesn't support this file format"))
      assert(error1 == "Doesn't support this file format")
    }


}


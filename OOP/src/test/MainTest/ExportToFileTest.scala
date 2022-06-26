package MainTest

import ImageLoader.Exporters.ExportToFile
import org.scalatest.FunSuite

import java.nio.file.{Files, Paths}

class ExportToFileTest extends FunSuite{
  test("Export to File Test") {
    val path = "src/test/test.txt"
    val outputFile = new ExportToFile(path)
    val textTest = "This text is generated to test ExportToFIle"
    outputFile.writeImageTo(textTest)
    val lines = {
      new String(Files.readAllBytes(Paths.get(path)))
    }
    assert(lines == textTest)

  }

}

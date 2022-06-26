package ImageLoader.Exporters

import ImageLoader.fileExtension

import java.io.{BufferedWriter, File, FileWriter}

class  ExportToFile (filepath: String) extends ImageExporterModule {

  def writeImageTo (ascifiedImage: String): Unit = {
    if (fileExtension.isValid(filepath)) {
      val writer = new BufferedWriter(new FileWriter(filepath))
      writer.write(ascifiedImage)
      writer.close()
    }
  }
}
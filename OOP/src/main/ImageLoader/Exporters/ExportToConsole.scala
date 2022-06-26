package ImageLoader.Exporters

class ExportToConsole extends ImageExporterModule {
    def writeImageTo (ascifiedImage: String): Unit = {
      Console.println(ascifiedImage)
    }
  }

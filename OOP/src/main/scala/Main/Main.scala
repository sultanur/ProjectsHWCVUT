
package Main

object Main extends App {

  var ImageLoader = args.toList.take(2)
  var Commands = args.toList.drop(2)

  var image = Configuration.parsingImage(ImageLoader).loadImage()

  var arguments = Configuration.parsingCommands(Commands)
    for (argument <- arguments) {
    argument.apply(image)
  }
}







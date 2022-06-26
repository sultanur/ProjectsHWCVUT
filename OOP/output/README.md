# AsciiArt

UI – 8 points

The application provides a user interface via the console.
Feel free to handle application arguments in a way you think is the best and makes the most sense. 
All UI solutions that make some sort of sense for your solution will be accepted.
Some of the recommended and possible ways to handle arguments are:
    Ignore the order of arguments and handle operations in a pre-defined order.
    Load all arguments one-by-one and process them all one-by-one in the inputted order.
    The most recommended: Read some arguments regardless of their order (load), 
but read and then execute all other arguments (filters, outputs) in their inputted order.
It is expected that the UI part of the program will be handled in an OOP manner and well thought out. 
Feel free to use any suitable pattern (MVC, MVP, MVVM) or make your own system.


Load an image – 8 points

The application must always process an image. The minimum requirement for receiving full points from this section is the 
support of at least two different formats and a random image generator.
If one of the arguments is --image-random, the application will generate a random image. 
The process of generating an image is up to you. Use trivial randomness of pixels, a noise function of whatever your 
heart desires. Dimensions of the random image should be also random, but with reasonable limits.
At least one of the following image formats must be supported:
    jpg, png, gif,
When specifying a concrete image, the path can be absolute or relative. The specific image is passed as an argument --image "path". 
If a user uses unsupported extensions, he must be notified.
Only one --image* argument can be specified. If there is not exactly one --image* argument, the user must be notified.
It is expected that even tho libraries such as ImageIO can load various types of images without any setup, 
the student will at least check the image type and use appropriate tools. Loading must be extendable, meaning it should be possible to 
easily add more loading sources, such as exotic file formats, network data, random image generation methods, and other various data sources.


ASCII conversion – 10 points

Any loaded image must be at some point translated into ASCII art. A simple and recommended method works as follows:
    Load individual pixels in RGB (Red Green Blue values in 0-255 range).
    Calculate each pixels greyscale value using the following formula: greyscale value = ((0.3 * Red) + (0.59 * Green) + (0.11 * Blue)) (explained on Tutorials Point).
    Convert greyscale values into ASCII characters using some conversion table. The table is up to the student but the result ASCII image must at least resemble its source image.
Note that the pixel conversion is supposed to be one to one, meaning one pixel translates into one character. 
You may notice that the resulting ASCII images have a different aspect ratio, but that is probably caused by the currently used font to
display the text. If you want to fix this, make a filter that will correct the aspect ratio according to the most popular fonts and their
letter aspect ratio. It is not mandatory tho.
Other smarter conversion methods are welcomed as well.
The ASCII conversion process should be easily modifiable and extendable.


Image filters – 10 points
Rotate --rotate degrees – “degrees” parameter can be for example: +90, 90 (same as +90), -180.....
Scale  filter scales the ASCII image. The filter should support scaling by 0.25, 1, and 4
Invert filter inverts the greyscale value of the pixes and reassigns a new appropriate ASCII symbol. Inversion is done as follows:
        Inverted greyscale = white - greyscale, where white is usually 255. The invert argument is --invert.
Flip filter flips the image on “y” or “x” axes.
Brightness filter. The brightness filter changes the greyscale value of pixes and reassigns new appropriate ASCII symbols.
        The brightness argument is --brightness value – “value” parameter can be for example: +1, 1 (same as +1), -5, …
Font aspect ratio. The aspect ratio filter changes the aspect ratio of the output image according to a font’s aspect ratio.
        Using parameter --font-aspect-ratio x:y, where x:y is the aspect ratio of a font character.


Save an image – 6 points

The resulting image can be saved to a file, printed in the console, or both. 
Printing in the console is done using the --output-console argument and saving in a file 
is done using the --output-file "path" argument. The file path can be relative or absolute.
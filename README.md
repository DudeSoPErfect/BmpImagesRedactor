# bmp_images_redactor

### The essence of the program
The program allows you to apply apply to images.bmp format the following filters:
* **negative** - inverting the color.
* **replace_color from to** - replacing one rgb color with another.
* **improved clarity** - the matrix filter of the same name.
* **Gaussian blur** is a matrix filter of the same name.
* **grey** - makes the image gray.
* **border selection** is a matrix filter of the same name.
* **vignette** - darkening of the edge in a circle with a smooth transition, matrix filter.
* **crop** - crop the file to the specified rectangle.
* **resize** - compresses the image to the specified size.

The program allows you to iterate through directories and select several files at once to apply filters, the implementation of ls and cd commands works. 
The viewing of already selected files, their saving and the choice of names is implemented. For this purpose, appropriate folders are provided, but the user can choose them in any way.
The --help command and error handling are provided.

### File Description
* **main.cpp ** - The main program file.
Calls functions from other files.
* **filters.cpp ** - Auxiliary program file.
Contains an implementation of filters.
* **filters.hpp** - The header file of the program.
Contains headers for the file "filters.cpp "
* **handle_commands.cpp ** - Auxiliary program file.
Contains processing of all commands that the user sends to the program
* **handle_commands.hpp** - The header file of the program.
Contains headers for the file "handle_commands.cpp "
* **help.cpp ** - Auxiliary program file.
Contains an implementation of the --help command.
* **help.hpp** is the header file of the program.
Contains headers for the file "help.hpp
* **structures.hpp** - The header file of the program.
Contains structures for the operation of the program.
* **fillPixelsUsingMidImage.hpp** - The header file of the program.
Contains template information for filling in the matrix of the matrix filter.

### How to launch
1. Upload all project files to one directory.
2. Install the g++ compiler and add it to the PATH environment variable.
3. Go to the files directory.
4. Launch the application "cmd.exe " in the current directory.
5. In "cmd.exe " run the "make" command
6. The in folder contains template images for editing
7. Enjoy

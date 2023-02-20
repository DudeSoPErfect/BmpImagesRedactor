#include <iostream>

void print_help() {       
        std::cout << "usage: bmpRedact [command] [flag] ..."
                  << "\n\n";
        std::cout << "command list:\n";
        std::cout << "ls - print all files in current directory (no flags)\n";
        std::cout << "path - print current path (no flags)\n";
        std::cout << "'YOUR FILE NAME' - use file in current directory to "
                     "redact (flags needed)\n\n";
        std::cout << "flag list:\n";
        std::cout << "--neg - uses negative filter to selected file\n";
        std::cout << "--grey - uses grey filter to selected file\n";
        std::cout << "--clarity - uses clarity filter to selected file\n";
        std::cout << "--borders - uses borders highlighting filter in selected file\n";
        std::cout << "--gauss - uses gaussian blur to selected file\n";
        std::cout << "--vignette - uses vignette to selected file\n\n";
        std::cout << "After following flags additional input is needed:\n";
        std::cout << "--crop - crops selected file from pixel (x, y input is needed), "
                     "with height and width (height, width input is needed)\n";
        std::cout << "--compress - compresses selected file to the heigth and width"
                     "(width and height input is needed)\n";
        std::cout << "--replace-color - replaces one color to another color(colors input is needed)\n";

}
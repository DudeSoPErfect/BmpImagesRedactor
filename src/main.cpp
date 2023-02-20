#include <iostream>
#include "handle_commands.hpp"
#include <SFML/Graphics.hpp>


int main(int argc, char* argv[]) {
    if (argv == nullptr) {
        throw std::invalid_argument("argv is nullptr");
    }


    int return_code = handle_commands();

    if (return_code == 0) {
        std::cout << "New image successfully saved! Check it out!\n";
    } else if (return_code == 1){
        std::cout << "Smth went wrong!\n";
    }

    return 0;
}
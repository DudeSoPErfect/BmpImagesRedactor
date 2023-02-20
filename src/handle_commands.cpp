////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <fstream>
#include <vector>
#include <string.h>

////////////////////////////////////////////////////////////
/// SFML Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>


#include "help.hpp"
#include "filters.hpp"
#include "structs.hpp"

std::string CURRENT_DIRECTORY_PATH = "./";
static const std::string IN_IMAGES_DIRECTORY_PATH = "./images/in/";
static const std::string OUT_IMAGES_DIRECTORY_PATH = "./images/out/";


void ls_cmd() {
    DIR* d_strg;
    struct dirent* dirent_;

    char cur_path[PATH_MAX];

    d_strg = opendir(getcwd(cur_path, sizeof(cur_path)));
    if (d_strg != nullptr) {
        while ((dirent_ = readdir(d_strg)) != nullptr) {
            std::cout << dirent_->d_name << "\n";
        }
        closedir(d_strg);
    }

    return;
}

void cd(const char *arg) {
    if (chdir(arg)) 
        throw std::invalid_argument("No such directory\n");
}

int handle_commands() {
    

    std::cout << "Starting...\n\n";


    std::string cur_cmd = "";
    std::vector<sf::Image> current_files;
    std::vector<std::string> current_names;

    while (cur_cmd != "quit") { //DO NOT FORGET { 
 
        sf::Image cur_image;

        std::cin >> cur_cmd;
        if (cur_cmd == "ls") {
            fprintf(stderr, "-------\n");
            ls_cmd();
            fprintf(stderr, "-------\n");
        } else if (cur_cmd == "path") {
            char cur_path[PATH_MAX]; 
            std::cout << getcwd(cur_path, sizeof(cur_path)) << std::endl;
        } else if (cur_cmd == "--help") {
            print_help();
        } else if (cur_cmd == "cd") {
            std::string folder;
            std::cin >> folder;
            cd(folder.c_str());
            //CURRENT_DIRECTORY_PATH += folder;
            //CURRENT_DIRECTORY_PATH += "/";
        } else if (cur_cmd == "redact") {
            char cur_path[PATH_MAX]; 
            std::string file_name;
            std::cin >> file_name;
            strcat(getcwd(cur_path, sizeof(cur_path)), "/");
            if (cur_image.loadFromFile(strcat(cur_path, file_name.c_str()))) {
                current_files.push_back(cur_image);
                current_names.push_back(file_name);
            }    
        } else if (cur_cmd == "cancel") {
            std::string file_name;
            std::cin >> file_name;
            bool found = false;
            for (size_t file_i = 0; file_i < current_names.size(); ++file_i) {
                if (current_names[file_i] == file_name || file_name == "--all") {
                    found = true;
                    current_names.erase(current_names.begin() + file_i);
                    current_files.erase(current_files.begin() + file_i);
                    std::cout << "File canceled" << std::endl;
                }
            }
            if (!found) {
                std::cout << "No such file" << std::endl;                
            }
        } else if (cur_cmd == "apply") {
            std::string file_name;
            std::cin >> file_name;
            bool found = false;
            std::cout << current_names.size() << std::endl ;
            for (size_t file_i = 0; file_i < current_names.size(); ++file_i) {
                if (current_names[file_i] == file_name || file_name == "--all") {
                    found = true;
                    //char cur_path[PATH_MAX];
                    //char dot[PATH_MAX] = ""; 
                    std::cout << "input name for " << current_names[file_i] << " to save\n" << std::endl;
                    std::string save_name;
                    std::cin >> save_name;
                    //strcat(getcwd(cur_path, sizeof(cur_path)), "/");
                    //strcat(dot, cur_path);
                    cur_image = current_files[file_i];
                    cur_image.saveToFile(CURRENT_DIRECTORY_PATH + save_name);
                    current_names.erase(current_names.begin() + file_i);
                    current_files.erase(current_files.begin() + file_i);
                    std::cout << "File successfully saved!" << std::endl;
                }
            }   
            if (!found) {
                std::cout << "No such file" << std::endl;
            }     
        } else if (cur_cmd == "current") {
            if (current_names.size() == 0) {
                std::cout << "No files" << std::endl;   
            }
            std::cout << "\n";
            for (size_t file_i = 0; file_i < current_names.size(); ++file_i) {
                std::cout << current_names[file_i] << std::endl;
            }
            std::cout << "\n";
        } else {
            if (current_files.size() == 0) {
                std::cout << "You should choose files first!" << std::endl;
            }
            for (size_t file_i = 0; file_i < current_files.size(); ++file_i) {
                if (cur_cmd == "--neg") {
                    std::cout << current_names[file_i] << ":" << std::endl;
                    negative(current_files[file_i]);
                    std::cout << "\n" << "Negative filter used successfully!\n" << std::endl;
                } else if (cur_cmd == "--crop") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    std::string x_str, y_str, w_str, h_str;
                    std::cout << "Input x and y coordinates, that image will have as a beginning, separated by space symbol\n" << std::endl;
                    std::cin >> x_str >> y_str;
                    std::cout << "Input height and width, that image will have, separated by space symbol\n" << std::endl;
                    std::cin >> h_str >> w_str;
                    crop_image(current_files[file_i], std::stoi(x_str), std::stoi(y_str),
                               std::stoi(w_str), std::stoi(h_str));
                    std::cout << "Crop used successfully!\n" << std::endl;
                } else if (cur_cmd == "--compress") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    std::string w_str,   h_str;
                    std::cout << "Input width, that image will have\n" << std::endl;
                    std::cin >> w_str;
                    std::cout << "Input height, that image will have\n" << std::endl;
                    std::cin >> h_str;
                    compress_img(current_files[file_i], std::stoi(w_str), std::stoi(h_str)); 
                    std::cout << "Compress used successfully!\n" << std::endl; 
                } else if (cur_cmd == "--grey") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    grey(current_files[file_i]);
                    std::cout << "Grey filter used successfully!\n" << std::endl;
                } else if (cur_cmd == "--replace_color") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    std::string from, to;
                    std::cout << "Input color, that will be replaced (red/green/blue)\n" << std::endl;
                    std::cin >> from;
                    std::cout << "Input color, that will replace " << from << " (red/green/blue)\n" << std::endl;
                    std::cin >> to;
                    replace(current_files[file_i], from, to);
                    std::cout << "Color replacement used successfully!\n" << std::endl;
                } else if (cur_cmd == "--clarity") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    clarity(current_files[file_i]);
                    std::cout << "Clarity used successfully!\n" << std::endl;
                } else if (cur_cmd == "--borders") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    borders(current_files[file_i]);
                    std::cout << "Border highlighting used successfully!\n" << std::endl;
                } else if (cur_cmd == "--gauss") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    blur_gauss(current_files[file_i]);
                    std::cout << "Gaussian blur used successfully!\n" << std::endl;
                } else if (cur_cmd == "--vignette") {
                    std::cout << "\n" << current_names[file_i] << ":" << std::endl;
                    vignette(current_files[file_i]);
                    std::cout << "Vignette used successfully!\n" << std::endl;
                } else {
                    std::cout << "Error: unknown command\n" << std::endl;
                }
            }
        }
        
    }   
    std::cout << "\n";
    return 0;
}

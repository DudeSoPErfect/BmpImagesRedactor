////////////////////////////////////////////////////////////
/// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

//matrix filling defines
#include "fillPixelsUsingMidImage.hpp"


#define _USE_MATH_DEFINES 
#include <cmath>

////////////////////////////////////////////////////////////
/// SFML Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>



const std::string red = "red";
const std::string blue = "blue";
const std::string green = "green";

typedef int int_matrix[3][3];
typedef double d_matrix[3][3];

//------------------------------------------------------------

void negative(sf::Image& current_image) {


    sf::Vector2u image_size = current_image.getSize();
    for (size_t row = 0; row < image_size.y; ++row) {
        for (size_t column = 0; column < image_size.x; ++column) {
            sf::Color pixel_color = current_image.getPixel(column, row);

            pixel_color.r = 0xFF - pixel_color.r;
            pixel_color.g = 0xFF - pixel_color.g;
            pixel_color.b = 0xFF - pixel_color.b;

            current_image.setPixel(column, row, pixel_color);
        }
    }
    return;
}

//------------------------------------------------------------

void grey(sf::Image& current_image) {

    for (size_t row = 0; row < current_image.getSize().y; ++row) {
        for (size_t column = 0; column < current_image.getSize().x; ++column) {
            sf::Color pixel_color = current_image.getPixel(column, row);

            double average_color_value =
                (pixel_color.r + pixel_color.g + pixel_color.b) / 3.0f;

            pixel_color.r = pixel_color.g = pixel_color.b = average_color_value;
            current_image.setPixel(column, row, pixel_color);
        }
    }
    return;
}

//------------------------------------------------------------

void replace(sf::Image& current_image, std::string color_from, std::string color_to) {

    for (size_t row = 0; row < current_image.getSize().y; ++row) {
        for (size_t column = 0; column < current_image.getSize().x; ++column) {
 
            sf::Color pixel_color = current_image.getPixel(column, row);

            if (color_from == red && color_to == blue) {
                pixel_color.b = std::max((pixel_color.b + pixel_color.r) % 0xFF, 0xFF);
                pixel_color.r = 0;
            } else if (color_from == red && color_to == green) {
                pixel_color.g = std::max((pixel_color.g + pixel_color.r) % 0xFF, 0xFF);
                pixel_color.r = 0;
            } else if (color_from == green && color_to == blue) {
                pixel_color.b = std::max((pixel_color.b + pixel_color.g) % 0xFF, 0xFF);
                pixel_color.g = 0;
            } else if (color_from == green && color_to == red) {
                pixel_color.r = std::max((pixel_color.r + pixel_color.g) % 0xFF, 0xFF);
                pixel_color.g = 0;
            } else if (color_from == blue && color_to == green) {
                pixel_color.g = std::max((pixel_color.b + pixel_color.g) % 0xFF, 0xFF);
                pixel_color.b = 0;
            } else if (color_from == blue && color_to == red) {
                pixel_color.r = std::max((pixel_color.b + pixel_color.r) % 0xFF, 0xFF);
                pixel_color.b = 0;
            } else {
                throw std::invalid_argument("wrong colors\n");
            }

            current_image.setPixel(column, row, pixel_color);
        }
    }

    return;
}

//------------------------------------------------------------

void crop_image(sf::Image& current_image,
                size_t row,
                size_t column,
                size_t width,
                size_t height) {

    if (row > current_image.getSize().x || column > current_image.getSize().y) {
        throw std::invalid_argument("Dot is out of image\n");
    }
    if (row + height > current_image.getSize().x || column + width > current_image.getSize().y) {
        throw std::invalid_argument("Coordinates are out of file\n");
    }
 

    
    sf::Image cropped_image;
    cropped_image.create(width, height, sf::Color::Black);
    for (size_t cur_x = row; cur_x < row + width; ++cur_x) {
        for (size_t cur_y = column; cur_y < column + height; ++cur_y) {
            sf::Color current_color = current_image.getPixel(cur_x, cur_y);
            cropped_image.setPixel(cur_x - row, cur_y - column, current_color);
        }
    }

    current_image = cropped_image;
    return;
}

//------------------------------------------------------------

void compress_img(sf::Image& current_image, size_t width, size_t height) {

    double x_scr_ratio = static_cast<double>(current_image.getSize().x) /
                         static_cast<double>(width);
    double y_scr_ratio = static_cast<double>(current_image.getSize().y) /
                         static_cast<double>(height);

    sf::Image compressed_image;
    compressed_image.create(width, height, sf::Color::Black);

    for (size_t column  = 0; column < width; ++column) {
        for (size_t row = 0; row < height; ++row) {
            sf::Color current_color = current_image.getPixel(
                column * x_scr_ratio, row * y_scr_ratio);
            compressed_image.setPixel(column, row, current_color);
        }
    }

    current_image = compressed_image;
    return;
}

//------------------------------------------------------------

template <typename Type>
Type matr_mul(const int_matrix first_matrix, const Type second_matrix[3][3]) {

    return first_matrix[0][0] * second_matrix[0][0] +
           first_matrix[0][1] * second_matrix[0][1] +
           first_matrix[0][2] * second_matrix[0][2] +
           first_matrix[1][0] * second_matrix[1][0] +
           first_matrix[1][1] * second_matrix[1][1] +
           first_matrix[1][2] * second_matrix[1][2] +
           first_matrix[2][0] * second_matrix[2][0] +
           first_matrix[2][1] * second_matrix[2][1] +
           first_matrix[2][2] * second_matrix[2][2];
}

//----------------------------------------------------------

void fill_mid_image(sf::Image& initial, sf::Image& mid_image) {

    for (size_t row = 0; row < initial.getSize().y + 2; ++row) {
        for (size_t column = 0; column < initial.getSize().x + 2; ++column) {
            if (column == 0 && row == 0) {
                sf::Color color = initial.getPixel(column, row);
                mid_image.setPixel(column, row, color);
            } else if (column == 0 && row == mid_image.getSize().y - 1) {
                sf::Color color = initial.getPixel(column, row - 2);
                mid_image.setPixel(column, row, color);
            } else if (column == mid_image.getSize().x - 1 && row == 0) {
                sf::Color color = initial.getPixel(column - 2, row);
                mid_image.setPixel(column, row, color);
            } else if (column == 0) {
                sf::Color color = initial.getPixel(column, row - 1);
                mid_image.setPixel(column, row, color);
            } else if (row == 0) {
                sf::Color color = initial.getPixel(column - 1, row);
                mid_image.setPixel(column, row, color);
            } else if (column == mid_image.getSize().x - 1 &&
                       row == mid_image.getSize().y - 1) {
                sf::Color color = initial.getPixel(column - 2, row - 2);
                mid_image.setPixel(column, row, color);
            } else if (column == mid_image.getSize().x - 1) {
                sf::Color color = initial.getPixel(column - 2, row - 1);
                mid_image.setPixel(column, row, color);
            } else if (row == mid_image.getSize().y - 1) {
                sf::Color color = initial.getPixel(column - 1, row - 2);
                mid_image.setPixel(column, row, color);
            } else {
                sf::Color color = initial.getPixel(column - 1, row - 1);
                mid_image.setPixel(column, row, color);
            }
        }
    }

    return;
}

void clarity(sf::Image& current_image) {

    sf::Image mid_image;
    mid_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    fill_mid_image(current_image, mid_image);

    const int_matrix clarity_coefs = {{-1, -1, -1},
                                      {-1,  9, -1},
                                      {-1, -1, -1}};


    int_matrix pixels;

    sf::Image fin_image;
    fin_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    for (size_t row = 1; row < mid_image.getSize().y - 1; ++row) {
        for (size_t column = 1; column < mid_image.getSize().x - 1; ++column) {
            sf::Color color = fin_image.getPixel(column,  row);

            fill_pixels_r
            color.r = matr_mul(pixels, clarity_coefs);

            fill_pixels_g
            color.g = matr_mul(pixels, clarity_coefs);

            fill_pixels_b
            color.b = matr_mul(pixels, clarity_coefs);
            
            fin_image.setPixel(column, row, color);
        }
    }

    current_image = fin_image;
    crop_image(current_image, 1, 1, current_image.getSize().x - 2,
               current_image.getSize().y - 2);

    return;
}

//-----------------------

void borders(sf::Image& current_image) {

    sf::Image mid_image;
    mid_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    fill_mid_image(current_image, mid_image);

    const int_matrix G_x = {{-1, -2, -1},
                            { 0,  0,  0},
                            { 1,  2,  1}};

    const int_matrix G_y = {{-1,  0, -2},
                            { 0,  2,  0},
                            {-1,  0,  1}};

    int_matrix pixels;

    sf::Image fin_image;
    fin_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    int div_coef = 4;

    for (size_t row = 1; row < mid_image.getSize().y - 1; row++) {
        for (size_t column = 1; column < mid_image.getSize().x - 1; column++) {
            sf::Color color_1 = fin_image.getPixel(column, row);
            sf::Color color_2 = fin_image.getPixel(column, row);

            fill_pixels_r
            color_1.r = matr_mul<int>(G_x, pixels);
            color_2.r = matr_mul<int>(G_y, pixels);

            fill_pixels_g
            color_1.g = matr_mul<int>(G_x, pixels);
            color_2.g = matr_mul<int>(G_y, pixels);

            fill_pixels_b
            color_1.b = matr_mul<int>(G_x, pixels);
            color_2.b = matr_mul<int>(G_y, pixels);

            color_1.b = sqrt(color_1.b * color_1.b + color_2.b * color_2.b) /
                        static_cast<double>(div_coef);
            color_1.r = sqrt(color_1.r * color_1.r + color_2.r * color_2.r) /
                        static_cast<double>(div_coef);
            color_1.g = sqrt(color_1.g * color_1.g + color_2.g * color_2.g) /
                        static_cast<double>(div_coef);

            fin_image.setPixel(column, row, color_1);
        }
    }

    current_image = fin_image;
    crop_image(current_image, 1, 1, current_image.getSize().x - 2,
               current_image.getSize().y - 2);

    return;
}

//------------------------

double gauss_func(int x, int y, double sigma_coef) {
    return (1.0f / (2 * M_PI * sigma_coef * sigma_coef)) *
           exp(-(x * x + y * y) / (2 * sigma_coef * sigma_coef));
}

void fill_gauss_matr(d_matrix& matr) {
    matr[0][0] = gauss_func(-1,  1, 1.5);
    matr[0][1] = gauss_func( 0,  1, 1.5);
    matr[0][2] = gauss_func( 1,  1, 1.5);
    matr[1][0] = gauss_func(-1,  0, 1.5);
    matr[1][1] = gauss_func( 0,  0, 1.5);
    matr[1][2] = gauss_func( 1,  0, 1.5);
    matr[2][0] = gauss_func(-1, -1, 1.5);
    matr[2][1] = gauss_func( 0, -1, 1.5);
    matr[2][2] = gauss_func( 1, -1, 1.5);
} 

void blur_gauss(sf::Image& current_image) {


    sf::Image mid_image;
    mid_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    fill_mid_image(current_image, mid_image);

    d_matrix matr;
    fill_gauss_matr(matr);

    size_t N = 3;
    double local_sum = 0;
    for (size_t row = 0; row < N; ++row) {
        for (size_t column = 0; column < N; ++column) {
            local_sum += matr[row][column];
        }
    }

    for (size_t row = 0; row < N; ++row) {
        for (size_t column = 0; column < N; ++column) {
            matr[row][column] /= local_sum;
        }
    }

    int_matrix pixels; 

    sf::Image fin_image;
    fin_image.create(current_image.getSize().x + 2,
                     current_image.getSize().y + 2, sf::Color::Black);

    for (size_t row = 1; row < mid_image.getSize().y - 1; ++row) {
        for (size_t column = 1; column < mid_image.getSize().x - 1; ++column) {
            sf::Color color = fin_image.getPixel(column, row);

            fill_pixels_r
            color.r = matr_mul<double>(pixels, matr);
            
            fill_pixels_g
            color.g = matr_mul<double>(pixels, matr);

            fill_pixels_b
            color.b = matr_mul<double>(pixels, matr);
            fin_image.setPixel(column, row, color);
        }
    }

    current_image = fin_image;
    crop_image(current_image, 1, 1, current_image.getSize().x - 2,
               current_image.getSize().y - 2);

    return;
}

//----------------------

void vignette(sf::Image& current_image) {


    size_t rows = current_image.getSize().y;
    size_t columns = current_image.getSize().x;

    double coefs[rows][columns];

    int y_coef = -rows / 2;
    for (size_t row = 0; row < rows; ++row) {
        int x_coef = 0 - columns / 2;

        for (size_t column = 0; column < columns; ++column) {
            coefs[column][row] = gauss_func(x_coef, y_coef, 100);
            ++x_coef;
        }
        ++y_coef;
    }

    double maximum = std::numeric_limits<int>::min();
   

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            maximum = std::max(maximum, coefs[x][y]);
        }
    }

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            coefs[x][y] /= maximum;
        }
    }

    sf::Image fin_image;
    fin_image.create(current_image.getSize().x, current_image.getSize().y,
                     sf::Color::Black);

    for (size_t y = 0; y < rows; y++) {
        for (size_t x = 0; x < columns; x++) {
            sf::Color color = current_image.getPixel(x, y);

            color.r *= coefs[x][y];
            color.g *= coefs[x][y];
            color.b *= coefs[x][y];

            fin_image.setPixel(x, y, color);
        }
    }

    current_image = fin_image;
    return;
}
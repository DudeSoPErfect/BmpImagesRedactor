#pragma once

void negative(sf::Image& current_image);

void grey(sf::Image& current_image);

void replace(sf::Image& current_image, std::string color_from, std::string color_to);

void crop_image(sf::Image& current_image, size_t row, size_t column, size_t width, size_t height);

void compress_img(sf::Image& current_image, size_t width, size_t height);

template <typename Type>
Type matr_mul(int first_matrix[3][3], Type second_matrix[3][3]);

void fill_mid_image(sf::Image& initial, sf::Image& mid_image);

void clarity(sf::Image& current_image);

void borders(sf::Image& current_image);

double gauss_func(int x, int y, double sigma_coef);

void fill_gauss_matr(double matr[3][3]);

void blur_gauss(sf::Image& current_image);

void vignette(sf::Image& current_image);
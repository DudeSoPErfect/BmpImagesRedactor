#pragma once

#define fill_pixels_r   pixels[0][0] = mid_image.getPixel(column - 1, row - 1).r;\
                        pixels[1][0] = mid_image.getPixel(column - 1, row    ).r;\
                        pixels[2][0] = mid_image.getPixel(column - 1, row + 1).r;\
                        pixels[0][1] = mid_image.getPixel(column,     row - 1).r;\
                        pixels[1][1] = mid_image.getPixel(column,     row    ).r;\
                        pixels[2][1] = mid_image.getPixel(column,     row + 1).r;\
                        pixels[0][2] = mid_image.getPixel(column + 1, row - 1).r;\
                        pixels[1][2] = mid_image.getPixel(column + 1, row    ).r;\
                        pixels[2][2] = mid_image.getPixel(column + 1, row + 1).r;

#define fill_pixels_g   pixels[0][0] = mid_image.getPixel(column - 1, row - 1).g;\
                        pixels[1][0] = mid_image.getPixel(column - 1, row    ).g;\
                        pixels[2][0] = mid_image.getPixel(column - 1, row + 1).g;\
                        pixels[0][1] = mid_image.getPixel(column,     row - 1).g;\
                        pixels[1][1] = mid_image.getPixel(column,     row    ).g;\
                        pixels[2][1] = mid_image.getPixel(column,     row + 1).g;\
                        pixels[0][2] = mid_image.getPixel(column + 1, row - 1).g;\
                        pixels[1][2] = mid_image.getPixel(column + 1, row    ).g;\
                        pixels[2][2] = mid_image.getPixel(column + 1, row + 1).g;

#define fill_pixels_b   pixels[0][0] = mid_image.getPixel(column - 1, row - 1).b;\
                        pixels[1][0] = mid_image.getPixel(column - 1, row    ).b;\
                        pixels[2][0] = mid_image.getPixel(column - 1, row + 1).b;\
                        pixels[0][1] = mid_image.getPixel(column,     row - 1).b;\
                        pixels[1][1] = mid_image.getPixel(column,     row    ).b;\
                        pixels[2][1] = mid_image.getPixel(column,     row + 1).b;\
                        pixels[0][2] = mid_image.getPixel(column + 1, row - 1).b;\
                        pixels[1][2] = mid_image.getPixel(column + 1, row    ).b;\
                        pixels[2][2] = mid_image.getPixel(column + 1, row + 1).b;
                        
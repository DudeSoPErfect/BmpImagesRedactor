                
#ifdef NON_SFML_READ
        std::vector<char> bmp_content;

        //PBITMAPFILEHEADER file_header;
        PBITMAPINFOHEADER info_header;

        std::ifstream bmp_file(IN_IMAGES_DIRECTORY_PATH + file_name);
        if (bmp_file) {
            bmp_file.seekg(0, std::ios::end);
            std::streampos length = bmp_file.tellg();
            bmp_file.seekg(0, std::ios::beg);

            bmp_content.resize(length);
            bmp_file.read(&bmp_content[0], length);

            //file_header = (PBITMAPFILEHEADER)(&bmp_content[0]);
            info_header =
                (PBITMAPINFOHEADER)(&bmp_content[0] + sizeof(BITMAPFILEHEADER));
        }

        int32_t width = info_header->biWidth, height = info_header->biHeight;
        size_t size = 4 * width * height;
        sf::Uint8 data[size];

        size_t file_content_shift =
            sizeof(BITMAPINFOHEADER) + sizeof(BITMAPFILEHEADER);

        for (size_t pixel_idx = 0; pixel_idx < size; ++pixel_idx) {
            switch ((pixel_idx + 1) % 4) {
                case 0: {
                    data[pixel_idx] = 0xFF;
                    break;
                }

                case 1: {
                    data[pixel_idx] = bmp_content[file_content_shift++ + 2];
                    break;
                }

                case 2: {
                    data[pixel_idx] = bmp_content[file_content_shift++];
                    break;
                }

                case 3: {
                    data[pixel_idx] = bmp_content[file_content_shift++ - 2];
                    break;
                }

                default: {
                    throw std::runtime_error("yo wtf");
                }
            }
        }

        cur_image.create(width, height, data);
#endif

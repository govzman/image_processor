#include <string>
#include <fstream>
#include <iostream>
#include "FileWorker.h"

namespace {
const int64_t FILE_HEADER_SIZE = 14;
const int64_t INFORMATION_HEADER_SIZE = 40;

const int64_t ONE_BYTE_SHIFT = 8;
const int64_t TWO_BYTES_SHIFT = 16;
const int64_t THREE_BYTES_SHIFT = 24;

const int64_t INFO_HEADER_BIT4 = 4;
const int64_t INFO_HEADER_BIT5 = 5;
const int64_t INFO_HEADER_BIT6 = 6;
const int64_t INFO_HEADER_BIT7 = 7;
const int64_t INFO_HEADER_BIT8 = 8;
const int64_t INFO_HEADER_BIT9 = 9;
const int64_t INFO_HEADER_BIT10 = 10;
const int64_t INFO_HEADER_BIT11 = 11;
const int64_t INFO_HEADER_BIT12 = 12;
const int64_t INFO_HEADER_BIT13 = 13;
const int64_t INFO_HEADER_BIT14 = 14;

const int64_t LAST_INDEX_OF_INFO_HEADER_BIT = 40;
const int64_t BMP_FORMAT_COLORS = 24;

const float MAX_COLOR_VALUE = 255.0f;
}  // namespace

Image FileWorker::Read(const std::string& path) const {
    Image image;

    std::ifstream f;
    f.open(path, std::ios::in | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "File could not be opened" << std::endl;
        return Image();
    }

    unsigned char file_header[FILE_HEADER_SIZE];
    unsigned char information_header[INFORMATION_HEADER_SIZE];

    f.read(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);

    if (file_header[0] != 'B' || file_header[1] != 'M') {
        std::cout << "Not a bitmap image" << std::endl;
        f.close();
        return Image();
    }

    f.read(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    int64_t image_width = information_header[INFO_HEADER_BIT4] +
                          (information_header[INFO_HEADER_BIT5] << ONE_BYTE_SHIFT) +
                          (information_header[INFO_HEADER_BIT6] << TWO_BYTES_SHIFT) +
                          (information_header[INFO_HEADER_BIT7] << THREE_BYTES_SHIFT);

    int64_t image_height = information_header[INFO_HEADER_BIT8] +
                           (information_header[INFO_HEADER_BIT9] << ONE_BYTE_SHIFT) +
                           (information_header[INFO_HEADER_BIT10] << TWO_BYTES_SHIFT) +
                           (information_header[INFO_HEADER_BIT11] << THREE_BYTES_SHIFT);

    std::vector<std::vector<Pixel>> bit_map =
        std::vector<std::vector<Pixel>>(image_height, std::vector<Pixel>(image_width));

    const int64_t padding = ((4 - (image_width * 3) % 4) % 4);

    for (int64_t y = 0; y < image_height; ++y) {
        for (int64_t x = 0; x < image_width; ++x) {
            unsigned char color[3];
            f.read(reinterpret_cast<char*>(color), 3);

            bit_map[y][x].r = static_cast<float>(color[2]) / MAX_COLOR_VALUE;
            bit_map[y][x].g = static_cast<float>(color[1]) / MAX_COLOR_VALUE;
            bit_map[y][x].b = static_cast<float>(color[0]) / MAX_COLOR_VALUE;
        }

        f.ignore(padding);
    }
    f.close();

    image.SetWidth(image_width);
    image.SetHeight(image_height);
    image.SetBitMap(bit_map);

    std::cout << "File read successfully" << std::endl;
    return image;
}

void FileWorker::Write(const std::string& path, const Image& image) const {
    std::ofstream f;
    f.open(path, std::ios::out | std::ios::binary);

    if (!f.is_open()) {
        std::cout << "file couldn't be opened" << std::endl;
        return;
    }
    unsigned char bmp_pad[3] = {0, 0, 0};
    const int64_t padding = ((4 - (image.GetWidth() * 3) % 4) % 4);

    const int64_t file_size = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE + image.GetWidth() * image.GetHeight() * 3 +
                              padding * image.GetHeight();

    unsigned char file_header[FILE_HEADER_SIZE];

    file_header[0] = 'B';
    file_header[1] = 'M';

    file_header[2] = file_size;
    file_header[3] = file_size >> ONE_BYTE_SHIFT;
    file_header[4] = file_size >> TWO_BYTES_SHIFT;
    file_header[INFO_HEADER_BIT5] = file_size >> THREE_BYTES_SHIFT;
    // Reserved 1 (Not used)
    file_header[INFO_HEADER_BIT6] = 0;
    file_header[INFO_HEADER_BIT7] = 0;
    // Reserved 2 (Not used)
    file_header[INFO_HEADER_BIT8] = 0;
    file_header[INFO_HEADER_BIT9] = 0;
    // Pixel data offset
    file_header[INFO_HEADER_BIT10] = FILE_HEADER_SIZE + INFORMATION_HEADER_SIZE;
    file_header[INFO_HEADER_BIT11] = 0;
    file_header[INFO_HEADER_BIT12] = 0;
    file_header[INFO_HEADER_BIT13] = 0;

    unsigned char information_header[INFORMATION_HEADER_SIZE];

    // Headersize
    information_header[0] = INFORMATION_HEADER_SIZE;
    information_header[1] = 0;
    information_header[2] = 0;
    information_header[3] = 0;
    // Image width
    information_header[4] = image.GetWidth();
    information_header[INFO_HEADER_BIT5] = image.GetWidth() >> ONE_BYTE_SHIFT;
    information_header[INFO_HEADER_BIT6] = image.GetWidth() >> TWO_BYTES_SHIFT;
    information_header[INFO_HEADER_BIT7] = image.GetWidth() >> THREE_BYTES_SHIFT;
    // Image height
    information_header[INFO_HEADER_BIT8] = image.GetHeight();
    information_header[INFO_HEADER_BIT9] = image.GetHeight() >> ONE_BYTE_SHIFT;
    information_header[INFO_HEADER_BIT10] = image.GetHeight() >> TWO_BYTES_SHIFT;
    information_header[INFO_HEADER_BIT11] = image.GetHeight() >> THREE_BYTES_SHIFT;

    information_header[INFO_HEADER_BIT12] = 1;

    for (int64_t bit = INFO_HEADER_BIT13; bit < LAST_INDEX_OF_INFO_HEADER_BIT; ++bit) {
        information_header[bit] = 0;
    }
    information_header[INFO_HEADER_BIT14] = BMP_FORMAT_COLORS;

    f.write(reinterpret_cast<char*>(file_header), FILE_HEADER_SIZE);
    f.write(reinterpret_cast<char*>(information_header), INFORMATION_HEADER_SIZE);

    auto bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            unsigned char r = static_cast<unsigned char>(bit_map[y][x].r * MAX_COLOR_VALUE);
            unsigned char g = static_cast<unsigned char>(bit_map[y][x].g * MAX_COLOR_VALUE);
            unsigned char b = static_cast<unsigned char>(bit_map[y][x].b * MAX_COLOR_VALUE);

            unsigned char color[3] = {b, g, r};

            f.write(reinterpret_cast<char*>(color), 3);
        }
        f.write(reinterpret_cast<char*>(bmp_pad), padding);
    }
    f.close();

    std::cout << "File created succesfully";
}

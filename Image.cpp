#include "Image.h"

Image::Image(int64_t width, int64_t height) {
    image_height_ = height;
    image_width_ = width;
}

void Image::SetHeight(int64_t height) {
    image_height_ = height;
}

void Image::SetWidth(int64_t width) {
    image_width_ = width;
}

void Image::SetBitMap(std::vector<std::vector<Pixel>>& bit_map) {
    bit_map_ = std::move(bit_map);
}

int64_t Image::GetWidth() const {
    return image_width_;
}

int64_t Image::GetHeight() const {
    return image_height_;
}

std::vector<std::vector<Pixel>>& Image::GetBitMap() {
    return bit_map_;
}

std::vector<std::vector<Pixel>> Image::GetBitMap() const {
    return bit_map_;
}

bool Image::operator==(Image image) const {
    return this->bit_map_ == image.GetBitMap();
}

#include <algorithm>
#include "FilterCrop.h"

void FilterCrop::Apply(Image& image, int64_t width, int64_t height) {
    auto& bit_map = image.GetBitMap();
    width = std::min(width, image.GetWidth());
    height = std::min(height, image.GetHeight());

    std::reverse(bit_map.begin(), bit_map.end());
    bit_map.resize(height);
    std::reverse(bit_map.begin(), bit_map.end());

    for (auto& row : bit_map) {
        row.resize(width);
    }

    image.SetHeight(height);
    image.SetWidth(width);
}

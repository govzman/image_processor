#include "FilterNegative.h"

void FilterNegative::Apply(Image& image) {
    auto& bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            bit_map[y][x].r = 1 - bit_map[y][x].r;
            bit_map[y][x].g = 1 - bit_map[y][x].g;
            bit_map[y][x].b = 1 - bit_map[y][x].b;
        }
    }
}

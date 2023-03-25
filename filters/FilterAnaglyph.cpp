#include "FilterAnaglyph.h"

void FilterAnaglyph::Apply(Image& image, int64_t shift) {
    auto& bit_map = image.GetBitMap();
    auto base_bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            if (x >= shift) {
                bit_map[y][x].r = base_bit_map[y][x - shift].r;
            }
        }
    }
}

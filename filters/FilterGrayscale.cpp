#include "FilterGrayscale.h"

void FilterGrayscale::Apply(Image& image) {
    auto& bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            float res_color =
                bit_map[y][x].r * RED_COLOR + bit_map[y][x].g * GREEN_COLOR + bit_map[y][x].b * BLUE_COLOR;
            bit_map[y][x] = Pixel(res_color, res_color, res_color);
        }
    }
}

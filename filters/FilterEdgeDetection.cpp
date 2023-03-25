#include "FilterEdgeDetection.h"
#include "MatrixFilter.h"
#include "FilterGrayscale.h"

void FilterEdgeDetection::Apply(Image& image, float threshold) {
    MatrixFilter matrix_filter;
    FilterGrayscale filter_grayscale;

    filter_grayscale.Apply(image);
    matrix_filter.Apply(image, {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}});

    auto& bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            if (bit_map[y][x].r <= threshold) {
                bit_map[y][x] = Pixel(0, 0, 0);
            } else {
                bit_map[y][x] = Pixel(1, 1, 1);
            }
        }
    }
}

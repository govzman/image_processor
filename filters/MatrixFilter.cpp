#include "MatrixFilter.h"

void MatrixFilter::Apply(Image& image, Matrix matrix) {
    auto bit_map = image.GetBitMap();
    auto& new_bit_map = image.GetBitMap();

    for (int64_t y = 0; y < image.GetHeight(); ++y) {
        for (int64_t x = 0; x < image.GetWidth(); ++x) {
            if (x == 0 && y == 0) {
                new_bit_map[y][x].MatrixApplier(bit_map[y][x], bit_map[y][x], bit_map[y][x + 1], bit_map[y][x],
                                                bit_map[y][x], bit_map[y][x + 1], bit_map[y + 1][x], bit_map[y + 1][x],
                                                bit_map[y + 1][x + 1], matrix);
            } else if (x == 0 && y == image.GetHeight() - 1) {
                new_bit_map[y][x].MatrixApplier(bit_map[y - 1][x], bit_map[y - 1][x], bit_map[y - 1][x + 1],
                                                bit_map[y][x], bit_map[y][x], bit_map[y][x + 1], bit_map[y][x],
                                                bit_map[y][x], bit_map[y][x + 1], matrix);
            } else if (x == image.GetWidth() - 1 && y == 0) {
                new_bit_map[y][x].MatrixApplier(bit_map[y][x - 1], bit_map[y][x], bit_map[y][x], bit_map[y][x - 1],
                                                bit_map[y][x], bit_map[y][x], bit_map[y + 1][x - 1], bit_map[y + 1][x],
                                                bit_map[y + 1][x], matrix);
            } else if (x == image.GetWidth() - 1 && y == image.GetHeight() - 1) {
                new_bit_map[y][x].MatrixApplier(bit_map[y - 1][x - 1], bit_map[y - 1][x], bit_map[y - 1][x],
                                                bit_map[y][x - 1], bit_map[y][x], bit_map[y][x], bit_map[y][x - 1],
                                                bit_map[y][x], bit_map[y][x], matrix);
            } else if (x == 0) {
                new_bit_map[y][x].MatrixApplier(bit_map[y - 1][x], bit_map[y - 1][x], bit_map[y - 1][x + 1],
                                                bit_map[y][x], bit_map[y][x], bit_map[y][x + 1], bit_map[y + 1][x],
                                                bit_map[y + 1][x], bit_map[y + 1][x + 1], matrix);
            } else if (x == image.GetWidth() - 1) {
                new_bit_map[y][x].MatrixApplier(bit_map[y - 1][x - 1], bit_map[y - 1][x], bit_map[y - 1][x],
                                                bit_map[y][x - 1], bit_map[y][x], bit_map[y][x], bit_map[y + 1][x - 1],
                                                bit_map[y + 1][x], bit_map[y + 1][x], matrix);
            } else if (y == 0) {
                new_bit_map[y][x].MatrixApplier(bit_map[y][x - 1], bit_map[y][x], bit_map[y][x + 1], bit_map[y][x - 1],
                                                bit_map[y][x], bit_map[y][x + 1], bit_map[y + 1][x - 1],
                                                bit_map[y + 1][x], bit_map[y + 1][x + 1], matrix);
            } else if (y == image.GetHeight() - 1) {
                new_bit_map[y][x].MatrixApplier(bit_map[y - 1][x - 1], bit_map[y - 1][x], bit_map[y - 1][x + 1],
                                                bit_map[y][x - 1], bit_map[y][x], bit_map[y][x + 1], bit_map[y][x - 1],
                                                bit_map[y][x], bit_map[y][x + 1], matrix);
            } else {
                new_bit_map[y][x].MatrixApplier(
                    bit_map[y - 1][x - 1], bit_map[y - 1][x], bit_map[y - 1][x + 1], bit_map[y][x - 1], bit_map[y][x],
                    bit_map[y][x + 1], bit_map[y + 1][x - 1], bit_map[y + 1][x], bit_map[y + 1][x + 1], matrix);
            }
            new_bit_map[y][x].Normalize();
        }
    }
}

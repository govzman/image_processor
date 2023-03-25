#include "FilterGauss.h"

void FilterGauss::Apply(Image& image, double sigma) {
    auto original_bit_map = image.GetBitMap();
    std::vector<std::vector<Pixel>> horizontal_bit_map(image.GetHeight(),
                                                       std::vector<Pixel>(image.GetWidth(), Pixel()));
    std::vector<std::vector<Pixel>> final_bit_map(image.GetHeight(), std::vector<Pixel>(image.GetWidth(), Pixel()));

    double distance = std::ceil((MATRIX_SIZE_COEF * sigma) / 2);

    std::vector<double> coef_vector;

    for (double i = -distance; i <= 0; ++i) {
        coef_vector.push_back(
            static_cast<float>(sqrt(1 / (2 * PI * sigma * sigma)) * std::exp((-i * i) / (2 * sigma * sigma))));
    }
    for (int i = static_cast<int>(distance) - 1; i >= 0; --i) {
        coef_vector.push_back(coef_vector[i]);
    }

    for (int64_t x0 = 0; x0 < image.GetWidth(); ++x0) {
        for (int64_t i = static_cast<int64_t>(-distance); i < static_cast<int64_t>(distance + 1); ++i) {
            int64_t main_point_x = std::min<int64_t>(image.GetWidth() - 1, std::max<int64_t>(x0 + i, 0ll));
            for (int64_t y0 = 0; y0 < image.GetHeight(); ++y0) {
                horizontal_bit_map[y0][x0] += original_bit_map[y0][main_point_x] *
                                              static_cast<float>(coef_vector[i + static_cast<int64_t>(distance)]);
            }
        }
        for (int64_t y = 0; y < image.GetHeight(); ++y) {
            for (int64_t i = static_cast<int64_t>(-distance); i < static_cast<int64_t>(distance + 1); ++i) {
                int64_t y0 = std::min<int64_t>(image.GetHeight() - 1, std::max<int64_t>(y + i, 0ll));
                final_bit_map[y][x0] +=
                    horizontal_bit_map[y0][x0] * static_cast<float>(coef_vector[i + static_cast<int64_t>(distance)]);
            }
        }
    }

    image.SetBitMap(final_bit_map);
}

#include "FilterSharpening.h"

const int64_t CENTRAL_MATRIX_COEF = 5;

void FilterSharpening::Apply(Image& image) {
    MatrixFilter matrix_filter;

    matrix_filter.Apply(image, {{0, -1, 0}, {-1, CENTRAL_MATRIX_COEF, -1}, {0, -1, 0}});
}

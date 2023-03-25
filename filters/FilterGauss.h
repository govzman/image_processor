#include "../Image.h"
#include <cmath>

const double PI = acos(-1.0);
const double MATRIX_SIZE_COEF = 6.0;

class FilterGauss {
public:
    void Apply(Image& image, double sigma);
};

#include "../Image.h"

const float RED_COLOR = 0.299f;
const float GREEN_COLOR = 0.587f;
const float BLUE_COLOR = 0.114f;

class FilterGrayscale {
public:
    void Apply(Image& image);
};

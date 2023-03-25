#pragma once
#include <string>
#include <vector>

const float EPS = 0.005;

using Matrix = std::vector<std::vector<float>>;

struct Pixel {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;

    Pixel() = default;
    Pixel(float r, float g, float b) {
        this->r = r;
        this->g = g;
        this->b = b;
    };

    Pixel operator+(Pixel pixel) const {
        Pixel res_pixel;
        res_pixel.r = this->r + pixel.r;
        res_pixel.g = this->g + pixel.g;
        res_pixel.b = this->b + pixel.b;
        return res_pixel;
    }

    Pixel operator*(float lambda) const {
        Pixel res_pixel;
        res_pixel.r = this->r * lambda;
        res_pixel.g = this->g * lambda;
        res_pixel.b = this->b * lambda;
        return res_pixel;
    }

    Pixel& operator+=(Pixel pixel) {
        *this = *this + pixel;
        return *this;
    }

    Pixel& operator*=(float lambda) {
        *this = *this * lambda;
        return *this;
    }

    bool operator==(Pixel pixel) const {
        return (std::abs(pixel.r - this->r) < EPS && std::abs(pixel.g - this->g) < EPS &&
                std::abs(pixel.b - this->b) < EPS);
    }

    void Normalize() {
        this->r = std::min(1.0f, std::max(0.0f, this->r));
        this->g = std::min(1.0f, std::max(0.0f, this->g));
        this->b = std::min(1.0f, std::max(0.0f, this->b));
    }

    void MatrixApplier(Pixel pixel11, Pixel pixel12, Pixel pixel13, Pixel pixel21, Pixel pixel22, Pixel pixel23,
                       Pixel pixel31, Pixel pixel32, Pixel pixel33, Matrix matrix) {
        const float m11 = matrix[0][0];
        const float m12 = matrix[0][1];
        const float m13 = matrix[0][2];
        const float m21 = matrix[1][0];
        const float m22 = matrix[1][1];
        const float m23 = matrix[1][2];
        const float m31 = matrix[2][0];
        const float m32 = matrix[2][1];
        const float m33 = matrix[2][2];

        *this = pixel11 * m11 + pixel12 * m12 + pixel13 * m13 + pixel21 * m21 + pixel22 * m22 + pixel23 * m23 +
                pixel31 * m31 + pixel32 * m32 + pixel33 * m33;
    }
};

class Image {
public:
    Image() = default;
    Image(int64_t width, int64_t height);

    bool operator==(Image image) const;

    void SetHeight(int64_t height);
    void SetWidth(int64_t width);
    void SetBitMap(std::vector<std::vector<Pixel>>& bit_map);

    int64_t GetHeight() const;
    int64_t GetWidth() const;
    std::vector<std::vector<Pixel>>& GetBitMap();
    std::vector<std::vector<Pixel>> GetBitMap() const;

private:
    int64_t image_width_ = 0;
    int64_t image_height_ = 0;
    std::vector<std::vector<Pixel>> bit_map_ = {};
};

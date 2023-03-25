#include <math.h>
#include <iostream>
#include <cstring>
#include <sstream>
#include "Image.h"
#include "file_worker/FileWorker.h"
#include "filters/FilterNegative.h"
#include "filters/FilterGrayscale.h"
#include "filters/FilterSharpening.h"
#include "filters/FilterCrop.h"
#include "filters/FilterEdgeDetection.h"
#include "filters/FilterAnaglyph.h"
#include "filters/FilterGauss.h"

bool IsNumber(const std::string& s) {
    auto it = s.begin();
    while (it != s.end() && std::isdigit(*it)) {
        ++it;
    }
    return !s.empty() && it == s.end();
}

bool IsFloat(std::string my_string) {
    std::istringstream iss(my_string);
    float f = NAN;
    iss >> std::noskipws >> f;
    return iss.eof() && !iss.fail();
}

int main(int argc, char** argv) {
    FilterNegative filter_negative;
    FilterGrayscale filter_grayscale;
    FilterSharpening filter_sharpening;
    FilterCrop filter_crop;
    FilterEdgeDetection filter_edge_detection;
    FilterAnaglyph filter_anaglyph;
    FilterGauss filter_gauss;

    if (argc < 3) {
        std::cout << "Image processor" << std::endl;
        std::cout << "Program for apply some filters to image" << std::endl;
        std::cout << std::endl;
        std::cout << "Usage:" << std::endl;
        std::cout << "\tbuild/image_processor input_file_name.bmp output_file_name.bmp [-filter1 [arg1 arg2 ...] ]"
                  << std::endl;
        std::cout << std::endl;
        std::cout << "Filters:" << std::endl;
        std::cout << "\t-crop width height Crop filter" << std::endl;
        std::cout << "\t-gs Grayscale filter" << std::endl;
        std::cout << "\t-neg Negative filter" << std::endl;
        std::cout << "\t-sharp Sharpening filter" << std::endl;
        std::cout << "\t-edge threshold Edge Detection filter" << std::endl;
        std::cout << "\t-blur sigma Gaussian Blur filter" << std::endl;
        std::cout << "\t-anag shift Anaglyph filter" << std::endl;
        return 0;
    }

    std::string path_read = argv[1];
    std::string path_write = argv[2];

    std::cout << path_read << std::endl;
    std::cout << path_write << std::endl;

    FileWorker file_worker;

    Image image = file_worker.Read(path_read);

    for (int i = 3; i < argc; ++i) {
        std::cout << "Apply " << argv[i] << std::endl;
        if (strcmp(argv[i], "-crop") == 0) {
            if (argc < i + 2) {
                std::cout << "crop filter haven't width and/or height parametrs" << std::endl;
                return -1;
            } else if (!IsNumber(argv[i + 1]) || !IsNumber(argv[i + 2])) {
                std::cout << "crop filter has non-numeric parametrs" << std::endl;
                return -1;
            }
            filter_crop.Apply(image, std::stoi(argv[i + 1]), std::stoi(argv[i + 2]));
            i += 2;
        } else if (strcmp(argv[i], "-gs") == 0) {
            filter_grayscale.Apply(image);
        } else if (strcmp(argv[i], "-neg") == 0) {
            filter_negative.Apply(image);
        } else if (strcmp(argv[i], "-sharp") == 0) {
            filter_sharpening.Apply(image);
        } else if (strcmp(argv[i], "-edge") == 0) {
            if (argc < i + 1) {
                std::cout << "edge filter haven't threshold parametr" << std::endl;
                return -1;
            } else if (!IsFloat(argv[i + 1])) {
                std::cout << "edge filter has non-numeric parametr" << std::endl;
                return -1;
            } else if (!(0 <= std::stof(argv[i + 1]) && std::stof(argv[i + 1]) <= 1)) {
                std::cout << "edge filter threshold parametr must be from 0 to 1" << std::endl;
                return -1;
            }
            filter_edge_detection.Apply(image, std::stof(argv[i + 1]));
            i += 1;
        } else if (strcmp(argv[i], "-blur") == 0) {
            if (argc < i + 1) {
                std::cout << "blur filter haven't sigma parametr" << std::endl;
                return -1;
            } else if (!IsFloat(argv[i + 1])) {
                std::cout << "blur filter has non-numeric parametr" << std::endl;
                return -1;
            }
            filter_gauss.Apply(image, std::stof(argv[i + 1]));
            i += 1;
        } else if (strcmp(argv[i], "-anag") == 0) {
            if (argc < i + 1) {
                std::cout << "anaglyph filter haven't shift parametr" << std::endl;
                return -1;
            } else if (!IsNumber(argv[i + 1])) {
                std::cout << "anaglyph filter has non-numeric parametr" << std::endl;
                return -1;
            }
            filter_anaglyph.Apply(image, std::stoi(argv[i + 1]));
            i += 1;
        } else {
            std::cout << argv[i] << " filter not exist" << std::endl;
            return -1;
        }
    }

    file_worker.Write(path_write, image);

    return 0;
}

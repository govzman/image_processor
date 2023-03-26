cmake_minimum_required(VERSION 3.24)

project(image_processor)

add_executable(
        image_processor
        image_processor.cpp
        file_worker/FileWorker.cpp
        Image.cpp
        filters/FilterNegative.cpp
        filters/FilterGrayscale.cpp
        filters/FilterSharpening.cpp
        filters/MatrixFilter.cpp
        filters/FilterCrop.cpp
        filters/FilterEdgeDetection.cpp
        filters/FilterAnaglyph.cpp
        filters/FilterGauss.cpp
)

add_subdirectory(test_dir)

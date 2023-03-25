project(test_dir)

set(CMAKE_CXX_STANDARD 23)

add_executable(
        test_dir
        test.cpp

        ../file_worker/FileWorker.cpp
        ../Image.cpp
        ../filters/FilterNegative.cpp
        ../filters/FilterGrayscale.cpp
        ../filters/FilterSharpening.cpp
        ../filters/MatrixFilter.cpp
        ../filters/FilterCrop.cpp
        ../filters/FilterEdgeDetection.cpp
        ../filters/FilterAnaglyph.cpp
        ../filters/FilterGauss.cpp
)

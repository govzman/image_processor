#include <cassert>
#include "../Image.h"
#include "../file_worker/FileWorker.h"
#include "../filters/FilterNegative.h"
#include "../filters/FilterGrayscale.h"
#include "../filters/FilterSharpening.h"
#include "../filters/FilterCrop.h"
#include "../filters/FilterEdgeDetection.h"
#include "../filters/FilterAnaglyph.h"
#include "../filters/FilterGauss.h"

int main() {
    FileWorker file_worker;

    Image image_flag = file_worker.Read("../../data/flag.bmp");
    Image image_lenna = file_worker.Read("../../data/lenna.bmp");
    {
        FilterNegative filter_negative;
        Image flag_with_filter = image_flag;
        Image lenna_with_filter = image_lenna;

        filter_negative.Apply(flag_with_filter);
        filter_negative.Apply(lenna_with_filter);
        assert(flag_with_filter == file_worker.Read("../../data/flag_neg.bmp"));
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_neg.bmp"));
    }
    {
        FilterGrayscale filter_grayscale;
        Image flag_with_filter = image_flag;
        Image lenna_with_filter = image_lenna;

        filter_grayscale.Apply(flag_with_filter);
        filter_grayscale.Apply(lenna_with_filter);
        assert(flag_with_filter == file_worker.Read("../../data/flag_gs.bmp"));
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_gs.bmp"));
    }
    {
        FilterSharpening filter_sharpening;
        Image flag_with_filter = image_flag;
        Image lenna_with_filter = image_lenna;

        filter_sharpening.Apply(flag_with_filter);
        filter_sharpening.Apply(lenna_with_filter);
        assert(flag_with_filter == file_worker.Read("../../data/flag_sharp.bmp"));
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_sharp.bmp"));
    }
    {
        FilterCrop filter_crop;
        ;
        Image flag_with_filter = image_flag;
        Image lenna_with_filter = image_lenna;

        filter_crop.Apply(flag_with_filter, 100, 100);
        filter_crop.Apply(lenna_with_filter, 999, 1999);
        assert(flag_with_filter == file_worker.Read("../../data/flag_crop.bmp"));
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_crop.bmp"));
    }
    {
        FilterEdgeDetection filter_edge_detection;
        Image flag_with_filter = image_flag;

        filter_edge_detection.Apply(flag_with_filter, 0.1);
        assert(flag_with_filter == file_worker.Read("../../data/flag_edge.bmp"));
    }
    {
        FilterGauss filter_gauss;
        Image lenna_with_filter = image_lenna;

        filter_gauss.Apply(lenna_with_filter, 7.5);
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_blur.bmp"));
    }
    {
        FilterAnaglyph filter_anaglyph;
        Image lenna_with_filter = image_lenna;

        filter_anaglyph.Apply(lenna_with_filter, 15);
        assert(lenna_with_filter == file_worker.Read("../../data/lenna_anag.bmp"));
    }
    return 0;
}

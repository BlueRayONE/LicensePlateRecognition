#ifndef CLASSIFICATION_HPP
#define CLASSIFICATION_HPP

#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

#include "Segmentation.h"
#include "Segmentation_MSER.h"


class Classification
{
public:
    Classification();
    std::vector<std::string> characterRecognition(const std::vector<cv::Mat> plates, bool projection);

    cv::Mat originalImage;
};

#endif // CLASSIFICATION_HPP

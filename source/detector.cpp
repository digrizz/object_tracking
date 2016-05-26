#include "detector.h"

Detector::Detector()
{

}

Detector::~Detector()
{

}

detector_info_t Detector::detectObject(cv::Mat frame)
{
    detector_info_t retval;

    retval.x = 20;
    retval.y = 40;
    retval.width = 60;
    retval.height = 80;

    return retval;
}



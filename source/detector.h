#include "cv.h"


class Detector
{
    public:
        Detector();
        virtual ~Detector();

        cv::Mat trackObject(cv::Mat frame);
        void detectObject();

    private:

};


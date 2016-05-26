#include "cv.h"


struct tracker_info_t
{
    int x;
    int y;
    int width;
    int height;
    cv::Mat frame;
};


class Tracker
{
    public:
        Tracker();
        virtual ~Tracker();

        tracker_info_t trackObject(cv::Mat frame);

    private:

};


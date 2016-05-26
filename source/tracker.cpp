#include "tracker.h"


Tracker::Tracker()
{
}


Tracker::~Tracker()
{
}


tracker_info_t Tracker::trackObject(cv::Mat frame)
{
    tracker_info_t retval;

    retval.x = 20;
    retval.y = 40;
    retval.width = 60;
    retval.height = 80;



    retval.frame = frame;

    return retval;
}





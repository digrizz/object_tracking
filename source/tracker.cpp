#include "tracker.h"
#include "logger.h"

#include <chrono>
#include <iostream>

namespace ot
{

    Tracker::Tracker()
    {
        initialize();
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


    void Tracker::initialize()
    {
        std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now(); 

        for (int i=0; i<10000; i++)
        {
            std::cout << "dupa\n";
        }

        std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now(); 
        std::chrono::milliseconds timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        Logger::getInstance()->timeInfo("Initialization time", timeSpan.count());
    }


    void Tracker::searchObject()
    {

    }
}


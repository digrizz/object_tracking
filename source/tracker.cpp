#include "tracker.h"
#include "logger.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


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


    tracker_info_t Tracker::trackObject(cv::Mat& frame)
    {
        currentFrame = frame;
        //cv::imshow("frame", frame);
        //cv::waitKey(0);

        searchObject();

        tracker_info_t retval;
        retval.x = windowX;
        retval.y = windowY;
        retval.width = windowWidth;
        retval.height = windowHeight;
        retval.frame = currentFrame;

        previousFrameInfo = retval;
        return retval;
    }


    void Tracker::initialize()
    {
        std::cout << "initialize";
        windowX = 10;
        windowY = 10;
        windowWidth = 100;
        windowHeight = 100;
        r = 195;
        g = 195;
        b = 195;

        threshTol = 30;

        rMin = r-threshTol;
        gMin = g-threshTol;
        bMin = b-threshTol;
        if (rMin < 0) rMin = 0;
        if (gMin < 0) gMin = 0;
        if (bMin < 0) bMin = 0;

        rMax = r+threshTol;
        gMax = g+threshTol;
        bMax = b+threshTol;
        if (rMax > 255) rMax = 255;
        if (gMax > 255) gMax = 255;
        if (bMax > 255) bMax = 255;

        notMoveTolerance = 4;

        detector.initialize(windowWidth, windowHeight, r, g, b, 0, 160, 0, 60);

        // std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now(); 
        //
        // for (int i=0; i<10000; i++)
        // {
        //     std::cout << "dupa\n";
        // }
        //
        // std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now(); 
        // std::chrono::milliseconds timeSpan = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1);
        // Logger::getInstance()->timeInfo("Initialization time", timeSpan.count());
    }


    void Tracker::searchObject()
    {
        previousX = windowX;
        previousY = windowY;
        
        detector.setCanDetect(true);
        bool continueShift = false;
        do
        {
            continueShift = calcCenterOfMean();
        }
        while (!(abs(previousX - windowX) < notMoveTolerance &&
                    abs(previousY - windowY) < notMoveTolerance) &&
                continueShift);
    }

    bool Tracker::calcCenterOfMean()
    {
        std::cout << "windowX: " << windowX << " ; windowY: " << windowY << "\n";
        cv::Mat window(currentFrame, cv::Rect(windowX, windowY, windowWidth, windowHeight));
        cv::imshow("window", window);
        //cv::waitKey(0);

        cv::Mat threshold;
        cv::inRange(window, 
                    cv::Scalar(rMin, gMin, bMin), 
                    cv::Scalar(rMax, gMax, bMax),
                    threshold);

        //cv::imshow("threshold", threshold);
        //cv::waitKey(0);

        long long x = 0;
        long long y = 0;
        int count = 0;


        for(int i=0; i<threshold.rows; i++)
        {
            for(int j=0; j<threshold.cols; j++) 
            {
                if (threshold.at<uchar>(i,j) > 128)
                {
                    x += j;
                    y += i;
                    count++;
                }
            }
        }

        previousX = windowX;
        previousY = windowY;

        if (count == 0)
        {
            if (detector.getCanDetect())
            {
                detector_info_t detectInfo = detector.detectObject(currentFrame);

                if (detectInfo.isDetected)
                {
                    windowX = detectInfo.x;
                    windowY = detectInfo.y;

                    detector.setCanDetect(false);
                    return true;
                }
            }
            return false;
        }


        windowX += x / count - windowWidth / 2;
        windowY += y / count - windowHeight / 2;

        if (windowX < 0) windowX = 0;
        if (windowY < 0) windowY = 0;

        if (windowX > currentFrame.cols) windowX = currentFrame.cols;
        if (windowY > currentFrame.rows) windowY = currentFrame.rows;

        std::cout << "previousX: " << previousX << " ; previousY: " << previousY << "\n";
        std::cout << "windowX: " << windowX << " ; windowY: " << windowY << "\n";

        return true;
    }
}



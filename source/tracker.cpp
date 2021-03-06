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


    cv::Mat Tracker::markBall(cv::Mat &frame, int x, int y, int r)
    {
        cv::circle( frame, cv::Point( x, y ), r, cv::Scalar( 0, 0, 255 ), 1, 8 );
        return frame;
    }


    tracker_info_t Tracker::trackObject(cv::Mat& frame)
    {
        currentFrame = frame;

        searchObject();

        tracker_info_t retval;
        retval.x = ballX;
        retval.y = ballY;
        //retval.frame = frame;
        if (ballX > 0 && ballY > 0)
        {
            retval.frame = markBall(frame, ballX, ballY, 30);
        }
        else
        {
            retval.frame = frame;
        }
        //cv::imshow("frame", retval.frame);
        //cv::waitKey(0);
        retval.frameThreshold = frameThreshold;

        return retval;
    }


    void Tracker::initialize()
    {
        windowX = 0;
        windowY = 0;
        windowWidth = 100;
        windowHeight = 100;
        r = 225;
        g = 205;
        b = 205;

        threshTol = 50;

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

        detector.initialize(windowWidth, windowHeight, r, g, b, threshTol, 0, 160, 0, 60);

        trackCount = 0;
    }


    void Tracker::searchObject()
    {
        previousX = windowX;
        previousY = windowY;

        detector.setCanDetect(true);
        const int MAX_ITERATIONS = 4;
        bool continueShift = false;
        int i=0;
        do
        {
            continueShift = calcCenterOfMean();
            i++;
        }
        while (!(abs(previousX - windowX) < notMoveTolerance &&
                    abs(previousY - windowY) < notMoveTolerance) &&
                detector.getCanDetect() &&
                i < MAX_ITERATIONS &&
                continueShift);
    }

    bool Tracker::detect(cv::Mat currentFrame)
    {
        trackCount = 0;
        detector_info_t detectInfo = detector.detectObject(currentFrame);

        if (detectInfo.isDetected)
        {
            windowX = detectInfo.x;
            windowY = detectInfo.y;

            detector.setCanDetect(false);

            ballX = windowX + windowWidth / 2;
            ballY = windowY + windowHeight / 2;
            return true;
        }
        ballX = -1;
        ballY = -1;
        return false;
    }

    cv::Mat Tracker::getBall(cv::Mat window)
    {
        cv::Mat boardThreshold;

        cv::inRange(window, 
                cv::Scalar(detector.boardRMin, detector.boardGMin, detector.boardBMin), 
                cv::Scalar(detector.boardRMax, detector.boardGMax, detector.boardBMax), 
                boardThreshold);

        cv::Mat board;

        cv::Mat ball;
        cv::inRange(window, 
                cv::Scalar(detector.ballRMin, detector.ballGMin, detector.ballBMin), 
                cv::Scalar(detector.ballRMax, detector.ballGMax, detector.ballBMax), 
                ball);

        cv::Mat const structure_elem_ball = cv::getStructuringElement(
                cv::MORPH_RECT, cv::Size(15, 15));
        cv::morphologyEx(boardThreshold, board, cv::MORPH_DILATE, structure_elem_ball);

        ball = ball & board;
        return ball;
    }

    bool Tracker::calcCenterOfMean()
    {
        frameThreshold = getBall(currentFrame);
        //cv::imshow("ball", frameThreshold);
        //cv::waitKey(0);

        cv::Mat window(currentFrame, cv::Rect(windowX, windowY, windowWidth, windowHeight));
        //cv::imshow("window", window);

        trackCount++;

        if (trackCount > 10)
        {
            return detect(currentFrame);
        }

        cv::Mat ball = getBall(window);

        std::vector<int> regionPixelCount;
        cv::Mat ballRegions(ball.rows, ball.cols, CV_8UC1, cv::Scalar(0));


        for(int i=1; i<ball.rows-1; i++)
        {
            for(int j=1; j<ball.cols-1; j++) 
            {
                if (ball.at<uchar>(i,j) > 128)
                {
                    int neighbour = ballRegions.at<uchar>(i-1,j-1);
                    if (neighbour > 0)
                    {
                        regionPixelCount[neighbour]++;
                        ballRegions.at<uchar>(i,j) = neighbour;
                    }
                    neighbour = ballRegions.at<uchar>(i-1,j);
                    if (neighbour > 0)
                    {
                        regionPixelCount[neighbour]++;
                        ballRegions.at<uchar>(i,j) = neighbour;
                    }
                    neighbour = ballRegions.at<uchar>(i-1,j+1);
                    if (neighbour > 0)
                    {
                        regionPixelCount[neighbour]++;
                        ballRegions.at<uchar>(i,j) = neighbour;
                    }
                    neighbour = ballRegions.at<uchar>(i,j-1);
                    if (neighbour > 0)
                    {
                        regionPixelCount[neighbour]++;
                        ballRegions.at<uchar>(i,j) = neighbour;
                    }
                    else
                    {
                        regionPixelCount.push_back(1);
                        ballRegions.at<uchar>(i,j) = regionPixelCount.size();
                    }
                }
            }
        }

        int maxRegion = -1;
        int maxRegionCount = -1;
        for (int i=0; i<regionPixelCount.size(); i++)
        {
            if (regionPixelCount[i] > maxRegionCount)
            {
                maxRegion = i;
                maxRegionCount = regionPixelCount[i];
            }
        }

        long long x = 0;
        long long y = 0;
        int count = 0;


        for(int i=0; i<ballRegions.rows; i++)
        {
            for(int j=0; j<ballRegions.cols; j++) 
            {
                if (ballRegions.at<uchar>(i,j) == maxRegion)
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
                bool retval = detect(currentFrame);
                return retval;
            }
            return false;
        }


        windowX += x / count - windowWidth / 2;
        windowY += y / count - windowHeight / 2;

        if (windowX < 0) windowX = 0;
        if (windowY < 0) windowY = 0;

        if (windowX > currentFrame.cols-windowWidth) windowX = currentFrame.cols-windowWidth;
        if (windowY > currentFrame.rows-windowHeight) windowY = currentFrame.rows-windowHeight;

        ballX = windowX + windowWidth / 2;
        ballY = windowY + windowHeight / 2;
        return true;
    }
}



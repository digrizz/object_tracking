#include "detector.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>

namespace ot
{

    Detector::Detector()
    {

    }

    Detector::~Detector()
    {

    }

    detector_info_t Detector::detectObject(cv::Mat frame)
    {
        detector_info_t retval;

        ballX = 0;
        ballY = 0;

        cv::Mat boardThreshold;



        cv::inRange(frame, 
                    cv::Scalar(boardRMin, boardGMin, boardBMin), 
                    cv::Scalar(boardRMax, boardGMax, boardBMax), 
                    boardThreshold);

        cv::Mat board;
        cv::Mat const structure_elem = cv::getStructuringElement(
                 cv::MORPH_RECT, cv::Size(70, 70));
        cv::morphologyEx(boardThreshold, board, cv::MORPH_CLOSE, structure_elem);

        cv::Mat background;
        threshold(board, background, 128, 255, cv::THRESH_BINARY_INV);

        cv::Mat ball;

        cv::inRange(frame, 
                    cv::Scalar(ballRMin, ballGMin, ballBMin), 
                    cv::Scalar(ballRMax, ballGMax, ballBMax), 
                    ball);

        cv::Mat const structure_elem_ball = cv::getStructuringElement(
                 cv::MORPH_RECT, cv::Size(20, 20));
        cv::morphologyEx(boardThreshold, board, cv::MORPH_CLOSE, structure_elem);

        ball = ball & board;

        retval.isDetected = findBall(ball);

        //cv::imshow("ball", ball);
        //cv::waitKey(0);

        retval.x = ballX;
        retval.y = ballY;
        retval.width = windowWidth;
        retval.height = windowHeight;
        //retval.isDetected = true;

        return retval;
    }


    void Detector::initialize(int wWidth, int wHeight, int ballR, int ballG, int ballB, 
            int boardR, int boardG, int boardB, int tolerance)
    {
        ballRMin = ballR - tolerance;
        ballGMin = ballG - tolerance;
        ballBMin = ballB - tolerance;
        if (ballRMin < 0) ballRMin = 0;
        if (ballGMin < 0) ballGMin = 0;
        if (ballBMin < 0) ballBMin = 0;

        ballRMax = ballR + tolerance;
        ballGMax = ballG + tolerance;
        ballBMax = ballB + tolerance;
        if (ballRMax > 255) ballRMax = 255;
        if (ballGMax > 255) ballGMax = 255;
        if (ballBMax > 255) ballBMax = 255;

        boardRMin = boardR - tolerance;
        boardGMin = boardG - tolerance;
        boardBMin = boardB - tolerance;
        if (boardRMin < 0) boardRMin = 0;
        if (boardGMin < 0) boardGMin = 0;
        if (boardBMin < 0) boardBMin = 0;

        boardRMax = boardR + tolerance;
        boardGMax = boardG + tolerance;
        boardBMax = boardB + tolerance;
        if (boardRMax > 255) boardRMax = 255;
        if (boardGMax > 255) boardGMax = 255;
        if (boardBMax > 255) boardBMax = 255;

        this->tolerance = tolerance;

        windowWidth = wWidth;
        windowHeight = wHeight;
    }

    bool Detector::findBall(cv::Mat ballThreshold)
    {
        std::cout << "rows: " << ballThreshold.rows << " ; cols: " << ballThreshold.cols << "\n";

        std::vector<int> regionPixelCount;
        cv::Mat ballRegions(ballThreshold.cols, ballThreshold.rows, CV_8UC1, cv::Scalar(0));

        cv::imshow("ballThreshold", ballThreshold);
        //cv::waitKey(0);

        ballX = 0;
        ballY = 0;

        for(int i=1; i<ballThreshold.rows-1; i++)
        {
            for(int j=1; j<ballThreshold.cols-1; j++) 
            {
                if (ballThreshold.at<uchar>(i,j) > 128)
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
                    }
                }
            }
        }

        if (regionPixelCount.size() == 0)
        {
            return false;
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

        for(int i=1; i<ballRegions.rows-1; i++)
        {
            for(int j=1; j<ballRegions.cols-1; j++) 
            {
                if (ballRegions.at<uchar>(i,j) == maxRegion)
                {
                    x += j;
                    y += i;
                    count++;
                }
            }
        }

        ballX = x / count - windowWidth / 2;
        ballY = y / count - windowHeight / 2;

        std::cout << "ballX: " << ballX << " ; ballY: " << ballY << "\n";

        if (ballX < 0) ballX = 0;
        if (ballY < 0) ballY = 0;

        if (ballX > ballThreshold.cols - windowWidth) ballX = ballThreshold.cols - windowWidth;
        if (ballY > ballThreshold.rows - windowHeight) ballY = ballThreshold.rows - windowHeight;

        return true;
    }
}


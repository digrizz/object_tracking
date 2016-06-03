#ifndef TRACKER_H__
#define TRACKER_H__

#include "detector.h"

#include <opencv2/core/core.hpp>

namespace ot
{
    struct tracker_info_t
    {
        int x;
        int y;
        cv::Mat frame;
        cv::Mat frameThreshold;
    };


    class Tracker
    {
        public:
            Tracker();
            virtual ~Tracker();

            tracker_info_t trackObject(cv::Mat &frame);

            bool detect(cv::Mat currentFrame);

            cv::Mat getBall(cv::Mat frame);

            inline void setBallR(int value)
            {
                r = value;
            }

            inline void setBallG(int value)
            {
                g = value;
            }

            inline void setBallB(int value)
            {
                b = value;
            }

            inline void setThresholdTolerance(int value)
            {
                threshTol = value;
            }

        private:
            int windowX;
            int windowY;
            int windowWidth;
            int windowHeight;

            int ballX;
            int ballY;

            cv::Mat frameThreshold;

            int previousX;
            int previousY;

            int notMoveTolerance;

            tracker_info_t previousFrameInfo;
            cv::Mat currentFrame;

            int r, g, b;  /**< Interest colour */
            int rMax, gMax, bMax;  /**< Max colour */
            int rMin, gMin, bMin;  /**< Min colour */
            int threshTol;  /**< Threshold tolerancy */

            double density; /**< Indicates what is density of interest pixels in window */

            int trackCount;

            Detector detector;

            void initialize();
            void searchObject();
            bool calcCenterOfMean();
            cv::Mat markBall(cv::Mat &frame, int x, int y, int r);

    };
}

#endif

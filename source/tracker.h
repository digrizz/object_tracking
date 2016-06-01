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
        int width;
        int height;
        cv::Mat frame;
    };


    class Tracker
    {
        public:
            Tracker();
            virtual ~Tracker();

            tracker_info_t trackObject(cv::Mat &frame);

        private:
            int windowX;
            int windowY;
            int windowWidth;
            int windowHeight;

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

            Detector detector;

            void initialize();

            void searchObject();
            bool calcCenterOfMean();
    };
}

#endif

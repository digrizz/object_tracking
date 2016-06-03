#ifndef DETECTOR_H__
#define DETECTOR_H__

#include <opencv2/core/core.hpp>

namespace ot
{
    struct detector_info_t
    {
        int x;
        int y;
        int width;
        int height;

        bool isDetected;
    };

    class Detector
    {
        public:
            Detector();
            virtual ~Detector();

            detector_info_t detectObject(cv::Mat frame);

            inline bool getCanDetect()
            {
                return canPerformDetect;
            }

            inline void setCanDetect(bool value)
            {
                canPerformDetect = value;
            }

            void initialize(int wWidth, int wHeight, int ballR, int ballG, int ballB, 
                    int ballTolerance, int boardR, int boardG, int boardB, int tolerance);

            int boardRMin;
            int boardGMin;
            int boardBMin;
            int boardRMax;
            int boardGMax;
            int boardBMax;

            int ballRMin;
            int ballGMin;
            int ballBMin;
            int ballRMax;
            int ballGMax;
            int ballBMax;


        private:
            bool canPerformDetect;

            int tolerance;

            int ballX;
            int ballY;
            bool ballFound;

            int windowWidth;
            int windowHeight;

            bool findBall(cv::Mat ballThreshold);
    };
}

#endif

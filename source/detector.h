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

            void initialize(int ballR, int ballG, int ballB, 
                        int boardR, int boardG, int boardB, int tolerance);

        private:
            bool canPerformDetect;
            int ballRMin;
            int ballGMin;
            int ballBMin;
            int ballRMax;
            int ballGMax;
            int ballBMax;

            int boardRMin;
            int boardGMin;
            int boardBMin;
            int boardRMax;
            int boardGMax;
            int boardBMax;

            int tolerance;

            int ballX;
            int ballY;
            bool ballFound;

            void findBall(cv::Mat ballThreshold);
    };
}

#endif DETECTOR_H__


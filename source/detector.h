#include <opencv2/core/core.hpp>

namespace ot
{
    struct detector_info_t
    {
        int x;
        int y;
        int width;
        int height;
    };

    class Detector
    {
        public:
            Detector();
            virtual ~Detector();

            detector_info_t detectObject(cv::Mat frame);

        private:

    };
}


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

            tracker_info_t trackObject(cv::Mat frame);

        private:
            int windowX;
            int windowY;
            int windowWidht;
            int windowHeight;

            int r, g, b;  /**< Interest colour */

            double density; /**< Indicates what is density of interest pixels in window */

            void initialize();

            void searchObject();
    };
}


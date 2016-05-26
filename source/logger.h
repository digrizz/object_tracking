#include <string>

namespace ot
{
    class Logger
    {
        public:
            virtual ~Logger();

            void error(std::string message);
            void warning(std::string message);
            void into(std::string message);
            void debug(std::string message);
            void debug(std::string message, int level);

            void timeInfo(std::string message, time_t duration);
            void timeDebug(std::string message, time_t duration);
            void timeDebug(std::string message, time_t duration, int level);

            static Logger *getInstance();

        private:
            static Logger *instance;
            Logger();

    };
}


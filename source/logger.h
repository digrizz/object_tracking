#include <string>

class Logger
{
    public:
        virtual ~Logger();

        void error(std::string message);
        void warning(std::string message);
        void debug(std::string message);
        void debug(std::string message, int level);

        static Logger *getInstance();

    private:
        static Logger *instance;
        Logger();

};


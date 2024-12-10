#ifndef LOGGER_H
#define LOGGER_H
#include <string>
#include <fstream>
#include <filesystem>
#include <ctime>
#include <sstream>
#include <mutex>

namespace ShunscomUtils {
    class Logger {
    public:
        // 重载 << 运算符
        Logger& operator<<(const std::string& message); // 支持字符串输出
        Logger& operator<<(const char* message); // 支持 C 字符串输出
        Logger& operator<<(std::ostream& (*func)(std::ostream&)); // 支持流控制符，如 std::endl
        static Logger& getInstance();
        ~Logger(); // 析构函数
    private:
        Logger(const std::string& directory = "", const std::string& filename = ""); // 构造函数

        std::ofstream logFile; // 文件流
        std::string getCurrentTime(); // 获取当前时间的私有方法
        std::string createLogFile(const std::string& directory, const std::string& filename); // 创建日志文件
        bool endled = true;
    };


}
#endif // LOGGER_H
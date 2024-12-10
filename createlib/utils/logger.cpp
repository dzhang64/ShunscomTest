#include "Logger.h"
#include <iostream>
#include <iomanip>
namespace ShunscomUtils {
    // 构造函数
    Logger::Logger(const std::string& directory, const std::string& filename) {
        std::string logFileName = createLogFile(directory, filename);
        logFile.open(logFileName, std::ios::app); // 以追加模式打开文件
        if (!logFile.is_open()) {
            std::cerr << "无法打开日志文件: " << logFileName << std::endl;
        }
    }
    // 析构函数
    Logger::~Logger() {
        if (logFile.is_open()) {
            logFile.close(); // 关闭文件
        }
    }
    // 重载 << 运算符
    Logger& Logger::operator<<(const std::string& message) {
        if (logFile.is_open()) {
            if(endled){
                logFile << getCurrentTime() << " - " << message;// 写入时间戳和消息
            }else{
                logFile << message;
            }
            endled = false;
        }
        return *this; // 返回自身以支持链式调用
    }
    Logger& Logger::operator<<(const char* message) {
        return *this << std::string(message);
    }
    Logger& Logger::operator<<(std::ostream& (*func)(std::ostream&)) {
        if (func == static_cast<std::ostream& (*)(std::ostream&)>(std::endl)) {
            if (logFile.is_open()) {
                logFile << std::endl; // 在日志中添加换行
                endled = true;
            }
        }
        return *this;
    }
    // 获取当前时间字符串
    std::string Logger::getCurrentTime() {
        // 获取当前时间点
        auto now = std::chrono::system_clock::now();

        // 转换为时间_t并转换为本地时间
        auto now_time_t = std::chrono::system_clock::to_time_t(now);
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;
        // 创建一个字符串流来格式化输出
        std::ostringstream oss;
        oss << std::put_time(std::localtime(&now_time_t), "%Y-%m-%d %H:%M:%S")
            << '.' << std::setfill('0') << std::setw(3) << milliseconds.count(); // 输出毫秒
        return oss.str(); // 返回结果
    }
    // 创建日志文件
    std::string Logger::createLogFile(const std::string& directory, const std::string& filename) {
        std::string logFileName;
        // 如果目录为空，设置为当前程序目录下的log文件夹
        std::string finalDirectory = directory.empty() ? (std::filesystem::current_path().string() + "/log") : directory;
        if (filename.empty()) {
            // 创建默认的文件名
            std::time_t now = std::time(nullptr);
            std::tm tmNow = *std::localtime(&now);
            std::ostringstream oss;
            oss << "log_" << std::put_time(&tmNow, "%Y-%m-%d_%H-%M-%S") << ".txt"; // 默认格式
            logFileName = finalDirectory + "/" + oss.str(); // 完整路径
        } else {
            logFileName = finalDirectory + "/" + filename; // 使用提供的文件名
        }
        // 确保目录存在
        std::filesystem::create_directories(finalDirectory);
        return logFileName; // 返回完整的文件名
    }

    Logger &Logger::getInstance() {
        static Logger logger; // 局部静态变量，保证实例在第一次被使用时创建
        return logger;
    }

}
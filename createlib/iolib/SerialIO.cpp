#include "SerialIO.h"


// 构造函数，初始化串口
SerialIO::SerialIO(wchar_t *portName, DWORD inBufferSize, DWORD outBufferSize, int baudrate, bool rts, bool dsr,unsigned char endCharValue) {
    // 转换串口名为wchar*格式
    endChar = endCharValue;
    // 打开串口
    hSerial = CreateFileW(
            portName, // 串口名称（例如 "COM1"）
            GENERIC_READ | GENERIC_WRITE, // 允许读写
            0, // 不共享串口
            NULL, // 默认安全属性
            OPEN_EXISTING, // 打开已存在的串口
            0, // 默认文件属性
            NULL); // 不继承句柄

    if (hSerial == INVALID_HANDLE_VALUE) {
        ShunscomUtils::Logger::getInstance() << "打开串口失败: " << std::to_string(GetLastError()) << std::endl;
        throw std::runtime_error("打开串口失败");
    }

    // 设置缓冲区大小
    if (!SetupComm(hSerial, inBufferSize, outBufferSize)) {
        ShunscomUtils::Logger::getInstance() << "设置串口缓冲区大小失败: " << std::to_string(GetLastError()) << std::endl;
        throw std::runtime_error("设置串口缓冲区大小失败");
    }

    // 设置串口参数
    if (!setPortParams(baudrate, rts, dsr)) {
        ShunscomUtils::Logger::getInstance() << "设置串口参数失败: " << std::to_string(GetLastError()) << std::endl;
        throw std::runtime_error("设置串口参数失败");
    }

    // 配置串口超时
    if (!configureTimeouts()) {
        ShunscomUtils::Logger::getInstance() << "配置串口超时失败: " << std::to_string(GetLastError()) << std::endl;
        throw std::runtime_error("配置串口超时失败");
    }
}

// 析构函数，关闭串口
SerialIO::~SerialIO() {
    if (hSerial != INVALID_HANDLE_VALUE) {
        ShunscomUtils::Logger::getInstance() << "关闭串口" << std::endl;
        CloseHandle(hSerial); // 关闭串口句柄
    }
}

// 设置串口参数（波特率，RTS，DSR）
bool SerialIO::setPortParams(int baudrate, bool rts, bool dsr) {
    DCB dcbSerialParams = {0};

    // 获取当前串口设置
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        ShunscomUtils::Logger::getInstance() << "获取串口状态失败: " << std::to_string(GetLastError()) << std::endl;
        return false;
    }

    // 设置波特率、数据位、停止位和奇偶校验
    dcbSerialParams.BaudRate = baudrate;
    dcbSerialParams.ByteSize = 8; // 8 数据位
    dcbSerialParams.StopBits = ONESTOPBIT; // 1 停止位
    dcbSerialParams.Parity = NOPARITY; // 无奇偶校验

    // 处理 RTS 和 DSR 流控制
    if (rts) {
        dcbSerialParams.fOutxCtsFlow = TRUE; // 启用 RTS 流控制
    } else {
        dcbSerialParams.fOutxCtsFlow = FALSE;
    }
    if (dsr) {
        dcbSerialParams.fOutxDsrFlow = TRUE; // 启用 DSR 流控制
    } else {
        dcbSerialParams.fOutxDsrFlow = FALSE;
    }

    // 应用新的串口设置
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        ShunscomUtils::Logger::getInstance() << "设置串口状态失败: " <<  std::to_string(GetLastError()) << std::endl;
        return false;
    }
    return true;
}

// 配置串口的超时参数
bool SerialIO::configureTimeouts() {
    COMMTIMEOUTS timeouts = {0};
    timeouts.ReadIntervalTimeout = 50; // 读取间隔超时
    timeouts.ReadTotalTimeoutConstant = 50; // 读取超时常数
    timeouts.ReadTotalTimeoutMultiplier = 10; // 读取超时乘数
    timeouts.WriteTotalTimeoutConstant = 50; // 写入超时常数
    timeouts.WriteTotalTimeoutMultiplier = 10; // 写入超时乘数

    // 设置超时参数
    if (!SetCommTimeouts(hSerial, &timeouts)) {
        ShunscomUtils::Logger::getInstance() << "设置串口超时失败: " <<  std::to_string(GetLastError()) << std::endl;
        return false;
    }
    return true;
}


bool SerialIO::readLine(std::vector<uint8_t> &buffer) {
    DWORD bytesRead = 0;
    uint8_t temp = 0;
    try{
        do{
            if (!ReadFile(hSerial, &temp, 1, &bytesRead, NULL)) {
                ShunscomUtils::Logger::getInstance() << "串口读取失败: " <<  std::to_string(GetLastError()) << std::endl;
                return false;
            }

            if(bytesRead>0){
                buffer.push_back(temp);
            }
        } while (temp!=0x7e);
    }
    catch (const std::exception& e) {
        ShunscomUtils::Logger::getInstance() << "串口读取过程中发生异常: " << e.what()<< std::endl;
        return false;
    }
    return true;
}

bool SerialIO::readALL() {
    DWORD bytesRead = 0;
    try {
        do {
            uint8_t tempBuffer[8192]; // 临时缓冲区
            if (!ReadFile(hSerial, tempBuffer, sizeof(tempBuffer), &bytesRead, NULL)) {
                ShunscomUtils::Logger::getInstance() <<"串口读取失败: " << std::to_string(GetLastError()) << std::endl;
                throw std::runtime_error("串口读取失败");
                return false;
            }
            for (DWORD i = 0; i < bytesRead; ++i) {
                dataQueue.push(tempBuffer[i]);
            }
        } while (bytesRead > 0); // 如果有数据读取, 继续读取
    } catch (const std::exception& e) {
        ShunscomUtils::Logger::getInstance() <<"串口读取过程中发生异常: " << e.what() << std::endl;
        return false;
    }
    return true; // 返回新数组
}


// 向串口写入数据
bool SerialIO::write(std::vector<uint8_t> &writeBuf) {
    DWORD bytesWritten;
    // 向串口写入数据
    try{
        if (!WriteFile(hSerial, writeBuf.data(), writeBuf.size(), &bytesWritten, NULL)) {
            ShunscomUtils::Logger::getInstance() << "串口写入失败: " << std::to_string(GetLastError()) << std::endl;
            throw std::runtime_error("串口写入失败");
            return false;
        }
    }catch (std::exception& e) {
        ShunscomUtils::Logger::getInstance() << "串口写入过程中发生异常: " << e.what()<< std::endl;
        return false;
    }
    return true;
}


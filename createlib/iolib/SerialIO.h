#ifndef SERIALIO_H
#define SERIALIO_H

#include <windows.h>
#include <vector>
#include <string>
#include <cstdint>
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <queue>
#include "../utils/logger.h"



class SerialIO {
public:
    // 构造函数，初始化串口
    SerialIO(wchar_t *portName, DWORD inBufferSize = 8192, DWORD outBufferSize = 8192, int baudrate = 115200, bool rts = true, bool dsr = true,unsigned char endCharValue = 0x7e);
    // 析构函数，关闭串口
    ~SerialIO();

    // 持续读取串口数据，直到遇到结尾符
    bool readLine(std::vector<uint8_t> &buffer);
    bool readALL();

    // 写入串口数据
    bool write(std::vector<uint8_t> &writeBuf);

    //清空缓冲区
    bool purgeComm(){
        if (!PurgeComm(hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR)) {
            std::cerr << "Error clearing buffers." << std::endl;
            CloseHandle(hSerial);
            return false;
        }
        return true;
    }

private:
    HANDLE hSerial; // 串口句柄
    bool setPortParams(int baudrate, bool rts, bool dsr); // 设置串口参数
    bool configureTimeouts(); // 配置串口超时参数
    unsigned char endChar; //结尾字符
    std::queue<uint8_t> dataQueue; // 用于存储读取的数据
    size_t tryCount = 4;
};

#endif // SERIALIO_H
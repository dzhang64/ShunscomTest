#ifndef USBIO_H
#define USBIO_H

#include <libusb.h>  // 引入 libusb 库，用于 USB 操作
#include <iostream>
#include <vector>

class USBIO {
public:
    USBIO();  // 构造函数，初始化 USB 环境
    ~USBIO();  // 析构函数，释放 USB 资源

    // 读取数据
    bool read(int readSize, bool decodeHDLC = false);

    // 写入数据
    bool write(const std::vector<unsigned char>& writeBuf, bool encodeHDLC = false);

    // 写入数据后读取并丢弃
    bool writeThenReadDiscard(const std::vector<unsigned char>& writeBuf, int readSize = 0x1000, bool encodeHDLC = false);

    // 根据厂商 ID 和产品 ID 查找设备
    bool probeDeviceByVidPid(uint16_t vid, uint16_t pid);

    // 根据总线和设备地址查找设备
    bool probeDeviceByBusDev(uint8_t bus, uint8_t dev);

    // 猜测设备（基于预定义的厂商 ID）
    bool guessDevice();

    // 获取设备接口
    void claimInterface(int interfaceNum);

    // 设置设备配置
    void setConfiguration(int config);

    // 列出所有 USB 设备
    static void listUsbDevices();

private:
    libusb_device_handle* devHandle;  // 存储 USB 设备句柄
    static libusb_context* ctx;  // libusb 上下文
};

#endif // USBIO_H

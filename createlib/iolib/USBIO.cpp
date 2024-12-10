#include "USBIO.h"
#include <libusb.h>
#include <iostream>


libusb_context *USBIO::ctx = nullptr;  // 定义静态成员变量
// 构造函数，初始化 libusb 环境
USBIO::USBIO() {
    if (libusb_init(&ctx) < 0) {
        std::cerr << "无法初始化 libusb\n";
    }
    devHandle = nullptr;
}

// 析构函数，关闭设备并退出 libusb
USBIO::~USBIO() {
    if (devHandle) {
        libusb_close(devHandle);  // 关闭设备句柄
    }
    libusb_exit(ctx);  // 退出 libusb
}

// 读取数据，decodeHDLC 可选
bool USBIO::read(int readSize, bool decodeHDLC) {
    unsigned char* buffer = new unsigned char[readSize];
    int transferred = 0;

    int ret = libusb_bulk_transfer(devHandle, LIBUSB_ENDPOINT_IN, buffer, readSize, &transferred, 0);
    if (ret < 0) {
        std::cerr << "USB 读取错误\n";
        delete[] buffer;
        return false;
    }

    // 处理 HDLC 解码（若需要）
    if (decodeHDLC) {
        // 解码处理逻辑
    }

    delete[] buffer;
    return true;
}

// 写入数据，encodeHDLC 可选
bool USBIO::write(const std::vector<unsigned char>& writeBuf, bool encodeHDLC) {
    unsigned char* buffer = new unsigned char[writeBuf.size()];
    std::copy(writeBuf.begin(), writeBuf.end(), buffer);

    // 处理 HDLC 编码（若需要）
    if (encodeHDLC) {
        // 编码处理逻辑
    }

    int transferred = 0;
    int ret = libusb_bulk_transfer(devHandle, LIBUSB_ENDPOINT_OUT, buffer, writeBuf.size(), &transferred, 0);
    if (ret < 0) {
        std::cerr << "USB 写入错误\n";
        delete[] buffer;
        return false;
    }

    delete[] buffer;
    return true;
}

// 写入数据后读取并丢弃
bool USBIO::writeThenReadDiscard(const std::vector<unsigned char>& writeBuf, int readSize, bool encodeHDLC) {
    if (!write(writeBuf, encodeHDLC)) {
        return false;
    }
    return read(readSize, encodeHDLC);
}

// 根据厂商 ID 和产品 ID 查找设备
bool USBIO::probeDeviceByVidPid(uint16_t vid, uint16_t pid) {
    devHandle = libusb_open_device_with_vid_pid(ctx, vid, pid);
    if (!devHandle) {
        std::cerr << "设备未找到\n";
        return false;
    }
    return true;
}

// 根据总线和设备地址查找设备
bool USBIO::probeDeviceByBusDev(uint8_t bus, uint8_t dev) {
    // 这里需要通过 bus 和 dev 地址查找设备的代码
    return true;
}

// 猜测设备
bool USBIO::guessDevice() {
    // 尝试猜测常见设备，如厂商 ID 0408 (三星)，1004 (LG) 等
    uint16_t vidList[] = {0x1004, 0x04e8, 0x2931};
    for (auto vid : vidList) {
        devHandle = libusb_open_device_with_vid_pid(ctx, vid, 0);
        if (devHandle) {
            return true;
        }
    }
    std::cerr << "未找到设备\n";
    return false;
}

// 获取设备接口
void USBIO::claimInterface(int interfaceNum) {
    if (libusb_claim_interface(devHandle, interfaceNum) < 0) {
        std::cerr << "无法获取接口\n";
    }
}

// 设置设备配置
void USBIO::setConfiguration(int config) {
    if (libusb_set_configuration(devHandle, config) < 0) {
        std::cerr << "无法设置设备配置\n";
    }
}

// 列出所有 USB 设备
void USBIO::listUsbDevices() {
    if (ctx == nullptr) {
        libusb_init(&ctx);
    }
    libusb_device** devs;
    ssize_t cnt = libusb_get_device_list(ctx, &devs);
    if (cnt < 0) {
        std::cerr << "无法获取设备列表\n";
        return;
    }

    for (ssize_t i = 0; i < cnt; i++) {
        libusb_device* dev = devs[i];
        libusb_device_descriptor desc;
        if (libusb_get_device_descriptor(dev, &desc) < 0) {
            continue;
        }

        std::cout << "设备 ID: " << std::hex << desc.idVendor << ":" << desc.idProduct << std::dec << "\n";
    }
    libusb_free_device_list(devs, 1);
}

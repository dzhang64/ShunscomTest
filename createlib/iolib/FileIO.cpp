#include "FileIO.h"
#include <iostream>

FileIO::FileIO(const std::vector<std::string>& filenames)
        : filenames(filenames) {
    openNextFile();
}

FileIO::~FileIO() {
    if (file.is_open()) {
        file.close();
    }
}

bool FileIO::read(int readSize, bool decodeHDLC) {
    // 从文件读取数据
    char* buffer = new char[readSize];
    file.read(buffer, readSize);
    if (file.gcount() < readSize) {
        std::cerr << "文件读取错误\n";
        delete[] buffer;
        return false;
    }

    // 处理 HDLC 解码
    if (decodeHDLC) {
        // 解码逻辑
    }

    delete[] buffer;
    return true;
}

bool FileIO::write(const std::vector<unsigned char>& writeBuf, bool encodeHDLC) {
    // 写入数据（本例中没有实现写文件的逻辑）
    return true;
}

bool FileIO::writeThenReadDiscard(const std::vector<unsigned char>& writeBuf, int readSize, bool encodeHDLC) {
    // 写入并丢弃读取
    return true;
}

void FileIO::openNextFile() {
    if (file.is_open()) {
        file.close();
    }
    if (!filenames.empty()) {
        file.open(filenames.back(), std::ios::binary);
        filenames.pop_back();
    }
}

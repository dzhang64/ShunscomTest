#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include <vector>
#include <fstream>

class FileIO {
public:
    FileIO(const std::vector<std::string>& filenames);
    ~FileIO();

    bool read(int readSize, bool decodeHDLC = false);
    bool write(const std::vector<unsigned char>& writeBuf, bool encodeHDLC = false);
    bool writeThenReadDiscard(const std::vector<unsigned char>& writeBuf, int readSize, bool encodeHDLC = false);

private:
    std::ifstream file;  // 输入文件流
    std::vector<std::string> filenames;  // 文件名列表

    void openNextFile();  // 打开下一个文件
};

#endif // FILEIO_H

//
// Created by Administrator on 2024/11/21 0021.
//
#include "charutil.h"


wchar_t *ShunscomUtils::ConvertStringToWChar(const std::string &str) {
    // 使用 wavermap 转换 UTF-8 编码的 std::string 到 std::wstring
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wstr = converter.from_bytes(str);

    // 分配 wchar_t 数组内存以保存转换后的字符串
    wchar_t* wcharStr = new wchar_t[wstr.size() + 1]; // +1 用于 null 终止符
    wcscpy(wcharStr, wstr.c_str()); // 复制至 wchar_t
    return wcharStr; // 返回指向 wchar_t 的指针
}



std::vector<uint8_t> ShunscomUtils::parseHexByteArray(const char* input) {
    std::vector<uint8_t> byteArray;
    std::stringstream ss(input);
    std::string byteString;

    while (ss >> byteString) {
        // 移除前缀 '\x' 和解析十六进制数
        if (byteString.size() == 4 && byteString.substr(0, 2) == "\\x") {
            int byteValue;
            std::stringstream hexConverter(byteString.substr(2));
            if (!(hexConverter >> std::hex >> byteValue)) {
                Logger::getInstance() <<"Method:ShunscomUtils::parseHexByteArray" <<"Reason" << "Invalid byte format: " << byteString << std::endl;
                throw std::invalid_argument("Invalid byte format.");
            }
            byteArray.push_back(static_cast<uint8_t>(byteValue));
        } else {
            Logger::getInstance()  << "Invalid format: " << byteString << std::endl;
            throw std::invalid_argument("Invalid format. Expected '\\xhh' format.");
        }
    }
    return byteArray;
}
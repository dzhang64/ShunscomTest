//
// Created by Administrator on 2024/11/14 0014.
//
#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <vector>
#include <cstdint>
#include <algorithm> // For std::find
#include <sstream>
#include <stdexcept>
#include <cstdint>
#include <iomanip>
#include "logger.h"

#ifndef SHUNSCOMTEST_UTIL_H
#define SHUNSCOMTEST_UTIL_H

#endif //SHUNSCOMTEST_UTIL_H

namespace ShunscomUtils {

    std::vector<uint8_t> parseHexByteArray(const char *input);

    wchar_t *ConvertStringToWChar(const std::string &str);

}
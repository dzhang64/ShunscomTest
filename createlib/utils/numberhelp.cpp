//
// Created by Administrator on 2024/11/25 0025.
//

#include "numberhelp.h"

bool ShunscomUtils::containsValue(uint8_t value, const uint8_t* array, size_t length) {
    for (size_t i = 0; i < length; ++i) {
        if (array[i] == value) {
            return true; // 找到了匹配
        }
    }
    return false; // 未找到匹配
}

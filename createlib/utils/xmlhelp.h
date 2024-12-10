//
// Created by Administrator on 2024/11/16 0016.
//
#include <iostream>
#include <map>
#include <string>
#include <cstdint>
#include "tinyxml2.h"
#include "logger.h"
#ifndef SHUNSCOMTEST_XMLHELP_H
#define SHUNSCOMTEST_XMLHELP_H

#endif //SHUNSCOMTEST_XMLHELP_H
namespace ShunscomUtils {

    void getQualCommCommandsFromXml(std::map<std::int32_t , char*> &keyValuePairs,char* fileName);

    bool getQualCommandContentsFromXml(std::map<std::uint8_t , std::map<std::int32_t , char*>> &contentMap,char* fileName);

}

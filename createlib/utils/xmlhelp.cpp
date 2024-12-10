//
// Created by Administrator on 2024/11/21 0021.
//
#include "xmlhelp.h"

void ShunscomUtils::getQualCommCommandsFromXml(std::map<std::int32_t , char*> &keyValuePairs,char* fileName) {
    // 创建 XMLDocument 对象
    tinyxml2::XMLDocument doc;
    // 加载 XML 文件
    tinyxml2::XMLError eResult = doc.LoadFile(fileName); // 请确保 data.xml 在正确的位置
    if (eResult != tinyxml2::XML_SUCCESS) {
        ShunscomUtils::Logger::getInstance()<< "Error loading XML file: " << doc.ErrorIDToName(eResult) << std::endl;
        return;
    }

    // 获取根元素
    tinyxml2::XMLElement *root = doc.RootElement();
    if (root == nullptr) {
        std::cerr << "Error: Empty XML file." << std::endl;
        return;
    }

    // 遍历 Commands 中的每一个 Command 元素
    for (tinyxml2::XMLElement *item = root->FirstChildElement("Command");
         item != nullptr; item = item->NextSiblingElement("Command")) {
        std::int32_t key = item->FirstChildElement("Value")->IntText();
        const char *value = item->FirstChildElement("Name")->GetText();
        if (value != nullptr) {
            char* valueCopy = new char[strlen(value) + 1]; // 分配内存
            strcpy(valueCopy, value); // 拷贝字符串
            keyValuePairs[key] = valueCopy; // 添加到键值对中
        }
    }

}

bool ShunscomUtils::getQualCommandContentsFromXml(std::map<std::uint8_t , std::map<std::int32_t , char*>> &contentMap,char* fileName){

    // 读取XML文件
    tinyxml2::XMLDocument doc;
    if (doc.LoadFile(fileName) != tinyxml2::XML_SUCCESS) {
        ShunscomUtils::Logger::getInstance() << "Failed to load XML file: " << fileName << std::endl;
        return false; // 返回空结果
    }

    // 获取根元素
    tinyxml2::XMLElement* root = doc.RootElement();
    if (root == nullptr) {
        ShunscomUtils::Logger::getInstance()  << "Failed to get root element in XML file: " << fileName << std::endl;
        return false; // 返回空结果
    }

    // 遍历Command元素
    for (tinyxml2::XMLElement* command = root->FirstChildElement("Command"); command != nullptr; command = command->NextSiblingElement("Command")) {
        uint8_t commandValue = command->FirstChildElement("Value")->IntText();
        // 遍历Operation元素（注意这里修正了拼写错误，从"Operatoins"改为"Operations"）
        for (tinyxml2::XMLElement* operation = command->FirstChildElement("Operations")->FirstChildElement("Operation"); operation != nullptr; operation = operation->NextSiblingElement("Operation")) {
            int operationValue = operation->FirstChildElement("Value")->IntText();
            const char  *hexValue = operation->FirstChildElement("Hex")->GetText();
            // 存储到map中
            if (hexValue != nullptr) {
                char* hexValueCopy = new char[strlen(hexValue) + 1]; // 分配内存
                strcpy(hexValueCopy, hexValue); // 拷贝字符串
                contentMap[commandValue][operationValue] = hexValueCopy;
            }
        }
    }
    return true;
}

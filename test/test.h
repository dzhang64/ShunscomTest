//
// Created by Administrator on 2024/11/16 0016.
//
#include <atomic>
#include "../createlib/iolib/USBIO.h"
#include "../createlib/iolib/SerialIO.h"
#include "../createlib/utils//xmlhelp.h"
#include "../createlib/utils/logger.h"
#ifndef SHUNSCOMTEST_TESTSERIAL_H
#define SHUNSCOMTEST_TESTSERIAL_H

#endif //SHUNSCOMTEST_TESTSERIAL_H
namespace ShunToolsTest {
    void testSerial() {
        SerialIO serialIO(L"COM6");
    }

    void testXmlHelp() {
        char* filename = "../resource/qualcomm/qualcommand.xml";
        std::map<std::int32_t , char*> keyValuePairs;
        ShunscomUtils::getQualCommCommandsFromXml(keyValuePairs,filename);
        std::cout << keyValuePairs[18] << std::endl;

    };

    void testXmlHelp2() {
        char* filename = "../resource/qualcomm/qualcommandcontent.xml";
        std::map<std::uint8_t , std::map<std::int32_t , char*>> contentMap;
        ShunscomUtils::getQualCommandContentsFromXml(contentMap,filename);
        std::cout << contentMap[125][3] << std::endl;
        std::cout << "hi" << std::endl;

    };

    void testAtomic() {
        std::atomic_bool flag = true;
        std::cout << flag.load() << std::endl;
        flag.store(false);
        std::cout << flag.load() << std::endl;
    }

    void testLogger() {

        ShunscomUtils::Logger::getInstance()<<"test"<<",hi"<<std::endl;
        ShunscomUtils::Logger::getInstance()<<"test"<<",hi"<<std::endl;
    }


}

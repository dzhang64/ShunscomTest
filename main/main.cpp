#include "../test/test.h"
#include "../createlib/utils/charutil.h"
#include <iomanip>
#include <iostream>
#include <thread>
#include "../createlib/iolib/QualCommDMSerial.h"


int main(int argc, char *argv[]) {

    std::cout << "Hello world!" << std::endl;
    QualCommDmSerial qualCommDmSerial(L"COM6",115200);
    uint8_t types[] = {0x1,0x4,0x5,0x7,0xB};
    for (uint8_t type:types) {
        qualCommDmSerial.registerLog(type);
    }


}

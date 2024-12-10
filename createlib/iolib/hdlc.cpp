

#include "hdlc.h"



static const int ESCAPE_XOR = 0x20;



// Automatically generated CRC function
// polynomial: 0x11021, bit reverse algorithm
static uint16_t calc_crc (uint8_t *data, size_t len, uint16_t crc)
{
    static const uint16_t table[256] = {
    0x0000U,0x1189U,0x2312U,0x329BU,0x4624U,0x57ADU,0x6536U,0x74BFU,
    0x8C48U,0x9DC1U,0xAF5AU,0xBED3U,0xCA6CU,0xDBE5U,0xE97EU,0xF8F7U,
    0x1081U,0x0108U,0x3393U,0x221AU,0x56A5U,0x472CU,0x75B7U,0x643EU,
    0x9CC9U,0x8D40U,0xBFDBU,0xAE52U,0xDAEDU,0xCB64U,0xF9FFU,0xE876U,
    0x2102U,0x308BU,0x0210U,0x1399U,0x6726U,0x76AFU,0x4434U,0x55BDU,
    0xAD4AU,0xBCC3U,0x8E58U,0x9FD1U,0xEB6EU,0xFAE7U,0xC87CU,0xD9F5U,
    0x3183U,0x200AU,0x1291U,0x0318U,0x77A7U,0x662EU,0x54B5U,0x453CU,
    0xBDCBU,0xAC42U,0x9ED9U,0x8F50U,0xFBEFU,0xEA66U,0xD8FDU,0xC974U,
    0x4204U,0x538DU,0x6116U,0x709FU,0x0420U,0x15A9U,0x2732U,0x36BBU,
    0xCE4CU,0xDFC5U,0xED5EU,0xFCD7U,0x8868U,0x99E1U,0xAB7AU,0xBAF3U,
    0x5285U,0x430CU,0x7197U,0x601EU,0x14A1U,0x0528U,0x37B3U,0x263AU,
    0xDECDU,0xCF44U,0xFDDFU,0xEC56U,0x98E9U,0x8960U,0xBBFBU,0xAA72U,
    0x6306U,0x728FU,0x4014U,0x519DU,0x2522U,0x34ABU,0x0630U,0x17B9U,
    0xEF4EU,0xFEC7U,0xCC5CU,0xDDD5U,0xA96AU,0xB8E3U,0x8A78U,0x9BF1U,
    0x7387U,0x620EU,0x5095U,0x411CU,0x35A3U,0x242AU,0x16B1U,0x0738U,
    0xFFCFU,0xEE46U,0xDCDDU,0xCD54U,0xB9EBU,0xA862U,0x9AF9U,0x8B70U,
    0x8408U,0x9581U,0xA71AU,0xB693U,0xC22CU,0xD3A5U,0xE13EU,0xF0B7U,
    0x0840U,0x19C9U,0x2B52U,0x3ADBU,0x4E64U,0x5FEDU,0x6D76U,0x7CFFU,
    0x9489U,0x8500U,0xB79BU,0xA612U,0xD2ADU,0xC324U,0xF1BFU,0xE036U,
    0x18C1U,0x0948U,0x3BD3U,0x2A5AU,0x5EE5U,0x4F6CU,0x7DF7U,0x6C7EU,
    0xA50AU,0xB483U,0x8618U,0x9791U,0xE32EU,0xF2A7U,0xC03CU,0xD1B5U,
    0x2942U,0x38CBU,0x0A50U,0x1BD9U,0x6F66U,0x7EEFU,0x4C74U,0x5DFDU,
    0xB58BU,0xA402U,0x9699U,0x8710U,0xF3AFU,0xE226U,0xD0BDU,0xC134U,
    0x39C3U,0x284AU,0x1AD1U,0x0B58U,0x7FE7U,0x6E6EU,0x5CF5U,0x4D7CU,
    0xC60CU,0xD785U,0xE51EU,0xF497U,0x8028U,0x91A1U,0xA33AU,0xB2B3U,
    0x4A44U,0x5BCDU,0x6956U,0x78DFU,0x0C60U,0x1DE9U,0x2F72U,0x3EFBU,
    0xD68DU,0xC704U,0xF59FU,0xE416U,0x90A9U,0x8120U,0xB3BBU,0xA232U,
    0x5AC5U,0x4B4CU,0x79D7U,0x685EU,0x1CE1U,0x0D68U,0x3FF3U,0x2E7AU,
    0xE70EU,0xF687U,0xC41CU,0xD595U,0xA12AU,0xB0A3U,0x8238U,0x93B1U,
    0x6B46U,0x7ACFU,0x4854U,0x59DDU,0x2D62U,0x3CEBU,0x0E70U,0x1FF9U,
    0xF78FU,0xE606U,0xD49DU,0xC514U,0xB1ABU,0xA022U,0x92B9U,0x8330U,
    0x7BC7U,0x6A4EU,0x58D5U,0x495CU,0x3DE3U,0x2C6AU,0x1EF1U,0x0F78U,
    };

    crc = crc ^ 0xFFFFU;
    while (len > 0)
    {
        crc = table[*data ^ (uint8_t)crc] ^ (crc >> 8);
        data++;
        len--;
    }
    crc = crc ^ 0xFFFFU;
    return crc;
}

std::vector<uint8_t> ShunscomUtils::encode_hdlc_frame(std::vector<uint8_t> &payld) {
    std::vector<uint8_t> retvec;
    size_t length = payld.size();
    uint16_t crc16 = calc_crc(payld.data(), length, 0); // 计算 CRC 校验值
    for (int i = 0; i < length + 2; i++) {
        uint8_t c;
        if (i < length)
            c = payld[i]; // 从输入向量获取数据
        else if (i == length)   // little endian
            c = crc16 & 0x00FF;
        else
            c = (crc16 & 0xFF00) >> 8;
        if (c == 0x7d || c == 0x7e) {
            retvec.push_back(0x7d); // 添加转义字节
            retvec.push_back(c ^ ESCAPE_XOR); // 进行转义处理
        } else {
            retvec.push_back(c); // 添加原字节
        }
    }

    retvec.push_back(0x7e); // 添加结束帧标志
    return retvec;
}

std::vector<uint8_t>  ShunscomUtils::hdlc_decapsulate(std::vector<uint8_t>& payload) {
    // Check the message length
    if (payload.size() < 3) {
        ShunscomUtils::Logger::getInstance() << "Ignoring (partial?) frame: Too short." << std::endl;
        throw std::runtime_error("串口读取失败");
    }
    std::vector<uint8_t> frame(payload.begin(), payload.end() - 1); // Remove trailer
    std::vector<uint8_t> unescaped;
    for (size_t i = 0; i < frame.size(); ++i) {
        if (frame[i] == ESCAPE_XOR && (i + 1) < frame.size()) {
            uint8_t nextByte = frame[i + 1] ^ 0x20;
            unescaped.push_back(nextByte);
            ++i; // Skip the next byte as it was part of the escape sequence
        } else {
            unescaped.push_back(frame[i]);
        }
    }
    // Check the CRC16
    if (unescaped.size() < 2) {
        ShunscomUtils::Logger::getInstance() << "Ignoring (partial?) frame: Too short." << std::endl;
        throw std::runtime_error("串口读取失败");
    }
    uint16_t receivedCrc = unescaped[unescaped.size() - 2] | (unescaped[unescaped.size() - 1]<<8);
    unescaped.resize(unescaped.size() - 2); // Remove CRC
    uint16_t calculatedCrc = calc_crc(unescaped.data(), unescaped.size(), 0);
    if (receivedCrc != calculatedCrc) {
        ShunscomUtils::Logger::getInstance() << "Ignoring (partial?) frame: Wrong CRC. "
                  << "Received: "  << std::to_string(receivedCrc)
                  << " Calculated: " << std::to_string(calculatedCrc) << std::endl;
        throw std::runtime_error("Incorrect CRC");
    }
    return unescaped;
}

/*static std::string buffer;*/

/*void
ShunscomUtils::feed_binary (const char *b, int length) {
    buffer.append(b, length);
}

void
ShunscomUtils::reset_binary() {
    buffer.clear();
}

static void
unescape (std::string& frame) {
    bool esc = false;
    std::string output;
    for (size_t i = 0; i < frame.size(); i++) {
        if (esc) {
            output.append(1, char(frame[i] ^ ESCAPE_XOR));
            esc = false;
        } else if (frame[i] == '\x7d') {
            esc = true;
        } else {
            output.append(1, frame[i]);
        }
    }
    frame = output;
    return;
}

// Return: if there is new frame or not
bool
ShunscomUtils::get_next_frame(std::string& output_frame, bool& crc_correct) {
    size_t delim = buffer.find('\x7e');
    if (delim == std::string::npos)
        return false;
    output_frame = buffer.substr(0, delim);
    buffer.erase(0, delim + 1);

    unescape(output_frame);
    if (output_frame.size() <= 2) {
        crc_correct = false;
        return true;
    }
    // little endian
    uint16_t b1 = output_frame[output_frame.size() - 1] & 0xFF;
    uint16_t b2 = output_frame[output_frame.size() - 2] & 0xFF;
    uint16_t frame_crc16 = (b1 << 8) + b2;
    output_frame.erase(output_frame.size() - 2);

    uint16_t crc16 = calc_crc((uint8_t *) output_frame.c_str(), output_frame.size(), 0);

    crc_correct = (frame_crc16 == crc16);
    return true;
}

void
check_frame_format (std::string& output_frame) {
    size_t delim = output_frame.find("\x98\x01\x00\x00\x01\00\x00\x00");
    if (delim == 0) {
        output_frame.erase(0, 8);
    }
}*/

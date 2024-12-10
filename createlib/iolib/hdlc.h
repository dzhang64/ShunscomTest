#ifndef __DM_COLLECTOR_C_HDLC_H__
#define __DM_COLLECTOR_C_HDLC_H__

#include <string>
#include <vector>
#include <cstdint>
#include "../utils/logger.h"
#include <string>
#include <stdexcept>
namespace ShunscomUtils {
    std::vector<uint8_t> encode_hdlc_frame(std::vector<uint8_t> &payld);

    std::vector<uint8_t> hdlc_decapsulate(std::vector<uint8_t> &payload);

/*    void feed_binary(const char *b, int length);

    void reset_binary();

    bool get_next_frame(std::string &frame);*/
}
#endif // __DM_COLLECTOR_C_HDLC_H__
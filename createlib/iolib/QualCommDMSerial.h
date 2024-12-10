//
// Created by Administrator on 2024/11/18 0018.
//

#ifndef SHUNSCOMTEST_QUALCOMMDMSERIAL_H
#define SHUNSCOMTEST_QUALCOMMDMSERIAL_H

#endif //SHUNSCOMTEST_QUALCOMMDMSERIAL_H
#include "SerialIO.h"
#include "hdlc.h"
#include <mutex>
#include <condition_variable>
#include <thread>
#include <map>
#include <unordered_map>
#include "../utils/logger.h"
#include "../utils/qualcommcommand.h"
#include "../utils/numberhelp.h"
#include "../utils/xmlhelp.h"
#include "../utils/charutil.h"



class QualCommDmSerial{
    private:
        SerialIO* serialIO;
        uint8_t opcode;
        unsigned char* payload;
        bool logged = false;
        std::ofstream outFile;
        std::mutex mutex_; // 用于保护共享资源
        std::condition_variable event_diag_response_received; // 条件变量






    public:
        QualCommDmSerial(wchar_t *portName, int baudRate);
        void read();
        void dispatch_received_diag_packet(std::vector<uint8_t> unframed_diag_packet);
        bool sendAndReceive(std::vector<uint8_t>& request,std::vector<uint8_t> &response);
        bool registerLog(uint8_t typeID);
        ~QualCommDmSerial();
        void dispatch_diag_message(uint8_t opcode, const uint8_t *payload, size_t length);
        void dispatch_diag_response(const std::vector<uint8_t>& vector1, size_t length);
        bool start_log(const std::string& directory = "");
        bool stop_log();
        int DIAG_MAX_RETRANSMITS = 3;
        int DIAG_RESPONSE_TIMEOUT_MS = 3000;
        uint8_t ErrorCode[7]  = {QualcommCommand::DIAG_BAD_CMD_F, QualcommCommand::DIAG_BAD_PARM_F, QualcommCommand::DIAG_BAD_LEN_F,
                             QualcommCommand::DIAG_BAD_MODE_F, QualcommCommand::DIAG_BAD_SPC_MODE_F, QualcommCommand::DIAG_BAD_SEC_MODE_F,
                             QualcommCommand::DIAG_BAD_TRANS_F};
        std::map<std::uint8_t , std::map<std::int32_t , char*>> qualcommCommandContents;
        std::vector<uint8_t> fillLogMask(uint32_t log_type, uint32_t num_bits, uint32_t bit_value,
                                                    const std::vector<uint32_t> &limit_registered_logs);
        std::vector<uint32_t> parseLogMasks(const std::vector<uint8_t>& payload);
        std::unordered_map<uint8_t, uint32_t> log_types = {
                {0x1, 3665}, //1X
                {0x4, 2320}, //WCDMA
                {0x5, 1056}, //GSM
                {0x7, 1279}, //UMTS
                {0xB, 2559}, //LTE,5G
        };


    bool sendCommand(std::vector<uint8_t> &request);
};



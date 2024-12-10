#include "QualCommDMSerial.h"


QualCommDmSerial::QualCommDmSerial(wchar_t *portName, int baudRate) {
    serialIO = new SerialIO(portName, 8192, 8192, baudRate, true, true,0x7E);
    bool result = ShunscomUtils::getQualCommandContentsFromXml(qualcommCommandContents,"../resource/qualcomm/qualcommandcontent.xml");
    if(!result){
        ShunscomUtils::Logger::getInstance()<< "无法加载高通命令配置文件: " << std::endl;
        throw std::runtime_error("无法加载高通命令配置文件");
    }

}

QualCommDmSerial::~QualCommDmSerial() {
    serialIO->~SerialIO();
}

void QualCommDmSerial::read() {
    if(serialIO!= nullptr){
        while(true){
            try {
                serialIO->readALL();
                /*std::vector<uint8_t> unframed_message = ShunscomUtils::encode_hdlc_frame(readData);
                dispatch_received_diag_packet(unframed_message);*/
            }catch (std::exception &e){
                ShunscomUtils::Logger::getInstance()<< "记录log时读取log发生错误:" << e.what() << std::endl;
            }
        }
    }
}

void QualCommDmSerial::dispatch_received_diag_packet(std::vector<uint8_t> unframed_diag_packet) {
    size_t length = unframed_diag_packet.size();
    opcode = unframed_diag_packet[0];
    payload = unframed_diag_packet.data() + 1;
    size_t payload_length = length - 1;
    if (opcode == QualcommCommand::Command::DIAG_LOG_F) {
        // Extract the outer header and inner packet
        uint16_t outer_header;
        std::memcpy(&outer_header, payload+1, sizeof(outer_header));
        uint16_t inner_header;
        std::memcpy(&inner_header, payload+3, sizeof(inner_header));
        uint16_t log_type;
        std::memcpy(&log_type, payload+5, sizeof(log_type));
        uint64_t log_time;
        std::memcpy(&log_time, payload+7, sizeof(log_time));
        if(logged){
            outFile.write((char*)(payload+3), length - 3);
        }

    } else if (opcode == QualcommCommand::Command::DIAG_MULTI_RADIO_CMD_F) {
        // Handle multi radio command
        if (payload_length > 7) {
            std::vector<uint8_t> new_diag_packet(unframed_diag_packet.begin() + 6, unframed_diag_packet.end());
            dispatch_received_diag_packet(new_diag_packet);
        };
    } else if (opcode == QualcommCommand::Command::DIAG_MSG_F ||
               opcode == QualcommCommand::Command::DIAG_EXT_MSG_F ||
               opcode == QualcommCommand::Command::DIAG_EXT_MSG_TERSE_F ||
               opcode == QualcommCommand::Command::DIAG_QSR_EXT_MSG_TERSE_F ||
               opcode == QualcommCommand::Command::DIAG_QSR4_EXT_MSG_TERSE_F) {
        // Dispatch message
        dispatch_diag_message(opcode, payload, payload_length);
    } else {
        // Dispatch response
        dispatch_diag_response(unframed_diag_packet, length);
    }
}



void QualCommDmSerial::dispatch_diag_message(uint8_t opcode, const uint8_t *payload, size_t length) {

}

void QualCommDmSerial::dispatch_diag_response(const std::vector<uint8_t>& unframed_diag_packet, size_t length) {
    std::lock_guard<std::mutex> lock(mutex_);
    event_diag_response_received.notify_all(); // 通知所有等待的线程
}



bool QualCommDmSerial::stop_log() {
    if (!logged) {
        ShunscomUtils::Logger::getInstance()<< "尚未开始记录高通LOG" << std::endl;
        return false;
    }
    outFile.close();
    logged = false;
    ShunscomUtils::Logger::getInstance()<< "关闭记录高通LOG" << std::endl;
}

bool QualCommDmSerial::start_log(const std::string &directory) {
    if(logged){
        ShunscomUtils::Logger::getInstance()<< "已开始记录高通LOG" << std::endl;
        return false;
    }
    // 如果目录为空，设置为当前程序目录下的log文件夹
    std::string finalDirectory = directory.empty() ? (std::filesystem::current_path().string() + "/testlog") : directory;
    std::time_t now = std::time(nullptr);
    std::tm tmNow = *std::localtime(&now);
    std::ostringstream oss;
    oss << "log_" << std::put_time(&tmNow, "%Y-%m-%d_%H-%M-%S") << ".dlf"; // 默认格式
    std::string  logFileName = finalDirectory + "/" + oss.str(); // 完整路径
    //创建一个文件Handle
    outFile.open(logFileName, std::ios::binary);
    if (!outFile.is_open()) {
        ShunscomUtils::Logger::getInstance()<< "无法打开高通LOG: " << logFileName << std::endl;
        return false;
    }
    logged = true;
    return true;
}

bool QualCommDmSerial::sendAndReceive(std::vector<uint8_t>& request,std::vector<uint8_t> &response) {
    bool success = false;
    std::vector<uint8_t> sendFrame = ShunscomUtils::encode_hdlc_frame(request);
    std::unique_lock<std::mutex> lock(mutex_);
    for (int i = 0; i < DIAG_MAX_RETRANSMITS; i++) {
        bool result = serialIO->write(sendFrame);
        if(result){
            serialIO->readLine(response);
            if(response.at(0)==request.at(0)){
                success = true;
                break;
            }else{
                serialIO->purgeComm();
            }
        }
    }
    return success;
}

bool QualCommDmSerial::sendCommand(std::vector<uint8_t>& request) {
    std::vector<uint8_t> sendFrame = ShunscomUtils::encode_hdlc_frame(request);
    std::unique_lock<std::mutex> lock(mutex_);
    bool result = serialIO->write(sendFrame);
    return result;
}

bool QualCommDmSerial::registerLog(uint8_t typeID) {
    bool result =  false;
    try{
        uint32_t maskValue = log_types[typeID];
        if(maskValue==0){
            ShunscomUtils::Logger::getInstance()<< "LOG类型不存在" << std::endl;
            return false;
        }

        std::vector<uint8_t> request;
        std::vector<uint8_t>  mask_bits = fillLogMask(typeID,maskValue,1,std::vector<uint32_t>());
        request.push_back(QualcommCommand::Command::DIAG_LOG_CONFIG_F);
        request.push_back(0x00);
        request.push_back(0x00);
        request.push_back(0x00);
        request.push_back(0x03);
        request.push_back(0x00);
        request.push_back(0x00);
        request.push_back(0x00);
        request.push_back(typeID);
        request.push_back(0x00);
        request.push_back(0x00);
        request.push_back(0x00);
        uint8_t* log_mask_value = reinterpret_cast<uint8_t *>(&maskValue);
        request.push_back(log_mask_value[0]);
        request.push_back(log_mask_value[1]);
        request.push_back(log_mask_value[2]);
        request.push_back(log_mask_value[3]);
        request.insert(request.end(), mask_bits.rbegin(), mask_bits.rend());
        result = sendCommand(request);
        request.clear();
        if(!result){
            ShunscomUtils::Logger::getInstance()<< "注册LOG类型失败" << std::endl;
            throw std::runtime_error("注册LOG类型失败");
        }

    }catch (std::exception &e){
        ShunscomUtils::Logger::getInstance()<< "注册LOG类型发生错误:" << e.what() << std::endl;
    }
    return result;
}

std::vector<uint8_t> QualCommDmSerial::fillLogMask(uint32_t log_type, uint32_t num_bits, uint32_t bit_value,
                                                   const std::vector<uint32_t> &limit_registered_logs) {
    // 初始化一个字节数组，用于存储日志掩码
    std::vector<uint8_t> log_mask;
    // 当前字节的值，初始为0
    uint8_t current_byte = 0;
    // 已写入的位数计数器，初始为0
    uint32_t num_bits_written = 0;
    // 遍历指定数量的位
    for (uint32_t i = 0; i < num_bits; ++i) {
        bool enable_this_log_type = true;
        // 检查是否存在限制注册日志，如果存在则对当前日志类型进行过滤
        if (!limit_registered_logs.empty() &&
            std::find(limit_registered_logs.begin(), limit_registered_logs.end(), (log_type << 12) | i) == limit_registered_logs.end()) {
            // 如果当前日志类型未被注册，设置标志为False
            enable_this_log_type = false;
        }
        // 将当前位的值设置到当前字节的相应位置上
        current_byte |= (bit_value & enable_this_log_type) << num_bits_written;
        // 增加已经写入的位数计数
        num_bits_written++;
        // 如果当前字节已经写满8位或者是最后一个位，进行字节的存储
        if (num_bits_written == 8 || i == num_bits - 1) {
            // 将当前字节添加到日志掩码中
            log_mask.push_back(current_byte);
            // 重置当前字节和已写入位数计数
            current_byte = 0;
            num_bits_written = 0;
        }
    }
    // 返回生成的日志掩码
    return log_mask;
}

std::vector<uint32_t> QualCommDmSerial::parseLogMasks(const  std::vector<uint8_t> &payload) {
    uint32_t header_size = 12;
    std::vector<uint32_t> log_masks(16); // 初始化一个大小为 16 的 vector
    // 检查 payload 是否足够大
    if (payload.size() < header_size + log_masks.size() * sizeof(uint32_t)) {
        std::cerr << "Payload is too small!" << std::endl;
        return {}; // 返回一个空 vector
    }
    // 使用 memcpy 复制数据
    uint8_t* log_masks_ptr = const_cast<uint8_t *>(payload.data());
    std::memcpy(log_masks.data(), payload.data() + header_size, log_masks.size() * sizeof(uint32_t));
    uint32_t* log_masks_ptr1 = const_cast<uint32_t *>(log_masks.data());
    return log_masks; // 返回解析结果
}







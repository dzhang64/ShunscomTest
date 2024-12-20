//
// Created by Administrator on 2024/11/24 0024.
//

#ifndef SHUNSCOMTEST_QUALCOMMCOMMAND_H
#define SHUNSCOMTEST_QUALCOMMCOMMAND_H

#endif //SHUNSCOMTEST_QUALCOMMCOMMAND_H
namespace QualcommCommand {
    enum Command : uint8_t {
        DIAG_VERNO_F = 0,

        DIAG_ESN_F = 1,

        DIAG_PEEKB_F = 2,

        DIAG_PEEKW_F = 3,

        DIAG_PEEKD_F = 4,

        DIAG_POKEB_F = 5,

        DIAG_POKEW_F = 6,

        DIAG_POKED_F = 7,

        DIAG_OUTP_F = 8,

        DIAG_OUTPW_F = 9,

        DIAG_INP_F = 10,

        DIAG_INPW_F = 11,

        DIAG_STATUS_F = 12,

        DIAG_LOGMASK_F = 15,

        DIAG_LOG_F = 16,

        DIAG_NV_PEEK_F = 17,

        DIAG_NV_POKE_F = 18,

        DIAG_BAD_CMD_F = 19,

        DIAG_BAD_PARM_F = 20,

        DIAG_BAD_LEN_F = 21,

        DIAG_BAD_MODE_F = 24,

        DIAG_TAGRAPH_F = 25,

        DIAG_MARKOV_F = 26,

        DIAG_MARKOV_RESET_F = 27,

        DIAG_DIAG_VER_F = 28,

        DIAG_TS_F = 29,

        DIAG_TA_PARM_F = 30,

        DIAG_MSG_F = 31,

        DIAG_HS_KEY_F = 32,

        DIAG_HS_LOCK_F = 33,

        DIAG_HS_SCREEN_F = 34,

        DIAG_PARM_SET_F = 36,

        DIAG_NV_READ_F = 38,
        DIAG_NV_WRITE_F = 39,

        DIAG_CONTROL_F = 41,

        DIAG_ERR_READ_F = 42,

        DIAG_ERR_CLEAR_F = 43,

        DIAG_SER_RESET_F = 44,

        DIAG_SER_REPORT_F = 45,

        DIAG_TEST_F = 46,

        DIAG_GET_DIPSW_F = 47,

        DIAG_SET_DIPSW_F = 48,

        DIAG_VOC_PCM_LB_F = 49,

        DIAG_VOC_PKT_LB_F = 50,

        DIAG_ORIG_F = 53,
        DIAG_END_F = 54,

        DIAG_SW_VERSION_F = 56,

        DIAG_DLOAD_F = 58,
        DIAG_TMOB_F = 59,
        DIAG_FTM_CMD_F = 59,

        DIAG_EXT_SW_VERSION_F = 60,

        DIAG_TEST_STATE_F = 61,

        DIAG_STATE_F = 63,

        DIAG_PILOT_SETS_F = 64,

        DIAG_SPC_F = 65,

        DIAG_BAD_SPC_MODE_F = 66,

        DIAG_PARM_GET2_F = 67,

        DIAG_SERIAL_CHG_F = 68,

        DIAG_PASSWORD_F = 70,

        DIAG_BAD_SEC_MODE_F = 71,

        DIAG_PR_LIST_WR_F = 72,

        DIAG_PR_LIST_RD_F = 73,

        DIAG_SUBSYS_CMD_F = 75,

        DIAG_FEATURE_QUERY_F = 81,

        DIAG_SMS_READ_F = 83,

        DIAG_SMS_WRITE_F = 84,

        DIAG_SUP_FER_F = 85,

        DIAG_SUP_WALSH_CODES_F = 86,

        DIAG_SET_MAX_SUP_CH_F = 87,

        DIAG_PARM_GET_IS95B_F = 88,

        DIAG_FS_OP_F = 89,

        DIAG_AKEY_VERIFY_F = 90,

        DIAG_BMP_HS_SCREEN_F = 91,

        DIAG_CONFIG_COMM_F = 92,

        DIAG_EXT_LOGMASK_F = 93,

        DIAG_EVENT_REPORT_F = 96,

        DIAG_STREAMING_CONFIG_F = 97,

        DIAG_PARM_RETRIEVE_F = 98,

        DIAG_STATUS_SNAPSHOT_F = 99,

        DIAG_RPC_F = 100,

        DIAG_GET_PROPERTY_F = 101,

        DIAG_PUT_PROPERTY_F = 102,

        DIAG_GET_GUID_F = 103,

        DIAG_USER_CMD_F = 104,

        DIAG_GET_PERM_PROPERTY_F = 105,

        DIAG_PUT_PERM_PROPERTY_F = 106,

        DIAG_PERM_USER_CMD_F = 107,

        DIAG_GPS_SESS_CTRL_F = 108,

        DIAG_GPS_GRID_F = 109,

        DIAG_GPS_STATISTICS_F = 110,

        DIAG_ROUTE_F = 111,

        DIAG_IS2000_STATUS_F = 112,

        DIAG_RLP_STAT_RESET_F = 113,

        DIAG_TDSO_STAT_RESET_F = 114,

        DIAG_LOG_CONFIG_F = 115,

        DIAG_TRACE_EVENT_REPORT_F = 116,

        DIAG_SBI_READ_F = 117,

        DIAG_SBI_WRITE_F = 118,

        DIAG_SSD_VERIFY_F = 119,

        DIAG_LOG_ON_DEMAND_F = 120,

        DIAG_EXT_MSG_F = 121,

        DIAG_ONCRPC_F = 122,

        DIAG_PROTOCOL_LOOPBACK_F = 123,

        DIAG_EXT_BUILD_ID_F = 124,

        DIAG_EXT_MSG_CONFIG_F = 125,

        DIAG_EXT_MSG_TERSE_F = 126,

        DIAG_EXT_MSG_TERSE_XLATE_F = 127,

        DIAG_SUBSYS_CMD_VER_2_F = 128,

        DIAG_EVENT_MASK_GET_F = 129,

        DIAG_EVENT_MASK_SET_F = 130,

        DIAG_CHANGE_PORT_SETTINGS_F = 140,

        DIAG_CNTRY_INFO_F = 141,

        DIAG_SUPS_REQ_F = 142,

        DIAG_MMS_ORIG_SMS_REQUEST_F = 143,

        DIAG_MEAS_MODE_F = 144,

        DIAG_MEAS_REQ_F = 145,

        DIAG_QSR_EXT_MSG_TERSE_F = 146,

        DIAG_DCI_CMD_REQ_F = 147,

        DIAG_DCI_DELAYED_RSP_F = 148,

        DIAG_BAD_TRANS_F = 149,

        DIAG_SSM_DISALLOWED_CMD_F = 150,

        DIAG_LOG_ON_DEMAND_EXT_F = 151,

        DIAG_MULTI_RADIO_CMD_F = 152,

        DIAG_QSR4_EXT_MSG_TERSE_F = 153,

        DIAG_DCI_CONTROL_PACKET = 154,

        DIAG_COMPRESSED_PKT = 155,

        DIAG_MSG_SMALL_F = 156,

        DIAG_QSH_TRACE_PAYLOAD_F = 157,

        DIAG_MAX_F = 157,
    };



}
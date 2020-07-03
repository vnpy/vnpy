/* ===================================================================
 * 新股配号、中签记录信息 (OesLotWinningBaseInfo) 定义
 * =================================================================== */

/**
 * 新股配号、中签记录信息的内容定义
 */
#define __OES_LOT_WINNING_BASE_INFO_PKT                 \
        /** 证券账户 */ \
        char            invAcctId[OES_INV_ACCT_ID_MAX_LEN]; \
        /** 配号代码/中签代码 */ \
        char            securityId[OES_SECURITY_ID_MAX_LEN]; \
        /** 市场代码 @see eOesMarketIdT */ \
        uint8           mktId; \
        /** 记录类型 @see eOesLotTypeT */ \
        uint8           lotType; \
        /**
         * 失败原因, 当且仅当 lotType 为 OES_LOT_TYPE_FAILED 时此字段有效
         * @see eOesLotRejReasonT
         */ \
        uint8           rejReason; \
        /** 按64位对齐填充域 */ \
        int8            __LOT_WINNING_BASE_INFO_filler; \
        /** 配号日期/中签日期 (格式为 YYYYMMDD, 形如 20160830) */ \
        int32           lotDate; \
        \
        /** 证券名称 */ \
        char            securityName[OES_SECURITY_NAME_MAX_LEN]; \
        \
        /** 配号首个号码。当为中签记录时此字段固定为0 */ \
        int64           assignNum; \
        /** 配号成功数量/中签股数 */ \
        int32           lotQty; \
        /** 最终发行价, 单位精确到元后四位, 即1元 = 10000。当为配号记录时此字段值固定为0 */ \
        int32           lotPrice; \
        /** 中签金额, 单位精确到元后四位, 即1元 = 10000。当为配号记录时此字段值固定为0 */ \
        int64           lotAmt


/* 结构体的初始化值定义 */
#define __NULLOBJ_OES_LOT_WINNING_BASE_INFO_PKT         \
        {0}, {0}, \
        0, 0, 0, 0, 0, \
        {0}, \
        0, 0, 0, 0
/* -------------------------           */
"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""


"""
High level IB message info.
"""


# field types
INT = 1
STR = 2
FLT = 3


# incoming msg id's
class IN:
    TICK_PRICE                = 1
    TICK_SIZE                 = 2
    ORDER_STATUS              = 3
    ERR_MSG                   = 4
    OPEN_ORDER                = 5
    ACCT_VALUE                = 6
    PORTFOLIO_VALUE           = 7
    ACCT_UPDATE_TIME          = 8
    NEXT_VALID_ID             = 9
    CONTRACT_DATA             = 10
    EXECUTION_DATA            = 11
    MARKET_DEPTH              = 12
    MARKET_DEPTH_L2           = 13
    NEWS_BULLETINS            = 14
    MANAGED_ACCTS             = 15
    RECEIVE_FA                = 16
    HISTORICAL_DATA           = 17
    BOND_CONTRACT_DATA        = 18
    SCANNER_PARAMETERS        = 19
    SCANNER_DATA              = 20
    TICK_OPTION_COMPUTATION   = 21
    TICK_GENERIC              = 45
    TICK_STRING               = 46
    TICK_EFP                  = 47
    CURRENT_TIME              = 49
    REAL_TIME_BARS            = 50
    FUNDAMENTAL_DATA          = 51
    CONTRACT_DATA_END         = 52
    OPEN_ORDER_END            = 53
    ACCT_DOWNLOAD_END         = 54
    EXECUTION_DATA_END        = 55
    DELTA_NEUTRAL_VALIDATION  = 56
    TICK_SNAPSHOT_END         = 57
    MARKET_DATA_TYPE          = 58
    COMMISSION_REPORT         = 59
    POSITION_DATA             = 61
    POSITION_END              = 62
    ACCOUNT_SUMMARY           = 63
    ACCOUNT_SUMMARY_END       = 64
    VERIFY_MESSAGE_API        = 65
    VERIFY_COMPLETED          = 66
    DISPLAY_GROUP_LIST        = 67
    DISPLAY_GROUP_UPDATED     = 68
    VERIFY_AND_AUTH_MESSAGE_API = 69
    VERIFY_AND_AUTH_COMPLETED   = 70
    POSITION_MULTI            = 71
    POSITION_MULTI_END        = 72
    ACCOUNT_UPDATE_MULTI      = 73
    ACCOUNT_UPDATE_MULTI_END  = 74
    SECURITY_DEFINITION_OPTION_PARAMETER = 75
    SECURITY_DEFINITION_OPTION_PARAMETER_END = 76
    SOFT_DOLLAR_TIERS         = 77
    FAMILY_CODES              = 78
    SYMBOL_SAMPLES            = 79
    MKT_DEPTH_EXCHANGES       = 80
    TICK_REQ_PARAMS           = 81
    SMART_COMPONENTS          = 82
    NEWS_ARTICLE              = 83
    TICK_NEWS                 = 84
    NEWS_PROVIDERS            = 85
    HISTORICAL_NEWS           = 86
    HISTORICAL_NEWS_END       = 87
    HEAD_TIMESTAMP            = 88
    HISTOGRAM_DATA            = 89
    HISTORICAL_DATA_UPDATE    = 90
    REROUTE_MKT_DATA_REQ      = 91
    REROUTE_MKT_DEPTH_REQ     = 92
    MARKET_RULE               = 93
    PNL                       = 94
    PNL_SINGLE                = 95
    HISTORICAL_TICKS          = 96
    HISTORICAL_TICKS_BID_ASK  = 97
    HISTORICAL_TICKS_LAST     = 98
    TICK_BY_TICK              = 99
    ORDER_BOUND               = 100

# outgoing msg id's
class OUT:
    REQ_MKT_DATA                  = 1
    CANCEL_MKT_DATA               = 2
    PLACE_ORDER                   = 3
    CANCEL_ORDER                  = 4
    REQ_OPEN_ORDERS               = 5
    REQ_ACCT_DATA                 = 6
    REQ_EXECUTIONS                = 7
    REQ_IDS                       = 8
    REQ_CONTRACT_DATA             = 9
    REQ_MKT_DEPTH                 = 10
    CANCEL_MKT_DEPTH              = 11
    REQ_NEWS_BULLETINS            = 12
    CANCEL_NEWS_BULLETINS         = 13
    SET_SERVER_LOGLEVEL           = 14
    REQ_AUTO_OPEN_ORDERS          = 15
    REQ_ALL_OPEN_ORDERS           = 16
    REQ_MANAGED_ACCTS             = 17
    REQ_FA                        = 18
    REPLACE_FA                    = 19
    REQ_HISTORICAL_DATA           = 20
    EXERCISE_OPTIONS              = 21
    REQ_SCANNER_SUBSCRIPTION      = 22
    CANCEL_SCANNER_SUBSCRIPTION   = 23
    REQ_SCANNER_PARAMETERS        = 24
    CANCEL_HISTORICAL_DATA        = 25
    REQ_CURRENT_TIME              = 49
    REQ_REAL_TIME_BARS            = 50
    CANCEL_REAL_TIME_BARS         = 51
    REQ_FUNDAMENTAL_DATA          = 52
    CANCEL_FUNDAMENTAL_DATA       = 53
    REQ_CALC_IMPLIED_VOLAT        = 54
    REQ_CALC_OPTION_PRICE         = 55
    CANCEL_CALC_IMPLIED_VOLAT     = 56
    CANCEL_CALC_OPTION_PRICE      = 57
    REQ_GLOBAL_CANCEL             = 58
    REQ_MARKET_DATA_TYPE          = 59
    REQ_POSITIONS                 = 61
    REQ_ACCOUNT_SUMMARY           = 62
    CANCEL_ACCOUNT_SUMMARY        = 63
    CANCEL_POSITIONS              = 64
    VERIFY_REQUEST                = 65
    VERIFY_MESSAGE                = 66
    QUERY_DISPLAY_GROUPS          = 67
    SUBSCRIBE_TO_GROUP_EVENTS     = 68
    UPDATE_DISPLAY_GROUP          = 69
    UNSUBSCRIBE_FROM_GROUP_EVENTS = 70
    START_API                     = 71
    VERIFY_AND_AUTH_REQUEST       = 72
    VERIFY_AND_AUTH_MESSAGE       = 73
    REQ_POSITIONS_MULTI           = 74
    CANCEL_POSITIONS_MULTI        = 75
    REQ_ACCOUNT_UPDATES_MULTI     = 76
    CANCEL_ACCOUNT_UPDATES_MULTI  = 77
    REQ_SEC_DEF_OPT_PARAMS        = 78
    REQ_SOFT_DOLLAR_TIERS         = 79
    REQ_FAMILY_CODES              = 80
    REQ_MATCHING_SYMBOLS          = 81
    REQ_MKT_DEPTH_EXCHANGES       = 82
    REQ_SMART_COMPONENTS          = 83
    REQ_NEWS_ARTICLE              = 84
    REQ_NEWS_PROVIDERS            = 85
    REQ_HISTORICAL_NEWS           = 86
    REQ_HEAD_TIMESTAMP            = 87
    REQ_HISTOGRAM_DATA            = 88
    CANCEL_HISTOGRAM_DATA         = 89
    CANCEL_HEAD_TIMESTAMP         = 90
    REQ_MARKET_RULE               = 91
    REQ_PNL                       = 92
    CANCEL_PNL                    = 93
    REQ_PNL_SINGLE                = 94
    CANCEL_PNL_SINGLE             = 95
    REQ_HISTORICAL_TICKS          = 96
    REQ_TICK_BY_TICK_DATA         = 97
    CANCEL_TICK_BY_TICK_DATA      = 98

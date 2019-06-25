from typing import Dict, Tuple

from vnpy.api.tora.vntora import TORA_TSTP_D_Buy, TORA_TSTP_D_Sell, TORA_TSTP_EXD_SSE, \
    TORA_TSTP_EXD_SZSE, TORA_TSTP_OPT_LimitPrice, TORA_TSTP_OST_AllTraded, TORA_TSTP_OST_Canceled, \
    TORA_TSTP_OST_NoTradeQueueing, TORA_TSTP_OST_PartTradedQueueing, TORA_TSTP_OST_Unknown, \
    TORA_TSTP_PID_SHBond, TORA_TSTP_PID_SHFund, TORA_TSTP_PID_SHStock, TORA_TSTP_PID_SZBond, \
    TORA_TSTP_PID_SZFund, TORA_TSTP_PID_SZStock, TORA_TSTP_TC_GFD, TORA_TSTP_TC_IOC, TORA_TSTP_VC_AV

from vnpy.trader.constant import Direction, Exchange, OrderType, Product, Status

EXCHANGE_TORA2VT = {
    TORA_TSTP_EXD_SSE: Exchange.SSE,
    TORA_TSTP_EXD_SZSE: Exchange.SZSE,
    # TORA_TSTP_EXD_HK: Exchange.SEHK,
}
EXCHANGE_VT2TORA = {v: k for k, v in EXCHANGE_TORA2VT.items()}

PRODUCT_TORA2VT = {
    # 通用(内部使用)
    # TORA_TSTP_PID_COMMON: 0,
    # 上海股票
    TORA_TSTP_PID_SHStock: Product.EQUITY,
    # 上海配股配债
    # TORA_TSTP_PID_SHWarrant: 0,
    # 上海基金
    TORA_TSTP_PID_SHFund: Product.FUND,
    # 上海债券
    TORA_TSTP_PID_SHBond: Product.BOND,
    # 上海标准券
    # TORA_TSTP_PID_SHStandard: 0,
    # 上海质押式回购
    # TORA_TSTP_PID_SHRepurchase: 0,
    # 深圳股票
    TORA_TSTP_PID_SZStock: Product.EQUITY,
    # 深圳配股配债
    # TORA_TSTP_PID_SZWarrant: 0,
    # 深圳基金
    TORA_TSTP_PID_SZFund: Product.FUND,
    # 深圳债券
    TORA_TSTP_PID_SZBond: Product.BOND,
    # 深圳标准券
    # TORA_TSTP_PID_SZStandard: 0,
    # 深圳质押式回购
    # TORA_TSTP_PID_SZRepurchase: 0,
}
PRODUCT_VT2TORA = {v: k for k, v in PRODUCT_TORA2VT.items()}

DIRECTION_TORA2VT = {
    # 买入
    TORA_TSTP_D_Buy: Direction.LONG,
    # 卖出
    TORA_TSTP_D_Sell: Direction.SHORT,
    # # ETF申购
    # TORA_TSTP_D_ETFPur: 0,
    # # ETF赎回
    # TORA_TSTP_D_ETFRed: 0,
    # # 新股申购
    # TORA_TSTP_D_IPO: 0,
    # # 正回购
    # TORA_TSTP_D_Repurchase: 0,
    # # 逆回购
    # TORA_TSTP_D_ReverseRepur: 0,
    # # 开放式基金申购
    # TORA_TSTP_D_OeFundPur: 0,
    # # 开放式基金赎回
    # TORA_TSTP_D_OeFundRed: 0,
    # # 担保品划入
    # TORA_TSTP_D_CollateralIn: 0,
    # # 担保品划出
    # TORA_TSTP_D_CollateralOut: 0,
    # # 质押入库
    # TORA_TSTP_D_PledgeIn: 0,
    # # 质押出库
    # TORA_TSTP_D_PledgeOut: 0,
    # # 配股配债
    # TORA_TSTP_D_Rationed: 0,
    # # 开放式基金拆分
    # TORA_TSTP_D_Split: 0,
    # # 开放式基金合并
    # TORA_TSTP_D_Merge: 0,
    # # 融资买入
    # TORA_TSTP_D_MarginBuy: 0,
    # # 融券卖出
    # TORA_TSTP_D_ShortSell: 0,
    # # 卖券还款
    # TORA_TSTP_D_SellRepayment: 0,
    # # 买券还券
    # TORA_TSTP_D_BuyRepayment: 0,
    # # 还券划转
    # TORA_TSTP_D_SecurityRepay: 0,
    # # 余券划转
    # TORA_TSTP_D_RemainTransfer: 0,
    # # 债转股
    # TORA_TSTP_D_BondConvertStock: 0,
    # # 债券回售
    # TORA_TSTP_D_BondPutback: 0,
}
DIRECTION_VT2TORA = {v: k for k, v in DIRECTION_TORA2VT.items()}

# OrderType-> (OrderPriceType, TimeCondition, VolumeCondition)
ORDER_TYPE_VT2TORA: Dict[OrderType, Tuple[str, str, str]] = {
    OrderType.FOK: (TORA_TSTP_OPT_LimitPrice, TORA_TSTP_TC_IOC, TORA_TSTP_VC_AV),
    OrderType.FAK: (TORA_TSTP_OPT_LimitPrice, TORA_TSTP_TC_IOC, TORA_TSTP_VC_AV),
    OrderType.LIMIT: (TORA_TSTP_OPT_LimitPrice, TORA_TSTP_TC_GFD, TORA_TSTP_VC_AV),
}

ORDER_TYPE_TORA2VT: Dict[Tuple[str, str, str], OrderType] = {
    v: k for k, v in ORDER_TYPE_VT2TORA.items()
}

ORDER_STATUS_TORA2VT: Dict[str, Status] = {
    # 全部成交
    TORA_TSTP_OST_AllTraded: Status.ALLTRADED,
    # 部分成交还在队列中
    TORA_TSTP_OST_PartTradedQueueing: Status.PARTTRADED,
    # 部分成交不在队列中
    # TORA_TSTP_OST_PartTradedNotQueueing: _,
    # 未成交还在队列中
    TORA_TSTP_OST_NoTradeQueueing: Status.NOTTRADED,
    # 未成交不在队列中
    # TORA_TSTP_OST_NoTradeNotQueueing: _,
    # 撤单
    TORA_TSTP_OST_Canceled: Status.CANCELLED,
    # 未知
    TORA_TSTP_OST_Unknown: Status.NOTTRADED,  # todo: unknown status???
    # 尚未触发
    # TORA_TSTP_OST_NotTouched: _,
    # 已触发
    # TORA_TSTP_OST_Touched: _,
    # 预埋
    # TORA_TSTP_OST_Cached: _,
}

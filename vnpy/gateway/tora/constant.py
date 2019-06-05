from vnpy.api.tora.vntora import TORA_TSTP_EXD_SSE, TORA_TSTP_EXD_SZSE, TORA_TSTP_EXD_HK

from vnpy.trader.constant import Exchange

EXCHANGE_TORA2VT = {
    TORA_TSTP_EXD_SSE: Exchange.SSE,
    TORA_TSTP_EXD_SZSE: Exchange.SZSE,
    TORA_TSTP_EXD_HK: Exchange.SEHK,
}
EXCHANGE_VT2TORA = {v: k for k, v in EXCHANGE_TORA2VT.items()}
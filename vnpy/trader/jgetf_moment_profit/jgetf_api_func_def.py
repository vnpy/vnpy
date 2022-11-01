#!/usr/bin/env python
#  coding:utf-8
"""python调用今古Dll库函数声明文件"""
import os
from ctypes import *
from enum import Enum

class MARKET_TYPE(Enum):
	MARKET_TYPE_STOCKSZ = 0            # 深交所股票.0
	MARKET_TYPE_STOCKSH = 1            # 上交所股票.1



# ETF基本信息
class ETFRedemptionHead(Structure):
    _fields_ = [("szETFCode", c_char * 24),                 # ETF指数代码
                ("nETFExchangeType", c_int),                # 市场类型
                ("lCreationRedemptionUnit", c_int),         # 最小申购、赎回单位
                ("dEstimateCashComponent", c_double),       # 预估现金差额
                ("nRecordnum", c_int)]                      # 组合样本个数



# ETF代码组合信息
class ETFRedemptionCodeList(Structure):
    _fields_ = [("nMarketType", c_int),     # 市场类型
                ("szSecurityCode", c_char * 24),      # 证券代码
                ("szSecurityName", c_char * 32),    # 证券简称
                ("nSampleVolume", c_int),        # 样本数量
                ("cReplaceFlag", c_char),           # 现金替代标志
                # ‘0’——禁止：禁止（现金替代）
                # ‘1’——允许：允许（现金替代）
                # ‘2’——必须：必须（现金替代）
                # ‘3’——退补：深市退补，申购时扣除现金，但扣除的现金会多退少补。上海跨市场ETF用到
                # ‘4’——必须：深市必须，同标志2，申购时扣除现金，且不会多退少补。上海跨市场ETF用到
                # ‘5’——退补：退补，同标志3， 跨境ETF和黄金ETF有用到此标志。.
                # ‘6’——必须：非沪深市场成份证券必须现金替代。
                # ‘7’——港市退补现金替代（仅适用于跨沪深港ETF产品）
                # ‘8’——港市必须现金替代（仅适用于跨沪深港ETF产品）

                ("dRedemptionPremiumRatio", c_double),           # @申购溢价比例
                ("dCreationCashSubstitute", c_double),  # 替代总金额金额
                ("dRedemptionCashSubstitute", c_double),  # 赎回替代金额

                ("nType", c_int),  # 板块信息
                ("nPreClosePrice", c_uint),  # 前收盘价
                ("nOpenPrice", c_uint),  # 开盘价
                ("nHighPrice", c_uint),  # 最高价
                ("nLowPrice", c_uint),  # 最低价
                ("nNowPrice", c_uint),  # 最新价
                ("arrnAskPrice", c_uint * 10),  # 委卖价
                ("arrnAskVol", c_longlong * 10),  # 委卖量
                ("arrnBidPrice", c_uint * 10),  # 委买价
                ("arrnBidVol", c_longlong * 10),  # 委买量
                ("nHighLimitedPrice", c_uint),  # 涨停价
                ("nLowLimitedPrice", c_uint)]  # 跌停价


# 费率
class BenefitInfo(Structure):
    _fields_ = [("dStockBuyBenefit", c_double),                 # 买入股票手续费(‰)
                ("dStockSellBenefit", c_double),                # 卖出股票手续费(‰)
                ("dStockBuyExBenefit", c_double),               # 股票买入过户手续费(‰)
                ("dStockSellExBenefit", c_double),              # 股票卖出过户手续费(‰)
                ("dBuyStamps", c_double),                       # 买入印花税(‰)
                ("dSellStamps", c_double),                      # 卖出印花税(‰)
                ("dETFBuyBenefit", c_double),                   # 买入ETF手续费(‰)
                ("dETFSellBenefit", c_double),                  # 卖出ETF手续费(‰)
                ("dETFPurchaseBenefit", c_double),              # ETF申购手续费(‰)
                ("dETFRedeemBenefit", c_double),                # ETF赎回手续费(‰)
                ("dETFPurchaseExBenefit", c_double),            # ETF申购过户手续费(‰)
                ("dETFRedeemExBenefit", c_double),              # ETF赎回过户手续费(‰)
                ("dEtfInterCityRate", c_double)]                # 跨市ETF股票买卖手续费率(‰)


class ETFProfit(Structure):
    _fields_ = [("dPremium", c_double),                 # 溢价预期利润
                ("dDiscount", c_double)]                 # 折价预期利润



# 加载c格式的dll动态库
path = os.path.dirname(__file__)
jgetfapi = windll.LoadLibrary(os.path.join(path, 'JGETFLib.dll'))

# 设置调用api的返回值和参数

# 计算ETF折溢价利润
jgetfapi.CalETFProfit.restype = ETFProfit
jgetfapi.CalETFProfit.argtypes = [ETFRedemptionHead,POINTER(ETFRedemptionCodeList),c_int,c_double,c_double,BenefitInfo,BenefitInfo]


# @service_type  创建服务类型
# @headinfo ETF基本信息		ETFRedemptionHead
# @codelist ETF代码组合信息	ETFRedemptionCodeList
# @ncodelist ETF代码组合信息个数
# @etfbuyprice   ETF买一价
# @etfsellprice  ETF卖一价
# @szbenefit 深圳费率设置			BenefitInfo
# @shbenefit 上海费率设置			BenefitInfo
# @return  返回ETFProfit
def API_CalETFProfit(headinfo, codelist, ncodelist, etfbuyprice, etfsellprice, szbenefit, shbenefit):
    etfrprofit = jgetfapi.CalETFProfit(headinfo,codelist,ncodelist, etfbuyprice, etfsellprice, szbenefit, shbenefit)
    return  etfrprofit


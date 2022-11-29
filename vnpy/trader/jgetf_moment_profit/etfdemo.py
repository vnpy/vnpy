# coding:utf-8
"""python调用今古交易服务Dll库demo示例文件, Python3.6.1"""

# 引入今古交易api库
from jgetf_api_func_def import *


# 主函数
if __name__ == "__main__":
    print("start")

    headinfo = ETFRedemptionHead()
    headinfo.szETFCode = bytes("510050", encoding="gb2312")
    headinfo.nETFExchangeType = MARKET_TYPE.MARKET_TYPE_STOCKSH.value
    headinfo.dEstimateCashComponent = 1234
    headinfo.lCreationRedemptionUnit = 900000
    headinfo.nRecordnum = 2

    codelist = (ETFRedemptionCodeList *  headinfo.nRecordnum)()
    codelist[0].szSecurityCode = bytes("600000", encoding="gb2312")
    codelist[0].nMarketType = MARKET_TYPE.MARKET_TYPE_STOCKSH.value
    codelist[0].nSampleVolume = 5000
    codelist[0].cReplaceFlag = c_char(b"1")
    codelist[0].nNowPrice = 102300

    codelist[1].szSecurityCode = bytes("000001", encoding="gb2312")
    codelist[1].nMarketType = MARKET_TYPE.MARKET_TYPE_STOCKSZ.value
    codelist[1].nSampleVolume = 10000
    codelist[1].cReplaceFlag = c_char(b"1")
    codelist[1].nNowPrice = 152300



    etfbuyprice = 3.152
    etfsellprice = 3.152

    szbenefit = BenefitInfo()
    szbenefit.dStockBuyBenefit = 1
    szbenefit.dStockSellBenefit = 1


    shbenefit = BenefitInfo()
    shbenefit.dStockBuyBenefit = 2
    shbenefit.dStockSellBenefit = 2


    etfprofit =  API_CalETFProfit(headinfo,codelist, headinfo.nRecordnum,etfbuyprice,etfsellprice, szbenefit, shbenefit)

    print("预期折价利润：%.2f, 预期溢价利润：%.2f " % (etfprofit.dDiscount, etfprofit.dPremium))

    print("end")
    input()
#!/usr/bin/python
# -*- coding: utf-8 -*-
#用于访问OKCOIN 期货REST API
from vnpy.api.okex.HttpMD5Util import buildMySign,httpGet,httpPost
OKEX_FUTURE_HOST = 'www.okex.com'                           # OKEX 期货REST地址

class OKCoinFuture:

    def __init__(self,url,apikey,secretkey):
        self.__url = url
        self.__apikey = apikey
        self.__secretkey = secretkey

    #OKCOIN期货行情信息
    def future_ticker(self,symbol,contractType):
        FUTURE_TICKER_RESOURCE = "/api/v1/future_ticker.do"
        params = ''
        if symbol:
            params += '&symbol=' + symbol if params else 'symbol=' +symbol
        if contractType:
            params += '&contract_type=' + contractType if params else 'contract_type=' +symbol
        return httpGet(self.__url,FUTURE_TICKER_RESOURCE,params)

    #OKCoin期货市场深度信息
    def future_depth(self,symbol,contractType,size): 
        FUTURE_DEPTH_RESOURCE = "/api/v1/future_depth.do"
        params = ''
        if symbol:
            params += '&symbol=' + symbol if params else 'symbol=' +symbol
        if contractType:
            params += '&contract_type=' + contractType if params else 'contract_type=' +symbol
        if size:
            params += '&size=' + size if params else 'size=' + size
        return httpGet(self.__url,FUTURE_DEPTH_RESOURCE,params)

    #OKCoin期货交易记录信息
    def future_trades(self,symbol,contractType):
        FUTURE_TRADES_RESOURCE = "/api/v1/future_trades.do"
        params = ''
        if symbol:
            params += '&symbol=' + symbol if params else 'symbol=' +symbol
        if contractType:
            params += '&contract_type=' + contractType if params else 'contract_type=' +symbol
        return httpGet(self.__url,FUTURE_TRADES_RESOURCE,params)

    #OKCoin期货指数
    def future_index(self,symbol):
        FUTURE_INDEX = "/api/v1/future_index.do"
        params=''
        if symbol:
            params = 'symbol=' +symbol
        return httpGet(self.__url,FUTURE_INDEX,params)

    #获取美元人民币汇率
    def exchange_rate(self):
        EXCHANGE_RATE = "/api/v1/exchange_rate.do"
        return httpGet(self.__url,EXCHANGE_RATE,'')

    #获取预估交割价
    def future_estimated_price(self,symbol):
        FUTURE_ESTIMATED_PRICE = "/api/v1/future_estimated_price.do"
        params=''
        if symbol:
            params = 'symbol=' +symbol
        return httpGet(self.__url,FUTURE_ESTIMATED_PRICE,params)

    #期货全仓账户信息
    def future_userinfo(self):
        FUTURE_USERINFO = "/api/v1/future_userinfo.do?"
        params ={}
        params['api_key'] = self.__apikey
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_USERINFO,params)

    #期货全仓持仓信息
    def future_position(self,symbol,contractType):
        FUTURE_POSITION = "/api/v1/future_position.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType
        }
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_POSITION,params)

    #期货下单
    def future_trade(self,symbol,contractType,price='',amount='',tradeType='',matchPrice='',leverRate=''):
        FUTURE_TRADE = "/api/v1/future_trade.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType,
            'amount':amount,
            'type':tradeType,
            'match_price':matchPrice,
            'lever_rate':leverRate
        }
        if price:
            params['price'] = price
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_TRADE,params)

    #期货批量下单
    def future_batchTrade(self,symbol,contractType,orders_data,leverRate):
        FUTURE_BATCH_TRADE = "/api/v1/future_batch_trade.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType,
            'orders_data':orders_data,
            'lever_rate':leverRate
        }
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_BATCH_TRADE,params)

    #期货取消订单
    def future_cancel(self,symbol,contractType,orderId):
        FUTURE_CANCEL = "/api/v1/future_cancel.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType,
            'order_id':orderId
        }
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_CANCEL,params)

    #期货获取订单信息
    def future_orderinfo(self,symbol,contractType,orderId,status,currentPage,pageLength):
        FUTURE_ORDERINFO = "/api/v1/future_order_info.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType,
            'order_id':orderId,
            'status':status,
            'current_page':currentPage,
            'page_length':pageLength
        }
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_ORDERINFO,params)

    #期货逐仓账户信息
    def future_userinfo_4fix(self):
        FUTURE_INFO_4FIX = "/api/v1/future_userinfo_4fix.do?"
        params = {'api_key':self.__apikey}
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_INFO_4FIX,params)

    #期货逐仓持仓信息
    def future_position_4fix(self,symbol,contractType,type1):
        FUTURE_POSITION_4FIX = "/api/v1/future_position_4fix.do?"
        params = {
            'api_key':self.__apikey,
            'symbol':symbol,
            'contract_type':contractType,
            'type':type1
        }
        params['sign'] = buildMySign(params,self.__secretkey)
        return httpPost(self.__url,FUTURE_POSITION_4FIX,params)



    def future_kline(self,symbol,type_,contract_type,size,since):
        """
        获取OKEx合约K线信息
        参数名	参数类型	必填	描述
            
        :param symbol: String	是	btc_usd ltc_usd eth_usd etc_usd bch_usd
        :param type: String	是	1min/3min/5min/15min/30min/1day/3day/1week/1hour/2hour/4hour/6hour/12hour
        :param contract_type: String	是	合约类型: this_week:当周 next_week:下周 quarter:季度
        :param size: Integer	否(默认0)	指定获取数据的条数
        :param since: 否(默认0)	时间戳（eg：1417536000000）。 返回该时间戳以后的数据
        :return: [
    1440308760000,	时间戳
    233.38,		开
    233.38,		高
    233.27,		低
    233.37,		收
    186,		交易量
    79.70234956		交易量转化BTC或LTC数量
]
        """
        FUTURE_KLINE_RESOURCE = "/api/v1/future_kline.do"
        params = ''
        if symbol:
            params += '&symbol=' + symbol if params else 'symbol=' +symbol
        if tpye_:
            params += '&type=' + type_ if params else 'type=' + type_
        if contract_type:
            params += '&contract_type=' + contract_type if params else 'contract_type=' +contract_type
        if size:
            params += '&size=' + size if params else 'size=' + size
        if since:
            params += '&since=' + since if params else 'since=' + since

        return httpGet(self.__url, FUTURE_KLINE_RESOURCE, params)




    

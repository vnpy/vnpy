# encoding: utf-8

import urllib
import hashlib

import json
import requests
from time import time, sleep
from Queue import Queue, Empty
from threading import Thread
from websocket import create_connection
import urlparse
from datetime import datetime
import base64
import hmac
import hashlib
import httplib
import json
import gzip, binascii, os  
import time
from cStringIO import StringIO  

from vnpy.Function import systemSymbolToVnSymbol , VnSymbolToSystemSymbol

wss_huobi_hosts = "wss://api.huobipro.com/ws"
MARKET_URL = "api.huobi.pro"
TRADE_URL = MARKET_URL

FUNCTIONCODE_GET_SYMBOS_HUOBI = "get_symbols"
FUNCTIONCODE_GET_ACCOUNTS_HUOBI = "get_accounts"
FUNCTIONCODE_GET_GET_BALANCE_HUOBI = "get_balance"
FUNCTIONCODE_POST_SEND_ORDERS_HUOBI = "send_order"
FUNCTIONCODE_POST_CANCEL_ORDERS_HUOBI = "cancel_order"
FUNCTIONCODE_GET_ORDER_INFO_HUOBI = "order_info"
FUNCTIONCODE_GET_ORDER_LIST_HUOBI = "order_list"

TIMEOUT = 5
'''
通过 TradeApi 完成
'''
class Huobi_TradeApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.accessKey = ''
        self.secretKey = ''
        
        self.active = False         # API工作状态   
        self.reqID = 0              # 请求编号
        #self.reqQueue = Queue()    # 请求队列
        self.reqQueue = []          # 请求的队列
        self.reqThread = Thread(target=self.processQueue)   # 请求处理线程      

        self.account_id = None

        self.trade_info_limit_dic = None

    #----------------------------------------------------------------------
    def processRequest(self, req):
        """处理请求"""
        # 读取方法和参数
        try:
            url = req['url']
            method = req['method']
            kwargs = req['kwargs']

            data = None
            if method in [FUNCTIONCODE_GET_SYMBOS_HUOBI]:
                data = self.http_get_request( MARKET_URL ,resource = url , params = kwargs )
            elif method in [FUNCTIONCODE_GET_ACCOUNTS_HUOBI , FUNCTIONCODE_GET_GET_BALANCE_HUOBI , FUNCTIONCODE_GET_ORDER_INFO_HUOBI , FUNCTIONCODE_GET_ORDER_LIST_HUOBI]:
                data = self.api_key_get( params = kwargs , request_path = url)
            elif method in [FUNCTIONCODE_POST_SEND_ORDERS_HUOBI , FUNCTIONCODE_POST_CANCEL_ORDERS_HUOBI]:
                data = self.api_key_post( params = kwargs , request_path = url)
            
            return data
            
        except Exception,ex:
            print "Error in processRequest" , ex
            # pass
        return None

    #----------------------------------------------------------------------
    def processQueue(self):
        """处理请求队列中的请求"""
        while self.active:
            try:
                #req = self.reqQueue.get(block=True, timeout=0.001)  # 获取请求的阻塞为一秒
                (Type , req) = self.reqQueue[0]

                callback = req['callback']
                reqID = req['reqID']
                try:
                    data = self.processRequest(req)
                    # 请求成功
                    if data != None :
                        # print "11 " ,callback , data, req, reqID
                        callback(data, req, reqID)
                        # print "22"
                except Exception,ex:
                    print "Error in processQueue !!" , ex
                self.reqQueue.pop(0)
                sleep(0.1)
            except Exception,ex:
                pass

    #----------------------------------------------------------------------
    def sendRequest(self, resource , method, callback, kwargs = None,optional=None):
        """发送请求"""
        # 请求编号加1
        self.reqID += 1
        
        # 生成请求字典并放入队列中
        req = {}
        req['url'] = resource
        req['method'] = method
        req['callback'] = callback
        req['optional'] = optional
        req['kwargs'] = kwargs
        req['reqID'] = self.reqID

        try:
            if method in [  FUNCTIONCODE_GET_GET_BALANCE_HUOBI , FUNCTIONCODE_GET_ACCOUNTS_HUOBI]:
                flag = False
                for use_method ,r in self.reqQueue:
                    if use_method == method:
                        flag = True
                        break
                if False == flag:
                    self.reqQueue.append( (method , req))
            else:
                self.reqQueue.append( (method , req))
        except Exception,ex:
            print ex , "Error in sendRequest"
        
        # 返回请求编号
        return self.reqID

    #----------------------------------------------------------------------
    ####################################################
    ## 主动函数
    ####################################################    
    #----------------------------------------------------------------------
    def init(self, accessKey, secretKey):
        """初始化"""
        self.accessKey = accessKey
        self.secretKey = secretKey
        
        self.active = True
        self.reqThread.start()
    
    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.reqThread.isAlive():
            self.reqThread.join()  

    '''
    获得所有交易对

    '''
    #----------------------------------------------------------------------
    def get_symbols(self):
        print(u'vnhuobi.get_symbols')
        kwargs = {}
        return self.sendRequest( '/v1/common/symbols' , FUNCTIONCODE_GET_SYMBOS_HUOBI , self.onAllSymbols , kwargs = kwargs , optional = None)

    '''
    获得所有交易对
    '''
    #----------------------------------------------------------------------
    def get_accounts(self):
        print(u'vnhuobi.get_accounts')
        kwargs = {}
        return self.sendRequest( "/v1/account/accounts" , FUNCTIONCODE_GET_ACCOUNTS_HUOBI , self.onGetAccounts , kwargs = kwargs , optional = None)


    # 获取当前账户资产
    #----------------------------------------------------------------------
    def get_balance(self , num_try = 0):
        # print(u'vnhuobi.get_balance')
        if not self.account_id:
            try:
                self.get_accounts()
                time.sleep(5)
                if num_try < 3:
                    return self.get_balance( num_try + 1)
                # return self.get_accounts()
            except BaseException as e:
                print 'get acct_id error.%s' % e
            return None
        else:
            url = "/v1/account/accounts/{0}/balance".format( self.account_id)
            kwargs = {"account-id": self.account_id}
            return self.sendRequest( url , FUNCTIONCODE_GET_GET_BALANCE_HUOBI , self.onGetBalance , kwargs = kwargs , optional = None)


    # 创建并执行订单
            """
        :param amount: 
        :param source: 如果使用借贷资产交易，请在下单接口,请求参数source中填写'margin-api'
        :param symbol: 
        :param _type: 可选值 {buy-market：市价买, sell-market：市价卖, buy-limit：限价买, sell-limit：限价卖}
        :param price: 
        :return:
        /* POST /v1/order/orders/place {
               "account-id": "100009",
               "amount": "10.1",
               "price": "100.1",
               "source": "api",
               "symbol": "ethusdt",
               "type": "buy-limit"
             } */
            {
              "status": "ok",
              "data": "59378"
            } 
        """
    #----------------------------------------------------------------------
    def spotTrade(self, symbol , amount, _type , price = 0 ,source = "api" , num_try = 0):
        # print(u'vnhuobi.spotTrade symbol %s, amount %s, _type %s, price = %s ,source %s' % (str(symbol) , str(amount) , str(_type) , str(price) , str(source)))
        try:
            if not self.account_id:
                try:
                    self.get_accounts()
                    time.sleep(5)
                    if num_try < 3:
                        return self.spotTrade(symbol , amount, _type , price = price  ,source = source , num_try = num_try + 1)
                except BaseException as e:
                    print 'get acct_id error.%s' % e
                return None
            else:
                if self.trade_info_limit_dic :
                    dic = self.trade_info_limit_dic.get( symbol , None)

                    if dic != None:
                        price_str_pattern = '%.' + str(dic["minPrice"]) + "f"
                        volume_str_pattern = '%.' + str(dic["minVolume"]) + "f"

                        price = price_str_pattern % (price)
                        amount = volume_str_pattern % (amount)

                        symbol = (''.join(symbol.split('_'))).lower()
                        kwargs = {"account-id": str(self.account_id),
                                  "amount": amount,
                                  "symbol": symbol,
                                  "type": _type,
                                  "source": source ,
                                  'price': price }

                        # print(u'vnhuobi.spotTrade send symbol %s, amount %s, _type %s, price = %s ,source %s' % (str(symbol) , str(amount) , str(_type) , str(price) , str(source)))

                        url = '/v1/order/orders/place'
                        return self.sendRequest(url , FUNCTIONCODE_POST_SEND_ORDERS_HUOBI , self.onSpotTrade , kwargs = kwargs , optional = None)
                    else:
                        print "Error in spotTrade ,  can not find detail infomation about symbol %s" % (symbol)
                        return None
                else:
                    self.get_symbols()
                    time.sleep(5)
                    if num_try < 3:
                        return self.spotTrade(symbol , amount, _type , price = price  ,source = source , num_try = num_try + 1)
        except Exception,ex:
            print ex
            return None


    #----------------------------------------------------------------------
    # 撤销订单
    def cancel_order(self , order_id):
        # print(u'vnhuobi.cancel_order %s' % (str(order_id)))
        try:
            kwargs = {}
            url = "/v1/order/orders/{0}/submitcancel".format(order_id)
            return self.sendRequest(url , FUNCTIONCODE_POST_CANCEL_ORDERS_HUOBI , self.onCancelOrder , kwargs = kwargs , optional = None)
        except Exception,ex:
            print ex


    # 查询某个订单
    #----------------------------------------------------------------------
    def order_info(self , order_id):
        # print(u'vnhuobi.order_info , order_id %s' % (str(order_id)))
        kwargs = {}
        url = "/v1/order/orders/{0}".format(order_id)
        return self.sendRequest(url , FUNCTIONCODE_GET_ORDER_INFO_HUOBI , self.onOrderInfo , kwargs = kwargs , optional = None)


    # 查询某个订单的成交明细
    #----------------------------------------------------------------------
    def order_matchresults(self, order_id):
        pass
        # """

        # :param order_id: 
        # :return: 
        # """
        # params = {}
        # url = "/v1/order/orders/{0}/matchresults".format(order_id)
        # return api_key_get(params, url)


    # 查询当前委托、历史委托
    #----------------------------------------------------------------------
    def orders_list(self, symbol, states = None, types=None, start_date=None, end_date=None, _from=None, direct=None, size=None):
        """
        :param symbol: 
        :param states: 可选值 {pre-submitted 准备提交, submitted 已提交, partial-filled 部分成交, partial-canceled 部分成交撤销, filled 完全成交, canceled 已撤销}
        :param types: 可选值 {buy-market：市价买, sell-market：市价卖, buy-limit：限价买, sell-limit：限价卖}
        :param start_date: 
        :param end_date: 
        :param _from: 
        :param direct: 可选值{prev 向前，next 向后}
        :param size: 
        :return: 
        """
        # print(u'vnhuobi.orders_list symbol %s, states %s, types %s, start_date %s, end_date %s, _from %s, direct %s, size %s' % (str(symbol), str(states) , str(types) , str(start_date) , str(end_date) , str(_from) , str(direct) , str(size)))
        kwargs = {'symbol': symbol,
                  'states': 'submitted,partial-filled,filled,partial-canceled,canceled'}

        if types:
            kwargs[types] = types
        if states:
            kwargs['states'] = states
        if start_date:
            kwargs['start-date'] = start_date
        if end_date:
            kwargs['end-date'] = end_date
        if _from:
            kwargs['from'] = _from
        if direct:
            kwargs['direct'] = direct
        if size:
            kwargs['size'] = size
        url = '/v1/order/orders'

        return self.sendRequest(url , FUNCTIONCODE_GET_ORDER_LIST_HUOBI , self.onOrderList , kwargs = kwargs , optional = None)


    # 查询当前成交、历史成交
    #----------------------------------------------------------------------
    def orders_matchresults(self, symbol, types=None, start_date=None, end_date=None, _from=None, direct=None, size=None):
        pass

    #----------------------------------------------------------------------
    def onAllSymbols(self,data, req, reqID):
        #print data
        self.trade_info_limit_dic = {}
        if data["status"] == "ok":
            pairs = data["data"]
            for info in pairs:
                base_currency = info["base-currency"]       # nas
                quote_currency = info["quote-currency"]     # eth
                price_precision = info["price-precision"]   # 6
                amount_precision = info["amount-precision"] # 4

                symbol = base_currency + "_" + quote_currency
                self.trade_info_limit_dic[symbol] = {"minPrice":int(price_precision) , "minVolume":int(amount_precision)}

        else:
            print "Error in onAllSymbols , data : %s" % (str(data))

    '''
    {u'status': u'ok', u'data': [{u'subtype': u'', u'state': u'working', u'type': u'
spot', u'id': 932763}]}
    '''
    #----------------------------------------------------------------------
    def onGetAccounts(self,data, req, reqID):
        if data["status"] == "ok":
            self.account_id = int(data["data"][0]["id"])
        else:
            print "Error in onGetAccounts , the status is not ok!"

    #----------------------------------------------------------------------
    def onGetBalance(self,data, req, reqID):
        print data
    #----------------------------------------------------------------------
    def onSpotTrade(self,data, req, reqID):
        print data
    #----------------------------------------------------------------------
    def onCancelOrder(self,data, req, reqID):
        print data
    #----------------------------------------------------------------------
    def onOrderInfo(self,data, req, reqID):
        print data
    #----------------------------------------------------------------------
    def onOrderList(self,data, req, reqID):
        print data

    #各种请求,获取数据方式
    #----------------------------------------------------------------------
    def http_get_request(self, url , resource, params, add_to_headers=None):
        headers = {
            "Content-type": "application/x-www-form-urlencoded",
            'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        try:
            # print url , resource
            conn = httplib.HTTPSConnection(url, timeout=10)
            params = urllib.urlencode(params)
            conn.request("GET", resource + '?' + params)
            response = conn.getresponse()
            data = response.read().decode('utf-8')
            return json.loads(data) 
        except Exception,ex:
            print("httpGet failed, detail is:%s" %ex)
            return {"status":"fail","msg":ex}

    #----------------------------------------------------------------------
    def http_post_request(self, url, params, add_to_headers=None):
        headers = {
            "Accept": "application/json",
            'Content-Type': 'application/json',
            "User-Agent": "Chrome/39.0.2171.71",
            'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        postdata = json.dumps(params)

        # print "http_post_request\n\n"
        # print url , postdata
        try:
            response = requests.post(url, postdata, headers=headers, timeout=TIMEOUT)
            if response.status_code == 200:
                return response.json()
            else:
                return response.json()
        except Exception as e:
            print("httpPost failed, detail is:%s" % e)
            return {"status":"fail","msg":e}


    #----------------------------------------------------------------------
    def api_key_get(self, params, request_path):
        method = 'GET'
        timestamp = datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S')
        params.update({'AccessKeyId': self.accessKey,
                       'SignatureMethod': 'HmacSHA256',
                       'SignatureVersion': '2',
                       'Timestamp': timestamp})

        host_name = host_url = TRADE_URL
        params['Signature'] = self.createSign(params, method, host_name, request_path, self.secretKey)

        return self.http_get_request(host_url , request_path, params)

    #----------------------------------------------------------------------
    def api_key_post(self, params, request_path):
        method = 'POST'
        timestamp = datetime.utcnow().strftime('%Y-%m-%dT%H:%M:%S')
        params_to_sign = {'AccessKeyId': self.accessKey,
                          'SignatureMethod': 'HmacSHA256',
                          'SignatureVersion': '2',
                          'Timestamp': timestamp}

        host_name = host_url = TRADE_URL
        params_to_sign['Signature'] = self.createSign(params_to_sign, method, host_name, request_path, self.secretKey)

        url = "https://" + TRADE_URL + request_path + '?' + urllib.urlencode(params_to_sign)

        return self.http_post_request(url  , params)
        # url = host_url + request_path + '?' + urllib.urlencode(params_to_sign)
        # return self.http_post_request(url, params)

    #----------------------------------------------------------------------
    def createSign(self, pParams, method, host_url, request_path, secret_key):
        sorted_params = sorted(pParams.items(), key=lambda d: d[0], reverse=False)
        encode_params = urllib.urlencode(sorted_params)
        payload = [method, host_url, request_path, encode_params]
        payload = '\n'.join(payload)
        payload = payload.encode(encoding='UTF8')
        secret_key = secret_key.encode(encoding='UTF8')
        digest = hmac.new(secret_key, payload, digestmod=hashlib.sha256).digest()
        signature = base64.b64encode(digest)
        signature = signature.decode()
        return signature


'''
通过 DataApi 完成
'''
class Huobi_DataApi(object):
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.active = False
        
        self.taskInterval = 3                       # 每轮请求延时
        self.taskList = []                          # 订阅的任务列表
        self.taskThread = Thread(target=self.run)   # 处理任务的线程

    #----------------------------------------------------------------------
    def init(self, interval, debug):
        """初始化"""
        self.taskInterval = interval
        self.DEBUG = debug
        
        self.active = True
        self.taskThread.start()

    #----------------------------------------------------------------------
    def exit(self):
        """退出"""
        self.active = False
        
        if self.taskThread.isAlive():
            self.taskThread.join()

    #----------------------------------------------------------------------
    def run(self):
        """连续运行"""
        while self.active:
            for url, resource ,callback ,params in self.taskList:
                try:
                    callback(self.http_get_request(url, resource , params , add_to_headers = None))
                except Exception, e:
                    print e
            sleep(self.taskInterval)

    #----------------------------------------------------------------------
    def rightFormatSimple(self, symbol):
        symbol = ''.join(symbol.split('_'))
        return symbol.lower()


    #各种请求,获取数据方式
    #----------------------------------------------------------------------
    def http_get_request(self, url , resource, params, add_to_headers=None):
        headers = {
            "Content-type": "application/x-www-form-urlencoded",
            'User-Agent':'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:53.0) Gecko/20100101 Firefox/53.0'
        }
        if add_to_headers:
            headers.update(add_to_headers)
        try:
            # print url , resource
            conn = httplib.HTTPSConnection(url, timeout=10)
            params = urllib.urlencode(params)
            conn.request("GET", resource + '?' + params)
            response = conn.getresponse()
            data = response.read().decode('utf-8')
            return json.loads(data)
        except Exception,ex:
            print("httpGet failed, detail is:%s" %ex)
            return {"status":"fail","msg":ex}
        # postdata = urllib.urlencode(params)
        # try:
        #     url = url + resource
        #     response = requests.get(url, postdata, headers=headers, timeout=5)
        #     if response.status_code == 200:
        #         return response.json()
        #     else:
        #         return {"status":"fail"}
        # except Exception as e:
        #     print("httpGet failed, detail is:%s" %e)
        #     return {"status":"fail","msg":e}

    #----------------------------------------------------------------------
    def subscribeTick(self, symbol):
        """订阅实时成交数据"""
        #url = MARKET_URL + '/market/history/kline'
        params = {'symbol': self.rightFormatSimple(symbol),
              'period': "1min",
              'size': 1}
        task = (MARKET_URL , '/market/history/kline' , self.onTick , params)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def subscribeTrades(self, symbol):
        """订阅实时成交数据"""
        params = {'symbol': self.rightFormatSimple(symbol)}
        #url = MARKET_URL + '/market/trade'

        task = (MARKET_URL , '/market/trade' , self.onTrades , params)
        self.taskList.append(task)
    
    #----------------------------------------------------------------------
    def subscribeOrderbooks(self, symbol):
        """订阅实时成交数据"""
        # url = MARKET_URL + '/market/depth'
        params = {'symbol': self.rightFormatSimple(symbol),
              'type': "step0"}

        task = (MARKET_URL , '/market/depth' , self.onDepth , params)
        self.taskList.append(task)

    #----------------------------------------------------------------------
    def onTick(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onTrades(self, data):
        """实时成交推送"""
        print data

    #----------------------------------------------------------------------
    def onDepth(self, data):
        """实时成交推送"""
        print data

'''
通过socket API 获得
'''
class Huobi_DataApiSocket(object):
    """基于Websocket的API对象"""
    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.host = ''          # 服务器地址
        
        self.ws = None          # websocket应用对象
        self.thread = None      # 工作线程

        self.subscribeStrList = set([])

    #----------------------------------------------------------------------
    def gzip_uncompress(self,c_data):  
        buf = StringIO(c_data)  
        f = gzip.GzipFile(mode = 'rb', fileobj = buf)  
        try:  
            r_data = f.read()  
        finally:  
            f.close()  
        return r_data  

    #----------------------------------------------------------------------
    def run_forever(self):
        try:
            while(1):
                compressData=self.ws.recv()
                result = self.gzip_uncompress( compressData )
                if result[:7] == '{"ping"':
                    ts=result[8:21]
                    pong='{"pong":'+ts+'}'
                    self.ws.send(pong)
                    for ss in self.subscribeStrList:
                        self.ws.send(ss)
                else:
                    result = json.loads(result)
                    if "ch" in result.keys():
                        if "depth" in result["ch"]:
                            self.onDepth(result)
                        elif "kline" in result["ch"]:
                            self.onTicker(result)
        except Exception,ex:
            print ex , " run_forever error, now try to reconnect"
            self.reconnect()

    #----------------------------------------------------------------------
    def connect(self, host,  trace=False):
        """连接服务器"""
        self.host = host
            
        self.ws = create_connection(self.host)     

        self.thread = Thread(target=self.run_forever)
        self.thread.start()


    #----------------------------------------------------------------------
    def reconnect(self):
        """重新连接"""
        # 首先关闭之前的连接
        self.close()
        
        # 再执行重连任务
        # self.ws = websocket.WebSocketApp(self.host, 
        #                                  on_message=self.onMessage,
        #                                  on_error=self.onError,
        #                                  on_close=self.onClose,
        #                                  on_open=self.onOpen)        

        self.ws = create_connection(self.host)
    
        self.thread = Thread(target=self.run_forever)
        self.thread.start()

    #----------------------------------------------------------------------
    def exit(self):
        self.close()

    #----------------------------------------------------------------------
    def close(self):
        """关闭接口"""
        if self.thread and self.thread.isAlive():
            self.ws.close()
            self.thread.join()

    #----------------------------------------------------------------------
    def rightFormatSimple(self, symbol):
        symbol = ''.join(symbol.split('_'))
        return symbol.lower()

    #----------------------------------------------------------------------
    def sendTickerRequest(self, symbol):
        """发送行情请求 , 订阅 orderbook"""
        # 生成请求
        right_symbol = self.rightFormatSimple(symbol)
        j = """{"sub": "market.%s.kline.1min","id": "id10"}""" % right_symbol
        
        self.subscribeStrList.add(j)
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass

    #----------------------------------------------------------------------
    def sendOrderbookRequest(self , symbol):
        """订阅最近的交易记录 """
        
        # 生成请求
        right_symbol = self.rightFormatSimple(symbol)
        j = """{"sub": "market.%s.depth.step0", "id": "id10"}""" % right_symbol
        
        self.subscribeStrList.add(j)
        # 若触发异常则重连
        try:
            self.ws.send(j)
        except websocket.WebSocketConnectionClosedException:
            pass 

    #----------------------------------------------------------------------
    def onTicker(self , data):
        print data

    #----------------------------------------------------------------------
    def onDepth(self , data):
        print data



# encoding: UTF-8

"""
对接天勤行情的网关接口，可以提供国内期货的报价/K线/Tick序列等数据的实时推送和历史仿真
使用时需要在本机先启动一个天勤终端进程
天勤行情终端: http://www.tq18.cn
天勤接口文档: http://doc.tq18.cn/tq/latest/extension/wsapi/index.html
"""
from __future__ import print_function


import json
import threading
import tornado
from tornado import websocket
from sortedcontainers import SortedDict

########################################################################
class TqApi(object):
    """天勤行情接口"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""        
        self.data = {}          # 数据存储
        
        self.client = None      # websocket客户端
        self.requests = []      # 请求缓存
        
        self.quote_callback_func = None     # tick回调函数
        self.quote_ins_list = []
        self.chart_subscribes = {}       # k线回调函数
        
    #----------------------------------------------------------------------
    def connect(self):        
        """
        建立行情连接。
        """
        self.start()
        
        # 启动tornado的IO线程
        loop_thread = threading.Thread(target=lambda: tornado.ioloop.IOLoop.current().start())
        loop_thread.setDaemon(True)
        loop_thread.start()

    #----------------------------------------------------------------------
    def subscribe_quote(self, ins_list, callback_func=None):
        """
        订阅实时行情.
        指定一个合约列表，订阅其实时报价信息
        每次调用此函数时，都会覆盖前一次的订阅设定，不在订阅列表里的合约，会停止行情推送
        :param ins_list: ins_list 是一个列表，列出全部需要实时行情的合约代码。注意：天勤接口从0.8版本开始，合约代码格式变更为 交易所代码.合约代码的格式. 交易所代码如下：
                         CFFEX: 中金所
                         SHFE: 上期所
                         DCE: 大商所
                         CZCE: 郑商所
                         INE: 能源交易所(原油)
        :param callback_func (可选): callback_func 是一个回调函数，每当有报价数据变更时会触发。此函数应该接受一个参数 ins_id
        :example:
            订阅 SHFE.cu1803,CZCE.SR709,CFFEX.IF1709 这三个合约的报价:  subscribe_quote(["SHFE.cu1803", ”CZCE.SR709", "CFFEX.IF1709"])
        """
        if callback_func:
            self.quote_callback_func = callback_func
            self.quote_ins_list = ins_list

        req = {
            "aid": "subscribe_quote",
            "ins_list": ",".join(ins_list),
        }
        self.send_json(req)

    #----------------------------------------------------------------------
    def subscribe_chart(self, ins_id, duration_seconds, data_length=200, callback_func=None):
        """
        订阅历史行情序列.
        订阅指定合约及周期的历史行情序列（K线数据序列或Tick数据序列），这些序列数据会持续推送
        :param ins_id: 合约代码，需注意大小写
        :param duration_seconds: 历史数据周期，以秒为单位。目前支持的周期包括：
                3秒，5秒，10秒，15秒，20秒，30秒，1分钟，2分钟，3分钟，5分钟，10分钟，15分钟，20分钟，30分钟，1小时，2小时，4小时，1日
                特别的，此值指定为0表示订阅tick序列。
        :param data_length: 需要获取的序列长度。每个序列最大支持请求 8964 个数据
        :param callback_func (可选): callback_func 是一个回调函数，每当序列数据变更时会触发。此函数应该接受2个参数 ins_id, duration_seconds
        :example:
            订阅 SHFE.cu1803 的1分钟线： subscribe_chart("SHFE.cu1803", 60)
            订阅 CFFEX.IF1709 的tick线： subscribe_chart("CFFEX.IF1709", 0)
        """
        chart_id = self._generate_chart_id(ins_id, duration_seconds)
        
        # 限制最大数据长度
        if data_length > 8964:
            data_length = 8964

        req = {
            "aid": "set_chart",
            "chart_id": chart_id,
            "ins_list": ins_id,
            "duration": duration_seconds * 1000000000,
            "view_width": data_length,
        }
        self.send_json(req)
        self.chart_subscribes[chart_id] = req
        self.chart_subscribes[chart_id]["callback"] = callback_func

    #----------------------------------------------------------------------
    def get_quote(self, ins_id):
        """
        获取报价数据
        :param ins_id: 指定合约代码
        :return: 若指定的数据不存在，返回None，否则返回如下所示的一个dict
        {
            u'datetime': u'2017-07-26 23:04:21.000001',# tick从交易所发出的时间(按北京时区)
            u'instrument_id': u'CZCE.SR801', # 合约代码
            u'last_price': 6122.0, # 最新价
            u'bid_price1': 6121.0, # 买一价
            u'ask_price1': 6122.0, # 卖一价
            u'bid_volume1': 54, # 买一量
            u'ask_volume1': 66, # 卖一量
            u'upper_limit': 6388.0, # 涨停价
            u'lower_limit': 5896.0, # 跌停价
            u'volume': 89252, # 成交量
            u'amount': 5461329880.0, # 成交额
            u'open_interest': 616424, # 持仓量
            u'highest': 6129.0, # 当日最高价
            u'lowest': 6101.0, # 当日最低价
            u'average': 6119.0, # 当日均价
            u'open': 6102.0, # 开盘价
            u'close': u'-', # 收盘价
            u'settlement': u'-', # 结算价
            u'pre_close': 6106.0, # 昨收盘价
            u'pre_settlement': 6142.0 #  昨结算价
            u'pre_open_interest': 616620, # 昨持仓量
        }
        """
        return self.data.setdefault("quotes", {}).get(ins_id, None)

    #----------------------------------------------------------------------
    def get_tick_serial(self, ins_id):
        """
        获取tick序列数据
        :param ins_id: 指定合约代码
        :return: 若指定的序列数据不存在，返回None，否则返回如下所示的一个dict
        {
            u'485107':{     # 每个Tick都有一个唯一编号，在一个序列中，编号总是连续递增的
                u'datetime': 1501074872000000000L, # tick从交易所发出的时间(按北京时区)，以nano epoch 方式表示(等于从1970-01-01时刻开始的纳秒数)
                u'trading_day': 1501084800000000000L, #交易日, 格式同上
                u'last_price': 3887, # 最新价
                u'bid_price1': 3881, # 买一价
                u'ask_price1': 3886, # 卖一价
                u'bid_volume1': 5, # 买一量
                u'ask_volume1': 1, #卖一量
                u'highest': 3887, # 当日最高价
                u'lowest': 3886,    # 当日最低价
                u'volume': 6, # 成交量
                u'open_interest': 1796 # 持仓量
            },
            u'485108': {
                ...
            }
        }
        """
        return self.data.setdefault("ticks", {}).setdefault(ins_id, {}).get("data", None)

    #----------------------------------------------------------------------
    def get_kline_serial(self, ins_id, duration_seconds):
        """
        获取k线序列数据
        :param ins_id: 指定合约代码
        :param duration_seconds: 指定K线周期
        :return: 若指定的序列数据不存在，返回None，否则返回如下所示的一个dict
        {
            u'494835': {     # 每根K线都有一个唯一编号，在一个序列中，编号总是连续递增的
                u'datetime': 1501080715000000000L, # K线起点时间(按北京时区)，以nano epoch 方式表示(等于从1970-01-01时刻开始的纳秒数)
                u'open': 51450, # K线起始时刻的最新价
                u'high': 51450, # K线时间范围内的最高价
                u'low': 51450, # K线时间范围内的最低价
                u'close': 51450, # K线结束时刻的最新价
                u'volume': 0, # K线时间范围内的成交量
                u'open_oi': 27354, # K线起始时刻的持仓量
                u'close_oi': 27354 # K线结束时刻的持仓量
            },
            u'494836': {
                ...
            }
        }
        """
        dur_id = "%d" % (duration_seconds * 1000000000)
        return self.data.setdefault("klines", {}).setdefault(ins_id, {}).setdefault(dur_id, {}).get("data", None)

    #----------------------------------------------------------------------
    @tornado.gen.coroutine
    def start(self):
        """启动websocket客户端"""
        self.client = yield tornado.websocket.websocket_connect(url="ws://127.0.0.1:7777/")
        
        # 发出所有缓存的请求
        for req in self.requests:
            self.client.write_message(req)
        self.requests = []

        # 协程式读取数据
        while True:
            msg = yield self.client.read_message()
            self.on_receive_msg(msg)

    #----------------------------------------------------------------------
    def send_json(self, obj):
        """发送JSON内容"""
        s = json.dumps(obj)
        
        # 如果已经创建了客户端则直接发出请求
        if self.client:
            self.client.write_message(s)
        # 否则缓存在请求缓存中
        else:
            self.requests.append(s)

    #----------------------------------------------------------------------
    def on_receive_msg(self, msg):
        """收到数据推送"""
        pack = json.loads(msg)
        
        if 'data' in pack:
            l = pack["data"]
        else:
            print(u'on_receive_msg收到的数据中没有data字段，数据内容%s' %str(pack))
            return

        for data in l:
            # 合并更新数据字典
            self._merge_obj(self.data, data)
            # 遍历更新内容并调用回调函数
            for selector, section in data.items():
                if selector == "quotes":
                    if self.quote_callback_func:
                        for ins_id in section.keys():
                            if ins_id in self.quote_ins_list:
                                self.quote_callback_func(ins_id)
                
                elif selector == "ticks":
                    for ins_id in section.keys():
                        chart_id = self._generate_chart_id(ins_id, 0)
                        sub_info = self.chart_subscribes.get(chart_id, None)
                        tick_serial = self.get_tick_serial(ins_id)
                        if tick_serial and sub_info:
                            while len(tick_serial) > sub_info["view_width"]:
                                tick_serial.popitem(last=False)
                            callback_func = sub_info["callback"]
                            if callback_func:
                                callback_func(ins_id, 0)

                elif selector == "klines":
                    for ins_id, sub_section in section.items():
                        for dur_nanoseconds in sub_section.keys():
                            dur_seconds = int(dur_nanoseconds) / 1000000000
                            chart_id = self._generate_chart_id(ins_id, dur_seconds)
                            sub_info = self.chart_subscribes.get(chart_id, None)
                            kline_serial = self.get_kline_serial(ins_id, dur_seconds)
                            if kline_serial and sub_info:
                                while len(kline_serial) > sub_info["view_width"]:
                                    kline_serial.popitem(last=False)
                                callback_func = sub_info["callback"]
                                if callback_func:
                                    callback_func(ins_id, dur_seconds)

    #----------------------------------------------------------------------
    def _merge_obj(self, result, obj):
        """合并对象"""
        for key, value in obj.items():
            if value is None:
                result.pop(key, None)
            elif isinstance(value, dict):
                target = result.setdefault(key, SortedDict())
                self._merge_obj(target, value)
            else:
                result[key] = value

    #----------------------------------------------------------------------
    def _generate_chart_id(self, ins_id, duration_seconds):
        """生成图表编号"""
        chart_id = "VN_%s_%d" % (ins_id, duration_seconds)
        chart_id = chart_id.replace(".", "_")
        return chart_id
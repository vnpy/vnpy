# encoding: UTF-8

"""
对接天勤行情的网关接口，可以提供国内期货的 报价/K线/Tick序列 等数据的实时推送和历史仿真
使用时需要在本机先启动一个天勤终端进程(http://www.tq18.cn)

使用示例见：


"""


import json
import threading
import sortedcontainers
import tornado.ioloop
import tornado.iostream
import tornado.websocket
from tornado import gen

from vnpy.event import *


########################################################################
class DataBackEndMemory(object):
    def __init__(self):
        self.data = sortedcontainers.SortedDict()

    def input_data_pack(self, pack):
        for data in pack:
            self.data = self._dict_merge(self.data, data)

    def get_tick_serial(self, ins_id):
        return self.data.setdefault("ticks", {}).setdefault(ins_id, {}).get("data", None)

    def get_kline_serial(self, ins_id, duration_seconds):
        dur_id = "%d" % (duration_seconds * 1000000000)
        return self.data.setdefault("klines", {}).setdefault(ins_id, {}).setdefault(dur_id, {}).get("data", None)

    def _dict_merge(self, *objs):
        result = objs[0]
        for obj in objs[1:]:
            result = self._merge_obj(result, obj)
        return result

    def _merge_obj(self, result, obj):
        if not isinstance(result, dict):
            result = {}
        if not isinstance(obj, dict):
            return obj
        for key, value in obj.items():
            if isinstance(value, dict):
                target = result.get(key)
                if isinstance(target, dict):
                    self._merge_obj(target, value)
                    continue
                result[key] = {}
                self._merge_obj(result[key], value)
                continue
            if value is None:
                result.pop(key, None)
                continue
            result[key] = value
        return result


class DataBackendMongo(object):
    def __init__(self, mc):
        self.dbClient = mc

    def input_data_pack(self, pack):
        for data in pack:
            for selector, section in data.items():
                if selector == "ticks":
                    self.process_tick_data(section)
                elif selector == "klines":
                    self.process_kline_data(section)

    def process_tick_data(self, section):
        db_name = "TICK"
        db = self.dbClient[db_name]  # 数据库
        for ins_id, serials in section.items():
            cl = db[ins_id]
            for tick_id, tick in serials:
                flt = {'datetime': tick.datetime}
                cl.replace_one(flt, tick, True)

    def get_tick_serial(self, ins_id):
        collection = self.dbClient["TICK"][ins_id]
        cursor = collection.find({}).sort('datetime')
        return cursor

    def process_kline_data(self, section):
        #todo
        pass

    def get_kline_serial(self, ins_id, duration_seconds):
        #todo
        pass


class TianQinGateway(object):
    """天勤行情服务"""

    # ----------------------------------------------------------------------
    def __init__(self, eventEngine, back_end=DataBackEndMemory()):
        """Constructor"""
        self.client = None
        self.back_end = back_end
        self.data = {}
        self.requests = []
        self.eventEngine = eventEngine
        self.eventEngine.register('eTianQin.', self._process_pack)
        self.quote_callback_func = None
        self.chart_callback_func = {}

    # ----------------------------------------------------------------------
    def connect(self):
        """
        建立行情连接。
        """
        self._start()
        loop_thread = threading.Thread(target=lambda: tornado.ioloop.IOLoop.current().start())
        loop_thread.setDaemon(True)
        loop_thread.start()

    # ----------------------------------------------------------------------
    def subscribe_quote(self, ins_list, notify_func=None):
        """
        订阅实时行情.
        指定一个合约列表，订阅其实时报价信息
        每次调用此函数时，都会覆盖前一次的订阅设定，不在订阅列表里的合约，会停止行情推送
        :param ins_list: ins_list 是一个列表，列出全部需要实时行情的合约代码。
        :param notify_func (可选): callback_func 是一个回调函数，每当有报价数据变更时会触发。此函数应该接受一个参数 ins_id
        :example:
            订阅 cu1803,SR709,IF1709 这三个合约的报价:  subscribe_quote(["cu1803", ”SR709", "IF1709"])
        """
        if notify_func:
            self.quote_callback_func = notify_func
        req = {
            "aid": "subscribe_quote",
            "ins_list": ",".join(ins_list),
        }
        self._send_json(req)

    # ----------------------------------------------------------------------
    def subscribe_chart(self, ins_id, duration_seconds, data_length=200, notify_func=None):
        """
        订阅历史行情序列
        订阅指定合约及周期的历史数据序列（K线数据序列或Tick数据序列），这些序列数据会持续推送
        :param ins_id: 合约代码，需注意大小写
        :param duration_seconds: 历史数据周期，以秒为单位。特别的，此值指定为0表示订阅tick序列。目前支持的周期包括：
                3秒，5秒，10秒，15秒，20秒，30秒，1分钟，2分钟，3分钟，5分钟，10分钟，15分钟，20分钟，30分钟，1小时，2小时，4小时，1日
        :param data_length: 需要获取的序列长度。每个序列最大支持请求 8964 个数据
        :param notify_func (可选): notify_func 是一个回调函数，每当序列数据变更时会触发。此函数应该接受2个参数 ins_id, duration_seconds
        :example:
            订阅 cu1803 的1分钟线： subscribe_chart("cu1803", 60)
            订阅 IF1709 的tick线： subscribe_chart("IF1709", 0)
        """
        chart_id = "VN_%s_%d" % (ins_id, duration_seconds)
        if data_length > 8964:
            data_length = 8964
        if notify_func:
            self.chart_callback_func[chart_id] = notify_func
        req = {
            "aid": "set_chart",
            "chart_id": chart_id,
            "ins_list": ins_id,
            "duration": duration_seconds * 1000000000,
            "view_width": data_length,
        }
        self._send_json(req)

    # ----------------------------------------------------------------------
    def get_quote(self, ins_id):
        """
        获取报价数据
        :param ins_id: 指定合约代码
        :return: 若指定的数据不存在，返回None，否则返回如下所示的一个dict
        {
            u'datetime': u'2017-07-26 23:04:21.000001',# tick从交易所发出的时间(按北京时区)
            u'instrument_id': u'SR801', # 合约代码
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

    # ----------------------------------------------------------------------
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
        return self.back_end.get_tick_serial(ins_id)

    # ----------------------------------------------------------------------
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
        return self.back_end.get_kline_serial(ins_id, duration_seconds)

    # ----------------------------------------------------------------------
    @gen.coroutine
    def _start(self):
        self.client = yield tornado.websocket.websocket_connect(url="ws://127.0.0.1:7777/")
        print("connected")
        for req in self.requests:
            self.client.write_message(req)
        self.requests = []
        while True:
            msg = yield self.client.read_message()
            self._on_receive_msg(msg)

    def _send_json(self, obj):
        s = json.dumps(obj)
        if self.client:
            self.client.write_message(s)
        else:
            self.requests.append(s)

    def _on_receive_msg(self, msg):
        print("msg", msg)
        pack = json.loads(msg)
        datas = pack["data"]
        event1 = Event(type_='eTianQin.')
        event1.dict_['data'] = datas
        self.eventEngine.put(event1)

    def _process_pack(self, event):
        datas = event.dict_['data']
        #更新数据到存储后端
        self.back_end.input_data_pack(datas)
        #发出数据变更通知
        for data in datas:
            for selector, section in data.items():
                if selector == "quotes":
                    if self.quote_callback_func:
                        for ins_id in section.keys():
                            self.quote_callback_func(ins_id)
                elif selector == "ticks":
                    for ins_id in section.keys():
                        chart_id = "VN_%s_%d" % (ins_id, 0)
                        callback_func = self.chart_callback_func.get(chart_id, None)
                        if callback_func:
                            callback_func(ins_id, 0)
                elif selector == "klines":
                    for ins_id, sub_section in section.items():
                        for dur_nanoseconds in sub_section.keys():
                            dur_seconds = int(dur_nanoseconds) / 1000000000
                            chart_id = "VN_%s_%d" % (ins_id, dur_seconds)
                            callback_func = self.chart_callback_func.get(chart_id, None)
                            if callback_func:
                                callback_func(ins_id, dur_seconds)


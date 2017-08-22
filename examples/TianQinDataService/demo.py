# encoding: UTF-8

# 重载sys模块，设置默认字符串编码方式为utf8
import sys
reload(sys)
sys.setdefaultencoding('utf8')

from vnpy.event import EventEngine
from vnpy.data.tianqin.vntianqin import TianQinGateway, DataBackEndMemory, DataBackendMongo
from vnpy.trader.uiQt import createQApp


class DemoApp(object):
    # ----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.eventEngine = EventEngine()
        self.eventEngine.start()
        self.tianqinGateway = TianQinGateway(self.eventEngine, back_end=DataBackEndMemory())
        # mc = MongoClient(MONGO_HOST, MONGO_PORT)  # Mongo连接
        # self.tianqinGateway = TianQinGateway(self.eventEngine, back_end=DataBackendMongo(mc))

    def start(self):
        self.tianqinGateway.connect()
        self.tianqinGateway.subscribe_quote(["cu1803", "SR801", "c1801", "IF1708"], self.on_quote_data)
        self.tianqinGateway.subscribe_chart("cu1803", 5, 1000, self.on_chart_data)
        self.tianqinGateway.subscribe_chart("au1712", 0, 1000, self.on_chart_data)

    def on_quote_data(self, ins_id):
        quote = self.tianqinGateway.get_quote(ins_id)
        print("quote_update", ins_id, quote)

    def on_chart_data(self, ins_id, dur_seconds):
        if dur_seconds == 0:
            tick_serial = self.tianqinGateway.get_tick_serial(ins_id)
            print("tick_serial_update", tick_serial)
        else:
            kline_serial = self.tianqinGateway.get_kline_serial(ins_id, dur_seconds)
            print("kline_serial_update", kline_serial)

#----------------------------------------------------------------------
if __name__ == '__main__':
    app = DemoApp()
    app.start()
    sys.exit(createQApp().exec_())

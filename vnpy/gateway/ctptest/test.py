# flake8: noqa

import sys
import os
import traceback
from time import sleep

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    print(u'append {}'.format(vnpy_root))
    sys.path.append(vnpy_root)

from vnpy.gateway.ctptest import CtptestGateway
from vnpy.event import EventEngine
from vnpy.trader.constant import Exchange
from vnpy.trader.event import (
    EVENT_TICK,
    EVENT_ORDER,
    EVENT_TRADE,
    EVENT_POSITION,
    EVENT_ACCOUNT,
    EVENT_LOG,
)
from vnpy.trader.object import (
    SubscribeRequest,
)
# 这里放期货公司需要你连接的测试系统的相关信息
ctp_setting = {
    "用户名": "xxx",
    "密码": "xxx",
    "经纪商代码": "9999",
    "交易服务器": "tcp://180.168.146.187:10100",
    "行情服务器": "tcp://180.168.146.187:10110",
    "产品名称": "simnow_client_test",
    "授权编码": "0000000000000000",
    "产品信息": ""
}


def test():
    """测试"""
    from qtpy import QtCore
    import sys

    def print_log(event):
        log = event.data
        print(f'{log.time}: {log.msg}\n')

    def print_event(event):
        data = event.data
        print(f'{data.__dict__}')

    app = QtCore.QCoreApplication(sys.argv)

    event_engine = EventEngine()
    event_engine.register(EVENT_LOG, print_log)
    event_engine.register(EVENT_TICK, print_event)
    event_engine.register(EVENT_ACCOUNT, print_event)
    event_engine.register(EVENT_ORDER, print_event)
    event_engine.register(EVENT_TRADE, print_event)
    event_engine.register(EVENT_POSITION, print_event)

    event_engine.start()

    gateway = CtptestGateway(event_engine)
    gateway.connect(ctp_setting)

    # gateway.connect()
    auto_subscribe_symbols = ['rb2010']
    for symbol in auto_subscribe_symbols:
        print(u'自动订阅合约:{}'.format(symbol))
        sub = SubscribeRequest(symbol=symbol, exchange=Exchange.SHFE)
        sub.symbol = symbol
        gateway.subscribe(sub)

    couter = 20
    gateway.init_query()

    while couter > 0:
        print(u'{}'.format(couter))
        sleep(1)
        couter -= 1

    sys.exit(app.exec_())


if __name__ == '__main__':

    try:
        test()
    except Exception as ex:
        print(u'异常:{},{}'.format(str(ex), traceback.format_exc()), file=sys.stderr)
    print('Finished')

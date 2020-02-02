# flake8: noqa

# 测试 app.cta_strategy_pro.CtaLineBar组件
# 从通达信获取历史交易记录，模拟tick。推送至line_bar

import os
import sys
import json

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..', '..'))
if vnpy_root not in sys.path:
    print(f'sys.path apppend:{vnpy_root}')
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.trader.constant import Interval, Exchange
from vnpy.data.tdx.tdx_common import FakeStrategy
from vnpy.data.tdx.tdx_future_data import TdxFutureData
from vnpy.app.cta_strategy_pro.cta_line_bar import CtaLineBar
from vnpy.trader.object import TickData
from vnpy.trader.utility import get_trading_date

t1 = FakeStrategy()

tdx_api = TdxFutureData(strategy=t1)


def on_bar(bar):
    print(f'{bar.__dict__}')


# 创建10秒周期的k线
kline_setting = {}
kline_setting["name"] = "S10"
kline_setting['interval'] = Interval.SECOND
kline_setting['bar_interval'] = 10
kline_setting['price_tick'] = 0.5
kline_setting['underlying_symbol'] = 'J'
kline_s10 = CtaLineBar(strategy=t1, cb_on_bar=on_bar, setting=kline_setting)

ret, result = tdx_api.get_history_transaction_data('J99', '20200106')
# for data in result[0:10] + result[-10:]:
#    print(data)

for data in result:
    dt = data['datetime']
    price = float(data['price'])
    volume = float(data['volume'])

    tick = TickData(
        gateway_name='tdx',
        datetime=dt,
        last_price=price,
        volume=volume,
        symbol='J99',
        exchange=Exchange('DCE'),
        date=dt.strftime('%Y-%m-%d'),
        time=dt.strftime('%H:%M:%S'),
        trading_day=get_trading_date(dt)
    )

    kline_s10.on_tick(tick)

os._exit(0)

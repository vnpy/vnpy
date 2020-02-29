# flake8: noqa

import sys, os, copy, csv, signal

vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
if vnpy_root not in sys.path:
    print(f'append {vnpy_root} into sys.path')
    sys.path.append(vnpy_root)

os.environ["VNPY_TESTING"] = "1"

from vnpy.data.renko.rebuild_future import *


if __name__ == "__main__":

    if len(sys.argv) < 4:
        print(u'请输入三个参数 host symbol pricetick')
        exit()
    print(sys.argv)
    host = sys.argv[1]

    setting = {
        "host": host,
        "db_name": FUTURE_RENKO_DB_NAME,
        "cache_folder": os.path.join(vnpy_root, 'ticks', 'tdx', 'future')
    }
    builder = FutureRenkoRebuilder(setting)

    symbol = sys.argv[2]
    price_tick = float(sys.argv[3])

    print(f'启动期货renko补全,数据库:{host}/{FUTURE_RENKO_DB_NAME} 合约:{symbol}')
    builder.start(symbol=symbol, price_tick=price_tick, height=[3, 5, 10, 'K3', 'K5', 'K10'], refill=True)

    print(f'exit refill {symbol} renkos')


from time import time

import rqdatac as rq

from vnpy.trader.object import BarData
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import database_manager

USERNAME = ""
PASSWORD = ""
FIELDS = ["open", "high", "low", "close", "volume"]

rq.init(USERNAME, PASSWORD, ("rqdatad-pro.ricequant.com", 16011))


def generate_bar_from_row(row, symbol, exchange):
    """"""
    bar = BarData(
        symbol=symbol,
        exchange=Exchange(exchange),
        interval=Interval.MINUTE,
        open_price=row["open"],
        high_price=row["high"],
        low_price=row["low"],
        close_price=row["close"],
        volume=row["volume"],
        datetime=row.name.to_pydatetime(),
        gateway_name="DB"
    )
    return bar


def download_minute_bar(vt_symbol):
    """下载某一合约的分钟线数据"""
    print(f"开始下载合约数据{vt_symbol}")
    symbol, exchange = vt_symbol.split(".")

    start = time()

    df = rq.get_price(
        symbol,
        frequency="1m",
        fields=FIELDS,
        start_date='20100416',
        end_date='20190416'
    )

    bars = []
    for ix, row in df.iterrows():
        bar = generate_bar_from_row(row, symbol, exchange)
        bars.append(bar)

    database_manager.save_bar_data(bars)

    end = time()
    cost = (end - start) * 1000

    print(
        "合约%s的分钟K线数据下载完成%s - %s，耗时%s毫秒"
        % (symbol, df.index[0], df.index[-1], cost)
    )


if __name__ == "__main__":
    download_minute_bar("IF88.CFFEX")

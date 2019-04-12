from time import time

import rqdatac as rq

from vnpy.trader.database import DbBarData

USERNAME = ""
PASSWORD = ""
FIELDS = ["open", "high", "low", "close", "volume"]

rq.init(USERNAME, PASSWORD, ("rqdatad-pro.ricequant.com", 16011))


def generate_bar_from_row(row, symbol, exchange):
    """"""
    bar = DbBarData()

    bar.symbol = symbol
    bar.exchange = exchange
    bar.interval = "1m"
    bar.open_price = row["open"]
    bar.high_price = row["high"]
    bar.low_price = row["low"]
    bar.close_price = row["close"]
    bar.volume = row["volume"]
    bar.datetime = row.name.to_pydatetime()
    bar.gateway_name = "DB"
    bar.vt_symbol = f"{symbol}.{exchange}"

    return bar


def download_minute_bar(vt_symbol):
    """下载某一合约的分钟线数据"""
    print(f"开始下载合约数据{vt_symbol}")
    symbol, exchange = vt_symbol.split(".")

    start = time()

    df = rq.get_price(symbol, frequency="1m", fields=FIELDS)

    bars = []
    for ix, row in df.iterrows():
        bar = generate_bar_from_row(row, symbol, exchange)
        bars.append(bar)
    DbBarData.save_all(bars)

    end = time()
    cost = (end - start) * 1000

    print(
        "合约%s的分钟K线数据下载完成%s - %s，耗时%s毫秒"
        % (symbol, df.index[0], df.index[-1], cost)
    )


if __name__ == "__main__":
    download_minute_bar("IF88.CFFEX")

from datetime import datetime, timedelta
from typing import List

from rqdatac import init as rqdata_init
from rqdatac.services.basic import all_instruments as rqdata_all_instruments
from rqdatac.services.get_price import get_price as rqdata_get_price

from .setting import SETTINGS
from .constant import Exchange, Interval
from .object import BarData


class RqdataClient:
    """
    Client for querying history data from RQData.
    """

    def __init__(self):
        """"""
        self.username = SETTINGS["rqdata.username"]
        self.password = SETTINGS["rqdata.password"]

        self.inited = False
        self.symbols = set()

    def init(self):
        """"""
        if self.inited:
            return True

        if not self.username or not self.password:
            return False

        rqdata_init(self.username, self.password,
                    ('rqdatad-pro.ricequant.com', 16011))

        try:
            df = rqdata_all_instruments(date=datetime.now())
            for ix, row in df.iterrows():
                self.symbols.add(row['order_book_id'])
        except RuntimeError:
            return False

        self.inited = True
        return True

    def to_rq_symbol(self, symbol: str, exchange: Exchange):
        """
        CZCE product of RQData has symbol like "TA1905" while
        vt symbol is "TA905.CZCE" so need to add "1" in symbol.
        """
        if exchange in [Exchange.SSE, Exchange.SZSE]:
            if exchange == Exchange.SSE:
                rq_symbol = f"{symbol}.XSHG"
            else:
                rq_symbol = f"{symbol}.XSHE"
        else:
            if exchange is not Exchange.CZCE:
                return symbol.upper()

            for count, word in enumerate(symbol):
                if word.isdigit():
                    break

            # noinspection PyUnboundLocalVariable
            product = symbol[:count]
            year = symbol[count]
            month = symbol[count + 1:]

            if year == "9":
                year = "1" + year
            else:
                year = "2" + year

            rq_symbol = f"{product}{year}{month}".upper()

        return rq_symbol

    def query_bar(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ):
        """
        Query bar data from RQData.
        """
        rq_symbol = self.to_rq_symbol(symbol, exchange)
        if rq_symbol not in self.symbols:
            return None

        end += timedelta(1)     # For querying night trading period data

        df = rqdata_get_price(
            rq_symbol,
            frequency=interval.value,
            fields=["open", "high", "low", "close", "volume"],
            start_date=start,
            end_date=end
        )

        data: List[BarData] = []
        for ix, row in df.iterrows():
            bar = BarData(
                symbol=symbol,
                exchange=exchange,
                interval=interval,
                datetime=row.name.to_pydatetime(),
                open_price=row["open"],
                high_price=row["high"],
                low_price=row["low"],
                close_price=row["close"],
                volume=row["volume"],
                gateway_name="RQ"
            )
            data.append(bar)

        return data


rqdata_client = RqdataClient()

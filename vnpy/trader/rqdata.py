from datetime import timedelta
from typing import List, Optional

from numpy import ndarray
from rqdatac import init as rqdata_init
from rqdatac.services.basic import all_instruments as rqdata_all_instruments
from rqdatac.services.get_price import get_price as rqdata_get_price
from rqdatac.share.errors import AuthenticationFailed

from .setting import SETTINGS
from .constant import Exchange, Interval
from .object import BarData, HistoryRequest


INTERVAL_VT2RQ = {
    Interval.MINUTE: "1m",
    Interval.HOUR: "60m",
    Interval.DAILY: "1d",
}

INTERVAL_ADJUSTMENT_MAP = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta()         # no need to adjust for daily bar
}


class RqdataClient:
    """
    Client for querying history data from RQData.
    """

    def __init__(self):
        """"""
        self.username: str = SETTINGS["rqdata.username"]
        self.password: str = SETTINGS["rqdata.password"]

        self.inited: bool = False
        self.symbols: ndarray = None

    def init(self, username: str = "", password: str = "") -> bool:
        """"""
        if self.inited:
            return True

        if username and password:
            self.username = username
            self.password = password

        if not self.username or not self.password:
            return False

        try:
            rqdata_init(
                self.username,
                self.password,
                ("rqdatad-pro.ricequant.com", 16011),
                use_pool=True,
                max_pool_size=1
            )

            df = rqdata_all_instruments()
            self.symbols = df["order_book_id"].values
        except (RuntimeError, AuthenticationFailed):
            return False

        self.inited = True
        return True

    def to_rq_symbol(self, symbol: str, exchange: Exchange) -> str:
        """
        CZCE product of RQData has symbol like "TA1905" while
        vt symbol is "TA905.CZCE" so need to add "1" in symbol.
        """
        # Equity
        if exchange in [Exchange.SSE, Exchange.SZSE]:
            if exchange == Exchange.SSE:
                rq_symbol = f"{symbol}.XSHG"
            else:
                rq_symbol = f"{symbol}.XSHE"
        # Futures and Options
        elif exchange in [Exchange.SHFE, Exchange.CFFEX, Exchange.DCE, Exchange.CZCE, Exchange.INE]:
            for count, word in enumerate(symbol):
                if word.isdigit():
                    break

            product = symbol[:count]
            time_str = symbol[count:]

            # Futures
            if time_str.isdigit():
                if exchange is not Exchange.CZCE:
                    return symbol.upper()

                # Check for index symbol
                if time_str in ["88", "888", "99"]:
                    return symbol

                year = symbol[count]
                month = symbol[count + 1:]

                if year == "9":
                    year = "1" + year
                else:
                    year = "2" + year

                rq_symbol = f"{product}{year}{month}".upper()
            # Options
            else:
                if exchange in [Exchange.CFFEX, Exchange.DCE, Exchange.SHFE]:
                    rq_symbol = symbol.replace("-", "").upper()
                elif exchange == Exchange.CZCE:
                    year = symbol[count]
                    suffix = symbol[count + 1:]

                    if year == "9":
                        year = "1" + year
                    else:
                        year = "2" + year

                    rq_symbol = f"{product}{year}{suffix}".upper()
        else:
            rq_symbol = f"{symbol}.{exchange.value}"

        return rq_symbol

    def query_history(self, req: HistoryRequest) -> Optional[List[BarData]]:
        """
        Query history bar data from RQData.
        """
        if self.symbols is None:
            return None

        symbol = req.symbol
        exchange = req.exchange
        interval = req.interval
        start = req.start
        end = req.end

        rq_symbol = self.to_rq_symbol(symbol, exchange)
        if rq_symbol not in self.symbols:
            return None

        rq_interval = INTERVAL_VT2RQ.get(interval)
        if not rq_interval:
            return None

        # For adjust timestamp from bar close point (RQData) to open point (VN Trader)
        adjustment = INTERVAL_ADJUSTMENT_MAP[interval]

        # For querying night trading period data
        end += timedelta(1)

        # Only query open interest for futures contract
        fields = ["open", "high", "low", "close", "volume"]
        if not symbol.isdigit():
            fields.append("open_interest")

        df = rqdata_get_price(
            rq_symbol,
            frequency=rq_interval,
            fields=fields,
            start_date=start,
            end_date=end,
            adjust_type="none"
        )

        data: List[BarData] = []

        if df is not None:
            for ix, row in df.iterrows():
                bar = BarData(
                    symbol=symbol,
                    exchange=exchange,
                    interval=interval,
                    datetime=row.name.to_pydatetime() - adjustment,
                    open_price=row["open"],
                    high_price=row["high"],
                    low_price=row["low"],
                    close_price=row["close"],
                    volume=row["volume"],
                    open_interest=row.get("open_interest", 0),
                    gateway_name="RQ"
                )

                data.append(bar)

        return data


rqdata_client = RqdataClient()

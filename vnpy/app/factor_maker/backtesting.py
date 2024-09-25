from datetime import timedelta, datetime

from vnpy.app.portfolio_strategy.base import EngineType
from vnpy.trader.constant import Interval, Exchange
from vnpy.trader.database import BaseDatabase, get_database
from vnpy.trader.object import BarData
import polars as pl

from vnpy.trader.utility import extract_vt_symbol, convert_dict_to_dataframe

INTERVAL_DELTA_MAP: dict[Interval, timedelta] = {
    Interval.MINUTE: timedelta(minutes=1),
    Interval.HOUR: timedelta(hours=1),
    Interval.DAILY: timedelta(days=1),
}


class BacktestingEngine:
    """因子回测引擎"""

    engine_type: EngineType = EngineType.BACKTESTING
    gateway_name: str = "BACKTESTING"

    def __init__(self) -> None:
        self.vt_symbols: list[str] = []
        self.start: datetime = None
        self.end: datetime = None

        self.interval: Interval = Interval.MINUTE

        self.factor_name: str = ""

        self.commission_rate: float = 0
        self.slippage: float = 0
        self.size: int = 1
        self.price_tick: float = 0

        self.history_bar: dict[tuple, float] = None
        self.history_data = None
        self.dts: set[datetime] = set()

        self.factor: pl.DataFrame = None
        self.logs: list = []

        self.database: BaseDatabase = get_database()

    def clear_data(self) -> None:
        """清空数据"""
        self.bars = None
        self.factor = None
        self.logs = []

    def set_parameters(
            self,
            vt_symbols: list[str],
            start: datetime,
            end: datetime,
            interval: Interval,
            factor_name: str,
            commission_rate: float,
            slippage: float,
            size: int,
            price_tick: float
    ) -> None:
        """设置回测参数"""
        self.vt_symbols = vt_symbols
        self.start = start
        self.end = end
        self.interval = interval
        self.factor_name = factor_name
        self.commission_rate = commission_rate
        self.slippage = slippage
        self.size = size
        self.price_tick = price_tick

    def load_data(self) -> None:
        """加载数据"""
        self.clear_data()
        self.load_bars()
        self.load_factor()

    def load_bars(self):
        """加载K线数据"""
        self.output("开始加载历史数据")

        if not self.end:
            self.end = datetime.now()

        if self.start >= self.end:
            self.output(f"起始日期必须小于结束日期")
            return

        # 清理上次加载的历史数据
        self.history_bar.clear()
        self.dts.clear()

        # 每次加载30天历史数据
        progress_delta: timedelta = timedelta(days=30)
        total_delta: timedelta = self.end - self.start
        interval_delta: timedelta = INTERVAL_DELTA_MAP[self.interval]

        for vt_symbol in self.vt_symbols:
            symbol, exchange = extract_vt_symbol(vt_symbol)
            if self.interval == Interval.MINUTE:
                start: datetime = self.start
                end: datetime = self.start + progress_delta
                progress = 0

                data_count = 0
                while start < self.end:
                    end = min(end, self.end)

                    data: list[BarData] = self.database.load_bar_data(
                        symbol=symbol,
                        exchange=exchange,
                        interval=self.interval,
                        start=start,
                        end=end
                    )

                    for bar in data:
                        self.dts.add(bar.datetime)
                        self.history_bar[(bar.datetime, vt_symbol)] = (bar.open_price + bar.high_price + bar.low_price + bar.close_price) / 4
                        data_count += 1

                    progress += progress_delta / total_delta
                    progress = min(progress, 1)
                    self.output(
                        "{}加载进度：[{:.0%}]".format(
                            vt_symbol, progress
                        )
                    )

                    start = end + interval_delta
                    end += (progress_delta + interval_delta)
            else:
                data: list[BarData] = self.database.load_bar_data(
                    symbol=symbol,
                    exchange=exchange,
                    interval=self.interval,
                    start=self.start,
                    end=self.end
                )

                for bar in data:
                    self.dts.add(bar.datetime)
                    self.history_bar[(bar.datetime, vt_symbol)] = (bar.open_price + bar.high_price + bar.low_price + bar.close_price) / 4

                data_count = len(data)

            self.output("{}历史数据加载完成，数据量：{}".format(vt_symbol, data_count))

        self.history_data: pl.DataFrame = convert_dict_to_dataframe(data=self.history_bar, is_polars=True)


        self.output("所有历史数据加载完成")

    def load_factor(self):
        pass

    def run_backtesting(self):
        """运行回测"""
        pass

    def output(self, msg) -> None:
        """输出回测引擎信息"""
        print(f"{datetime.now()}\t{msg}")

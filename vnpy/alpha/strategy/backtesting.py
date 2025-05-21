from collections import defaultdict
from datetime import date, datetime
from copy import copy
from typing import cast
import traceback

import numpy as np
import polars as pl
import plotly.graph_objects as go               # type: ignore
from plotly.subplots import make_subplots       # type: ignore
from tqdm import tqdm                           # type: ignore

from vnpy.trader.constant import Direction, Offset, Interval, Status
from vnpy.trader.object import OrderData, TradeData, BarData
from vnpy.trader.utility import round_to, extract_vt_symbol

from ..logger import logger
from ..lab import AlphaLab
from .template import AlphaStrategy


class BacktestingEngine:
    """Alpha strategy backtesting engine"""

    gateway_name: str = "BACKTESTING"

    def __init__(self, lab: AlphaLab) -> None:
        """Constructor"""
        self.lab: AlphaLab = lab

        self.vt_symbols: list[str] = []
        self.start: datetime
        self.end: datetime

        self.long_rates: dict[str, float] = {}
        self.short_rates: dict[str, float] = {}
        self.sizes: dict[str, float] = {}
        self.priceticks: dict[str, float] = {}

        self.capital: float = 0
        self.risk_free: float = 0
        self.annual_days: int = 0

        self.strategy_class: type[AlphaStrategy]
        self.strategy: AlphaStrategy
        self.bars: dict[str, BarData] = {}
        self.datetime: datetime | None = None

        self.interval: Interval
        self.history_data: dict[tuple, BarData] = {}
        self.dts: set[datetime] = set()

        self.limit_order_count: int = 0
        self.limit_orders: dict[str, OrderData] = {}
        self.active_limit_orders: dict[str, OrderData] = {}

        self.trade_count: int = 0
        self.trades: dict[str, TradeData] = {}

        self.logs: list[str] = []

        self.daily_results: dict[date, PortfolioDailyResult] = {}
        self.daily_df: pl.DataFrame

        self.pre_closes: defaultdict = defaultdict(float)

        self.cash: float = 0
        self.signal_df: pl.DataFrame

    def set_parameters(
        self,
        vt_symbols: list[str],
        interval: Interval,
        start: datetime,
        end: datetime,
        capital: int = 1_000_000,
        risk_free: float = 0,
        annual_days: int = 240
    ) -> None:
        """Set parameters"""
        self.vt_symbols = vt_symbols
        self.interval = interval

        self.start = start
        self.end = end
        self.capital = capital
        self.risk_free = risk_free
        self.annual_days = annual_days

        self.cash = capital

        contract_settings: dict = self.lab.load_contract_setttings()
        for vt_symbol in vt_symbols:
            setting: dict = contract_settings.get(vt_symbol, None)
            if not setting:
                logger.warning(f"Trading configuration for contract {vt_symbol} not found, please check!")
                continue

            self.long_rates[vt_symbol] = setting["long_rate"]
            self.short_rates[vt_symbol] = setting["short_rate"]
            self.sizes[vt_symbol] = setting["size"]
            self.priceticks[vt_symbol] = setting["pricetick"]

    def add_strategy(self, strategy_class: type, setting: dict, signal_df: pl.DataFrame) -> None:
        """Add strategy"""
        self.strategy_class = strategy_class
        self.strategy = strategy_class(
            self, strategy_class.__name__, copy(self.vt_symbols), setting
        )
        self.signal_df = signal_df

    def load_data(self) -> None:
        """Load historical data"""
        logger.info("Start loading historical data")

        if not self.end:
            self.end = datetime.now()

        if self.start >= self.end:
            logger.info("Start date must be less than end date")
            return

        # Clear previously loaded historical data
        self.history_data.clear()
        self.dts.clear()

        # Load historical data for each symbol
        empty_symbols: list[str] = []
        for vt_symbol in tqdm(self.vt_symbols, total=len(self.vt_symbols)):
            data: list[BarData] = self.lab.load_bar_data(
                vt_symbol,
                self.interval,
                self.start,
                self.end
            )

            for bar in data:
                self.dts.add(bar.datetime)
                self.history_data[(bar.datetime, vt_symbol)] = bar

            data_count = len(data)
            if not data_count:
                empty_symbols.append(vt_symbol)

        if empty_symbols:
            logger.info(f"Historical data for some contracts is empty: {empty_symbols}")

        logger.info("All historical data loading complete")

    def run_backtesting(self) -> None:
        """Start backtesting"""
        self.strategy.on_init()
        logger.info("Strategy initialization complete")

        # Use remaining historical data for strategy backtesting
        dts: list = list(self.dts)
        dts.sort()

        logger.info("Start replaying historical data")
        for dt in dts:
            try:
                self.new_bars(dt)
            except Exception:
                logger.info("Exception triggered, backtest terminated")
                logger.info(traceback.format_exc())
                return

        logger.info("Historical data replay finished")

    def calculate_result(self) -> pl.DataFrame | None:
        """Calculate daily mark-to-market profit and loss"""
        logger.info("Start calculating daily mark-to-market P&L")

        if not self.trades:
            logger.info("Trade records are empty, cannot calculate")
            return None

        for trade in self.trades.values():
            if not trade.datetime:
                continue

            d: date = trade.datetime.date()
            daily_result: PortfolioDailyResult = self.daily_results[d]
            daily_result.add_trade(trade)

        pre_closes: dict[str, float] = {}
        start_poses: dict[str, float] = {}

        for daily_result in self.daily_results.values():
            daily_result.calculate_pnl(
                pre_closes,
                start_poses,
                self.sizes,
                self.long_rates,
                self.short_rates
            )

            pre_closes = daily_result.close_prices
            start_poses = daily_result.end_poses

        results: dict = defaultdict(list)

        for daily_result in self.daily_results.values():
            fields: list = [
                "date", "trade_count", "turnover",
                "commission", "trading_pnl",
                "holding_pnl", "total_pnl", "net_pnl"
            ]
            for key in fields:
                value = getattr(daily_result, key)
                results[key].append(value)

        if results:
            self.daily_df = pl.DataFrame([
                pl.Series("date", results["date"], dtype=pl.Date),
                pl.Series("trade_count", results["trade_count"], dtype=pl.Int64),
                pl.Series("turnover", results["turnover"], dtype=pl.Float64),
                pl.Series("commission", results["commission"], dtype=pl.Float64),
                pl.Series("trading_pnl", results["trading_pnl"], dtype=pl.Float64),
                pl.Series("holding_pnl", results["holding_pnl"], dtype=pl.Float64),
                pl.Series("total_pnl", results["total_pnl"], dtype=pl.Float64),
                pl.Series("net_pnl", results["net_pnl"], dtype=pl.Float64),
            ])

        logger.info("Daily mark-to-market P&L calculation complete")
        return self.daily_df

    def calculate_statistics(self) -> dict:
        """Calculate strategy statistics"""
        logger.info("Start calculating strategy statistics")

        # Initialize statistics
        start_date: str = ""
        end_date: str = ""
        total_days: int = 0
        profit_days: int = 0
        loss_days: int = 0
        end_balance: float = 0
        max_drawdown: float = 0
        max_ddpercent: float = 0
        max_drawdown_duration: int = 0
        total_net_pnl: float = 0
        daily_net_pnl: float = 0
        total_commission: float = 0
        daily_commission: float = 0
        total_turnover: float = 0
        daily_turnover: float = 0
        total_trade_count: int = 0
        daily_trade_count: float = 0
        total_return: float = 0
        annual_return: float = 0
        daily_return: float = 0
        return_std: float = 0
        sharpe_ratio: float = 0
        return_drawdown_ratio: float = 0

        # Check if bankruptcy occurred
        positive_balance: bool = False

        # Calculate capital-related metrics
        df: pl.DataFrame = self.daily_df

        if df is not None:
            df = df.with_columns(
                # Strategy capital
                balance=pl.col("net_pnl").cum_sum() + self.capital
            ).with_columns(
                # Strategy return
                pl.col("balance").pct_change().fill_null(0).alias("return"),
                # Capital high watermark
                highlevel=pl.col("balance").cum_max()
            ).with_columns(
                # Capital drawdown
                drawdown=pl.col("balance") - pl.col("highlevel"),
                # Percentage drawdown
                ddpercent=(pl.col("balance") / pl.col("highlevel") - 1) * 100
            )

            # Check if bankruptcy occurred
            positive_balance = (df["balance"] > 0).all()
            if not positive_balance:
                logger.info("Bankruptcy (capital less than or equal to 0) occurred during backtesting, cannot calculate strategy statistics")

            # Save data object
            self.daily_df = df

        # Calculate statistics
        if positive_balance:
            start_date = df["date"][0]
            end_date = df["date"][-1]

            total_days = len(df)
            profit_days = df.filter(pl.col("net_pnl") > 0).height
            loss_days = df.filter(pl.col("net_pnl") < 0).height

            end_balance = df["balance"][-1]
            max_drawdown = cast(float, df["drawdown"].min())
            max_ddpercent = cast(float, df["ddpercent"].min())

            max_drawdown_end_idx = cast(int, df["drawdown"].arg_min())
            max_drawdown_end = df["date"][max_drawdown_end_idx]

            if isinstance(max_drawdown_end, date):
                max_drawdown_start_idx = cast(int, df.slice(0, max_drawdown_end_idx + 1)["balance"].arg_max())
                max_drawdown_start = df["date"][max_drawdown_start_idx]
                max_drawdown_duration = (max_drawdown_end - max_drawdown_start).days
            else:
                max_drawdown_duration = 0

            total_net_pnl = df["net_pnl"].sum()
            daily_net_pnl = total_net_pnl / total_days

            total_commission = df["commission"].sum()
            daily_commission = total_commission / total_days

            total_turnover = df["turnover"].sum()
            daily_turnover = total_turnover / total_days

            total_trade_count = cast(int, df["trade_count"].sum())
            daily_trade_count = total_trade_count / total_days

            total_return = (end_balance / self.capital - 1) * 100
            annual_return = total_return / total_days * self.annual_days
            daily_return = cast(float, df["return"].mean()) * 100
            return_std = cast(float, df["return"].std()) * 100

            if return_std:
                daily_risk_free = self.risk_free / np.sqrt(self.annual_days)
                sharpe_ratio = (daily_return - daily_risk_free) / return_std * np.sqrt(self.annual_days)
            else:
                sharpe_ratio = 0

            return_drawdown_ratio = -total_net_pnl / max_drawdown

        # Output results
        logger.info("-" * 30)
        logger.info(f"First trading day:  {start_date}")
        logger.info(f"Last trading day:  {end_date}")

        logger.info(f"Total trading days:  {total_days}")
        logger.info(f"Profit trading days:  {profit_days}")
        logger.info(f"Loss trading days:  {loss_days}")

        logger.info(f"Starting capital:  {self.capital:,.2f}")
        logger.info(f"Ending capital:  {end_balance:,.2f}")

        logger.info(f"Total return:  {total_return:,.2f}%")
        logger.info(f"Annualized return:  {annual_return:,.2f}%")
        logger.info(f"Max drawdown:   {max_drawdown:,.2f}")
        logger.info(f"Max drawdown percentage: {max_ddpercent:,.2f}%")
        logger.info(f"Longest drawdown duration (days):   {max_drawdown_duration}")

        logger.info(f"Total net P&L:  {total_net_pnl:,.2f}")
        logger.info(f"Total commission:  {total_commission:,.2f}")
        logger.info(f"Total turnover:  {total_turnover:,.2f}")
        logger.info(f"Total trades:  {total_trade_count}")

        logger.info(f"Daily average P&L:  {daily_net_pnl:,.2f}")
        logger.info(f"Daily average commission:  {daily_commission:,.2f}")
        logger.info(f"Daily average turnover:  {daily_turnover:,.2f}")
        logger.info(f"Daily average trades:  {daily_trade_count}")

        logger.info(f"Daily average return:  {daily_return:,.2f}%")
        logger.info(f"Return standard deviation:  {return_std:,.2f}%")
        logger.info(f"Sharpe Ratio：  {sharpe_ratio:,.2f}")
        logger.info(f"Return/Drawdown ratio:  {return_drawdown_ratio:,.2f}")

        statistics: dict = {
            "start_date": start_date,
            "end_date": end_date,
            "total_days": total_days,
            "profit_days": profit_days,
            "loss_days": loss_days,
            "capital": self.capital,
            "end_balance": end_balance,
            "max_drawdown": max_drawdown,
            "max_ddpercent": max_ddpercent,
            "max_drawdown_duration": max_drawdown_duration,
            "total_net_pnl": total_net_pnl,
            "daily_net_pnl": daily_net_pnl,
            "total_commission": total_commission,
            "daily_commission": daily_commission,
            "total_turnover": total_turnover,
            "daily_turnover": daily_turnover,
            "total_trade_count": total_trade_count,
            "daily_trade_count": daily_trade_count,
            "total_return": total_return,
            "annual_return": annual_return,
            "daily_return": daily_return,
            "return_std": return_std,
            "sharpe_ratio": sharpe_ratio,
            "return_drawdown_ratio": return_drawdown_ratio,
        }

        # Filter extreme values
        for key, value in statistics.items():
            if value in (np.inf, -np.inf):
                value = 0
            statistics[key] = np.nan_to_num(value)

        logger.info("Strategy statistics calculation complete")
        return statistics

    def show_chart(self) -> None:
        """Display chart"""
        df: pl.DataFrame = self.daily_df

        fig = make_subplots(
            rows=4,
            cols=1,
            subplot_titles=["Balance", "Drawdown", "Daily Pnl", "Pnl Distribution"],
            vertical_spacing=0.06
        )

        balance_line = go.Scatter(
            x=df["date"],
            y=df["balance"],
            mode="lines",
            name="Balance"
        )
        drawdown_scatter = go.Scatter(
            x=df["date"],
            y=df["drawdown"],
            fillcolor="red",
            fill='tozeroy',
            mode="lines",
            name="Drawdown"
        )
        pnl_bar = go.Bar(y=df["net_pnl"], name="Daily Pnl")
        pnl_histogram = go.Histogram(x=df["net_pnl"], nbinsx=100, name="Days")

        fig.add_trace(balance_line, row=1, col=1)
        fig.add_trace(drawdown_scatter, row=2, col=1)
        fig.add_trace(pnl_bar, row=3, col=1)
        fig.add_trace(pnl_histogram, row=4, col=1)

        fig.update_layout(height=1000, width=1000)
        fig.show()

    def show_performance(self, benchmark_symbol: str) -> None:
        """Display performance metrics"""
        # Load benchmark prices
        benchmark_bars: list[BarData] = self.lab.load_bar_data(benchmark_symbol, self.interval, self.start, self.end)

        benchmark_prices: list[float] = []
        for bar in benchmark_bars:
            benchmark_prices.append(bar.close_price)

        # Calculate strategy performance
        performance_df: pl.DataFrame = (
            self.daily_df.with_columns(
                # Cumulative return
                cumulative_return=pl.col("balance").pct_change().cum_sum(),
                # Cumulative cost
                cumulative_cost=(pl.col("commission") / pl.col("balance").shift(1)).cum_sum()
            ).with_columns(
                # Benchmark price
                benchmark_price=pl.Series(values=benchmark_prices, dtype=pl.Float64)
            ).with_columns(
                # Benchmark return
                benchmark_return=pl.col("benchmark_price").pct_change().cum_sum()
            ).with_columns(
                # Excess return
                excess_return=(pl.col("cumulative_return") - pl.col("benchmark_return"))
            ).with_columns(
                # Net excess return
                net_excess_return=(pl.col("excess_return") - pl.col("cumulative_cost")),
            ).with_columns(
                # Excess return drawdown
                excess_return_drawdown=(pl.col("excess_return") - pl.col("excess_return").cum_max()),
                # Net excess return drawdown
                net_excess_return_drawdown=(pl.col("net_excess_return") - pl.col("net_excess_return").cum_max())
            )
        )

        # Draw chart
        fig: go.Figure = make_subplots(
            rows=5,
            cols=1,
            subplot_titles=["Return", "Alpha", "Turnover", "Alpha Drawdown", "Alpha Drawdown with Cost"],
            vertical_spacing=0.06
        )

        strategy_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["cumulative_return"],
            mode="lines",
            name="Strategy"
        )
        net_strategy_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["cumulative_return"] - performance_df["cumulative_cost"],
            mode="lines",
            name="Strategy with Cost"
        )
        benchmark_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["benchmark_return"],
            mode="lines",
            name="Benchmark"
        )
        excess_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["excess_return"],
            mode="lines",
            name="Alpha"
        )
        net_excess_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["net_excess_return"],
            mode="lines",
            name="Alpha with Cost"
        )
        turnover_curve: go.Scatter = go.Scatter(
            x=self.daily_df["date"],
            y=self.daily_df["turnover"] / self.daily_df["balance"].shift(1),
            name="Turnover",
        )
        excess_drawdown_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["excess_return_drawdown"],
            fill='tozeroy',
            mode="lines",
            name="Alpha Drawdown"
        )
        net_excess_drawdown_curve: go.Scatter = go.Scatter(
            x=performance_df["date"],
            y=performance_df["net_excess_return_drawdown"],
            fill='tozeroy',
            mode="lines",
            name="Alpha Drawdown with Cost"
        )

        fig.add_trace(strategy_curve, row=1, col=1)
        fig.add_trace(net_strategy_curve, row=1, col=1)
        fig.add_trace(benchmark_curve, row=1, col=1)
        fig.add_trace(excess_curve, row=2, col=1)
        fig.add_trace(net_excess_curve, row=2, col=1)
        fig.add_trace(turnover_curve, row=3, col=1)
        fig.add_trace(excess_drawdown_curve, row=4, col=1)
        fig.add_trace(net_excess_drawdown_curve, row=5, col=1)

        fig.update_layout(
            height=1500,
            width=1200,
            plot_bgcolor="white",
            paper_bgcolor="white",
            xaxis=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            xaxis2=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            xaxis3=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            xaxis4=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            xaxis5=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            yaxis=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            yaxis2=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            yaxis3=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            yaxis4=dict(showgrid=True, gridwidth=1, gridcolor='LightGray'),
            yaxis5=dict(showgrid=True, gridwidth=1, gridcolor='LightGray')
        )
        fig.show()

    def update_daily_close(self, bars: dict[str, BarData], dt: datetime) -> None:
        """Update daily closing price"""
        d: date = dt.date()

        close_prices: dict[str, float] = {}
        for bar in bars.values():
            if not bar.close_price:
                close_prices[bar.vt_symbol] = self.pre_closes[bar.vt_symbol]
            else:
                close_prices[bar.vt_symbol] = bar.close_price

        daily_result: PortfolioDailyResult | None = self.daily_results.get(d, None)

        if daily_result:
            daily_result.update_close_prices(close_prices)
        else:
            self.daily_results[d] = PortfolioDailyResult(d, close_prices)

    def new_bars(self, dt: datetime) -> None:
        """Push historical data"""
        self.datetime = dt

        bars: dict[str, BarData] = {}
        for vt_symbol in self.vt_symbols:
            last_bar = self.bars.get(vt_symbol, None)
            if last_bar:
                if last_bar.close_price:
                    self.pre_closes[vt_symbol] = last_bar.close_price

            bar: BarData | None = self.history_data.get((dt, vt_symbol), None)

            # Check if historical data for the specified time of the contract is obtained
            if bar:
                # Update K-line for order matching
                self.bars[vt_symbol] = bar
                # Cache K-line data for strategy.on_bars update
                bars[vt_symbol] = bar
            # If not available, but there is contract data cached in the self.bars dictionary, use previous data to fill
            elif vt_symbol in self.bars:
                old_bar: BarData = self.bars[vt_symbol]

                fill_bar: BarData = BarData(
                    symbol=old_bar.symbol,
                    exchange=old_bar.exchange,
                    datetime=dt,
                    open_price=old_bar.close_price,
                    high_price=old_bar.close_price,
                    low_price=old_bar.close_price,
                    close_price=old_bar.close_price,
                    gateway_name=old_bar.gateway_name
                )
                self.bars[vt_symbol] = fill_bar

        self.cross_order()
        self.strategy.on_bars(bars)

        self.update_daily_close(self.bars, dt)

    def cross_order(self) -> None:
        """Match limit orders"""
        for order in list(self.active_limit_orders.values()):
            bar: BarData = self.bars[order.vt_symbol]

            long_cross_price: float = bar.low_price
            short_cross_price: float = bar.high_price
            long_best_price: float = bar.open_price
            short_best_price: float = bar.open_price

            # Push order status update for unfilled orders
            if order.status == Status.SUBMITTING:
                order.status = Status.NOTTRADED
                self.strategy.update_order(order)

            # Calculate price limits
            pricetick: float = self.priceticks[order.vt_symbol]
            pre_close: float = self.pre_closes.get(order.vt_symbol, 0)

            limit_up: float = round_to(pre_close * 1.1, pricetick)
            limit_down: float = round_to(pre_close * 0.9, pricetick)

            # Check limit orders that can be matched
            long_cross: bool = (
                order.direction == Direction.LONG
                and order.price >= long_cross_price
                and long_cross_price > 0
                and bar.low_price < limit_up        # Not a full-day limit-up market
            )

            short_cross: bool = (
                order.direction == Direction.SHORT
                and order.price <= short_cross_price
                and short_cross_price > 0
                and bar.high_price > limit_down     # Not a full-day limit-down market
            )

            if not long_cross and not short_cross:
                continue

            # Push order status update for filled orders
            order.traded = order.volume
            order.status = Status.ALLTRADED
            self.strategy.update_order(order)

            if order.vt_orderid in self.active_limit_orders:
                self.active_limit_orders.pop(order.vt_orderid)

            # Generate trade information
            self.trade_count += 1

            if long_cross:
                trade_price = min(order.price, long_best_price)
            else:
                trade_price = max(order.price, short_best_price)

            trade: TradeData = TradeData(
                symbol=order.symbol,
                exchange=order.exchange,
                orderid=order.orderid,
                tradeid=str(self.trade_count),
                direction=order.direction,
                offset=order.offset,
                price=trade_price,
                volume=order.volume,
                datetime=self.datetime,
                gateway_name=self.gateway_name,
            )

            # Update available funds
            size: float = self.sizes[trade.vt_symbol]

            trade_turnover: float = trade.price * trade.volume * size

            if trade.direction == Direction.LONG:
                trade_commission: float = trade_turnover * self.long_rates[trade.vt_symbol]
            else:
                trade_commission = trade_turnover * self.short_rates[trade.vt_symbol]

            if trade.direction == Direction.LONG:
                self.cash -= trade_turnover
            else:
                self.cash += trade_turnover

            self.cash -= trade_commission

            # Push trade information
            self.strategy.update_trade(trade)
            self.trades[trade.vt_tradeid] = trade

    def get_signal(self) -> pl.DataFrame:
        """Get model prediction signal for current time"""
        if not self.datetime:
            self.write_log("Data replay has not started, cannot load model predictions")
            return pl.DataFrame()

        dt: datetime = self.datetime.replace(tzinfo=None)
        signal: pl.DataFrame = self.signal_df.filter(pl.col("datetime") == dt)

        if signal.is_empty():
            self.write_log(f"Cannot find signal model predictions for {dt}")

        return signal

    def send_order(
        self,
        strategy: AlphaStrategy,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float,
    ) -> list[str]:
        """Send order"""
        price = round_to(price, self.priceticks[vt_symbol])
        symbol, exchange = extract_vt_symbol(vt_symbol)

        self.limit_order_count += 1

        order: OrderData = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=str(self.limit_order_count),
            direction=direction,
            offset=offset,
            price=price,
            volume=volume,
            status=Status.SUBMITTING,
            datetime=self.datetime,
            gateway_name=self.gateway_name,
        )

        self.active_limit_orders[order.vt_orderid] = order
        self.limit_orders[order.vt_orderid] = order

        return [order.vt_orderid]

    def cancel_order(self, strategy: AlphaStrategy, vt_orderid: str) -> None:
        """Cancel order"""
        if vt_orderid not in self.active_limit_orders:
            return
        order: OrderData = self.active_limit_orders.pop(vt_orderid)

        order.status = Status.CANCELLED
        self.strategy.update_order(order)

    def write_log(self, msg: str, strategy: AlphaStrategy | None = None) -> None:
        """Output log message"""
        msg = f"{self.datetime}  {msg}"
        self.logs.append(msg)

    def get_all_trades(self) -> list[TradeData]:
        """Get all trade information"""
        return list(self.trades.values())

    def get_all_orders(self) -> list[OrderData]:
        """Get all order information"""
        return list(self.limit_orders.values())

    def get_all_daily_results(self) -> list["PortfolioDailyResult"]:
        """Get all daily profit and loss information"""
        return list(self.daily_results.values())

    def get_cash_available(self) -> float:
        """Get current available cash"""
        return self.cash

    def get_holding_value(self) -> float:
        """Get current holding market value"""
        holding_value: float = 0

        for vt_symbol, pos in self.strategy.pos_data.items():
            bar: BarData = self.bars[vt_symbol]
            size: float = self.sizes[vt_symbol]

            holding_value += bar.close_price * pos * size

        return holding_value


class ContractDailyResult:
    """Contract daily profit and loss result"""

    def __init__(self, result_date: date, close_price: float) -> None:
        """Constructor"""
        self.date: date = result_date
        self.close_price: float = close_price
        self.pre_close: float = 0

        self.trades: list[TradeData] = []
        self.trade_count: int = 0

        self.start_pos: float = 0
        self.end_pos: float = 0

        self.turnover: float = 0
        self.commission: float = 0

        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0
        self.net_pnl: float = 0

    def add_trade(self, trade: TradeData) -> None:
        """Add trade information"""
        self.trades.append(trade)

    def calculate_pnl(
        self,
        pre_close: float,
        start_pos: float,
        size: float,
        long_rate: float,
        short_rate: float
    ) -> None:
        """Calculate profit and loss"""
        # If there is no previous close price, use 1 instead to avoid division error
        if pre_close:
            self.pre_close = pre_close
        # else:
        #     self.pre_close = 1

        # Calculate holding profit and loss
        self.start_pos = start_pos
        self.end_pos = start_pos

        self.holding_pnl = self.start_pos * (self.close_price - self.pre_close) * size

        # Calculate trading profit and loss
        self.trade_count = len(self.trades)

        for trade in self.trades:
            if trade.direction == Direction.LONG:
                pos_change: float = trade.volume
                rate: float = long_rate
            else:
                pos_change = -trade.volume
                rate = short_rate

            self.end_pos += pos_change

            turnover: float = trade.volume * size * trade.price

            self.trading_pnl += pos_change * (self.close_price - trade.price) * size
            self.turnover += turnover
            self.commission += turnover * rate

        # Calculate daily profit and loss
        self.total_pnl = self.trading_pnl + self.holding_pnl
        self.net_pnl = self.total_pnl - self.commission

    def update_close_price(self, close_price: float) -> None:
        """Update daily close price"""
        self.close_price = close_price


class PortfolioDailyResult:
    """Portfolio daily profit and loss result"""

    def __init__(self, result_date: date, close_prices: dict[str, float]) -> None:
        """Constructor"""
        self.date: date = result_date
        self.close_prices: dict[str, float] = close_prices
        self.pre_closes: dict[str, float] = {}
        self.start_poses: dict[str, float] = {}
        self.end_poses: dict[str, float] = {}

        self.contract_results: dict[str, ContractDailyResult] = {}

        for vt_symbol, close_price in close_prices.items():
            self.contract_results[vt_symbol] = ContractDailyResult(result_date, close_price)

        self.trade_count: int = 0
        self.turnover: float = 0
        self.commission: float = 0
        self.trading_pnl: float = 0
        self.holding_pnl: float = 0
        self.total_pnl: float = 0
        self.net_pnl: float = 0

    def add_trade(self, trade: TradeData) -> None:
        """Add trade information"""
        contract_result: ContractDailyResult = self.contract_results[trade.vt_symbol]
        contract_result.add_trade(trade)

    def calculate_pnl(
        self,
        pre_closes: dict[str, float],
        start_poses: dict[str, float],
        sizes: dict[str, float],
        long_rates: dict[str, float],
        short_rates: dict[str, float]
    ) -> None:
        """Calculate profit and loss"""
        self.pre_closes = pre_closes
        self.start_poses = start_poses

        for vt_symbol, contract_result in self.contract_results.items():
            contract_result.calculate_pnl(
                pre_closes.get(vt_symbol, 0),
                start_poses.get(vt_symbol, 0),
                sizes[vt_symbol],
                long_rates[vt_symbol],
                short_rates[vt_symbol]
            )

            self.trade_count += contract_result.trade_count
            self.turnover += contract_result.turnover
            self.commission += contract_result.commission
            self.trading_pnl += contract_result.trading_pnl
            self.holding_pnl += contract_result.holding_pnl
            self.total_pnl += contract_result.total_pnl
            self.net_pnl += contract_result.net_pnl

            self.end_poses[vt_symbol] = contract_result.end_pos

    def update_close_prices(self, close_prices: dict[str, float]) -> None:
        """Update daily close prices"""
        self.close_prices.update(close_prices)

        for vt_symbol, close_price in close_prices.items():
            contract_result: ContractDailyResult | None = self.contract_results.get(vt_symbol, None)
            if contract_result:
                contract_result.update_close_price(close_price)
            else:
                self.contract_results[vt_symbol] = ContractDailyResult(self.date, close_price)

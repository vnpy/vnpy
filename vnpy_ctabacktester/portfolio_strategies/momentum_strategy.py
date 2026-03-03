from __future__ import annotations

from collections import defaultdict

from vnpy.trader.object import BarData
from vnpy_ctabacktester.portfolio_template import PortfolioTemplate


class MomentumScoreStrategy(PortfolioTemplate):
    """
    Simple momentum score strategy for portfolio backtesting.
    """

    author = "vnpy"

    lookback: int = 5
    parameters = ["lookback"]

    def __init__(self, engine, strategy_name: str, vt_symbols: list[str], setting: dict) -> None:
        super().__init__(engine, strategy_name, vt_symbols, setting)
        self.close_buffers: defaultdict[str, list[float]] = defaultdict(list)

    def on_bars(self, bars: dict[str, BarData]) -> dict[str, float]:
        scores: dict[str, float] = {}

        for vt_symbol, bar in bars.items():
            closes = self.close_buffers[vt_symbol]
            closes.append(bar.close_price)

            if len(closes) <= self.lookback:
                continue

            if len(closes) > self.lookback + 1:
                closes.pop(0)

            start_price = closes[0]
            end_price = closes[-1]
            if start_price <= 0:
                continue

            scores[vt_symbol] = end_price / start_price - 1

        return scores

from __future__ import annotations

from datetime import datetime

import pytest

from vnpy.event import Event
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.object import BarData
import vnpy_ctabacktester.engine as backtester_engine_module
from vnpy_ctabacktester.engine import (
    BacktesterEngine,
    EVENT_BACKTESTER_PORTFOLIO_FINISHED,
)
from vnpy_ctabacktester.portfolio_strategies.momentum_strategy import MomentumScoreStrategy


class DummyEventEngine:
    def __init__(self) -> None:
        self.events: list[Event] = []

    def put(self, event: Event) -> None:
        self.events.append(event)


class DummyMainEngine:
    def __init__(self) -> None:
        self._contracts = {}

    def get_contract(self, vt_symbol: str):
        return self._contracts.get(vt_symbol)


def make_bar(vt_symbol: str, dt: datetime, close_price: float) -> BarData:
    symbol, exchange = vt_symbol.split(".")
    return BarData(
        gateway_name="BACKTESTING",
        symbol=symbol,
        exchange=Exchange(exchange),
        datetime=dt,
        interval=Interval.MINUTE,
        close_price=close_price,
    )


def test_run_portfolio_backtesting_generates_result(monkeypatch) -> None:
    d0 = datetime(2024, 1, 1, 0, 0)
    d1 = datetime(2024, 1, 1, 0, 1)
    d2 = datetime(2024, 1, 1, 0, 2)

    data = {
        "BTC.NASDAQ": [
            make_bar("BTC.NASDAQ", d0, 100),
            make_bar("BTC.NASDAQ", d1, 110),
            make_bar("BTC.NASDAQ", d2, 121),
        ],
        "ETH.NASDAQ": [
            make_bar("ETH.NASDAQ", d0, 100),
            make_bar("ETH.NASDAQ", d1, 105),
            make_bar("ETH.NASDAQ", d2, 100),
        ],
    }

    def fake_load_bar_data(symbol, exchange, interval, start, end):
        vt_symbol = f"{symbol}.{exchange.value}"
        return data.get(vt_symbol, [])

    monkeypatch.setattr(backtester_engine_module, "load_bar_data", fake_load_bar_data)

    engine = BacktesterEngine.__new__(BacktesterEngine)
    engine.event_engine = DummyEventEngine()  # type: ignore[attr-defined]
    engine.main_engine = DummyMainEngine()  # type: ignore[attr-defined]
    engine.default_channel_profile = {"rate": 0.0, "slippage": 0.0, "size": 1.0, "pricetick": 0.01}
    engine._channel_profiles = {}
    engine.thread = None
    engine.portfolio_classes = {"MomentumScoreStrategy": MomentumScoreStrategy}

    engine.run_portfolio_backtesting(
        vt_symbols=["BTC.NASDAQ", "ETH.NASDAQ"],
        interval="1m",
        start=d0,
        end=d2,
        capital=1_000_000,
        top_n=1,
        class_name="MomentumScoreStrategy",
        setting={"lookback": 1},
        max_workers=1,
    )

    df = engine.get_portfolio_result_df()
    assert df is not None
    assert not df.empty
    assert "balance" in df.columns

    weights = engine.get_portfolio_latest_weights()
    assert len(weights) == 1

    event_types = [event.type for event in engine.event_engine.events]  # type: ignore[attr-defined]
    assert EVENT_BACKTESTER_PORTFOLIO_FINISHED in event_types


def test_portfolio_backtesting_with_cost_has_lower_balance(monkeypatch) -> None:
    d0 = datetime(2024, 1, 1, 0, 0)
    d1 = datetime(2024, 1, 1, 0, 1)
    d2 = datetime(2024, 1, 1, 0, 2)

    data = {
        "BTC.NASDAQ": [
            make_bar("BTC.NASDAQ", d0, 100),
            make_bar("BTC.NASDAQ", d1, 110),
            make_bar("BTC.NASDAQ", d2, 121),
        ]
    }

    def fake_load_bar_data(symbol, exchange, interval, start, end):
        vt_symbol = f"{symbol}.{exchange.value}"
        return data.get(vt_symbol, [])

    monkeypatch.setattr(backtester_engine_module, "load_bar_data", fake_load_bar_data)

    def run_with_cost(rate: float, slippage: float) -> float:
        engine = BacktesterEngine.__new__(BacktesterEngine)
        engine.event_engine = DummyEventEngine()  # type: ignore[attr-defined]
        engine.main_engine = DummyMainEngine()  # type: ignore[attr-defined]
        engine.default_channel_profile = {"rate": 0.0, "slippage": 0.0, "size": 1.0, "pricetick": 0.01}
        engine._channel_profiles = {}
        engine.thread = None
        engine.portfolio_classes = {"MomentumScoreStrategy": MomentumScoreStrategy}

        def fake_profile(vt_symbol: str, gateway_name: str = "") -> dict[str, float | str]:
            return {
                "rate": rate,
                "slippage": slippage,
                "size": 1.0,
                "pricetick": 0.01,
                "min_volume": 1.0,
                "source": "test",
            }

        engine.resolve_contract_profile = fake_profile  # type: ignore[method-assign]

        engine.run_portfolio_backtesting(
            vt_symbols=["BTC.NASDAQ"],
            interval="1m",
            start=d0,
            end=d2,
            capital=1_000_000,
            top_n=1,
            class_name="MomentumScoreStrategy",
            setting={"lookback": 1},
            max_workers=1,
        )
        df = engine.get_portfolio_result_df()
        assert df is not None
        return float(df["balance"].iloc[-1])

    balance_no_cost = run_with_cost(0.0, 0.0)
    balance_high_cost = run_with_cost(0.002, 0.002)

    assert balance_high_cost < balance_no_cost


def test_portfolio_backtesting_slippage_matches_price_unit(monkeypatch) -> None:
    d0 = datetime(2024, 1, 1, 0, 0)
    d1 = datetime(2024, 1, 1, 0, 1)
    d2 = datetime(2024, 1, 1, 0, 2)

    data = {
        "BTC.NASDAQ": [
            make_bar("BTC.NASDAQ", d0, 100),
            make_bar("BTC.NASDAQ", d1, 110),
            make_bar("BTC.NASDAQ", d2, 121),
        ]
    }

    def fake_load_bar_data(symbol, exchange, interval, start, end):
        vt_symbol = f"{symbol}.{exchange.value}"
        return data.get(vt_symbol, [])

    monkeypatch.setattr(backtester_engine_module, "load_bar_data", fake_load_bar_data)

    engine = BacktesterEngine.__new__(BacktesterEngine)
    engine.event_engine = DummyEventEngine()  # type: ignore[attr-defined]
    engine.main_engine = DummyMainEngine()  # type: ignore[attr-defined]
    engine.default_channel_profile = {"rate": 0.0, "slippage": 0.0, "size": 1.0, "pricetick": 0.01}
    engine._channel_profiles = {}
    engine.thread = None
    engine.portfolio_classes = {"MomentumScoreStrategy": MomentumScoreStrategy}

    def fake_profile(vt_symbol: str, gateway_name: str = "") -> dict[str, float | str]:
        return {
            "rate": 0.0,
            "slippage": 0.2,
            "size": 1.0,
            "pricetick": 0.01,
            "min_volume": 1.0,
            "source": "test",
        }

    engine.resolve_contract_profile = fake_profile  # type: ignore[method-assign]

    engine.run_portfolio_backtesting(
        vt_symbols=["BTC.NASDAQ"],
        interval="1m",
        start=d0,
        end=d2,
        capital=1_000_000,
        top_n=1,
        class_name="MomentumScoreStrategy",
        setting={"lookback": 1},
        max_workers=1,
    )

    df = engine.get_portfolio_result_df()
    assert df is not None

    expected_slippage = 1_000_000 / 110 * 0.2
    assert float(df["slippage"].iloc[-1]) == pytest.approx(expected_slippage)

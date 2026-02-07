from __future__ import annotations

from typing import Any

from vnpy_ctastrategy.base import EngineType
from vnpy_ctastrategy.template import CtaTemplate


class DummyEngine:
    def __init__(self, size: float, min_volume: float, capital: float) -> None:
        self._size: float = size
        self._min_volume: float = min_volume
        self.capital: float = capital

    def get_size(self, strategy: CtaTemplate) -> float:
        return self._size

    def get_min_volume(self, strategy: CtaTemplate) -> float:
        return self._min_volume

    def get_engine_type(self) -> EngineType:
        return EngineType.BACKTESTING


class DummyStrategy(CtaTemplate):
    author = "test"
    parameters: list[str] = []
    variables: list[str] = []

    def __init__(self, cta_engine: Any) -> None:
        super().__init__(cta_engine, "dummy", "BTC.USDT", {})

    def on_init(self) -> None:
        pass


def test_calc_order_volume_uses_engine_capital_and_min_volume() -> None:
    strategy = DummyStrategy(DummyEngine(size=0.001, min_volume=0.01, capital=10_000))

    volume: float = strategy.calc_order_volume(
        price=100_000,
        leverage=10,
        use_ratio=0.9,
        volume_ratio=0.5,
    )

    assert volume == 450.0


def test_calc_order_volume_returns_zero_on_invalid_input() -> None:
    strategy = DummyStrategy(DummyEngine(size=0.001, min_volume=0.01, capital=10_000))

    assert strategy.calc_order_volume(price=0) == 0
    assert strategy.calc_order_volume(price=100_000, leverage=0) == 0
    assert strategy.calc_order_volume(price=100_000, use_ratio=0) == 0
    assert strategy.calc_order_volume(price=100_000, volume_ratio=0) == 0

from __future__ import annotations

from abc import ABC, abstractmethod
from typing import Any

from vnpy.trader.object import BarData


class PortfolioTemplate(ABC):
    """
    Template for portfolio backtesting strategies.
    """

    author: str = ""
    parameters: list[str] = []

    def __init__(self, engine: Any, strategy_name: str, vt_symbols: list[str], setting: dict) -> None:
        self.engine = engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: list[str] = vt_symbols
        self.inited: bool = False
        self.update_setting(setting)

    def update_setting(self, setting: dict) -> None:
        for name in self.parameters:
            if name in setting:
                setattr(self, name, setting[name])

    @classmethod
    def get_class_parameters(cls) -> dict:
        class_parameters: dict = {}
        for name in cls.parameters:
            class_parameters[name] = getattr(cls, name)
        return class_parameters

    def on_init(self) -> None:
        """
        Optional init callback.
        """
        return

    @abstractmethod
    def on_bars(self, bars: dict[str, BarData]) -> dict[str, float]:
        """
        Return score by vt_symbol for current bar set.
        """
        raise NotImplementedError

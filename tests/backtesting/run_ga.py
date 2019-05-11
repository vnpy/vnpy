from vnpy.app.cta_strategy.backtesting import BacktestingEngine, OptimizationSetting
from vnpy.app.cta_strategy.strategies.atr_rsi_strategy import (
    AtrRsiStrategy,
)
from datetime import datetime

if __name__ == "__main__":
    engine = BacktestingEngine()
    engine.set_parameters(
        vt_symbol="IF88.CFFEX",
        interval="1m",
        start=datetime(2019, 1, 1),
        end=datetime(2019, 4, 30),
        rate=0.3 / 10000,
        slippage=0.2,
        size=300,
        pricetick=0.2,
        capital=1_000_000,
    )
    engine.add_strategy(AtrRsiStrategy, {})

    setting = OptimizationSetting()
    setting.set_target("sharpe_ratio")
    setting.add_parameter("atr_length", 3, 39, 1)
    setting.add_parameter("atr_ma_length", 10, 30, 1)

    engine.run_ga_optimization(setting)

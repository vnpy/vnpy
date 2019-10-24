from vnpy.app.cta_strategy.backtesting import BacktestingEngine, OptimizationSetting
from vnpy.app.cta_strategy.strategies.atr_rsi_strategy import AtrRsiStrategy
from vnpy.app.cta_strategy.strategies.turtle_signal_strategy import TurtleSignalStrategy
from datetime import datetime

engine = BacktestingEngine()
engine.set_parameters(
    vt_symbol="BTCUSD.BITFINEX",
    interval="1m",
    start=datetime(2017, 8, 30),
    end=datetime(2019, 8, 30),
    rate=0.3 / 1000,
    slippage=0.2,
    size=300,
    pricetick=0.2,
    capital=1_000_000,
)
engine.add_strategy(TurtleSignalStrategy, {})

engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
# exit()
# engine.show_chart()


setting = OptimizationSetting()
setting.set_target("total_return")
setting.add_parameter("entry_window", 5, 50, 5)
setting.add_parameter("exit_window", 10, 90, 10)

engine.run_ga_optimization(setting)

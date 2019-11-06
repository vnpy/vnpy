from vnpy.app.cta_strategy.backtesting import BacktestingEngine, OptimizationSetting
from vnpy.app.cta_strategy.strategies.atr_rsi_strategy import AtrRsiStrategy
from datetime import datetime
from examples.cta_backtesting.turtle_strategy import TurtleStrategy
# from backtesting_yue import BacktestingEngine,OptimizationSetting
engine = BacktestingEngine()
engine.set_parameters(
    vt_symbol="BTCUSD.BITFINEX",
    interval="1m",
    start=datetime(2018, 8, 1),
    end=datetime(2019, 8, 1),
    rate=0.3 / 1000,
    slippage=0.2,
    size=300,
    pricetick=0.2,
    capital=1_000_000,
)
engine.add_strategy(TurtleStrategy, {})

engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
exit()

setting = OptimizationSetting()
setting.set_target("sharpe_ratio")
setting.add_parameter("atr_length", 3, 39, 1)
setting.add_parameter("atr_ma_length", 10, 30, 1)

engine.run_ga_optimization(setting)

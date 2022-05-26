import json
from datetime import datetime
import pandas as pd
import dateutil.parser
from sqlalchemy import desc
import contextlib
from datetime import datetime
from importlib import reload

from vnpy.app.portfolio_strategy import BacktestingEngine
from vnpy.trader.constant import Interval
from vnpy.app.portfolio_strategy.strategies.wc_option_iv_strategy_bars2 import WCIVStrategy


date_ratio = pd.read_csv('C:/Users/kangy/.wc-vntrader/data_ratio.csv', parse_dates=['date'])
ratio_dict = date_ratio.set_index('date')['ratio'].shift(1).to_dict()
ratio_dict = {k.date(): v/100 for k, v in ratio_dict.items()}
code1 = "10003784.SSE"
code2 = "10004037.SSE"
vt_symbols = ["510050.SSE", code1, code2, "10003785.SSE", "10004038.SSE", "10003531.SSE",
              "10003532.SSE", "10003533.SSE", "10003534.SSE", "10003535.SSE",
              "10003536.SSE", "10003537.SSE", "10003538.SSE", "10003539.SSE", "10003540.SSE", "10003541.SSE",
              "10003542.SSE", "10003543.SSE",
              "10003544.SSE", "10003545.SSE", "10003546.SSE", "10003547.SSE", "10003548.SSE", "10003571.SSE",
              "10003572.SSE", "10003579.SSE",
              "10003580.SSE", "10003667.SSE", "10003668.SSE", "10003709.SSE", "10003710.SSE", "10003711.SSE",
              "10003712.SSE", "10003713.SSE",
              "10003714.SSE", "10003715.SSE", "10003716.SSE", "10003717.SSE", "10003718.SSE", "10003719.SSE",
              "10003720.SSE", "10003721.SSE",
              "10003722.SSE", "10003723.SSE", "10003724.SSE", "10003725.SSE", "10003726.SSE", "10003765.SSE",
              "10003766.SSE", "10003767.SSE",
              "10003768.SSE", "10003769.SSE", "10003770.SSE", "10003771.SSE", "10003772.SSE", "10003773.SSE",
              "10003774.SSE", "10003775.SSE",
              "10003776.SSE", "10003777.SSE", "10003778.SSE", "10003779.SSE", "10003780.SSE", "10003781.SSE",
              "10003782.SSE", "10003783.SSE",
              "10003785.SSE", "10003786.SSE", "10003787.SSE", "10003788.SSE", "10003789.SSE", "10003790.SSE",
              "10003791.SSE",
              "10003792.SSE", "10003793.SSE", "10003794.SSE", "10003795.SSE", "10003796.SSE", "10003797.SSE",
              "10003798.SSE", "10003799.SSE",
              "10003800.SSE", "10003821.SSE", "10003822.SSE", "10003823.SSE", "10003824.SSE", "10003829.SSE",
              "10003830.SSE", "10003831.SSE",
              "10003832.SSE", "10003841.SSE", "10003842.SSE", "10003843.SSE", "10003844.SSE", "10003845.SSE",
              "10003846.SSE", "10003847.SSE",
              "10003848.SSE", "10003849.SSE", "10003850.SSE", "10003851.SSE", "10003852.SSE", "10003853.SSE",
              "10003854.SSE", "10003855.SSE",
              "10003856.SSE", "10003857.SSE", "10003858.SSE", "10003877.SSE", "10003878.SSE", "10003887.SSE",
              "10003888.SSE", "10003889.SSE",
              "10003890.SSE", "10003891.SSE", "10003892.SSE", "10004019.SSE", "10004020.SSE", "10004021.SSE",
              "10004022.SSE", "10004035.SSE",
              "10004036.SSE", "10004038.SSE", "10004039.SSE", "10004040.SSE", "10004041.SSE", "10004042.SSE",
              "10004043.SSE",
              "10004044.SSE", "10004045.SSE", "10004046.SSE", "10004047.SSE", "10004048.SSE", "10004049.SSE",
              "10004050.SSE", "10004051.SSE",
              "10004052.SSE", "10004071.SSE", "10004072.SSE", "10004075.SSE", "10004076.SSE", "10004077.SSE",
              "10004078.SSE", "10004099.SSE",
              "10004100.SSE", "10004101.SSE", "10004102.SSE", "10004115.SSE", "10004116.SSE", "10004117.SSE",
              "10004118.SSE", "10004123.SSE",
              "10004124.SSE", "10004125.SSE", "10004126.SSE", "10004127.SSE", "10004128.SSE", "10004129.SSE",
              "10004130.SSE", "10004131.SSE",
              "10004132.SSE", "10004133.SSE", "10004134.SSE", "10004209.SSE", "10004210.SSE"]

engine = BacktestingEngine()
engine.set_parameters(
    vt_symbols=vt_symbols,
    interval=Interval.MINUTE,
    start=datetime(2022, 2, 24),
    end=datetime(2022, 3, 23),
    rates={
        "510050.SSE": 0.3/10000,
        "10003785.SSE": 0,
        "10004038.SSE": 0,
        "10003784.SSE": 0,
        "10004037.SSE": 0
    },
    slippages={
        "510050.SSE": 0.2,
        "10003785.SSE": 0.0002,
        "10004038.SSE": 0.0002,
        "10003784.SSE": 0.0002,
        "10004037.SSE": 0.0002
    },
    sizes={
        "510050.SSE": 300,
        "10003785.SSE": 10000,
        "10004038.SSE": 10000,
        "10003784.SSE": 10000,
        "10004037.SSE": 10000
    },
    priceticks={
        "510050.SSE": 0.001,
        "10003785.SSE": 0.0001,
        "10004038.SSE": 0.0001,
        "10003784.SSE": 0.0001,
        "10004037.SSE": 0.0001
    },
    capital=10000,
)
# engine.add_strategy(DeltaNeutralStrategy, {})
engine.add_strategy(WCIVStrategy, {'r': ratio_dict})
#%%
engine.load_data()
engine.run_backtesting()
df = engine.calculate_result()
engine.calculate_statistics()
engine.show_chart()
# 每日资金汇总

strategy_name = f'{vt_symbols[1]}-{vt_symbols[2]}.csv'
engine.daily_df['end_poses'] = engine.daily_df['end_poses'].apply(lambda xd: f'{code1}: {xd[code1]}, {code2}: {xd[code2]}')
engine.daily_df.to_csv(f'C:/Users/kangy/.wc-vntrader/result/{strategy_name}')

# for trade in engine.trades.values():
#     print(trade.datetime, trade.vt_symbol, trade.direction, trade.volume, "@", trade.price)
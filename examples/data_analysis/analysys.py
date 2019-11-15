#%%

from vnpy.trader.constant import Exchange,Interval
from .data_analysis import DataAnalysis
from datetime import datetime
import matplotlib.pyplot as plt

#%%
if __name__ == "__main__":

    herramiento = DataAnalysis()
    herramiento.load_history(
        symbol="BTCUSD",
        exchange=Exchange.BITFINEX,
        interval=Interval.MINUTE,
        start=datetime(2019, 1, 1),
        end=datetime(2019, 8, 30),
        rate = 8/10000,
        index_3to1 = ["ATR","CCI"],
        index_1to1 = ["STDDEV","SMA"],
        index_2to2 = ["AROON"],
        index_2to1 = ["AROONOSC"],
        index_4to1 = ["BOP"],
        window_index=30,
    )

    #%%

    data = herramiento.base_analysis()

    #%%

    herramiento.show_chart(data[:1500], boll_wide=2.8)

    #%%

    # 多时间周期分析
    intervals = ["5min","15min","30min","1h","2h","4h"]
    herramiento.multi_time_frame_analysis(intervals=intervals)

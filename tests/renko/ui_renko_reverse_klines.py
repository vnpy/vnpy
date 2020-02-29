# flake8: noqa
"""
多周期显示K线，
时间点同步
华富资产/李来佳
"""

import sys
import os
import ctypes
import platform
system = platform.system()
os.environ["VNPY_TESTING"] = "1"

# 将repostory的目录，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..' , '..'))
sys.path.append(ROOT_PATH)

from vnpy.trader.ui.kline.crosshair import Crosshair
from vnpy.trader.ui.kline.kline import *

if __name__ == '__main__':

    # K线界面
    try:
        kline_settings = {
            "M15":
                {
                    "data_file": "log/renko_reverse_v1_J99_M15.csv",
                    "main_indicators": [
                        "pre_high",
                        "pre_low",
                        "ma5",
                        "ma18",
                        "ma60"
                    ],
                    "sub_indicators": [
                        "atr"
                    ],
                    "dist_file": "log/renko_reverse_v1_J99_dist.csv",
                    "dist_include_list": ["M15 new signal"]
                },
            "Renko_K3":
                {
                    "data_file": "log/renko_reverse_v1_J99_Renko_K3.csv",
                    "main_indicators": [
                        "pre_high",
                        "pre_low",
                        "boll_upper",
                        "boll_middle",
                        "boll_lower",
                        "ma5",
                        "yb"
                    ],
                    "sub_indicators": [
                        "sk",
                        "sd",
                    ],
                    "trade_list_file": "log/renko_reverse_test_0229_1638_J99_trade_list.csv",
                    "dist_file": "log/renko_reverse_v1_J99_dist.csv",
                    "dist_include_list": ["new signal"]
                }
        }
        display_multi_grid(kline_settings)

    except Exception as ex:
        print(u'exception:{},trace:{}'.format(str(ex), traceback.format_exc()))

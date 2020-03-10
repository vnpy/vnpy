"""
定义appc常使用的基础组件
"""
import sys
from abc import ABC
from enum import Enum
from logging import INFO, ERROR
from vnpy.trader.constant import Direction

class Area(Enum):
    """ Kline area """
    LONG_A = 'LONG_A'
    LONG_B = 'LONG_B'
    LONG_C = 'LONG_C'
    LONG_D = 'LONG_D'
    LONG_E = 'LONG_E'
    SHORT_A = 'SHORT_A'
    SHORT_B = 'SHORT_B'
    SHORT_C = 'SHORT_C'
    SHORT_D = 'SHORT_D'
    SHORT_E = 'SHORT_E'


# 各类商品所在市场，underly_symbol: price_tick
# 上期所夜盘，9:00~10:15, 10:30~11:30, 13:30~15:00,  21:00 ~2:30
NIGHT_MARKET_SQ1 = {'AU': 0.05, 'AG': 1, 'SC': 0.1}
# 上期所夜盘，9:00~10:15, 10:30~11:30, 13:30~15:00,  21:00 ~1:00
NIGHT_MARKET_SQ2 = {'CU': 10, 'PB': 5, 'AL': 5, 'ZN': 5, 'WR': 1, 'NI': 10}
# 上期所夜盘，9:00~10:15, 10:30~11:30, 13:30~15:00,  21:00 ~23:00
NIGHT_MARKET_SQ3 = {'RU': 5, 'RB': 1, 'HC': 1, 'SP': 2, 'FU': 1, 'BU': 2, 'NR': 5, 'C': 1, 'CS': 1}
# 郑商所夜盘，9:00~10:15, 10:30~11:30, 13:30~15:00, 21:00 ~23:00
NIGHT_MARKET_ZZ = {'TA': 2, 'JR': 1, 'OI': 0, 'RO': 1, 'PM': 1, 'WH': 1, 'CF': 5, 'SR': 0, 'FG': 1,
                   'MA': 1, 'RS': 1, 'RM': 1, 'RI': 1, 'ZC': 0.2}
# 大商所夜盘，9:00~10:15, 10:30~11:30, 13:30~15:00, 21:00 ~23:00
NIGHT_MARKET_DL = {'V': 5, 'L': 5, 'BB': 0.05, 'I': 0.5, 'FB': 0.05, 'C': 1, 'PP': 1, 'A': 1, 'B': 1, 'M': 1, 'Y': 2,
                   'P': 2,
                   'JM': 0.5, 'J': 0.5, 'EG': 1}
# 中金日盘，9:15 ~11:30, 13:00~15:15
MARKET_ZJ = {'IC': 0.2, 'IF': 0.2, 'IH': 0.2, 'T': 0.005, 'TF': 0.005, 'TS': 0.005}

# 只有日盘得合约
MARKET_DAY_ONLY = {'IC': 0.2, 'IF': 0.2, 'IH': 0.2, 'T': 0.005, 'TF': 0.005, 'TS': 0.005,
                   'JD': 1, 'BB': 0.05, 'CS': 1, 'FB': 0.05, 'L': 5, 'V': 5,
                   'JR': 1, 'LR': 1, 'PM': 1, 'RI': 1, 'RS': 1, 'SM': 2, 'WH': 1, 'AP': 1, 'CJ': 1, 'UR': 1}

# 夜盘23:00收盘的合约
NIGHT_MARKET_23 = {**NIGHT_MARKET_DL, **NIGHT_MARKET_ZZ, **NIGHT_MARKET_SQ3}


class CtaComponent(ABC):
    """ CTA策略基础组件"""

    def __init__(self, strategy=None, **kwargs):
        """
        构造
        :param strategy:
        """
        self.strategy = strategy

    def write_log(self, content: str):
        """记录日志"""
        if self.strategy:
            self.strategy.write_log(msg=content, level=INFO)
        else:
            print(content)

    def write_error(self, content: str, level: int = ERROR):
        """记录错误日志"""
        if self.strategy:
            self.strategy.write_log(msg=content, level=level)
        else:
            print(content, file=sys.stderr)

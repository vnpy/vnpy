# encoding: UTF-8

import sys

from vnpy.app.cta_strategy_pro.base import Direction, CtaComponent


class CtaPosition(CtaComponent):
    """策略的仓位管理类组件
     简单的数值，代表多仓数量和空仓数量, 净仓数量，最大仓位
     上层策略使用:
     1、 on_trade 或 on_order（套利) 时，通过open_pos close_pos，更新仓位
     2、 逻辑判断, self.pos:代表净仓位; self.long_pos:代表多仓， self.short_pos，代表空仓
    """

    def __init__(self, strategy, **kwargs):
        super(CtaPosition, self).__init__(strategy=strategy, kwargs=kwargs)
        self.long_pos = 0    # 多仓持仓(正数)
        self.short_pos = 0   # 空仓持仓(负数)
        self.pos = 0        # 持仓状态 0:空仓/对空平等； >=1 净多仓 ；<=-1 净空仓
        self.maxPos = sys.maxsize        # 最大持仓量（多仓+空仓总量）

    def open_pos(self, direction: Direction, volume: float):
        """开、加仓"""
        # volume: 正整数

        if direction == Direction.LONG:     # 加多仓
            if (max(self.pos, self.long_pos) + volume) > self.maxPos:
                self.write_error(content=f'开仓异常,净:{self.pos},多:{self.long_pos},加多:{volume},超过:{self.maxPos}')

            # 更新
            self.write_log(f'多仓:{self.long_pos}->{self.long_pos + volume}')
            self.write_log(f'净:{self.pos}->{self.pos + volume}')
            self.long_pos += volume
            self.pos += volume

        if direction == Direction.SHORT:    # 加空仓
            if (min(self.pos, self.short_pos) - volume) < (0 - self.maxPos):
                self.write_error(content=f'开仓异常,净:{self.pos},空:{self.short_pos},加空:{volume},超过:{self.maxPos}')

            self.write_log(f'空仓:{self.short_pos}->{self.short_pos - volume}')
            self.write_log(f'净:{self.pos}->{self.pos - volume}')
            self.short_pos -= volume
            self.pos -= volume

        return True

    def close_pos(self, direction: Direction, volume:float):
        """平、减仓"""
        # vol: 正整数

        if direction == Direction.LONG:     # 平空仓 Cover
            if self.short_pos + volume > 0:
                self.write_error(u'平仓异常，超出仓位。净:{0},空:{1},平仓:{2}'.format(self.pos, self.short_pos, volume))

            self.write_log(f'空仓:{self.short_pos}->{self.short_pos + volume}')
            self.write_log(f'净:{self.pos}->{self.pos + volume}')
            self.short_pos += volume
            self.pos += volume

            # 更新上层策略的pos。该方法不推荐使用
            self.strategy.pos = self.pos

        if direction == Direction.SHORT:    # 平多仓
            if self.long_pos - volume < 0:
                self.write_error(u'平仓异常，超出仓位。净:{0},多:{1},平仓:{2}'.format(self.pos, self.long_pos, volume))

            self.write_log(f'多仓:{self.long_pos}->{self.long_pos - volume}')
            self.write_log(f'净:{self.pos}->{self.pos - volume}')

            self.long_pos -= volume
            self.pos -= volume

        return True

    def clear(self):
        """清除状态"""
        self.write_log(u'清除所有持仓状态')
        self.pos = 0
        self.long_pos = 0
        self.short_pos = 0

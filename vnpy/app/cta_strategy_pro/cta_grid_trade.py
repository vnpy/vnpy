# encoding: UTF-8

import os
import sys
import json
import uuid

import traceback

from collections import OrderedDict
from datetime import datetime
from vnpy.trader.utility import get_folder_path
from vnpy.app.cta_strategy_pro.base import Direction, CtaComponent

"""
网格交易，用于套利单
作者：李来佳，QQ/Wechat:28888502
ChangeLog:
160713,修改closeGrid，增加volume字段，关闭网格时，根据价格和交易量进行双重匹配.
160715,增加保存json和重启后加载本地json文件
170504，增加锁单网格
170707，增加重用选项
170719, 增加网格类型
171208，增加open_prices/snapshot
180420, 增加CtaLegacyGridTrade(传统网格：上网格做多，下网格做空)
"""

# 网格类型
SPREAD_GRID = 'spread'  # 价差回归网格
PERIOD_GRID = 'period'  # 周期网格
TREND_GRID = 'trend'  # 趋势网格
LOCK_GRID = 'lock'  # 对锁网格


class CtaGrid(object):
    """网格类
    它是网格交易的最小单元
    包括交易方向，开仓价格，平仓价格，止损价格，开仓状态，平仓状态
    """

    def __init__(self,
                 direction: Direction = None,
                 open_price: float = 0,
                 close_price: float = 0,
                 stop_price: float = 0,
                 vt_symbol: str = '',
                 volume: float = 0,
                 traded_volume: float = 0,
                 order_status: bool = False,
                 open_status: bool = False,
                 close_status: bool = False,
                 open_time: datetime = None,
                 order_time: datetime = None,
                 reuse_count: int = 0,
                 type: str = ''
                 ):

        self.id: str = str(uuid.uuid1())  # gid
        self.direction = direction  # 交易方向（LONG：多，正套；SHORT：空，反套）
        self.open_price = open_price  # 开仓价格
        self.close_price = close_price  # 止盈价格
        self.stop_price = stop_price  # 止损价格
        self.vt_symbol = vt_symbol  # 品种合约
        self.volume = volume  # 开仓数量( 兼容数字货币 )
        self.traded_volume = traded_volume  # 已成交数量 开仓时，为开仓数量，平仓时，为平仓数量
        self.order_status = order_status  # 挂单状态: True,已挂单，False，未挂单
        self.order_ids = []  # order_id list
        self.open_status = open_status  # 开仓状态
        self.close_status = close_status  # 平仓状态
        self.open_time = open_time  # 开仓时间
        self.order_time = order_time  # 委托时间
        self.lock_grid_ids = []  # 锁单的网格，[gid,gid]
        self.reuse_count = reuse_count  # 重用次数（0， 平仓后是否删除）
        self.type = type  # 网格类型标签
        self.snapshot = {}  # 切片数据，如记录开仓点时的某些状态数据

    def to_json(self):
        """输出JSON"""

        j = OrderedDict()
        j['id'] = self.id
        j['direction'] = self.direction.value if self.direction else ''
        j['open_price'] = self.open_price  # 开仓价格
        j['close_price'] = self.close_price  # 平仓价格
        j['stop_price'] = self.stop_price  # 止损价格
        j['vt_symbol'] = self.vt_symbol  # 品种数量
        j['volume'] = self.volume  # 开仓数量
        j['traded_volume'] = self.traded_volume  # 成交数量
        j['order_status'] = self.order_status  # 挂单状态: True,已挂单，False，未挂单
        j['order_ids'] = self.order_ids  # OrderId
        j['open_status'] = self.open_status  # 开仓状态
        j['close_status'] = self.close_status  # 平仓状态
        j['lockGrids'] = self.lock_grid_ids  # 对锁的网格
        j['reuse_count'] = self.reuse_count  # 是否重用
        j['type'] = self.type  # 类型
        j['snapshot'] = self.snapshot  # 切片数据

        # datetime => string
        j['open_time'] = self.open_time.strftime('%Y-%m-%d %H:%M:%S') if isinstance(self.open_time, datetime) else ''
        j['order_time'] = self.order_time.strftime('%Y-%m-%d %H:%M:%S') if isinstance(self.order_time, datetime) else ''

        return j

    def from_json(self, j):
        """从JSON恢复"""
        try:
            self.id = j.get('id', str(uuid.uuid1()))
            s = j.get('direction', '')
            self.direction = Direction(s) if len(s) > 0 else None
            self.close_price = j.get('close_price', 0)
            self.open_price = j.get('open_price', 0)
            self.stop_price = j.get('stop_price', 0)
            self.order_status = j.get('order_status', False)  # 挂单状态: True,已挂单，False，未挂单
            self.order_ids = j.get('order_ids', [])  # OrderId
            self.open_status = j.get('open_status', False)  # 开仓状态
            self.close_status = j.get('close_status', False)  # 平仓状态

            # str => datetime
            open_time = j.get('open_time', '')
            self.open_time = datetime.strptime(open_time, '%Y-%m-%d %H:%M:%S') if len(open_time) > 0 else None
            order_time = j.get('order_time', '')
            self.order_time = datetime.strptime(order_time, '%Y-%m-%d %H:%M:%S') if len(order_time) > 0 else None

            self.vt_symbol = j.get('vt_symbol', '')
            self.volume = j.get('volume', 0.0)
            self.traded_volume = j.get('traded_volume', 0.0)  # 已交易的合约数量
            self.lock_grid_ids = j.get('lockGrids', [])
            self.type = j.get('type', '')

            self.reuse_count = j.get('reuse_count', 0)

            self.snapshot = j.get('snapshot', {})
        except Exception as ex:
            print('CtaGrid fromJson Exception:{} {}'.format(str(ex), traceback.format_exc()), file=sys.stderr)

    def to_str(self):
        """转换字符串显示内容"""

        str = u'o:{}/{};c:{}/{},r:{}/opentime:{}/ordertime:{}' \
            .format(self.open_price, self.open_status, self.close_price,
                    self.close_status, self.order_ids, self.open_time, self.order_time)
        if len(self.vt_symbol) > 0:
            return u'{} {}'.format(self.vt_symbol, str)
        else:
            return str

    def __eq__(self, other):
        return self.id == other.id


class CtaGridTrade(CtaComponent):
    """网格交易类
    包括两个方向的网格队列，
    v1, 基本版
    v2，增加更新最小价格跳动，增加动态上下网格间距
    v3, 合并up/dn为一个文件
    """

    def __init__(self, strategy, **kwargs):
        """初始化
        maxlots,最大网格数
        height，网格高度（绝对值，包含minDiff）
        win，盈利数（包含minDiff）
        vol，网格开仓数
        minDiff, 最小价格跳动
        """
        super(CtaGridTrade, self).__init__(strategy=strategy)

        self.price_tick = kwargs.get('price_tick', 1)
        self.json_name = self.strategy.strategy_name  # 策略名称
        self.max_lots = kwargs.get('max_lots', 10)  # 缺省网格数量
        self.grid_height = kwargs.get('grid_height', 10 * self.price_tick)  # 最小网格高度
        self.grid_win = kwargs.get('grid_win', 10 * self.price_tick)  # 最小止盈高度

        self.volume = kwargs.get('volume', 1)  # 每次网格开仓数量
        self.rate_list = kwargs.get('rate_list', [1, 1, 1, 1, 1, 1, 1, 1, 1, 1])  # 梯级开仓数量比例

        self.up_grids = []  # 上网格列表，专门做空
        self.dn_grids = []  # 下网格列表，专门做多

        self.avg_up_open_price = 0.0  # 上网格开仓均价
        self.avg_dn_open_price = 0.0  # 下网格开仓均价

        self.max_up_open_price = 0.0  # 上网格最高开仓价
        self.min_dn_open_price = 0.0  # 下网格最小开仓价

        # 网格json文件的路径
        self.json_file_path = os.path.join(get_folder_path('data'), f'{self.json_name}_Grids.json')

    def get_volume_rate(self, idx: int = 0):
        """获取网格索引对应的开仓数量比例"""
        if idx >= len(self.rate_list) or idx < 0:
            return 1
        rate = self.rate_list[idx]

        if rate == 0:
            return 1
        else:
            return rate

    def create_grids(self, upper_line: float = 0.0, down_line: float = 0.0, max_lots: int = 0, reuse_count: int = 0):
        """创建网格队列
        upline，上支撑线
        dnline，下阻力线
        """
        lots = self.max_lots if max_lots == 0 else max_lots

        self.write_log(f'创建网格队列，upline:{upper_line},dnline:{down_line}')

        # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
        for i in range(0, lots, 1):
            grid = CtaGrid(direction=Direction.SHORT,
                           open_price=upper_line + self.grid_height * i,
                           close_price=upper_line + self.grid_height * i - self.grid_win,
                           volume=self.volume * self.get_volume_rate(i))
            if reuse_count:
                grid.reuse_count = reuse_count
            self.up_grids.append(grid)

        self.write_log(u'上网格{}==>{}初始化完成'.format(upper_line, upper_line + self.grid_height * self.max_lots))

        for i in range(0, lots, 1):
            # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
            grid = CtaGrid(direction=Direction.LONG,
                           open_price=down_line - self.grid_height * i,
                           close_price=down_line - self.grid_height * i + self.grid_win,
                           volume=self.volume * self.get_volume_rate(i))
            if reuse_count:
                grid.reuse_count = reuse_count
            self.dn_grids.append(grid)

        self.write_log(u'下网格{}==>{}初始化完成'.format(down_line, down_line - self.grid_height * self.max_lots))

        self.save()

    def to_str(self, direction: Direction):
        """显示网格"""

        pending_close_list = u''  # 平仓清单
        pending_open_list = u''  # 开仓清单
        deactive_list = u''  # 待激活清单
        opened_volume_dict = {}  # 开仓数量汇总

        if direction == Direction.LONG:
            for grid in self.dn_grids:
                t = ''
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.open_status:
                    opened_volume = 0
                    if grid.traded_volume == 0:
                        pending_close_list = pending_close_list + u'{}[{}->{},sp:{},v:{}];' \
                            .format(t, grid.open_price, grid.close_price, grid.stop_price, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pending_close_list = pending_close_list + u'[{}{}->{},sp:{},v:{}/{}];' \
                            .format(t, grid.open_price, grid.close_price, grid.stop_price, grid.volume,
                                    grid.traded_volume)
                        opened_volume = grid.volume - grid.traded_volume

                    if grid.type != '':
                        if grid.type not in opened_volume_dict:
                            opened_volume_dict[grid.type] = opened_volume
                        else:
                            opened_volume_dict[grid.type] += opened_volume

                    if 'All' not in opened_volume_dict:
                        opened_volume_dict['All'] = opened_volume
                    else:
                        opened_volume_dict['All'] += opened_volume

                # 待开仓成交
                elif not grid.open_status and grid.order_status:
                    if grid.traded_volume == 0:
                        pending_open_list = pending_open_list + u'[{}{},v:{}];'.format(t, grid.open_price, grid.volume)
                    else:
                        pending_open_list = pending_open_list + u'[{} {},v:{}/{}];' \
                            .format(t, grid.open_price, grid.volume, grid.traded_volume)

                # 等待挂单
                else:
                    deactive_list = deactive_list + u'[{}{}];'.format(t, grid.open_price)

            return u'多:待平:[{}],{};开:{};待:{}'.format(opened_volume_dict, pending_close_list, pending_open_list,
                                                    deactive_list)

        if direction == Direction.SHORT:
            for grid in self.up_grids:
                t = ''
                if grid.type == LOCK_GRID:
                    t = u'L:'
                elif grid.type == TREND_GRID:
                    t = u'T:'
                elif grid.type == PERIOD_GRID:
                    t = u'P:'
                else:
                    t = grid.type
                # 待平仓
                if grid.open_status:
                    opened_volume = 0
                    if grid.traded_volume == 0:
                        pending_close_list = pending_close_list + u'[{} {}->{},sp:{},v:{}];' \
                            .format(t, grid.open_price, grid.close_price, grid.stop_price, grid.volume)
                        opened_volume = grid.volume
                    else:
                        pending_close_list = pending_close_list + u'[{} {}->{},sp:{}, v:{}/{}];' \
                            .format(t, grid.open_price, grid.close_price, grid.stop_price, grid.volume,
                                    grid.traded_volume)
                        opened_volume = grid.volume - grid.traded_volume
                    if grid.type != '':
                        if grid.type not in opened_volume_dict:
                            opened_volume_dict[grid.type] = opened_volume
                        else:
                            opened_volume_dict[grid.type] += opened_volume
                    if 'All' not in opened_volume_dict:
                        opened_volume_dict['All'] = opened_volume
                    else:
                        opened_volume_dict['All'] += opened_volume

                # 待开仓成交
                elif not grid.open_status and grid.order_status:
                    if grid.traded_volume == 0:
                        pending_open_list = pending_open_list + u'[{} {},v:{}];'.format(t, grid.open_price, grid.volume)
                    else:
                        pending_open_list = pending_open_list + u'[{} {},v:{}/{}];' \
                            .format(t, grid.open_price, grid.volume, grid.traded_volume)

                # 等待挂单
                else:
                    deactive_list = deactive_list + u'[{}{}];'.format(t, grid.open_price)

            return u'空:待平:[{}],{};开:{};待:{}'.format(opened_volume_dict, pending_close_list, pending_open_list,
                                                    deactive_list)

    def get_grids_with_types(self, direction: Direction, types: list = []):
        """获取符合类型的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == Direction.LONG:
            grids = [x for x in self.dn_grids
                     if x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == Direction.SHORT:
            grids = [x for x in self.up_grids
                     if x.type in types]
            return grids

    def get_opened_grids_within_types(self, direction: Direction, types: list = []):
        """获取符合类型的持仓网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：网格类型列表，
        """
        # 状态一致，价格大于最低价格
        if direction == Direction.LONG:
            grids = [x for x in self.dn_grids
                     if x.open_status and x.type in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == Direction.SHORT:
            grids = [x for x in self.up_grids
                     if x.open_status and x.type in types]
            return grids

    def get_opened_grids_without_types(self, direction: Direction, types: list = []):
        """获取不符合类型的持仓网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        type：不符合网格类型列表(排除)
        """
        # 状态一致，价格大于最低价格
        if direction == Direction.LONG:
            grids = [x for x in self.dn_grids
                     if x.open_status and x.type not in types]
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == Direction.SHORT:
            grids = [x for x in self.up_grids
                     if x.open_status and x.type not in types]
            return grids

    def get_opened_grids(self, direction: Direction, allow_empty_volume: bool = False):
        """获取已开仓的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        """
        # 状态一致，价格大于最低价格
        if direction == Direction.LONG:
            grids = [x for x in self.dn_grids
                     if x.open_status and (x.volume - x.traded_volume > 0 or allow_empty_volume)]

            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == Direction.SHORT:
            grids = [x for x in self.up_grids
                     if x.open_status and (x.volume - x.traded_volume > 0 or allow_empty_volume)]
            return grids

    def get_grids(self, direction: Direction,
                  ordered: bool = False,
                  opened: bool = False,
                  closed: bool = False,
                  begin: float = 0.0,
                  end: float = 0.0,
                  type: str = ''):
        """获取未挂单的网格
        direction:做多、做空方向: 做多方向时，从dnGrids中获取;  做空方向时，从upGrids中获取
        ordered:是否已提交至服务器
        opened：是否已开仓
        closed：是否已平仓
        begin：开始价格,
        end：结束价格，
        """

        # 状态一致，价格大于最低价格
        if direction == Direction.LONG:
            if begin == 0.0:
                begin = sys.maxsize
            if end == 0.0:
                end = 0 - sys.maxsize

            grids = []
            for x in self.dn_grids:
                if x.order_status == ordered \
                        and x.open_status == opened \
                        and x.close_status == closed \
                        and end <= x.open_price <= begin \
                        and x.type == type:
                    grids.append(x)
            return grids

        # 状态一致，开仓价格小于最高价格
        if direction == Direction.SHORT:
            if begin == 0.0:
                begin = 0 - sys.maxsize
            if end == 0.0:
                end = sys.maxsize
            grids = []
            for x in self.up_grids:
                if x.order_status == ordered \
                        and x.open_status == opened \
                        and x.close_status == closed \
                        and end >= x.open_price >= begin \
                        and x.type == type:
                    grids.append(x)
            return grids

    def get_grid_by_id(self, direction: Direction, id: str):
        """寻找指定id的网格"""
        if id == '' or len(id) < 1:
            return None

        if direction == Direction.LONG:
            for x in self.dn_grids[:]:
                if x.id == id:
                    self.write_log(u'找到下网格[open={},close={},stop={},volume={}]'
                                   .format(x.open_price, x.close_price, x.stop_price, x.volume))
                    return x

        if direction == Direction.SHORT:
            for x in self.up_grids[:]:
                if x.id == id:
                    self.write_log(u'找到上网格[open={},close={},stop={},volume={}]'
                                   .format(x.open_price, x.close_price, x.stop_price, x.volume))
                    return x
        return None

    def get_opened_volumes(self, direction: Direction, types: list = []):
        """获取特定类型的网格持仓"""
        if direction == Direction.LONG:
            long_vol = [x.volume - x.traded_volume for x in self.dn_grids if x.open_status and x.type in types]
            return sum(long_vol)

        if direction == Direction.SHORT:
            short_vol = [x.volume - x.traded_volume for x in self.up_grids if x.open_status and x.type in types]
            return sum(short_vol)

    def get_first_n_last_grid(self, direction: Direction, type: str = ''):
        """获取最前/后一个的网格"""
        # 做空网格：,first =开仓价最高一个,last= 最低一个
        if direction == Direction.SHORT:
            short_grids = self.get_grids_with_types(direction=direction, types=[type])
            if short_grids is None or len(short_grids) == 0:
                return None, None

            if len(short_grids) == 1:
                return short_grids[0], short_grids[0]

            # 价格由低至高排列
            sortedGrids = sorted(short_grids, key=lambda g: g.open_price)
            return sortedGrids[-1], sortedGrids[0]

        # 做多网格： first =最低一个,last= 开仓价最高一个
        if direction == Direction.LONG:
            long_grids = self.get_grids_with_types(direction=direction, types=[type])
            if long_grids is None or len(long_grids) == 0:
                return None, None

            if len(long_grids) == 1:
                return long_grids[0], long_grids[0]

            sortedGrids = sorted(long_grids, key=lambda g: g.open_price)
            return sortedGrids[0], sortedGrids[-1]

        return None, None

    def get_last_opened_grid(self, direction: Direction, type: str = '', orderby_asc: bool = True):
        """获取最后一个开仓的网格"""
        # highest_short_price_grid = getLastOpenedGrid(Direction.SHORT
        if direction == Direction.SHORT:

            opened_short_grids = self.get_grids(direction=direction, opened=True, type=type)
            if opened_short_grids is None or len(opened_short_grids) == 0:
                return None
            if len(opened_short_grids) > 1:
                sorted_grids = sorted(opened_short_grids, key=lambda g: g.open_price)
                if orderby_asc:
                    # 取价格最高的一格
                    opened_short_grids = sorted_grids[-1:]
                else:
                    # 取价格最低的一格
                    opened_short_grids = sorted_grids[0:1]

            return opened_short_grids[0]

        if direction == Direction.LONG:
            opened_long_grids = self.get_grids(direction=direction, opened=True, type=type)
            if opened_long_grids is None or len(opened_long_grids) == 0:
                return None
            if len(opened_long_grids) > 1:
                sorted_grids = sorted(opened_long_grids, key=lambda g: g.open_price)
                if orderby_asc:
                    # 取价格最低的一格
                    opened_long_grids = sorted_grids[0:1]
                else:
                    # 取价格最高的一格
                    opened_long_grids = sorted_grids[-1:]

            return opened_long_grids[0]

    def remove_grids_by_ids(self, direction: Direction, ids: list = []):
        """移除指定id的网格"""
        if len(ids) == 0:
            return

        if direction == Direction.LONG:
            for x in self.dn_grids[:]:
                if x.id in ids:
                    self.write_log(u'清除下网格[open={},close={},stop={},volume={}]'
                                   .format(x.open_price, x.close_price, x.stop_price, x.volume))
                    self.dn_grids.remove(x)

        if direction == Direction.SHORT:
            for x in self.up_grids[:]:
                if x.id in ids:
                    self.write_log(u'清除上网格[open={},close={},stop={},volume={}]'
                                   .format(x.open_price, x.close_price, x.stop_price, x.volume))
                    self.up_grids.remove(x)

    def remove_unopen_grids_by_price(self, direction: Direction, priceline: float, types: list = ['']):
        """清除价格线以下的未开仓，未委托网格"""
        if direction == Direction.LONG:
            for x in self.dn_grids[:]:
                if x.open_price > priceline \
                        and not x.order_status \
                        and not x.open_status \
                        and not x.close_status \
                        and x.type in types:
                    self.write_log(u'清除下网格[open={0}]'.format(x.open_price))
                    self.dn_grids.remove(x)

        if direction == Direction.SHORT:
            for x in self.up_grids[:]:
                if x.open_price < priceline \
                        and not x.order_status \
                        and not x.open_status \
                        and not x.close_status \
                        and x.type in types:
                    self.write_log(u'清除上网格[open={0}]'.format(x.open_price))
                    self.up_grids.remove(x)

    def shift_grids(self, direction, pricedelta, type=''):
        """按pricedelta平移所有网格"""
        if direction == Direction.LONG:
            for x in self.dn_grids[:]:
                x.open_price += pricedelta  # 开仓价格
                x.close_price += pricedelta  # 平仓价格
                x.stop_price += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.open_prices = {}  # 套利使用，开仓价格，symbol:price

        if direction == Direction.SHORT:
            for x in self.up_grids[:]:
                x.open_price += pricedelta  # 开仓价格
                x.close_price += pricedelta  # 平仓价格
                x.stop_price += pricedelta  # 止损价格
                x.type = type  # 网格类型标签
                # self.open_prices = {}  # 套利使用，开仓价格，symbol:price

    def rebuild_grids(self, direction: Direction,
                      upper_line: float = 0.0,
                      down_line: float = 0.0,
                      middle_line: float = 0.0,
                      upper_rate: float = 1,
                      down_rate: float = 1,
                      reuse_count: int = 0):
        """重新拉网
        清除未挂单的网格，
        在上轨/下轨位置重新挂单
        upRate , 上轨网格高度比率
        dnRate， 下轨网格高度比率
        """
        self.write_log(u'重新拉网:direction:{},upline:{},dnline:{}'.format(direction, upper_line, down_line))

        # 检查上下网格的高度比率，不能低于0.5
        if upper_rate < 0.5 or down_rate < 0.5:
            upper_rate = max(0.5, upper_rate)
            down_rate = max(0.5, down_rate)

        # 重建下网格(移除未挂单、保留开仓得网格、在最低价之下才增加网格
        if direction == Direction.LONG:
            min_long_price = middle_line
            remove_grids = []
            opened_grids = []
            # 移除未挂单的下网格
            for x in self.dn_grids[:]:
                if not x.order_status and not x.open_status and not x.close_status:
                    remove_grids.append(u'{}=>{}'.format(x.open_price, x.close_price))
                    self.dn_grids.remove(x)
                else:
                    opened_grids.append(u'{}=>{}'.format(x.open_price, x.close_price))
                    if x.open_price < min_long_price:
                        min_long_price = x.open_price

            if len(remove_grids) > 0:
                self.write_log(u'清除下网格[{}]'.format(remove_grids))
            if len(opened_grids) > 0:
                self.write_log(u'保留下网格[{}]'.format(opened_grids))

            # 需要重建的剩余网格数量
            remainLots = len(self.dn_grids)
            lots = self.max_lots - remainLots

            down_line = min(down_line, min_long_price - self.grid_height * down_rate)
            self.write_log(u'需要重建的网格数量:{0},起点:{1}'.format(lots, down_line))

            if lots > 0:
                for i in range(0, lots, 1):
                    # 做多，开仓价为下阻力线-网格高度*i，平仓价为开仓价+止盈高度，开仓数量为缺省
                    open_price = int((down_line - self.grid_height * down_rate) / self.price_tick) * self.price_tick
                    close_price = int((open_price + self.grid_win * down_rate) / self.price_tick) * self.price_tick

                    grid = CtaGrid(direction=Direction.LONG,
                                   open_price=open_price,
                                   close_price=close_price,
                                   volume=self.volume * self.get_volume_rate(remainLots + i))
                    grid.reuse_count = reuse_count
                    self.dn_grids.append(grid)
                self.write_log(u'重新拉下网格:[{0}==>{1}]'.format(down_line, down_line - lots * self.grid_height * down_rate))

        # 重建上网格(移除未挂单、保留开仓得网格、在最高价之上才增加网格
        if direction == Direction.SHORT:
            max_short_price = middle_line  # 最高开空价
            remove_grids = []  # 移除的网格列表
            opened_grids = []  # 已开仓的网格列表
            # 移除未挂单的上网格
            for x in self.up_grids[:]:
                if not x.order_status and not x.open_status and not x.close_status:
                    remove_grids.append(u'{}=>{}'.format(x.open_price, x.close_price))
                    self.up_grids.remove(x)
                else:
                    opened_grids.append(u'{}=>{}'.format(x.open_price, x.close_price))

                    if x.open_price > max_short_price:
                        max_short_price = x.open_price

            if len(remove_grids) > 0:
                self.write_log(u'清除上网格[{}]'.format(remove_grids))
            if len(opened_grids) > 0:
                self.write_log(u'保留上网格[{}]'.format(opened_grids))

            # 需要重建的剩余网格数量
            remainLots = len(self.up_grids)
            lots = self.max_lots - remainLots
            upper_line = max(upper_line, max_short_price + self.grid_height * upper_rate)
            self.write_log(u'需要重建的网格数量:{0},起点:{1}'.format(lots, upper_line))

            if lots > 0:
                # 做空，开仓价为上阻力线+网格高度*i，平仓价为开仓价-止盈高度，开仓数量为缺省
                for i in range(0, lots, 1):
                    open_price = int((upper_line + self.grid_height * upper_rate) / self.price_tick) * self.price_tick
                    close_price = int((open_price - self.grid_win * upper_rate) / self.price_tick) * self.price_tick

                    grid = CtaGrid(direction=Direction.SHORT,
                                   open_price=open_price,
                                   close_price=close_price,
                                   volume=self.volume * self.get_volume_rate(remainLots + i))
                    grid.reuse_count = reuse_count
                    self.up_grids.append(grid)

                self.write_log(
                    u'重新拉上网格:[{0} ==> {1}]'.format(upper_line, upper_line + lots * self.grid_height * upper_rate))

    def recount_avg_open_price(self):
        """计算网格的平均开仓价"""
        up_open_list = [x for x in self.up_grids if x.open_status]

        self.max_up_open_price = 0 - sys.maxsize
        self.avg_up_open_price = 0 - sys.maxsize
        self.min_dn_open_price = sys.maxsize
        self.avg_dn_open_price = sys.maxsize

        total_price = 0.0
        total_volume = 0
        for x in up_open_list:
            self.max_up_open_price = max(self.max_up_open_price, x.open_price)
            total_price += x.open_price * x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_up_open_price = total_price / total_volume

        total_price = 0.0
        total_volume = 0

        dn_open_list = [x for x in self.dn_grids if x.open_status]
        for x in dn_open_list:
            self.min_dn_open_price = min(self.min_dn_open_price, x.open_price)
            total_price += x.open_price * x.volume
            total_volume += x.volume

        if total_volume > 0:
            self.avg_dn_open_price = total_price / total_volume

    def count_avg_open_price(self, grid_list):
        """计算平均开仓价"""
        total_price = 0.0
        total_volume = 0
        avg_price = 0.0

        for g in grid_list:
            total_price += g.open_price * g.volume
            total_volume += g.volume

        if total_volume > 0:
            avg_price = total_price / total_volume
        return avg_price

    def combine_opened_grids(self, direction, type=''):
        """合并已开仓的网格"""
        total_open_price = 0.0
        total_close_price = 0.0
        total_volume = 0

        if direction == Direction.SHORT:
            opened_short_grids = self.get_grids(direction=direction,
                                                opened=True,
                                                ordered=False,
                                                type=type)

            if len(opened_short_grids) <= 1:
                return
            self.write_log(u'{}个空网格合并为1个'.format(len(opened_short_grids)))
            saved_grid = opened_short_grids[-1]

            for g in opened_short_grids:
                total_open_price += g.open_price * g.volume
                total_close_price += g.close_price * g.volume
                total_volume += g.volume
                if g != saved_grid:
                    self.write_log(u'删除空网格 {}=>{},v:{}'.format(g.open_price, g.close_price, g.volume))
                    self.up_grids.remove(g)
                else:
                    self.write_log(u'保留空网格 {}=>{},v:{}'.format(g.open_price, g.close_price, g.volume))

            # 更新网格的开仓价和仓位数量
            saved_grid.open_price = int((total_open_price / total_volume) / self.price_tick) * self.price_tick
            saved_grid.volume = total_volume
            saved_grid.close_price = int((total_close_price / total_volume) / self.price_tick) * self.price_tick

            self.write_log(
                u'合并后空网格为{}=>{},v:{}'.format(saved_grid.open_price, saved_grid.close_price, saved_grid.volume))

        elif direction == Direction.LONG:
            opened_long_grids = self.get_grids(direction=direction, opened=True, ordered=False, type=type)

            if len(opened_long_grids) <= 1:
                return
            self.write_log(u'{}个多网格合并为1个'.format(len(opened_long_grids)))
            saved_grid = opened_long_grids[-1]

            for g in opened_long_grids:
                total_open_price += g.open_price * g.volume
                total_close_price += g.close_price * g.volume
                total_volume += g.volume
                if g != saved_grid:
                    self.write_log(u'删除多网格 {}=>{},v:{}'.format(g.open_price, g.close_price, g.volume))
                    self.dn_grids.remove(g)
                else:
                    self.write_log(u'保留多网格 {}=>{},v:{}'.format(g.open_price, g.close_price, g.volume))

            # 更新网格的开仓价和仓位数量
            saved_grid.open_price = int((total_open_price / total_volume) / self.price_tick) * self.price_tick
            saved_grid.volume = total_volume
            saved_grid.close_price = int((total_close_price / total_volume) / self.price_tick) * self.price_tick

            self.write_log(f'合并后多网格为{saved_grid.open_price}=>{saved_grid.close_price},v:{saved_grid.volume}')

    def clear_duplicate_grids(self, direction: Direction = None, type: str = ''):
        """去除重复开仓价的未开仓网格"""

        if direction == Direction.SHORT or direction is None:
            if len(self.up_grids) < 2:
                return
            checking_grids = self.get_grids(direction=Direction.SHORT, opened=False, ordered=False, type=type)

            if len(checking_grids) < 2:
                return

            open_price_list = []
            remove_grids = []

            for g in checking_grids:
                if g.open_price in open_price_list:
                    remove_grids.append(g)
                    continue

                open_price_list.append(g.open_price)

            for rg in remove_grids:
                try:
                    self.up_grids.remove(rg)
                except Exception:
                    pass

        if direction == Direction.LONG or direction is None:
            if len(self.dn_grids) < 2:
                return
            checking_grids = self.get_grids(direction=Direction.LONG, opened=False, ordered=False, type=type)

            if len(checking_grids) < 2:
                return

            open_price_list = []
            remove_grids = []
            for g in checking_grids:
                if g.open_price in open_price_list:
                    remove_grids.append(g)
                    continue

                open_price_list.append(g.open_price)

            for rg in remove_grids:
                try:
                    self.dn_grids.remove(rg)
                except Exception:
                    pass

    def save(self):
        """
        保存网格至本地Json文件
        2017/11/23 update: 保存时，空的列表也保存
        :return:
        """""
        # 回测模式不保存
        if self.strategy and getattr(self.strategy, 'backtesting', False):
            return

        # 更新开仓均价
        self.recount_avg_open_price()
        grids_save_path = get_folder_path('data')

        # 确保json名字与策略一致
        if self.json_name != self.strategy.strategy_name:
            self.write_log(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.json_name, self.strategy.strategy_name))
            self.json_name = self.strategy.strategy_name

        # 新版网格持久化文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.json_name))
        self.json_file_path = grid_json_file

        data = {}
        up_grids = []
        for grid in self.up_grids:
            up_grids.append(grid.to_json())
        dn_grids = []
        for grid in self.dn_grids:
            dn_grids.append(grid.to_json())
        data[u'up_grids'] = up_grids
        data[u'dn_grids'] = dn_grids

        with open(grid_json_file, 'w') as f:
            json_data = json.dumps(data, indent=4)
            f.write(json_data)

        self.write_log(u'GrideTrade保存文件{}完成'.format(grid_json_file))

    def load(self, direction, open_status_filter=[]):
        """
        加载本地Json至网格
        :param direction: Direction.SHORT,做空网格；Direction.LONG，做多网格
        :param open_status_filter: 缺省，不做过滤；True，只提取已开仓的数据，False，只提取未开仓的数据
        :return:
        """
        data = {}
        grids_save_path = get_folder_path('data')

        if self.json_name != self.strategy.strategy_name:
            self.write_log(u'JsonName {} 与 上层策略名{} 不一致.'.format(self.json_name, self.strategy.strategy_name))
            self.json_name = self.strategy.strategy_name

        # 若json文件不存在，就保存一个；若存在，就优先使用数据文件
        grid_json_file = os.path.join(grids_save_path, u'{}_Grids.json'.format(self.json_name))
        if not os.path.exists(grid_json_file):
            data['up_grids'] = []
            data['dn_grids'] = []
            self.write_log(u'{}不存在，新建保存保存'.format(grid_json_file))
            try:
                with open(grid_json_file, 'w') as f:
                    json_data = json.dumps(data, indent=4)
                    f.write(json_data)
            except Exception as ex:
                self.write_log(u'写入网格文件{}异常:{}'.format(grid_json_file, str(ex)))
        else:
            # 读取json文件
            try:
                with open(grid_json_file, 'r', encoding='utf8') as f:
                    data = json.load(f)
            except Exception as ex:
                self.write_error(u'读取网格文件{}异常:{}'.format(grid_json_file, str(ex)))

        #  从文件获取数据
        json_grids = []
        if direction == Direction.SHORT:
            json_grids = data['up_grids'] if 'up_grids' in data else []

        elif direction == Direction.LONG:
            json_grids = data['dn_grids'] if 'dn_grids' in data else []

        grids = []
        for grid_obj in json_grids:

            grid = CtaGrid(grid_obj)

            self.write_log(grid.to_str())

            # 增加对开仓状态的过滤，满足某些策略只提取已开仓的网格数据
            if len(open_status_filter) > 0:
                if grid.open_status not in open_status_filter:
                    continue

            grids.append(grid)

        # 更新开仓均价
        self.recount_avg_open_price()
        return grids

    def change_strategy_name(self, old_name, new_name):
        """
        在线更换策略实例名称，需要把Json文件也转移
        :param old_name:
        :param new_name:
        :return:
        """
        if old_name == new_name:
            self.write_log(u'更换策略实例名称失败,old:{} =>new:{}'.format(old_name, new_name))
            return

        data_folder = get_folder_path('data')

        self.json_name = new_name
        # 旧文件
        old_json_file = os.path.join(data_folder, u'{0}_Grids.json'.format(old_name))

        if os.path.isfile(old_json_file):  # 新文件若存在，移除
            try:
                os.remove(old_json_file)
            except Exception as ex:
                self.write_error(u'GridTrade.change_strategy_name 删除文件：{}异常:{}'.format(old_json_file, str(ex)))

        self.save()

    def get_types_of_opened_grids(self, direction: Direction, include_empty: bool = False):
        """
        获取开仓的网格类型列表
        :param direction:
        :param include_empty: 是否包含空值的类型
        :return:
        """
        grids = self.get_opened_grids(direction)
        types = []
        for g in grids:
            if g.type not in types and (g.type != '' if not include_empty else True):
                types.append(g.type)

        return types

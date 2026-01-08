# The MIT License (MIT)
#
# Copyright (c) 2015-present, Xiaoyou Chen
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.


from pathlib import Path

from vnpy.trader.app import BaseApp
from vnpy.trader.constant import Direction
from vnpy.trader.object import TickData, BarData, TradeData, OrderData
from vnpy.trader.utility import BarGenerator, ArrayManager

from vnpy_ctastrategy.base import APP_NAME, StopOrder
from vnpy_ctastrategy.engine import CtaEngine
from vnpy_ctastrategy.template import CtaTemplate, CtaSignal, TargetPosTemplate


__all__ = [
    "APP_NAME",
    "CtaEngine",
    "CtaTemplate",
    "CtaSignal",
    "TargetPosTemplate",
    "StopOrder",
    "Direction",
    "TickData",
    "BarData",
    "TradeData",
    "OrderData",
    "BarGenerator",
    "ArrayManager",
    "CtaStrategyApp",
]


__version__ = "1.4.1"


class CtaStrategyApp(BaseApp):
    """"""
    from vnpy_ctastrategy.locale import _

    app_name: str = APP_NAME
    app_module: str = __module__
    app_path: Path = Path(__file__).parent
    display_name: str = _("CTA策略")
    engine_class: type[CtaEngine] = CtaEngine
    widget_name: str = "CtaManager"
    icon_name: str = str(app_path.joinpath("ui", "cta.ico"))

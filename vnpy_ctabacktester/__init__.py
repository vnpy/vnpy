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

from vnpy_ctabacktester.engine import BacktesterEngine, APP_NAME


all = [
    "APP_NAME",
    "BacktesterEngine",
    "CtaBacktesterApp",
]

__version__ = "1.3.0"


class CtaBacktesterApp(BaseApp):
    """"""
    from vnpy_ctabacktester.locale import _

    app_name: str = APP_NAME
    app_module: str = __module__
    app_path: Path = Path(__file__).parent
    display_name: str = _("CTA回测")
    engine_class: type[BacktesterEngine] = BacktesterEngine
    widget_name: str = "BacktesterManager"
    icon_name: str = str(app_path.joinpath("ui", "backtester.ico"))

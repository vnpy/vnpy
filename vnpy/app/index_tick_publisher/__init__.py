# encoding: UTF-8

import os
from pathlib import Path
from vnpy.trader.app import BaseApp
from .engine import IndexTickPublisher, APP_NAME


class IndexTickPublisherApp(BaseApp):
    """"""
    app_name = APP_NAME
    app_module = __module__
    app_path = Path(__file__).parent
    display_name = u'指数行情推送'
    engine_class = IndexTickPublisher

from typing import Any

import polars as pl

from vnpy.app.factor_maker.base import RollingDataFrame
from vnpy.app.factor_maker.template import FactorTemplate


class BarFactor(FactorTemplate):

    def __init__(self, setting, **kwargs):
        super().__init__(setting=setting, **kwargs)

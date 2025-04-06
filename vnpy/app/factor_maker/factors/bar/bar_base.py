from typing import Any

import polars as pl

from vnpy.app.factor_maker.template import FactorTemplate


class BarFactor(FactorTemplate):

    def __init__(self, setting):
        super().__init__(setting=setting)

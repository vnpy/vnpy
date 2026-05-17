"""Compatibility wrapper for nested local source layout."""

from __future__ import annotations

import sys

from .vnpy_okx import datafeed, okx_gateway
from .vnpy_okx import Datafeed, OkxGateway

sys.modules.setdefault(__name__ + ".datafeed", datafeed)
sys.modules.setdefault(__name__ + ".okx_gateway", okx_gateway)

__all__ = ["OkxGateway", "Datafeed"]

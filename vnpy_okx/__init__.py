"""Compatibility wrapper for nested local source layout.

This repository vendors the gateway source under:
    vnpy_okx/vnpy_okx/
"""

from .vnpy_okx import Datafeed, OkxGateway

__all__ = ["OkxGateway", "Datafeed"]

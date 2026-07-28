from decimal import Decimal
from uuid import uuid4

import pytest
from vnpy.trader.constant import Direction, Exchange, Offset, OrderType

from aqr.domain.order import (
    OrderKind,
    Side,
    SubmitOrderCommand,
    TradingEnvironment,
)
from aqr.execution.vnpy.mapper import map_to_vnpy_order_request


def command(**overrides: object) -> SubmitOrderCommand:
    values = {
        "command_id": uuid4(),
        "order_intent_id": uuid4(),
        "client_order_id": "PAPER-A01-S01-20260727-600519-SSE-BUY-001",
        "environment": TradingEnvironment.PAPER,
        "account_id": "A01",
        "symbol": "600519",
        "exchange": "SSE",
        "side": Side.BUY,
        "order_type": OrderKind.LIMIT,
        "quantity": 100,
        "limit_price": Decimal("1500"),
    }
    values.update(overrides)
    return SubmitOrderCommand(**values)


def test_maps_a_share_limit_order() -> None:
    request = map_to_vnpy_order_request(command())
    assert request.exchange is Exchange.SSE
    assert request.direction is Direction.LONG
    assert request.type is OrderType.LIMIT
    assert request.offset is Offset.OPEN
    assert request.reference.startswith("PAPER-A01")


def test_sell_maps_to_close_long_position() -> None:
    request = map_to_vnpy_order_request(command(side=Side.SELL))
    assert request.direction is Direction.SHORT
    assert request.offset is Offset.CLOSE


def test_rejects_unknown_exchange() -> None:
    with pytest.raises(ValueError, match="unsupported"):
        map_to_vnpy_order_request(command(exchange="NOT_REAL"))

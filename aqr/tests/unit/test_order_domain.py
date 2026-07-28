from datetime import UTC, date, datetime, timedelta
from decimal import Decimal
from uuid import uuid4

import pytest

from aqr.domain.order import (
    OrderIntent,
    OrderKind,
    Side,
    TradingEnvironment,
)


def make_intent(**overrides: object) -> OrderIntent:
    values = {
        "client_order_id": "PAPER-A01-S01-20260727-600519-SSE-BUY-001",
        "environment": TradingEnvironment.PAPER,
        "account_id": "A01",
        "strategy_id": "S01",
        "trade_date": date(2026, 7, 27),
        "symbol": "600519",
        "exchange": "SSE",
        "side": Side.BUY,
        "order_type": OrderKind.LIMIT,
        "target_quantity": 100,
        "limit_price": Decimal("1500.00"),
        "risk_run_id": uuid4(),
        "expires_at": datetime.now(UTC) + timedelta(hours=1),
    }
    values.update(overrides)
    return OrderIntent(**values)


def test_limit_order_requires_price() -> None:
    with pytest.raises(ValueError, match="limit_price"):
        make_intent(limit_price=None)


def test_quantity_must_be_positive() -> None:
    with pytest.raises(ValueError, match="positive"):
        make_intent(target_quantity=0)


def test_valid_intent_is_immutable() -> None:
    intent = make_intent()
    with pytest.raises(AttributeError):
        intent.target_quantity = 200  # type: ignore[misc]

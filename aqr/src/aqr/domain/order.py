from __future__ import annotations

from dataclasses import dataclass, field
from datetime import UTC, date, datetime
from decimal import Decimal
from enum import StrEnum
from uuid import UUID, uuid4


class TradingEnvironment(StrEnum):
    PAPER = "PAPER"
    SHADOW = "SHADOW"
    LIVE = "LIVE"


class Side(StrEnum):
    BUY = "BUY"
    SELL = "SELL"


class OrderKind(StrEnum):
    LIMIT = "LIMIT"
    MARKET = "MARKET"


class OrderIntentStatus(StrEnum):
    DRAFT = "DRAFT"
    RISK_APPROVED = "RISK_APPROVED"
    READY = "READY"
    DISPATCHED = "DISPATCHED"
    CLOSED = "CLOSED"
    RISK_REJECTED = "RISK_REJECTED"
    EXPIRED = "EXPIRED"
    MANUAL_REJECTED = "MANUAL_REJECTED"
    HALTED = "HALTED"


class ActualOrderStatus(StrEnum):
    CREATED = "CREATED"
    SUBMITTING = "SUBMITTING"
    SUBMITTED = "SUBMITTED"
    ACCEPTED = "ACCEPTED"
    PARTIALLY_FILLED = "PARTIALLY_FILLED"
    FILLED = "FILLED"
    REJECTED = "REJECTED"
    CANCELLED = "CANCELLED"
    EXPIRED = "EXPIRED"
    UNKNOWN = "UNKNOWN"


class OrderEventType(StrEnum):
    ORDER_CREATED = "ORDER_CREATED"
    ORDER_SUBMITTING = "ORDER_SUBMITTING"
    ORDER_SUBMITTED = "ORDER_SUBMITTED"
    ORDER_ACCEPTED = "ORDER_ACCEPTED"
    ORDER_REJECTED = "ORDER_REJECTED"
    ORDER_PARTIALLY_FILLED = "ORDER_PARTIALLY_FILLED"
    ORDER_FILLED = "ORDER_FILLED"
    CANCEL_REQUESTED = "CANCEL_REQUESTED"
    ORDER_CANCELLED = "ORDER_CANCELLED"
    ORDER_EXPIRED = "ORDER_EXPIRED"
    ORDER_UNKNOWN = "ORDER_UNKNOWN"


def utc_now() -> datetime:
    return datetime.now(UTC)


@dataclass(frozen=True, slots=True)
class OrderIntent:
    client_order_id: str
    environment: TradingEnvironment
    account_id: str
    strategy_id: str
    trade_date: date
    symbol: str
    exchange: str
    side: Side
    order_type: OrderKind
    target_quantity: int
    limit_price: Decimal | None
    risk_run_id: UUID
    status: OrderIntentStatus = OrderIntentStatus.RISK_APPROVED
    expires_at: datetime | None = None
    order_intent_id: UUID = field(default_factory=uuid4)
    created_at: datetime = field(default_factory=utc_now)

    def __post_init__(self) -> None:
        if not self.client_order_id.strip():
            raise ValueError("client_order_id is required")
        if self.target_quantity <= 0:
            raise ValueError("target_quantity must be positive")
        if self.order_type is OrderKind.LIMIT:
            if self.limit_price is None or self.limit_price <= 0:
                raise ValueError("a positive limit_price is required for LIMIT orders")
        if self.expires_at and self.expires_at <= self.created_at:
            raise ValueError("expires_at must be after created_at")


@dataclass(frozen=True, slots=True)
class SubmitOrderCommand:
    command_id: UUID
    order_intent_id: UUID
    client_order_id: str
    environment: TradingEnvironment
    account_id: str
    symbol: str
    exchange: str
    side: Side
    order_type: OrderKind
    quantity: int
    limit_price: Decimal | None


@dataclass(frozen=True, slots=True)
class CancelOrderCommand:
    command_id: UUID
    client_order_id: str
    external_order_id: str
    symbol: str
    exchange: str
    gateway_name: str

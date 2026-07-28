from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime
from decimal import Decimal
from uuid import UUID, uuid4

from aqr.domain.order import OrderEventType, utc_now


@dataclass(frozen=True, slots=True)
class OrderEvent:
    client_order_id: str
    gateway_name: str
    event_type: OrderEventType
    event_time: datetime
    event_sequence: int
    traded_quantity: int
    remaining_quantity: int
    deduplication_key: str
    raw_payload: dict
    external_order_id: str | None = None
    price: Decimal | None = None
    event_id: UUID = field(default_factory=uuid4)
    received_at: datetime = field(default_factory=utc_now)

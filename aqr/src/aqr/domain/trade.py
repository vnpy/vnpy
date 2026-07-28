from dataclasses import dataclass, field
from datetime import datetime
from decimal import Decimal
from uuid import UUID, uuid4

from aqr.domain.order import Side, utc_now


@dataclass(frozen=True, slots=True)
class TradeFill:
    client_order_id: str
    gateway_name: str
    external_order_id: str
    external_trade_id: str
    symbol: str
    side: Side
    quantity: int
    price: Decimal
    trade_time: datetime
    commission: Decimal = Decimal("0")
    tax: Decimal = Decimal("0")
    fill_id: UUID = field(default_factory=uuid4)
    received_at: datetime = field(default_factory=utc_now)

    def __post_init__(self) -> None:
        if self.quantity <= 0:
            raise ValueError("fill quantity must be positive")
        if self.price <= 0:
            raise ValueError("fill price must be positive")

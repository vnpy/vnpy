from dataclasses import dataclass
from decimal import Decimal


@dataclass(frozen=True, slots=True)
class Position:
    environment: str
    account_id: str
    symbol: str
    total_quantity: int
    available_quantity: int
    frozen_quantity: int
    average_cost: Decimal
    market_value: Decimal

    def __post_init__(self) -> None:
        if min(self.total_quantity, self.available_quantity, self.frozen_quantity) < 0:
            raise ValueError("position quantities cannot be negative")
        if self.available_quantity + self.frozen_quantity > self.total_quantity:
            raise ValueError("available plus frozen quantity exceeds total quantity")

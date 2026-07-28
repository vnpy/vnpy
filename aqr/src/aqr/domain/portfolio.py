from dataclasses import dataclass
from datetime import date
from decimal import Decimal
from uuid import UUID


@dataclass(frozen=True, slots=True)
class TargetPosition:
    portfolio_run_id: UUID
    trade_date: date
    symbol: str
    target_weight: Decimal
    target_quantity: int

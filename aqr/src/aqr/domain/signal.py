from dataclasses import dataclass
from datetime import datetime
from decimal import Decimal
from uuid import UUID


@dataclass(frozen=True, slots=True)
class Signal:
    signal_id: UUID
    dataset_version_id: UUID
    model_run_id: UUID
    strategy_id: str
    symbol: str
    generated_at: datetime
    score: Decimal

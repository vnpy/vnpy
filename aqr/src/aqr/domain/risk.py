from dataclasses import dataclass, field
from datetime import datetime
from enum import StrEnum
from uuid import UUID, uuid4

from aqr.domain.order import utc_now


class RiskDecision(StrEnum):
    APPROVED = "APPROVED"
    REJECTED = "REJECTED"
    HALTED = "HALTED"


@dataclass(frozen=True, slots=True)
class RiskResult:
    decision: RiskDecision
    rule: str
    reason: str
    risk_run_id: UUID = field(default_factory=uuid4)
    evaluated_at: datetime = field(default_factory=utc_now)

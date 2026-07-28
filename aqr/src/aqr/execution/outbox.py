from __future__ import annotations

from dataclasses import asdict
from datetime import UTC, datetime, timedelta
from enum import StrEnum
from typing import Protocol
from uuid import UUID, uuid4

from aqr.domain.order import OrderIntent, SubmitOrderCommand


class OutboxStatus(StrEnum):
    PENDING = "PENDING"
    CLAIMED = "CLAIMED"
    SENT = "SENT"
    ACKNOWLEDGED = "ACKNOWLEDGED"
    FAILED = "FAILED"


class OutboxRepository(Protocol):
    def create_order_with_command(
        self, intent: OrderIntent
    ) -> tuple[UUID, UUID]: ...

    def claim_pending(self, worker_id: str, limit: int = 20) -> list[dict]: ...

    def mark_sent(self, command_id: UUID) -> None: ...

    def mark_acknowledged(self, command_id: UUID) -> None: ...

    def mark_failed(self, command_id: UUID, error: str) -> None: ...

    def release_for_retry(
        self, command_id: UUID, error: str, retry_delay: timedelta
    ) -> None: ...

    def recover_stale_claims(
        self,
        cutoff: datetime,
        worker_id: str | None = None,
    ) -> list[dict]: ...


def command_from_intent(intent: OrderIntent, command_id: UUID | None = None) -> dict:
    command = SubmitOrderCommand(
        command_id=command_id or uuid4(),
        order_intent_id=intent.order_intent_id,
        client_order_id=intent.client_order_id,
        environment=intent.environment,
        account_id=intent.account_id,
        symbol=intent.symbol,
        exchange=intent.exchange,
        side=intent.side,
        order_type=intent.order_type,
        quantity=intent.target_quantity,
        limit_price=intent.limit_price,
    )
    payload = asdict(command)
    for key, value in payload.items():
        if isinstance(value, (UUID, StrEnum)):
            payload[key] = str(value)
        elif hasattr(value, "as_tuple"):
            payload[key] = str(value)
    return payload


def retry_at(delay: timedelta) -> datetime:
    return datetime.now(UTC) + delay

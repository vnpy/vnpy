from __future__ import annotations

from datetime import UTC, datetime, timedelta
from threading import RLock
from uuid import UUID, uuid4

from vnpy.trader.object import AccountData, PositionData

from aqr.domain.order import OrderIntent, OrderIntentStatus
from aqr.domain.trade import TradeFill
from aqr.execution.events import OrderEvent
from aqr.execution.outbox import command_from_intent


class InMemoryExecutionRepository:
    """Deterministic test/replay adapter; never used as a production ledger."""

    def __init__(self) -> None:
        self._lock = RLock()
        self.intents: dict[tuple[str, str], OrderIntent] = {}
        self.commands: dict[UUID, dict] = {}
        self.order_events: list[OrderEvent] = []
        self.trade_fills: list[TradeFill] = []
        self.positions: dict[str, int] = {}
        self.accounts: list[AccountData] = []
        self.reconciliations: list[dict] = []
        self._dedup_events: set[tuple[str, str]] = set()
        self._dedup_fills: set[tuple[str, str]] = set()

    def create_order_with_command(self, intent: OrderIntent) -> tuple[UUID, UUID]:
        key = (intent.account_id, intent.client_order_id)
        with self._lock:
            existing = self.intents.get(key)
            if existing:
                self._assert_same_intent(existing, intent)
                command = next(
                    value
                    for value in self.commands.values()
                    if value["aggregate_id"] == existing.order_intent_id
                )
                return existing.order_intent_id, command["command_id"]

            self._assert_executable(intent)
            command_id = uuid4()
            self.intents[key] = intent
            self.commands[command_id] = {
                "command_id": command_id,
                "aggregate_id": intent.order_intent_id,
                "command_type": "SEND_ORDER",
                "payload": command_from_intent(intent, command_id),
                "status": "PENDING",
                "retry_count": 0,
                "next_retry_at": None,
                "claimed_at": None,
            }
            return intent.order_intent_id, command_id

    def claim_pending(self, worker_id: str, limit: int = 20) -> list[dict]:
        del worker_id
        now = datetime.now(UTC)
        with self._lock:
            result = []
            for row in self.commands.values():
                if len(result) >= limit:
                    break
                if row["status"] != "PENDING":
                    continue
                if row["next_retry_at"] and row["next_retry_at"] > now:
                    continue
                row["status"] = "CLAIMED"
                row["claimed_at"] = now
                result.append(
                    {
                        "command_id": row["command_id"],
                        "command_type": row["command_type"],
                        "payload": dict(row["payload"]),
                    }
                )
            return result

    def mark_sent(self, command_id: UUID) -> None:
        row = self.commands[command_id]
        if row["status"] == "CLAIMED":
            row["status"] = "SENT"

    def mark_acknowledged(self, command_id: UUID) -> None:
        self.commands[command_id]["status"] = "ACKNOWLEDGED"

    def mark_failed(self, command_id: UUID, error: str) -> None:
        row = self.commands[command_id]
        if row["status"] in {"PENDING", "CLAIMED", "SENT"}:
            row["status"] = "FAILED"
            row["error"] = error

    def release_for_retry(
        self, command_id: UUID, error: str, retry_delay: timedelta
    ) -> None:
        del error
        row = self.commands[command_id]
        row["status"] = "PENDING"
        row["retry_count"] += 1
        row["next_retry_at"] = datetime.now(UTC) + retry_delay
        row["claimed_at"] = None

    def recover_stale_claims(
        self,
        cutoff: datetime,
        worker_id: str | None = None,
    ) -> list[dict]:
        del worker_id
        with self._lock:
            for row in self.commands.values():
                if (
                    row["status"] == "CLAIMED"
                    and row["claimed_at"] is not None
                    and row["claimed_at"] <= cutoff
                ):
                    row["status"] = "PENDING"
                    row["claimed_at"] = None
            return []

    def append_order_event(self, event: OrderEvent) -> bool:
        key = (event.gateway_name, event.deduplication_key)
        with self._lock:
            if key in self._dedup_events:
                return False
            self._dedup_events.add(key)
            self.order_events.append(event)
            return True

    def append_trade_fill(self, fill: TradeFill) -> bool:
        key = (fill.gateway_name, fill.external_trade_id)
        with self._lock:
            if key in self._dedup_fills:
                return False
            self._dedup_fills.add(key)
            self.trade_fills.append(fill)
            return True

    def save_position_snapshot(self, position: PositionData) -> None:
        self.positions[position.vt_symbol] = int(position.volume)

    def save_account_snapshot(self, account: AccountData) -> None:
        self.accounts.append(account)

    def acknowledge_order_command(self, client_order_id: str) -> None:
        intent = next(
            (
                intent
                for intent in self.intents.values()
                if intent.client_order_id == client_order_id
            ),
            None,
        )
        if intent is None:
            return
        command = next(
            value
            for value in self.commands.values()
            if value["aggregate_id"] == intent.order_intent_id
        )
        command["status"] = "ACKNOWLEDGED"

    def load_position_quantities(self) -> dict[str, int]:
        return dict(self.positions)

    def load_open_order_ids(self) -> set[str]:
        return set()

    def load_unknown_order_ids(self) -> set[str]:
        return set()

    def record_reconciliation(
        self, reason: str, diffs: list, passed: bool
    ) -> UUID:
        reconciliation_id = uuid4()
        self.reconciliations.append(
            {
                "reconciliation_id": reconciliation_id,
                "reason": reason,
                "diffs": list(diffs),
                "passed": passed,
            }
        )
        return reconciliation_id

    def find_acknowledgement_timeouts(self, cutoff: datetime) -> list[dict]:
        return [
            {
                "command_id": command_id,
                "client_order_id": row["payload"]["client_order_id"],
                "account_id": row["payload"]["account_id"],
                "symbol": row["payload"]["symbol"],
                "gateway_name": "PAPER",
                "quantity": int(row["payload"]["quantity"]),
            }
            for command_id, row in self.commands.items()
            if row["status"] == "SENT"
            and row["claimed_at"] is not None
            and row["claimed_at"] <= cutoff
        ]

    def mark_acknowledgement_timeout(self, command_id: UUID) -> None:
        self.commands[command_id]["status"] = "FAILED"

    @staticmethod
    def _assert_executable(intent: OrderIntent) -> None:
        if intent.status not in {
            OrderIntentStatus.RISK_APPROVED,
            OrderIntentStatus.READY,
        }:
            raise ValueError(f"order intent is not executable: {intent.status}")
        if intent.expires_at and intent.expires_at <= datetime.now(UTC):
            raise ValueError("order intent has expired")

    @staticmethod
    def _assert_same_intent(existing: OrderIntent, requested: OrderIntent) -> None:
        comparable_fields = (
            "environment",
            "account_id",
            "strategy_id",
            "trade_date",
            "symbol",
            "exchange",
            "side",
            "order_type",
            "target_quantity",
            "limit_price",
            "risk_run_id",
        )
        if any(
            getattr(existing, field) != getattr(requested, field)
            for field in comparable_fields
        ):
            raise ValueError(
                "client_order_id is already bound to a different order intent"
            )

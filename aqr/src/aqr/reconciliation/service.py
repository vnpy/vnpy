from __future__ import annotations

from dataclasses import dataclass
from datetime import UTC, datetime, timedelta
from typing import Protocol

from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.reconciliation.order_matcher import match_active_orders
from aqr.reconciliation.position_matcher import (
    DiffSeverity,
    ReconciliationDiff,
    match_positions,
)


class InternalSnapshotRepository(Protocol):
    def load_position_quantities(self) -> dict[str, int]: ...

    def load_open_order_ids(self) -> set[str]: ...

    def load_unknown_order_ids(self) -> set[str]: ...

    def record_reconciliation(
        self, reason: str, diffs: list[ReconciliationDiff], passed: bool
    ) -> object: ...


@dataclass(frozen=True, slots=True)
class GatewaySnapshot:
    positions: dict[str, int]
    active_order_ids: set[str]
    captured_at: datetime


class GatewaySnapshotProvider(Protocol):
    def capture_reconciliation_snapshot(
        self, account_id: str
    ) -> GatewaySnapshot: ...


@dataclass(frozen=True, slots=True)
class ReconciliationResult:
    passed: bool
    diffs: tuple[ReconciliationDiff, ...]


class ReconciliationService:
    def __init__(
        self,
        gateway_snapshot_provider: GatewaySnapshotProvider,
        repository: InternalSnapshotRepository,
        kill_switch: KillSwitch,
        *,
        account_id: str,
        max_snapshot_age_seconds: float = 5,
    ) -> None:
        self.gateway_snapshot_provider = gateway_snapshot_provider
        self.repository = repository
        self.kill_switch = kill_switch
        self.account_id = account_id
        self.max_snapshot_age = timedelta(seconds=max_snapshot_age_seconds)

    def startup_reconcile(self) -> ReconciliationResult:
        return self.reconcile("STARTUP", allow_resume=True)

    def reconcile(
        self, reason: str, *, allow_resume: bool = False
    ) -> ReconciliationResult:
        gateway_snapshot = (
            self.gateway_snapshot_provider.capture_reconciliation_snapshot(
                self.account_id
            )
        )
        now = datetime.now(UTC)
        if gateway_snapshot.captured_at.tzinfo is None:
            raise RuntimeError("Gateway snapshot timestamp must be timezone-aware")
        if (
            gateway_snapshot.captured_at > now
            or now - gateway_snapshot.captured_at > self.max_snapshot_age
        ):
            raise RuntimeError("Gateway snapshot is not fresh enough for reconciliation")

        internal_positions = self.repository.load_position_quantities()
        gateway_positions = gateway_snapshot.positions
        internal_orders = self.repository.load_open_order_ids()
        gateway_orders = gateway_snapshot.active_order_ids
        unknown_orders = self.repository.load_unknown_order_ids()

        diffs = [
            *match_positions(internal_positions, gateway_positions),
            *match_active_orders(internal_orders, gateway_orders),
            *(
                ReconciliationDiff(
                    entity_type="ORDER_UNKNOWN",
                    symbol=None,
                    field_name="status",
                    internal_value=client_order_id,
                    gateway_value=None,
                    severity=DiffSeverity.CRITICAL,
                )
                for client_order_id in sorted(unknown_orders)
            ),
        ]
        passed = not any(diff.severity is DiffSeverity.CRITICAL for diff in diffs)
        self.repository.record_reconciliation(reason, diffs, passed)
        if passed and allow_resume:
            self.kill_switch.resume(f"{reason.lower()} reconciliation passed")
        else:
            if not passed:
                self.kill_switch.halt(f"{reason.lower()} reconciliation failed")
        return ReconciliationResult(passed=passed, diffs=tuple(diffs))

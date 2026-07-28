from datetime import UTC, datetime, timedelta

import pytest

from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.reconciliation.service import GatewaySnapshot, ReconciliationService


class SnapshotProvider:
    def __init__(self, snapshot: GatewaySnapshot) -> None:
        self.snapshot = snapshot

    def capture_reconciliation_snapshot(
        self, account_id: str
    ) -> GatewaySnapshot:
        assert account_id == "A01"
        return self.snapshot


class SnapshotRepository:
    def __init__(self, *, unknown_orders: set[str] | None = None) -> None:
        self.unknown_orders = unknown_orders or set()
        self.records: list[tuple[str, list, bool]] = []

    def load_position_quantities(self) -> dict[str, int]:
        return {"600519.SSE": 100}

    def load_open_order_ids(self) -> set[str]:
        return set()

    def load_unknown_order_ids(self) -> set[str]:
        return set(self.unknown_orders)

    def record_reconciliation(
        self, reason: str, diffs: list, passed: bool
    ) -> object:
        self.records.append((reason, diffs, passed))
        return object()


def make_service(
    snapshot: GatewaySnapshot,
    repository: SnapshotRepository | None = None,
) -> tuple[ReconciliationService, KillSwitch]:
    switch = KillSwitch()
    service = ReconciliationService(
        SnapshotProvider(snapshot),
        repository or SnapshotRepository(),
        switch,
        account_id="A01",
    )
    return service, switch


def test_fresh_gateway_snapshot_can_resume_trading() -> None:
    service, switch = make_service(
        GatewaySnapshot(
            positions={"600519.SSE": 100},
            active_order_ids=set(),
            captured_at=datetime.now(UTC),
        )
    )
    result = service.startup_reconcile()
    assert result.passed
    assert not switch.is_halted


def test_stale_gateway_snapshot_is_rejected() -> None:
    service, switch = make_service(
        GatewaySnapshot(
            positions={"600519.SSE": 100},
            active_order_ids=set(),
            captured_at=datetime.now(UTC) - timedelta(minutes=1),
        )
    )
    with pytest.raises(RuntimeError, match="not fresh"):
        service.startup_reconcile()
    assert switch.is_halted


def test_unresolved_unknown_order_prevents_resume() -> None:
    repository = SnapshotRepository(unknown_orders={"client-unknown"})
    service, switch = make_service(
        GatewaySnapshot(
            positions={"600519.SSE": 100},
            active_order_ids={"client-unknown"},
            captured_at=datetime.now(UTC),
        ),
        repository,
    )
    result = service.startup_reconcile()
    assert not result.passed
    assert switch.is_halted
    assert any(diff.entity_type == "ORDER_UNKNOWN" for diff in result.diffs)

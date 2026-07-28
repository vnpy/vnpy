from datetime import UTC, datetime, timedelta

import pytest

from aqr.domain.order import OrderEventType
from aqr.execution.repositories.memory import InMemoryExecutionRepository
from aqr.execution.vnpy.ack_monitor import OrderAcknowledgementMonitor
from aqr.execution.vnpy.kill_switch import KillSwitch, TradingHalted

from .test_order_domain import make_intent


def test_ack_timeout_marks_unknown_and_halts_symbol() -> None:
    repository = InMemoryExecutionRepository()
    switch = KillSwitch()
    switch.resume("startup passed")
    _, command_id = repository.create_order_with_command(make_intent())
    repository.claim_pending("worker")
    repository.mark_sent(command_id)
    repository.commands[command_id]["claimed_at"] = datetime.now(UTC) - timedelta(
        seconds=20
    )

    monitor = OrderAcknowledgementMonitor(
        repository, switch, timeout_seconds=10
    )
    assert monitor.poll_once() == 1

    assert repository.commands[command_id]["status"] == "FAILED"
    assert repository.order_events[-1].event_type is OrderEventType.ORDER_UNKNOWN
    with pytest.raises(TradingHalted, match="acknowledgement timeout"):
        switch.assert_can_trade("A01", "600519")


def test_sent_update_does_not_downgrade_early_ack() -> None:
    repository = InMemoryExecutionRepository()
    intent = make_intent()
    _, command_id = repository.create_order_with_command(intent)
    repository.claim_pending("worker")
    repository.acknowledge_order_command(intent.client_order_id)
    repository.mark_sent(command_id)
    assert repository.commands[command_id]["status"] == "ACKNOWLEDGED"

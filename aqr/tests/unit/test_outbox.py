from datetime import UTC, datetime, timedelta

import pytest

from aqr.domain.order import OrderIntentStatus
from aqr.execution.contracts import (
    OrderSubmissionRejected,
    OrderSubmissionUnknown,
)
from aqr.execution.outbox import command_from_intent
from aqr.execution.repositories.memory import InMemoryExecutionRepository
from aqr.execution.vnpy.command_consumer import OutboxCommandConsumer
from aqr.execution.vnpy.kill_switch import KillSwitch, TradingHalted

from .test_order_domain import make_intent


def test_order_and_outbox_are_idempotent() -> None:
    repository = InMemoryExecutionRepository()
    intent = make_intent()

    first = repository.create_order_with_command(intent)
    second = repository.create_order_with_command(intent)

    assert first == second
    assert len(repository.intents) == 1
    assert len(repository.commands) == 1


def test_command_payload_is_json_safe() -> None:
    payload = command_from_intent(make_intent())
    assert payload["environment"] == "PAPER"
    assert payload["side"] == "BUY"
    assert payload["limit_price"] == "1500.00"


@pytest.mark.parametrize(
    "status",
    [
        OrderIntentStatus.DRAFT,
        OrderIntentStatus.RISK_REJECTED,
        OrderIntentStatus.EXPIRED,
    ],
)
def test_non_executable_intent_is_not_enqueued(
    status: OrderIntentStatus,
) -> None:
    repository = InMemoryExecutionRepository()
    with pytest.raises(ValueError, match="not executable"):
        repository.create_order_with_command(make_intent(status=status))
    assert not repository.commands


def test_expired_intent_is_not_enqueued() -> None:
    now = datetime.now(UTC)
    intent = make_intent(
        created_at=now - timedelta(hours=2),
        expires_at=now - timedelta(hours=1),
    )
    repository = InMemoryExecutionRepository()
    with pytest.raises(ValueError, match="expired"):
        repository.create_order_with_command(intent)


def test_idempotency_key_cannot_change_order_payload() -> None:
    repository = InMemoryExecutionRepository()
    repository.create_order_with_command(make_intent())

    with pytest.raises(ValueError, match="different order intent"):
        repository.create_order_with_command(
            make_intent(target_quantity=200)
        )


class FailingRuntime:
    def __init__(self, error: Exception) -> None:
        self.error = error
        self.calls = 0

    def submit_order(self, command: object) -> None:
        del command
        self.calls += 1
        raise self.error


def test_definitive_rejection_is_not_retried() -> None:
    repository = InMemoryExecutionRepository()
    _, command_id = repository.create_order_with_command(make_intent())
    runtime = FailingRuntime(OrderSubmissionRejected("rejected"))
    switch = KillSwitch()
    switch.resume("test")
    consumer = OutboxCommandConsumer(
        repository,
        runtime,  # type: ignore[arg-type]
        switch,
        worker_id="worker",
    )

    assert consumer.poll_once() == 1
    assert repository.commands[command_id]["status"] == "FAILED"
    assert consumer.poll_once() == 0
    assert runtime.calls == 1


def test_unknown_submission_is_not_retried_and_halts_symbol() -> None:
    repository = InMemoryExecutionRepository()
    intent = make_intent()
    _, command_id = repository.create_order_with_command(intent)
    runtime = FailingRuntime(OrderSubmissionUnknown("timeout"))
    switch = KillSwitch()
    switch.resume("test")
    consumer = OutboxCommandConsumer(
        repository,
        runtime,  # type: ignore[arg-type]
        switch,
        worker_id="worker",
    )

    assert consumer.poll_once() == 1
    assert repository.commands[command_id]["status"] == "FAILED"
    with pytest.raises(TradingHalted, match="unknown order submission"):
        switch.assert_can_trade(intent.account_id, intent.symbol)

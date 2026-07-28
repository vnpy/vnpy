from datetime import UTC, datetime
from decimal import Decimal

from aqr.domain.order import OrderEventType
from aqr.execution.events import OrderEvent
from aqr.execution.repositories.memory import InMemoryExecutionRepository
from aqr.execution.vnpy.command_consumer import OutboxCommandConsumer
from aqr.execution.vnpy.kill_switch import KillSwitch

from ..unit.test_order_domain import make_intent


class SimulatedRuntime:
    def __init__(self, repository: InMemoryExecutionRepository) -> None:
        self.repository = repository
        self.submitted = []

    def start(self) -> None:
        return

    def stop(self) -> None:
        return

    def submit_order(self, command) -> None:
        self.submitted.append(command)
        for sequence, event_type in enumerate(
            (
                OrderEventType.ORDER_SUBMITTING,
                OrderEventType.ORDER_SUBMITTED,
                OrderEventType.ORDER_ACCEPTED,
                OrderEventType.ORDER_FILLED,
            ),
            start=1,
        ):
            self.repository.append_order_event(
                OrderEvent(
                    client_order_id=command.client_order_id,
                    gateway_name="PAPER",
                    external_order_id="PAPER.100001",
                    event_type=event_type,
                    event_time=datetime.now(UTC),
                    event_sequence=sequence,
                    traded_quantity=command.quantity
                    if event_type is OrderEventType.ORDER_FILLED
                    else 0,
                    remaining_quantity=0
                    if event_type is OrderEventType.ORDER_FILLED
                    else command.quantity,
                    price=Decimal("1500"),
                    raw_payload={},
                    deduplication_key=f"e2e-{sequence}",
                )
            )

    def cancel_order(self, command) -> None:
        del command

    def query_account(self, account_id: str) -> None:
        del account_id

    def query_positions(self, account_id: str) -> None:
        del account_id

    def query_orders(self, account_id: str) -> None:
        del account_id

    def query_trades(self, account_id: str) -> None:
        del account_id


def test_intent_to_outbox_to_simulated_fill() -> None:
    repository = InMemoryExecutionRepository()
    runtime = SimulatedRuntime(repository)
    switch = KillSwitch()
    switch.resume("test reconciliation passed")
    consumer = OutboxCommandConsumer(
        repository,
        runtime,
        switch,
        worker_id="test-worker",
    )

    _, command_id = repository.create_order_with_command(make_intent())
    assert consumer.poll_once() == 1

    assert repository.commands[command_id]["status"] == "SENT"
    assert len(runtime.submitted) == 1
    assert [event.event_type for event in repository.order_events][-1] is (
        OrderEventType.ORDER_FILLED
    )


def test_duplicate_event_is_ignored() -> None:
    repository = InMemoryExecutionRepository()
    event = OrderEvent(
        client_order_id="client-1",
        gateway_name="PAPER",
        external_order_id="PAPER.1",
        event_type=OrderEventType.ORDER_ACCEPTED,
        event_time=datetime.now(UTC),
        event_sequence=1,
        traded_quantity=0,
        remaining_quantity=100,
        price=Decimal("10"),
        raw_payload={},
        deduplication_key="same-event",
    )
    assert repository.append_order_event(event)
    assert not repository.append_order_event(event)
    assert len(repository.order_events) == 1

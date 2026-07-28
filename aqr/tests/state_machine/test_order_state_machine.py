import pytest

from aqr.domain.order import ActualOrderStatus
from aqr.execution.order_state_machine import (
    InvalidOrderTransition,
    OrderStateMachine,
)


def test_happy_path_with_partial_fill() -> None:
    machine = OrderStateMachine()
    for status in (
        ActualOrderStatus.SUBMITTING,
        ActualOrderStatus.SUBMITTED,
        ActualOrderStatus.ACCEPTED,
        ActualOrderStatus.PARTIALLY_FILLED,
        ActualOrderStatus.FILLED,
    ):
        machine.move_to(status)
    assert machine.status is ActualOrderStatus.FILLED


@pytest.mark.parametrize(
    ("start", "target"),
    [
        (ActualOrderStatus.FILLED, ActualOrderStatus.CANCELLED),
        (ActualOrderStatus.REJECTED, ActualOrderStatus.PARTIALLY_FILLED),
        (ActualOrderStatus.CANCELLED, ActualOrderStatus.ACCEPTED),
    ],
)
def test_illegal_terminal_transition_is_rejected(
    start: ActualOrderStatus, target: ActualOrderStatus
) -> None:
    machine = OrderStateMachine(start)
    with pytest.raises(InvalidOrderTransition):
        machine.move_to(target)


def test_unknown_can_only_recover_from_broker_evidence() -> None:
    machine = OrderStateMachine(ActualOrderStatus.UNKNOWN)
    machine.move_to(ActualOrderStatus.ACCEPTED)
    assert machine.status is ActualOrderStatus.ACCEPTED


def test_unknown_cannot_be_resubmitted() -> None:
    machine = OrderStateMachine(ActualOrderStatus.UNKNOWN)
    with pytest.raises(InvalidOrderTransition):
        machine.move_to(ActualOrderStatus.SUBMITTING)

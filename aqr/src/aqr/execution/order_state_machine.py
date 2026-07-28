from __future__ import annotations

from dataclasses import dataclass

from aqr.domain.order import ActualOrderStatus


class InvalidOrderTransition(ValueError):
    pass


_ALLOWED: dict[ActualOrderStatus, frozenset[ActualOrderStatus]] = {
    ActualOrderStatus.CREATED: frozenset(
        {ActualOrderStatus.SUBMITTING, ActualOrderStatus.REJECTED}
    ),
    ActualOrderStatus.SUBMITTING: frozenset(
        {
            ActualOrderStatus.SUBMITTED,
            ActualOrderStatus.ACCEPTED,
            ActualOrderStatus.REJECTED,
            ActualOrderStatus.UNKNOWN,
        }
    ),
    ActualOrderStatus.SUBMITTED: frozenset(
        {
            ActualOrderStatus.ACCEPTED,
            ActualOrderStatus.PARTIALLY_FILLED,
            ActualOrderStatus.FILLED,
            ActualOrderStatus.REJECTED,
            ActualOrderStatus.CANCELLED,
            ActualOrderStatus.UNKNOWN,
        }
    ),
    ActualOrderStatus.ACCEPTED: frozenset(
        {
            ActualOrderStatus.PARTIALLY_FILLED,
            ActualOrderStatus.FILLED,
            ActualOrderStatus.CANCELLED,
            ActualOrderStatus.EXPIRED,
            ActualOrderStatus.UNKNOWN,
        }
    ),
    ActualOrderStatus.PARTIALLY_FILLED: frozenset(
        {
            ActualOrderStatus.PARTIALLY_FILLED,
            ActualOrderStatus.FILLED,
            ActualOrderStatus.CANCELLED,
            ActualOrderStatus.UNKNOWN,
        }
    ),
    ActualOrderStatus.UNKNOWN: frozenset(
        {
            ActualOrderStatus.SUBMITTED,
            ActualOrderStatus.ACCEPTED,
            ActualOrderStatus.PARTIALLY_FILLED,
            ActualOrderStatus.FILLED,
            ActualOrderStatus.REJECTED,
            ActualOrderStatus.CANCELLED,
            ActualOrderStatus.EXPIRED,
        }
    ),
    ActualOrderStatus.FILLED: frozenset(),
    ActualOrderStatus.REJECTED: frozenset(),
    ActualOrderStatus.CANCELLED: frozenset(),
    ActualOrderStatus.EXPIRED: frozenset(),
}


def transition(
    current: ActualOrderStatus, target: ActualOrderStatus
) -> ActualOrderStatus:
    if target == current:
        return current
    if target not in _ALLOWED[current]:
        raise InvalidOrderTransition(f"illegal order transition: {current} -> {target}")
    return target


@dataclass(slots=True)
class OrderStateMachine:
    status: ActualOrderStatus = ActualOrderStatus.CREATED

    def move_to(self, target: ActualOrderStatus) -> ActualOrderStatus:
        self.status = transition(self.status, target)
        return self.status

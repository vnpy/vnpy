from __future__ import annotations

from typing import Protocol

from aqr.domain.order import CancelOrderCommand, SubmitOrderCommand


class OrderSubmissionRejected(RuntimeError):
    """The execution adapter definitively rejected an order."""


class OrderSubmissionUnknown(RuntimeError):
    """The adapter may have submitted an order but cannot prove the outcome."""


class ExecutionRuntime(Protocol):
    def start(self) -> None: ...

    def stop(self) -> None: ...

    def submit_order(self, command: SubmitOrderCommand) -> None: ...

    def cancel_order(self, command: CancelOrderCommand) -> None: ...

    def query_account(self, account_id: str) -> None: ...

    def query_positions(self, account_id: str) -> None: ...

    def query_orders(self, account_id: str) -> None: ...

    def query_trades(self, account_id: str) -> None: ...


class KillSwitchPort(Protocol):
    @property
    def is_halted(self) -> bool: ...

    def assert_can_trade(self, account_id: str, symbol: str | None = None) -> None: ...

    def halt(self, reason: str, account_id: str | None = None) -> None: ...

    def resume(self, reason: str) -> None: ...

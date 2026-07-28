from __future__ import annotations

from datetime import UTC, datetime, timedelta
from decimal import Decimal
from threading import Event, Thread
from typing import Any
from uuid import UUID

from aqr.domain.order import (
    OrderKind,
    Side,
    SubmitOrderCommand,
    TradingEnvironment,
)
from aqr.execution.contracts import (
    ExecutionRuntime,
    OrderSubmissionRejected,
    OrderSubmissionUnknown,
)
from aqr.execution.outbox import OutboxRepository
from aqr.execution.vnpy.kill_switch import KillSwitch, TradingHalted


class OutboxCommandConsumer:
    def __init__(
        self,
        repository: OutboxRepository,
        runtime: ExecutionRuntime,
        kill_switch: KillSwitch,
        *,
        worker_id: str,
        poll_seconds: float = 0.5,
        claim_timeout_seconds: float = 30,
    ) -> None:
        self.repository = repository
        self.runtime = runtime
        self.kill_switch = kill_switch
        self.worker_id = worker_id
        self.poll_seconds = poll_seconds
        self.claim_timeout = timedelta(seconds=claim_timeout_seconds)
        self._stop = Event()
        self._thread: Thread | None = None

    def start(self) -> None:
        if self._thread and self._thread.is_alive():
            return
        self._stop.clear()
        self._thread = Thread(
            target=self._run,
            name="aqr-outbox-consumer",
            daemon=True,
        )
        self._thread.start()

    def stop(self) -> None:
        self._stop.set()
        if self._thread:
            self._thread.join(timeout=5)

    def poll_once(self) -> int:
        if self.kill_switch.is_halted:
            return 0
        ambiguous = self.repository.recover_stale_claims(
            datetime.now(UTC) - self.claim_timeout
        )
        if ambiguous:
            self.kill_switch.halt(
                "ambiguous stale Outbox claim requires Gateway reconciliation"
            )
            return 0
        commands = self.repository.claim_pending(self.worker_id)
        for item in commands:
            command_id = UUID(str(item["command_id"]))
            command: SubmitOrderCommand | None = None
            try:
                if item["command_type"] != "SEND_ORDER":
                    raise ValueError(f"unsupported command: {item['command_type']}")
                command = self._parse_submit(item["payload"])
                self.runtime.submit_order(command)
                self.repository.mark_sent(command_id)
            except TradingHalted:
                self.repository.release_for_retry(
                    command_id, "trading halted", timedelta(seconds=5)
                )
            except OrderSubmissionRejected as exc:
                self.repository.mark_failed(command_id, str(exc))
            except OrderSubmissionUnknown as exc:
                self.repository.mark_failed(command_id, str(exc))
                if command is None:
                    self.kill_switch.halt(f"unknown order submission: {exc}")
                else:
                    self.kill_switch.halt(
                        f"unknown order submission: {command.client_order_id}",
                        account_id=command.account_id,
                        symbol=command.symbol,
                    )
            except Exception as exc:
                self.repository.mark_failed(command_id, str(exc))
                self.kill_switch.halt(f"outbox command failed: {exc}")
        return len(commands)

    def _run(self) -> None:
        while not self._stop.wait(self.poll_seconds):
            try:
                self.poll_once()
            except Exception as exc:
                self.kill_switch.halt(f"outbox/database failure: {exc}")

    @staticmethod
    def _parse_submit(payload: dict[str, Any]) -> SubmitOrderCommand:
        price = payload.get("limit_price")
        return SubmitOrderCommand(
            command_id=UUID(payload["command_id"]),
            order_intent_id=UUID(payload["order_intent_id"]),
            client_order_id=payload["client_order_id"],
            environment=TradingEnvironment(payload["environment"]),
            account_id=payload["account_id"],
            symbol=payload["symbol"],
            exchange=payload["exchange"],
            side=Side(payload["side"]),
            order_type=OrderKind(payload["order_type"]),
            quantity=int(payload["quantity"]),
            limit_price=Decimal(price) if price is not None else None,
        )

from __future__ import annotations

from datetime import UTC, datetime, timedelta
from threading import Event, Thread
from time import time_ns
from typing import Protocol
from uuid import UUID

from aqr.domain.order import OrderEventType
from aqr.execution.events import OrderEvent
from aqr.execution.vnpy.kill_switch import KillSwitch


class AcknowledgementRepository(Protocol):
    def find_acknowledgement_timeouts(self, cutoff: datetime) -> list[dict]: ...

    def mark_acknowledgement_timeout(self, command_id: UUID) -> None: ...

    def append_order_event(self, event: OrderEvent) -> bool: ...


class OrderAcknowledgementMonitor:
    def __init__(
        self,
        repository: AcknowledgementRepository,
        kill_switch: KillSwitch,
        *,
        timeout_seconds: float,
        poll_seconds: float = 1,
    ) -> None:
        self.repository = repository
        self.kill_switch = kill_switch
        self.timeout = timedelta(seconds=timeout_seconds)
        self.poll_seconds = poll_seconds
        self._stop = Event()
        self._thread: Thread | None = None

    def start(self) -> None:
        if self._thread and self._thread.is_alive():
            return
        self._stop.clear()
        self._thread = Thread(
            target=self._run,
            name="aqr-order-ack-monitor",
            daemon=True,
        )
        self._thread.start()

    def stop(self) -> None:
        self._stop.set()
        if self._thread:
            self._thread.join(timeout=5)

    def poll_once(self, now: datetime | None = None) -> int:
        current = now or datetime.now(UTC)
        timed_out = self.repository.find_acknowledgement_timeouts(
            current - self.timeout
        )
        for item in timed_out:
            command_id = UUID(str(item["command_id"]))
            self.repository.append_order_event(
                OrderEvent(
                    client_order_id=item["client_order_id"],
                    gateway_name=item["gateway_name"],
                    event_type=OrderEventType.ORDER_UNKNOWN,
                    event_time=current,
                    event_sequence=time_ns(),
                    traded_quantity=0,
                    remaining_quantity=int(item["quantity"]),
                    raw_payload={
                        "reason": "ORDER_ACK_TIMEOUT",
                        "command_id": str(command_id),
                    },
                    deduplication_key=f"ack-timeout:{command_id}",
                )
            )
            self.repository.mark_acknowledgement_timeout(command_id)
            self.kill_switch.halt(
                f"order acknowledgement timeout: {item['client_order_id']}",
                account_id=item["account_id"],
                symbol=item["symbol"],
            )
        return len(timed_out)

    def _run(self) -> None:
        while not self._stop.wait(self.poll_seconds):
            try:
                self.poll_once()
            except Exception as exc:
                self.kill_switch.halt(f"acknowledgement monitor failure: {exc}")

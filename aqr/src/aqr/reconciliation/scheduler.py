from __future__ import annotations

from threading import Event, Thread

from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.reconciliation.service import ReconciliationService


class ReconciliationScheduler:
    def __init__(
        self,
        service: ReconciliationService,
        kill_switch: KillSwitch,
        *,
        interval_seconds: float,
    ) -> None:
        self.service = service
        self.kill_switch = kill_switch
        self.interval_seconds = interval_seconds
        self._stop = Event()
        self._thread: Thread | None = None

    def start(self) -> None:
        if self._thread and self._thread.is_alive():
            return
        self._stop.clear()
        self._thread = Thread(
            target=self._run,
            name="aqr-reconciliation",
            daemon=True,
        )
        self._thread.start()

    def stop(self) -> None:
        self._stop.set()
        if self._thread:
            self._thread.join(timeout=5)

    def _run(self) -> None:
        while not self._stop.wait(self.interval_seconds):
            try:
                self.service.reconcile("INTRADAY")
            except Exception as exc:
                self.kill_switch.halt(f"intraday reconciliation failure: {exc}")

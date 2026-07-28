from __future__ import annotations

from dataclasses import dataclass, field
from datetime import datetime
from threading import RLock

from aqr.domain.order import utc_now


class TradingHalted(RuntimeError):
    pass


@dataclass(frozen=True, slots=True)
class HaltRecord:
    reason: str
    account_id: str | None
    halted_at: datetime = field(default_factory=utc_now)


class KillSwitch:
    def __init__(self) -> None:
        self._lock = RLock()
        self._global_halt: HaltRecord | None = HaltRecord("startup reconciliation pending", None)
        self._account_halts: dict[str, HaltRecord] = {}
        self._symbol_halts: dict[tuple[str, str], HaltRecord] = {}

    @property
    def is_halted(self) -> bool:
        with self._lock:
            return self._global_halt is not None

    def assert_can_trade(self, account_id: str, symbol: str | None = None) -> None:
        with self._lock:
            record = self._global_halt or self._account_halts.get(account_id)
            if record is None and symbol:
                record = self._symbol_halts.get((account_id, symbol))
            if record:
                raise TradingHalted(record.reason)

    def halt(
        self,
        reason: str,
        account_id: str | None = None,
        symbol: str | None = None,
    ) -> None:
        with self._lock:
            record = HaltRecord(reason, account_id)
            if account_id and symbol:
                self._symbol_halts[(account_id, symbol)] = record
            elif account_id:
                self._account_halts[account_id] = record
            else:
                self._global_halt = record

    def resume(self, reason: str) -> None:
        if not reason.strip():
            raise ValueError("an audited resume reason is required")
        with self._lock:
            self._global_halt = None

    def resume_account(self, account_id: str, reason: str) -> None:
        if not reason.strip():
            raise ValueError("an audited resume reason is required")
        with self._lock:
            self._account_halts.pop(account_id, None)

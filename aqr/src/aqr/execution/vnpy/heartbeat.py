from __future__ import annotations

from dataclasses import dataclass, field
from datetime import UTC, datetime, timedelta
from threading import RLock


@dataclass(slots=True)
class HeartbeatMonitor:
    timeout: timedelta
    _last_seen: dict[str, datetime] = field(default_factory=dict)
    _lock: RLock = field(default_factory=RLock)

    def beat(self, component: str, at: datetime | None = None) -> None:
        with self._lock:
            self._last_seen[component] = at or datetime.now(UTC)

    def is_fresh(self, component: str, at: datetime | None = None) -> bool:
        now = at or datetime.now(UTC)
        with self._lock:
            last_seen = self._last_seen.get(component)
            return last_seen is not None and now - last_seen <= self.timeout

    def stale_components(self, required: set[str]) -> set[str]:
        return {name for name in required if not self.is_fresh(name)}

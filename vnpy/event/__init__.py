from .engine import Event, EventEngine, EVENT_TIMER


__all__ = [
    "Event",
    "EventEngine",
    "EVENT_TIMER",
    "DisruptorEventEngine",
    "create_engine",
]


def create_engine(interval: int = 1) -> "EventEngine":
    """
    Factory to create the appropriate EventEngine based on settings.

    Returns ``DisruptorEventEngine`` when ``SETTINGS["event.use_disruptor"]``
    is ``True`` *and* the Rust extension (``vnpy_disruptor``) is available.

    Falls back to the standard ``EventEngine`` otherwise.
    """
    from vnpy.trader.setting import SETTINGS

    if SETTINGS.get("event.use_disruptor", False):
        try:
            from .disruptor_engine import DisruptorEventEngine
            return DisruptorEventEngine(interval)
        except ImportError as exc:
            import warnings
            warnings.warn(
                f"event.use_disruptor=True but Rust extension unavailable "
                f"({exc}). Falling back to standard EventEngine.",
                stacklevel=2,
            )

    return EventEngine(interval)


def _lazy_disruptor():
    """Lazy import to avoid mandatory Rust dependency at package load time."""
    from .disruptor_engine import DisruptorEventEngine
    return DisruptorEventEngine


# Expose DisruptorEventEngine lazily so ``from vnpy.event import DisruptorEventEngine``
# works but does NOT trigger the ImportError if the Rust extension is absent.
def __getattr__(name: str):
    if name == "DisruptorEventEngine":
        return _lazy_disruptor()
    raise AttributeError(f"module 'vnpy.event' has no attribute {name!r}")

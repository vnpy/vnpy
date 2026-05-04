"""
High-performance event engine using the LMAX Disruptor pattern (disruptor-rs).

Drop-in replacement for ``vnpy.event.engine.EventEngine``.  The implementation
uses the Rust ``DisruptorProducer`` (PyO3 bindings for the ``disruptor`` crate
v4.1) when the ``vnpy_disruptor`` extension is available.
"""

from __future__ import annotations

import threading
from threading import Thread
from time import sleep

from vnpy.trader.setting import SETTINGS
from .engine import Event, EventEngine, EVENT_TIMER


# ---------------------------------------------------------------------------
# Try to import the Rust extension
# ---------------------------------------------------------------------------

try:
    from vnpy_disruptor import DisruptorProducer as _RustProducer

    _RUST_AVAILABLE = True
except ImportError:
    _RUST_AVAILABLE = False
    _RustProducer = None  # type: ignore[assignment,misc]


# ---------------------------------------------------------------------------
# DisruptorEventEngine
# ---------------------------------------------------------------------------


class DisruptorEventEngine(EventEngine):
    """
    High-performance event engine backed by the LMAX Disruptor pattern.

    Drop-in replacement for ``vnpy.event.engine.EventEngine``.
    Uses ``disruptor-rs`` (via PyO3) for the ring buffer when available.
    """

    def __init__(self, interval: int = 1) -> None:
        """
        Initialise the engine.

        Parameters
        ----------
        interval:
            Timer event generation interval in seconds (default: 1).

        Raises
        ------
        ImportError
            If the Rust extension (``vnpy_disruptor``) is absent.
        """
        super().__init__(interval)
        self._timer_thread: Thread | None = None

        buffer_size: int = SETTINGS.get("event.buffer_size", 65536)
        wait_strategy: str = SETTINGS.get("event.wait_strategy", "busy_spin")
        self._core_id: int | None = SETTINGS.get("event.core_id", None)

        if not _RUST_AVAILABLE:
            raise ImportError(
                "vnpy_disruptor Rust extension not found. "
                "Ensure it is installed via: cd vnpy-rs && maturin develop"
            )

        self._producer: _RustProducer = _RustProducer(buffer_size, wait_strategy)
        self._local: threading.local = threading.local()
        self._pre_start_queue: list[Event] = []
        self._lock: threading.Lock = threading.Lock()

    # ------------------------------------------------------------------
    # Event publication (Overridden for performance)
    # ------------------------------------------------------------------

    def put(self, event: Event) -> None:
        """
        Publish an event into the ring buffer.

        Uses zero-copy PyObject passing so that Python objects survive the
        Rust boundary faithfully without serialization overhead.

        Blocks (per wait strategy) if the ring buffer is full — provides
        backpressure without silent event loss.
        """
        if not self._active:
            with self._lock:
                if not self._active:
                    self._pre_start_queue.append(event)
                    return

        try:
            # Get or create thread-local producer handle for lock-free multi-producer support
            producer = getattr(self._local, "producer", None)
            if producer is None:
                producer = self._producer.clone_producer()
                self._local.producer = producer

            producer.publish(event)
        except RuntimeError as e:
            # Sync local active state with producer
            if not self._producer.is_active():
                self._active = False
            raise e

    def try_put(self, event: Event) -> bool:
        """
        Try to publish an event without blocking.
        Return True if successful, False if buffer is full.
        """
        if not self._active:
            with self._lock:
                if not self._active:
                    if len(self._pre_start_queue) < self._buffer_size:
                        self._pre_start_queue.append(event)
                        return True
                    return False

        try:
            # Get thread-local producer handle
            producer = getattr(self._local, "producer", None)
            if producer is None:
                producer = self._producer.clone_producer()
                self._local.producer = producer

            return producer.try_publish(event)
        except RuntimeError:
            # Engine stopped or other error
            return False

    def put_batch(self, events: list[Event]) -> None:
        """
        Publish a batch of events into the ring buffer.

        This is much more efficient than multiple calls to put().
        """
        if not events:
            return

        try:
            # Get or create thread-local producer handle
            producer = getattr(self._local, "producer", None)
            if producer is None:
                producer = self._producer.clone_producer()
                self._local.producer = producer

            producer.publish_batch(events)
        except RuntimeError as e:
            # Sync local active state with producer
            if not self._producer.is_active():
                self._active = False
            raise e

    # ------------------------------------------------------------------
    # Lifecycle (Overridden to manage Rust worker)
    # ------------------------------------------------------------------

    def start(self) -> None:
        """Start event processing and timer."""
        if self._active:
            return

        self._active = True

        # Spawn the managed Rust worker thread for event dispatch
        self._producer.start_worker(self._process_batch, self._core_id)

        # Drain pre-start queue
        with self._lock:
            if self._pre_start_queue:
                self.put_batch(self._pre_start_queue)
                self._pre_start_queue.clear()

        self._timer_thread = Thread(
            target=self._run_timer, daemon=True, name="vnpy-disruptor-timer"
        )
        self._timer_thread.start()

    def stop(self) -> None:
        """Stop event processing and timer."""
        if not self._active:
            return

        self._active = False

        # 1. Join timer thread first while producer is still potentially processing.
        if self._timer_thread and self._timer_thread.is_alive():
            self._timer_thread.join(timeout=0.1)

        # 2. Shutdown the Rust producer and worker thread.
        self._producer.stop()
        self._timer_thread = None

    # ------------------------------------------------------------------
    # Internal: worker and timer threads
    # ------------------------------------------------------------------

    def _run_timer(self) -> None:
        """Timer thread: generates ``EVENT_TIMER`` events at the configured interval."""
        while self._active:
            # Use small sleep increments to remain responsive to stop()
            for _ in range(10):
                if not self._active:
                    return
                sleep(self._interval / 10.0)

            if not self._active:
                break

            try:
                # Use try_put for timer events to avoid blocking during shutdown
                self.try_put(Event(EVENT_TIMER))
            except (RuntimeError, AttributeError):
                # Producer stopped or local storage cleared
                break

    def _process_batch(self, events: list[Event]) -> None:
        """
        Process a batch of events in a single call.
        Highly optimized with handler caching.
        """
        last_type = None
        handlers = []

        for event in events:
            # 1. Type-specific handlers
            etype = event.type
            if etype != last_type:
                last_type = etype
                handlers = self._handlers.get(etype, [])

            if handlers:
                for handler in handlers:
                    handler(event)

            # 2. General handlers (called for EVERY event)
            if self._general_handlers:
                for handler in self._general_handlers:
                    handler(event)

    # ------------------------------------------------------------------
    # Introspection
    # ------------------------------------------------------------------

    def is_active(self) -> bool:
        """Return ``True`` if the engine is running."""
        return self._active and self._producer.is_active()

    def get_handler_count(self, event_type: str) -> int:
        """Return the number of handlers registered for *event_type*."""
        return len(self._handlers.get(event_type, []))

    def get_metrics(self) -> dict:
        """Return real-time metrics from the underlying Rust engine."""
        return self._producer.get_metrics()

    def get_general_handler_count(self) -> int:
        """Return the number of general handlers."""
        return len(self._general_handlers)

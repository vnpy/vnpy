import time

from contextlib import redirect_stderr
from io import StringIO
from vnpy.event import Event, EventEngine


def test_event_engine_calls_registered_handler_once() -> None:
    engine: EventEngine = EventEngine()
    seen: list[int] = []

    def handler(event: Event) -> None:
        data: object = event.data
        assert isinstance(data, int)
        seen.append(data)

    engine.register("eTest", handler)
    engine.register("eTest", handler)
    engine.start()
    try:
        engine.put(Event("eTest", 7))
        deadline: float = time.monotonic() + 2
        while not seen and time.monotonic() < deadline:
            time.sleep(0.01)
        assert seen == [7]
    finally:
        engine.stop()

    assert not engine._thread.is_alive()
    assert not engine._timer.is_alive()


def test_event_engine_survives_handler_exception() -> None:
    engine: EventEngine = EventEngine()
    seen: list[int] = []
    stderr: StringIO = StringIO()

    def bad_handler(event: Event) -> None:
        raise ValueError("test exception")

    def good_handler(event: Event) -> None:
        # skip the timer event which the timer thread may emit while stopping
        if event.type == "eTest":
            seen.append(event.data)

    engine.register("eTest", bad_handler)
    engine.register("eTest", good_handler)
    engine.register_general(bad_handler)
    engine.register_general(good_handler)
    engine.start()
    with redirect_stderr(stderr):
        try:
            for i in range(3):
                engine.put(Event("eTest", i))

            deadline: float = time.monotonic() + 2
            while len(seen) < 6 and time.monotonic() < deadline:
                time.sleep(0.01)
        finally:
            engine.stop()

    assert seen == [0, 0, 1, 1, 2, 2]
    assert "ValueError: test exception" in stderr.getvalue()
    assert not engine._thread.is_alive()
    assert not engine._timer.is_alive()

import time

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

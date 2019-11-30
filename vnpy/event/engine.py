"""
Event-driven framework of vn.py framework.
"""
import sys
from collections import defaultdict
from queue import Empty, Queue
from threading import Thread
from time import sleep, time
from typing import Any, Callable

EVENT_TIMER = "eTimer"


class Event:
    """
    Event object consists of a type string which is used
    by event engine for distributing event, and a data
    object which contains the real data.
    """

    def __init__(self, type: str, data: Any = None):
        """"""
        self.type = type
        self.data = data


# Defines handler function to be used in event engine.
HandlerType = Callable[[Event], None]


class EventEngine:
    """
    Event engine distributes event object based on its type
    to those handlers registered.

    It also generates timer event by every interval seconds,
    which can be used for timing purpose.
    """

    def __init__(self, interval: int = 1, debug: bool = False, over_ms: int = 500):
        """
        Timer event is generated every 1 second by default, if
        interval not specified.
        增强模式：
            debug: performance debug
            over_ms: over micro seconds for each handler execution.
            add try catch handel event exception
        """
        self._interval = interval
        self._queue = Queue()
        self._active = False
        self._debug = debug
        self._over_ms = over_ms
        self._thread = Thread(target=self._run)
        self._timer = Thread(target=self._run_timer)
        self._handlers = defaultdict(list)
        self._general_handlers = []

    def _run(self):
        """
        Get event from queue and then process it.
        """
        while self._active:
            try:
                event = self._queue.get(block=True, timeout=1)
                self._process(event) if not self._debug else self._process_debug(event)
            except Empty:
                pass

    def _process_debug(self, event: Event):
        """
        process event with debug mode:
        1.performance
        2.try catch exception

        """
        for handler in self._handlers[event.type]:
            t1 = time()
            handler_name = str(handler.__qualname__)
            try:
                handler(event)
            except Exception as ex:
                print(f'运行 {event.type} {handler_name} 异常:{str(ex)}',
                      file=sys.stderr)
                continue
            t2 = time()
            execute_ms = (int(round(t2 * 1000))) - (int(round(t1 * 1000)))
            if execute_ms > self._over_ms:
                print(f'运行{event.type} {handler_name} 耗时:{execute_ms}ms >{self._over_ms}ms',
                      file=sys.stderr)

        if self._general_handlers:
            for handler in self._general_handlers:
                t1 = time()
                handler_name = str(handler.__qualname__)
                handler(event)
                t2 = time()
                execute_ms = (int(round(t2 * 1000))) - (int(round(t1 * 1000)))
                if execute_ms > self._over_ms:
                    print(f'运行 general {event.type} {handler_name} 耗时:{execute_ms}ms > {self._over_ms}ms',
                        file=sys.stderr)

    def _process(self, event: Event):
        """
        First ditribute event to those handlers registered listening
        to this type.

        Then distrubute event to those general handlers which listens
        to all types.
        """
        if event.type in self._handlers:
            [handler(event) for handler in self._handlers[event.type]]

        if self._general_handlers:
            [handler(event) for handler in self._general_handlers]

    def _run_timer(self):
        """
        Sleep by interval second(s) and then generate a timer event.
        """
        while self._active:
            sleep(self._interval)
            event = Event(EVENT_TIMER)
            self.put(event)

    def start(self):
        """
        Start event engine to process events and generate timer events.
        """
        self._active = True
        self._thread.start()
        self._timer.start()

    def stop(self):
        """
        Stop event engine.
        """
        self._active = False
        self._timer.join()
        self._thread.join()

    def put(self, event: Event):
        """
        Put an event object into event queue.
        """
        self._queue.put(event)

    def register(self, type: str, handler: HandlerType):
        """
        Register a new handler function for a specific event type. Every
        function can only be registered once for each event type.
        """
        handler_list = self._handlers[type]
        if handler not in handler_list:
            handler_list.append(handler)

    def unregister(self, type: str, handler: HandlerType):
        """
        Unregister an existing handler function from event engine.
        """
        handler_list = self._handlers[type]

        if handler in handler_list:
            handler_list.remove(handler)

        if not handler_list:
            self._handlers.pop(type)

    def register_general(self, handler: HandlerType):
        """
        Register a new handler function for all event types. Every
        function can only be registered once for each event type.
        """
        if handler not in self._general_handlers:
            self._general_handlers.append(handler)

    def unregister_general(self, handler: HandlerType):
        """
        Unregister an existing general handler function.
        """
        if handler in self._general_handlers:
            self._general_handlers.remove(handler)

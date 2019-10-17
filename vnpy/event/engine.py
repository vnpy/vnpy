"""
Event-driven framework of vn.py framework.
vn.py框架的事件驱动框架。
"""
##############################################
# 1.事件的注册和取消，使用者可以根据自己的需求来设置引擎需要关心那些事件
# 2.事件对于的处理方法的挂钩。显然，一个事件可以由多个方法来处理，也可以一个方法处理多个事件。
# 3.不断监听事件的发生与否，如果发生就进行相应的处理，也就是调用设置好的函数。
from collections import defaultdict
from queue import Empty, Queue
from threading import Thread
from time import sleep
from typing import Any, Callable

EVENT_TIMER = "eTimer"


class Event:
    """
    Event object consists of a type string which is used
    by event engine for distributing event, and a data
    object which contains the real data.

    事件对象由事件引擎用于分发事件的类型字符串和包含实际数据的数据对象组成。

    """

    def __init__(self, type: str, data: Any = None):
        """"""
        self.type = type
        self.data = data


# Defines handler function to be used in event engine.
# 定义要在事件引擎中使用的处理函数。
HandlerType = Callable[[Event], None]


class EventEngine:
    """
    Event engine distributes event object based on its type
    to those handlers registered.

    It also generates timer event by every interval seconds,
    which can be used for timing purpose.
    事件引擎根据事件对象的类型将其分配给已注册的处理程序。
    它还每间隔数秒生成一次计时器事件，可用于计时目的。（数秒自己定义）

    """

    def __init__(self, interval: int = 1):
        """
        Timer event is generated every 1 second by default, if
        interval not specified.
        如果未指定时间间隔，则默认情况下每1秒生成一次计时器事件。
        """
        ### 作用：初始化事件管理器
        self._interval = interval
        self._queue = Queue()  # 线程队列
        self._active = False  # 事件驱动开关
        self._thread = Thread(target=self._run)
        self._timer = Thread(target=self._run_timer)
        self._handlers = defaultdict(list)
        self._general_handlers = []

    def _run(self):
        """
        Get event from queue and then process it.
        从队列中获取事件，然后对其进行处理
        """
        while self._active:
            try:
                event = self._queue.get(block=True, timeout=1)
                self._process(event)
            except Empty:
                pass

    def _process(self, event: Event):
        """
        First ditribute event to those handlers registered listening
        to this type.

        Then distrubute event to those general handlers which listens
        to all types.

        首先将事件分发给已注册侦听此类型的处理程序。
        然后甚至分发给那些侦听所有类型的常规处理程序。

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
        将事件对象放入事件队列。
        """
        self._queue.put(event)

    def register(self, type: str, handler: HandlerType):
        """
        Register a new handler function for a specific event type. Every
        function can only be registered once for each event type.
        为特定事件类型注册新的处理函数。对于每种事件类型，每个功能只能注册一次。
        """
        handler_list = self._handlers[type]
        if handler not in handler_list:
            handler_list.append(handler)

    def unregister(self, type: str, handler: HandlerType):
        """
        Unregister an existing handler function from event engine.
        从事件引擎中注销现有的处理函数。
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
        为所有事件类型注册一个新的处理函数。对于每种事件类型，每个功能只能注册一次。
        """
        if handler not in self._general_handlers:
            self._general_handlers.append(handler)

    def unregister_general(self, handler: HandlerType):
        """
        Unregister an existing general handler function.
        注销现有的常规处理函数。
        """
        if handler in self._general_handlers:
            self._general_handlers.remove(handler)


if __name__ == "__main__":
    from vnpy.event import EventEngine

    EVENT_TIMER = "eTimer"


    def func(event):
        print("hello timer!")


    ee = EventEngine()
    ee.register(EVENT_TIMER, func)
    ee.start()
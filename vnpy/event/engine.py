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
    事件驱动引擎
    事件驱动引擎中所有的变量都设置为了私有，这是为了防止不小心
    从外部修改了这些变量的值或状态，导致bug。

    变量说明
    __queue：私有变量，事件队列
    __active：私有变量，事件引擎开关
    __thread：私有变量，事件处理线程
    __timer：私有变量，计时器
    __handlers：私有变量，事件处理函数字典


    方法说明
    __run: 私有方法，事件处理线程连续运行用
    __process: 私有方法，处理事件，调用注册在引擎中的监听函数
    __onTimer：私有方法，计时器固定事件间隔触发后，向事件队列中存入计时器事件
    start: 公共方法，启动引擎
    stop：公共方法，停止引擎
    register：公共方法，向引擎中注册监听函数
    unregister：公共方法，向引擎中注销监听函数
    put：公共方法，向事件队列中存入新的事件

    事件监听函数必须定义为输入参数仅为一个event对象，即：

    函数
    def func(event)
        ...

    对象方法
    def method(self, event)
        ...

    """

    def __init__(self, interval: int = 1):
        """
        Timer event is generated every 1 second by default, if
        interval not specified.
        如果未指定时间间隔，则默认情况下每1秒生成一次计时器事件。
        """
        ### 作用：初始化事件管理器
        self._interval = interval  # 事件周期
        self._queue = Queue()  # 事件队列
        self._active = False  # 事件引擎开关
        self._thread = Thread(target=self._run)  # 事件处理线程
        self._timer = Thread(target=self._run_timer)  # 计时器用于触发计时器事件
        # 这里的_handlers是一个字典，用来保存对应的事件调用关系
        # 其中每个键对应的值是一个列表，列表中保存了对该事件进行监听的函数功能
        self._handlers = defaultdict(list)  # 一个字典
        # _general_handlers是一个列表，用来保存通用回调函数（所有事件均调用）
        self._general_handlers = []

    def _run(self):
        """
        Get event from queue and then process it.
        从队列中循环获取事件，然后对其进行处理
        """
        while self._active:
            try:
                # 每1秒从队列里获取一次事件
                event = self._queue.get(block=True, timeout=1)
                self._process(event)  # 生成一个变量
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
        # 检查是否存在对该事件进行监听处理函数
        if event.type in self._handlers:
            # 若存在，则按顺序将事件传递给处理函数执行
            [handler(event) for handler in self._handlers[event.type]]

            # 以上语句为Python列表解析方式的写法，对应的常规循环写法为：
            # for handler in self._handlers[event.type]:
                # handler(event)

        # 检查是否存在常规线程的处理函数
        if self._general_handlers:
            # 同上
            [handler(event) for handler in self._general_handlers]

    def _run_timer(self):
        """
        Sleep by interval second(s) and then generate a timer event.
        以间隔秒为单位休眠，然后生成一个计时器事件
        """
        while self._active:
            sleep(self._interval)  # 阻塞时间，默认设置1秒，可以在初始化的时候更改
            event = Event(EVENT_TIMER)  # 创建计时器事件
            self.put(event)  # 向队列中存入计时器事件

    def start(self):
        """
        Start event engine to process events and generate timer events.
        启动事件引擎以处理事件并生成计时器事件
        """
        self._active = True  # 将事件引擎设置为启动
        self._thread.start()  # 启动事件引擎
        self._timer.start()  # 启动计时器，默认为1秒

    def stop(self):
        """
        Stop event engine.
        停止事件引擎
        """
        self._active = False  # 将引擎设置为停止
        self._timer.join()  # 停止计时器
        self._thread.join()  # 停止事件引擎线程

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

        # 获取该事件类型对应的处理函数列表
        handler_list = self._handlers[type]
        # 如果不在列表中，则添加进去
        if handler not in handler_list:
            handler_list.append(handler)

    def unregister(self, type: str, handler: HandlerType):
        """
        Unregister an existing handler function from event engine.
        从事件引擎中注销现有事件的处理函数。
        """

        handler_list = self._handlers[type]
        # 如果存在该事件，则移除
        if handler in handler_list:
            handler_list.remove(handler)
        # 如果不存在该事件，则移除该事件类型
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

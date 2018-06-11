# encoding: UTF-8

from vnpy.event.oeventEngine import EventEngine2 as vtEventEngine2


class EventEngine2(vtEventEngine2):
    """
    改动核心代码的开发在此进行
    """

    def register(self, type_, handler):
        # do something
        return super(EventEngine2, self).register(type_, handler)

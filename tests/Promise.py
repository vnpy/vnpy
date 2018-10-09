# encoding: UTF-8
from Queue import Queue

from enum import Enum


class PromiseResultType(Enum):
    Result = 1
    Exception = 2
    Traceback = 3


class Promise(object):
    """
    用队列实现的一个简单的Promise类型
    """
    
    def __init__(self):
        self._queue = Queue()
    
    def set_result(self, val):
        self._queue.put((PromiseResultType.Result, val))
    
    def get(self, timeout=None):
        res = self._queue.get(timeout=timeout)
        if res[0] == PromiseResultType.Result:
            return res[1]
        elif res[0] == PromiseResultType.Exception:
            raise res[1]
        else:
            et, ev, tb = res[1]
            raise et, ev, tb
    
    def set_exception(self, valueOrType, val=None, tb=None):
        if val is None:
            self._queue.put((PromiseResultType.Exception, val))
        else:
            self._queue.put((PromiseResultType.Traceback, (valueOrType, val, tb)))

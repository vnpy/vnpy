# encoding: UTF-8
from Queue import Queue

from enum import Enum


class PromiseResultType(Enum):
    Result = 1
    Exception = 2


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
        raise res[2]
    
    def set_exception(self, val):
        self._queue.put((PromiseResultType.Exception, val))

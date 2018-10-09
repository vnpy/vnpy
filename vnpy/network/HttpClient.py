# encoding: UTF-8


import sys
from Queue import Empty, Queue
from abc import abstractmethod
from multiprocessing.dummy import Pool

import requests
from enum import Enum
from typing import Any, Callable


class RequestStatus(Enum):
    ready = 0  # 刚刚构建
    success = 1  # 请求成功 code == 200
    failed = 2
    error = 3  # 发生错误 网络错误、json解析错误，等等


########################################################################
class Request(object):
    """
    表示一个内部的Request，用于状态查询
    构造该类的时候注意，reqid字段的增长没上锁，所以在多线程环境中不能直接构造该类。
    """
    _last_id = 0
    
    #----------------------------------------------------------------------
    def __init__(self, extra=None):
        Request._last_id += 1
        self._id = Request._last_id
        self._status = RequestStatus.ready
        self.extra = extra
    
    #----------------------------------------------------------------------
    @property
    def id(self):
        return self._id
    
    #----------------------------------------------------------------------
    @property
    def success(self):
        assert self.finished, "'success' property is only available after request is finished"
        return self._status == RequestStatus.success
    
    #----------------------------------------------------------------------
    @property
    def failed(self):
        assert self.finished, "'failed' property is only available after request is finished"
        return self._status == RequestStatus.failed
    
    #----------------------------------------------------------------------
    @property
    def finished(self):
        return self._status != RequestStatus.ready
    
    #----------------------------------------------------------------------
    @property
    def error(self):
        return self._status == RequestStatus.error


########################################################################
class HttpClient(object):
    """
    HTTP 客户端。目前是为了对接各种RESTFulAPI而设计的。
    
    如果需要给请求加上签名，请重载beforeRequest函数。
    如果需要处理非200的请求，请重载onFailed函数。
    如果捕获Python内部错误，例如网络连接失败等等，请重载onError函数。
    """
    
    #----------------------------------------------------------------------
    def __init__(self):
        """
        :param urlBase: 路径前缀。 例如'https://www.bitmex.com/api/v1/'
        """
        self.urlBase = None  # type: str
        self.sessionProvider = requestsSessionProvider
        
        self._active = False
        
        self._queue = Queue()
        self._pool = None  # type: Pool
    
    #----------------------------------------------------------------------
    def init(self, urlBase):
        self.urlBase = urlBase
    
    #----------------------------------------------------------------------
    def setSessionProvider(self, sessionProvider):
        """
        设置sessionProvider可以使用自定义的requests实现。
        @:param sessionProvider: callable。调用后应该返回一个对象带request函数的对象，该request函数的用法应该和requests中的一致。 \
                每个工作线程会调用该函数一次以期获得一个独立的session实例。
        """
        self.sessionProvider = sessionProvider
    
    #----------------------------------------------------------------------
    def start(self, n=3):
        """启动"""
        assert not self._active
        
        self._active = True
        self._pool = Pool(n)
        self._pool.apply_async(self._run)
    
    #----------------------------------------------------------------------
    def stop(self):
        """
        强制停止运行，未发出的请求都会被暂停（仍处于队列中）
        :return:
        """
        self._active = False
    
    #----------------------------------------------------------------------
    def addReq(self, method, path, callback, params=None, data=None,
               extra=None):  # type: (str, str, Callable[[dict, Request], Any], dict, dict, Any)->Request
        """
        发送一个请求
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param onSuccess: callback for success action(status code == 200) type: (dict, Request)
        :param onFailed: callback for failed action(status code != 200)   type: (code, dict, Request)
        :param params: dict for query string
        :param data: dict for body
        :return: 
        """
        
        req = Request(extra=extra)
        self._queue.put((method, path, callback, params, data, req))
        return req
    
    #----------------------------------------------------------------------
    def _run(self):
        session = self.sessionProvider()
        while self._active:
            try:
                method, path, callback, params, postdict, req = self._queue.get(timeout=1)
                self.processReq(method, path, callback, params, postdict, req, session)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    @abstractmethod
    def beforeRequest(self, method, path, params, data):  # type: (str, str, dict, dict)->(str, str, dict, dict, dict)
        """
        所有请求在发送之前都会经过这个函数
        签名之类的前奏可以在这里面实现
        @:return (method, path, params, body, headers) body可以是request中data参数能接收的任意类型，例如bytes,str,dict都可以。
        """
        return method, path, params, data, {}
    
    #----------------------------------------------------------------------
    def onFailed(self, httpStatusCode, data, req):
        """
        请求失败处理函数（HttpStatusCode!=200）.
        默认行为是打印到stderr
        
        @:param data 这个data是原始数据，并不是dict。而且有可能为null。
        """
        print("req {} failed with {}: \n"
              "{}\n".format(req.id, httpStatusCode, data))
    
    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb, req):
        """
        Python内部错误处理：默认行为是仍给excepthook
        """
        print("error in req : {}\n".format(req.id))
        sys.excepthook(exceptionType, exceptionValue, tb)
    
    #----------------------------------------------------------------------
    def processReq(self, method, path, callback, params, data, req,
                   session):  # type: (str, str, callable, dict, dict, Request, requests.Session)->None
        """处理请求"""
        try:
            method, path, params, data, headers = self.beforeRequest(method, path, params, data)
            
            url = self.urlBase + path
            
            resp = session.request(method, url, headers=headers, params=params, data=data)
            
            httpStatusCode = resp.status_code
            if httpStatusCode == 200:
                jsonBody = resp.json()
                callback(jsonBody, req)
                req._status = RequestStatus.success
            else:
                req._status = RequestStatus.failed
                self.onFailed(httpStatusCode, data, req)
        except:
            req._status = RequestStatus.error
            t, v, tb = sys.exc_info()
            self.onError(t, v, tb, req)


########################################################################
def requestsSessionProvider():
    return requests.session()

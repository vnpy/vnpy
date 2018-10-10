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
    """
    
    #----------------------------------------------------------------------
    def __init__(self, method, path, callback, params, data, headers):
        self.method = method  # type: str
        self.path = path  # type: str
        self.callback = callback  # type: callable
        self.params = params  # type: dict #, bytes, str
        self.data = data  # type: dict #, bytes, str
        self.headers = headers  # type: dict
        self.onFailed = None  # type: callable
        self.skipDefaultOnFailed = None  # type: callable
        self.extra = None  # type: Any
        
        self._response = None  # type: requests.Response
        self._status = RequestStatus.ready
    
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

    #----------------------------------------------------------------------
    def __str__(self):
        statusCode = 'not finished'
        if self._response:
            statusCode = self._response.status_code
        return "{} {} : {} {}\n".format(self.method, self.path, self._status, statusCode)


########################################################################
class HttpClient(object):
    """
    HTTP 客户端。目前是为了对接各种RESTFulAPI而设计的。
    
    如果需要给请求加上签名，请重载beforeRequest函数。
    如果需要处理非200的请求，请重载onFailed函数。
    如果每一个请求的非200返回都需要单独处理，使用addReq函数的onFailed参数
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
    def addReq(self, method, path, callback,
               params=None, data=None, headers = None,
               onFailed=None, skipDefaultOnFailed=True,
               extra=None):  # type: (str, str, Callable[[dict, Request], Any], dict, dict, dict, Callable[[dict, Request], Any], bool, Any)->Request
        """
        发送一个请求
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param callback: 请求成功后的回调(状态吗为2xx时认为请求成功)   type: (dict, Request)
        :param params: dict for query string
        :param data: dict for body
        :param headers: dict for headers
        :param onFailed: 请求失败后的回调(状态吗不为2xx时认为请求失败)   type: (code, dict, Request)
        :param skipDefaultOnFailed: 仅当onFailed参数存在时有效：忽略对虚函数onFailed的调用
        :param extra: 返回值的extra字段会被设置为这个值。当然，你也可以在函数调用之后再设置这个字段。
        :return: Request
        """

        req = Request(method, path, callback, params, data, headers)
        req.onFailed = onFailed
        req.skipDefaultOnFailed = skipDefaultOnFailed
        req.extra = extra
        self._queue.put(req)
        return req
    
    #----------------------------------------------------------------------
    def _run(self):
        session = self.sessionProvider()
        while self._active:
            try:
                req = self._queue.get(timeout=1)
                self.processReq(req, session)
            except Empty:
                pass
    
    #----------------------------------------------------------------------
    @abstractmethod
    def beforeRequest(self, req):  # type: (Request)->Request
        """
        所有请求在发送之前都会经过这个函数
        签名之类的前奏可以在这里面实现
        需要对request进行什么修改就做什么修改吧
        @:return (req)
        """
        return req
    
    #----------------------------------------------------------------------
    def onFailed(self, httpStatusCode, data, req):
        """
        请求失败处理函数（HttpStatusCode!=200）.
        默认行为是打印到stderr
        
        @:param data 这个data是原始数据，并不是dict。而且有可能为null。
        """
        print("reuqest : {} {} failed with {}: \n"
              "headers: {}\n"
              "params: {}\n"
              "data: {}\n"
              "response:"
              "{}\n"
              .format(req.method, req.path, httpStatusCode,
                      req.headers,
                      req.params,
                      req.data,
                      data))
    
    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb, req):
        """
        Python内部错误处理：默认行为是仍给excepthook
        """
        print("error in req : {}\n".format(req))
        sys.excepthook(exceptionType, exceptionValue, tb)
    
    #----------------------------------------------------------------------
    def processReq(self, req, session):  # type: (Request, requests.Session)->None
        """处理请求"""
        try:
            req = self.beforeRequest(req)
    
            url = self.makeFullUrl(req.path)
    
            response = session.request(req.method, url, headers=req.headers, params=req.params, data=req.data)
            req._response = response
    
            httpStatusCode = response.status_code
            if httpStatusCode/100 == 2:
                jsonBody = response.json()
                req.callback(jsonBody, req)
                req._status = RequestStatus.success
            else:
                req._status = RequestStatus.failed
                
                if req.onFailed:
                    req.onFailed(httpStatusCode, response.raw, req)
                
                # 若没有onFailed或者没设置skipDefaultOnFailed，则调用默认的处理函数
                if not req.onFailed or not req.skipDefaultOnFailed:
                    self.onFailed(httpStatusCode, response.raw, req)
        except:
            req._status = RequestStatus.error
            t, v, tb = sys.exc_info()
            self.onError(t, v, tb, req)

    def makeFullUrl(self, path):
        url = self.urlBase + path
        return url


########################################################################
def requestsSessionProvider():
    return requests.session()

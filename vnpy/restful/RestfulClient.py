# encoding: UTF-8


########################################################################
import sys
from Queue import Empty, Queue
from abc import abstractmethod
from multiprocessing.dummy import Pool

from enum import Enum


########################################################################
class RequestStatus(Enum):
    ready = 0  # 刚刚构建
    success = 1  # 请求成功 code == 200
    failed = 2  # 请求失败 code != 200
    error = 3  # 发生错误 网络错误、json解析错误，等等


########################################################################
class Request(object):
    """
    表示一个内部的Request，用于状态查询
    构造该类的时候注意，reqid字段的增长没上锁，所以在多线程环境中不能直接构造该类。
    """
    _last_id = 0
    
    #----------------------------------------------------------------------
    def __init__(self):
        Request._last_id += 1
        self._id = Request._last_id
        self._status = RequestStatus.ready
    
    #----------------------------------------------------------------------
    @property
    def id(self):
        return self._id
    
    #----------------------------------------------------------------------
    @property
    def finished(self):
        return self._status != RequestStatus.ready
    
    #----------------------------------------------------------------------
    @property
    def error(self):
        return self._status == RequestStatus.error
    
    #----------------------------------------------------------------------
    @property
    def success(self):
        return self._status == RequestStatus.success


########################################################################
class RestfulClient(object):
    
    #----------------------------------------------------------------------
    def __init__(self, urlBase, sessionProvider):
        """
        :param urlBase: 路径前缀。 例如'https://www.bitmex.com/api/v1/'
        :param sessionProvider: callable。调用后应该返回一个对象带request函数的对象，该request函数的用法应该和requests中的一致。\
        每个工作线程会调用该函数一次以期获得一个独立的session实例。可以选择requestsSessionProvider。
        """
        self.urlBase = urlBase  # type: str
        
        self._active = False
        
        self._queue = Queue()
        self._pool = None  # type: Pool
        
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
    def addReq(self, method, path, onSuccess, onFailed, params=None, postdict=None):
        """
        发送一个请求
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param onSuccess: callback for success action(status code == 200) type: (dict, Request)
        :param onFailed: callback for failed action(status code != 200)   type: (code, dict, Request)
        :param params: dict for query string
        :param postdict: dict for body
        :return: 
        """
        
        req = Request()
        self._queue.put((method, path, onSuccess, onFailed, params, postdict, Request()))
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
    def beforeRequest(self, method, path, params, postdict):  # type: (str, str, dict, dict)->(str, dict, dict, dict)
        """
        所有请求在发送之前都会经过这个函数
        签名之类的前奏可以在这里面实现
        @:return (path, params, body, headers) body可以是request中data参数能接收的任意类型，例如bytes,str,dict都可以。
        """
        pass
    
    #----------------------------------------------------------------------
    def onError(self, exceptionType, exceptionValue, tb, req):
        """
        Python内部错误处理：默认行为是仍给excepthook
        """
        sys.stderr.write("on req : {}".format(req.id))
        sys.excepthook(exceptionType, exceptionValue, tb)
    
    #----------------------------------------------------------------------
    def processReq(self, info, session):
        """处理请求"""
        method, path, onSuccess, onFailed, params, postdict, req = info  # type: str, str, callable, callable, dict, dict, Request
        
        path, params, body, headers = self.beforeRequest(method, path, params, postdict)
        
        url = self.urlBase + path
        
        try:
            # 使用长连接的session，比短连接的耗时缩短20%
            resp = session.request(method, url, headers=headers, params=params, data=body)
            
            code = resp.status_code
            jsonBody = resp.json()
            
            if code == 200:
                req._status = RequestStatus.success
                onSuccess(jsonBody, req)
            else:
                req._status = RequestStatus.failed
                onFailed(code, jsonBody, req)
        except:
            req._status = RequestStatus.error
            t, v, tb = sys.exc_info()
            self.onError(t, v, tb, req)


########################################################################
def requestsSessionProvider():
    import requests
    return requests.session()

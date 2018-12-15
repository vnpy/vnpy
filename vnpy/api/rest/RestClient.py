# encoding: UTF-8


import sys
import traceback
from queue import Empty, Queue
from datetime import datetime
from multiprocessing.dummy import Pool

import requests
from enum import Enum
from typing import Any, Callable, Optional


########################################################################
class RequestStatus(Enum):
    ready = 0  # 刚刚构建
    success = 1  # 请求成功 code == 2xx
    failed = 2
    error = 3  # 发生错误 网络错误、json解析错误，等等


########################################################################
class Request(object):
    """
    表示一个内部的Request，用于状态查询
    """
    
    #----------------------------------------------------------------------
    def __init__(self, method, path, params, data, headers, callback):
        self.method = method  # type: str
        self.path = path  # type: str
        self.callback = callback  # type: callable
        self.params = params  # type: dict #, bytes, str
        self.data = data  # type: dict #, bytes, str
        self.headers = headers  # type: dict
        
        self.onFailed = None  # type: callable
        self.onError = None  # type: callable
        self.extra = None  # type: Any

        self.response = None  # type: requests.Response
        self.status = RequestStatus.ready # type: RequestStatus

    #----------------------------------------------------------------------
    def __str__(self):
        if self.response is None:
            statusCode = 'terminated'
        else:
            statusCode = self.response.status_code
        return ("reuqest : {} {} {} because {}: \n"
                "headers: {}\n"
                "params: {}\n"
                "data: {}\n"
                "response:"
                "{}\n"
                .format(self.method, self.path, self.status.name, statusCode,
                        self.headers,
                        self.params,
                        self.data,
                        '' if self.response is None else self.response.text))


########################################################################
class RestClient(object):
    """
    HTTP 客户端。目前是为了对接各种RESTfulAPI而设计的。
    
    如果需要给请求加上签名，请设置beforeRequest, 函数类型请参考defaultBeforeRequest。
    如果需要处理非2xx的请求，请设置onFailed，函数类型请参考defaultOnFailed。
    如果每一个请求的非2xx返回都需要单独处理，使用addReq函数的onFailed参数
    如果捕获Python内部错误，例如网络连接失败等等，请设置onError，函数类型请参考defaultOnError
    """
    
    #----------------------------------------------------------------------
    def __init__(self):
        """
        """
        self.urlBase = None  # type: str
        self._active = False

        self._queue = Queue()
        self._pool = None  # type: Pool
    
    #----------------------------------------------------------------------
    def init(self, urlBase):
        """
        初始化
        :param urlBase: 路径前缀。 例如'https://www.bitmex.com/api/v1/'
        """
        self.urlBase = urlBase

    #----------------------------------------------------------------------
    def _createSession(self):
        """"""
        return requests.session()
    
    #----------------------------------------------------------------------
    def start(self, n=3):
        """启动"""
        if self._active:
            return
        
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
    def join(self):
        """
        等待所有请求处理结束
        如果要并确保RestClient的退出，请在调用stop之后紧接着调用join。
        如果只是要确保所有的请求都处理完，直接调用join即可。
        :return:
        """
        self._queue.join()
    
    #----------------------------------------------------------------------
    def addRequest(self,
                   method,          # type: str
                   path,            # type: str
                   callback,        # type: Callable[[dict, Request], Any]
                   params=None,     # type: dict
                   data=None,       # type: dict
                   headers=None,    # type: dict
                   onFailed=None,   # type: Callable[[int, Request], Any]
                   onError=None,    # type: Callable[[type, Exception, traceback, Request], Any]
                   extra=None       # type: Any
                   ):               # type: (...)->Request
        """
        发送一个请求
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param callback: 请求成功后的回调(状态吗为2xx时认为请求成功)   type: (dict, Request)
        :param params: dict for query string
        :param data: dict for body
        :param headers: dict for headers
        :param onFailed: 请求失败后的回调(状态吗不为2xx时认为请求失败)（如果指定该值，默认的onFailed将不会被调用） type: (code, dict, Request)
        :param onError: 请求出现Python错误后的回调（如果指定该值，默认的onError将不会被调用） type: (etype, evalue, tb, Request)
        :param extra: 返回值的extra字段会被设置为这个值。当然，你也可以在函数调用之后再设置这个字段。
        :return: Request
        """

        request = Request(method, path, params, data, headers, callback)
        request.extra = extra
        request.onFailed = onFailed
        request.onError = onError
        self._queue.put(request)
        return request
    
    #----------------------------------------------------------------------
    def _run(self):
        try:
            session = self._createSession()
            while self._active:
                try:
                    request = self._queue.get(timeout=1)
                    try:
                        self._processRequest(request, session)
                    finally:
                        self._queue.task_done()
                except Empty:
                    pass
        except:
            et, ev, tb = sys.exc_info()
            self.onError(et, ev, tb, None)
    
    #----------------------------------------------------------------------
    def sign(self, request):  # type: (Request)->Request
        """
        所有请求在发送之前都会经过这个函数
        签名之类的前奏可以在这里面实现
        需要对request进行什么修改就做什么修改吧
        @:return (request)
        """
        return request
    
    #----------------------------------------------------------------------
    def onFailed(self, *args):  # type:(int, Request)->None
        """
        请求失败处理函数（HttpStatusCode!=2xx）.
        默认行为是打印到stderr
        """
        status_code = args[0]
        request = args[1]
        sys.stderr.write(str(request))
        if len(args)==3:
            fail_msg = args[-1]
            sys.stderr.write(fail_msg)
    
    #----------------------------------------------------------------------
    def onError(self,
                exceptionType,  # type: type
                exceptionValue, # type: Exception
                tb,
                request         # type: Optional[Request]
                ):
        """
        Python内部错误处理：默认行为是仍给excepthook
        :param request 如果是在处理请求的时候出错，它的值就是对应的Request，否则为None
        """
        sys.stderr.write(self.exceptionDetail(exceptionType, exceptionValue, tb, request))
        sys.excepthook(exceptionType, exceptionValue, tb)
    
    #----------------------------------------------------------------------
    def exceptionDetail(self,
                        exceptionType,  # type: type
                        exceptionValue, # type: Exception
                        tb,
                        request         # type: Optional[Request]
                        ):
        text = "[{}]: Unhandled RestClient Error:{}\n".format(
            datetime.now().isoformat(),
            exceptionType
        )
        text += "request:{}\n".format(request)
        text += "Exception trace: \n"
        text += "".join(traceback.format_exception(
            exceptionType,
            exceptionValue,
            tb,
        ))
        return text
    
    #----------------------------------------------------------------------
    def _processRequest(self, request, session):  # type: (Request, requests.Session)->None
        """
        用于内部：将请求发送出去
        """
        # noinspection PyBroadException
        try:
            request = self.sign(request)
    
            url = self.makeFullUrl(request.path)
    
            response = session.request(request.method,
                                       url,
                                       headers=request.headers,
                                       params=request.params,
                                       data=request.data)
            request.response = response
    
            httpStatusCode = response.status_code
            if httpStatusCode / 100 == 2:                               # 2xx都算成功，尽管交易所都用200
                jsonBody = response.json()
                request.callback(jsonBody, request)
                request.status = RequestStatus.success
            else:
                fail_msg = response.json()
                request.status = RequestStatus.failed
                
                if request.onFailed:
                    request.onFailed(httpStatusCode, request,fail_msg)
                else:
                    self.onFailed(httpStatusCode, request,fail_msg)
        except:
            request.status = RequestStatus.error
            t, v, tb = sys.exc_info()
            if request.onError:
                request.onError(t, v, tb, request)
            else:
                self.onError(t, v, tb, request)

    #----------------------------------------------------------------------
    def makeFullUrl(self, path):
        """
        将相对路径补充成绝对路径：
        eg: makeFullUrl('/get') == 'http://xxxxx/get'
        :param path:
        :return:
        """
        url = self.urlBase + path
        return url


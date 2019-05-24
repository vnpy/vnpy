# encoding: UTF-8

import sys
import traceback
from datetime import datetime
from enum import Enum
from multiprocessing.dummy import Pool
from queue import Empty, Queue
from typing import Any, Callable, Optional

import requests


class RequestStatus(Enum):
    ready = 0  # Request created
    success = 1  # Request successful (status code 2xx)
    failed = 2  # Request failed (status code not 2xx)
    error = 3  # Exception raised


class Request(object):
    """
    Request object for status check.
    """

    def __init__(
        self,
        method: str,
        path: str,
        params: dict,
        data: dict,
        headers: dict,
        callback: Callable = None,
        on_failed: Callable = None,
        on_error: Callable = None,
        extra: Any = None,
    ):
        """"""
        self.method = method
        self.path = path
        self.callback = callback
        self.params = params
        self.data = data
        self.headers = headers

        self.on_failed = on_failed
        self.on_error = on_error
        self.extra = extra

        self.response = None
        self.status = RequestStatus.ready

    def __str__(self):
        if self.response is None:
            status_code = "terminated"
        else:
            status_code = self.response.status_code

        return (
            "request : {} {} {} because {}: \n"
            "headers: {}\n"
            "params: {}\n"
            "data: {}\n"
            "response:"
            "{}\n".format(
                self.method,
                self.path,
                self.status.name,
                status_code,
                self.headers,
                self.params,
                self.data,
                "" if self.response is None else self.response.text,
            )
        )


class RestClient(object):
    """
    HTTP Client designed for all sorts of trading RESTFul API.

    * Reimplement sign function to add signature function.
    * Reimplement on_failed function to handle Non-2xx responses.
    * Use on_failed parameter in add_request function for individual Non-2xx response handling.
    * Reimplement on_error function to handle exception msg.
    """

    def __init__(self):
        """
        """
        self.url_base = ''  # type: str
        self._active = False

        self._queue = Queue()
        self._pool = None  # type: Pool

        self.proxies = None

    def init(self, url_base: str, proxy_host: str = "", proxy_port: int = 0):
        """
        Init rest client with url_base which is the API root address.
        e.g. 'https://www.bitmex.com/api/v1/'
        """
        self.url_base = url_base

        if proxy_host and proxy_port:
            proxy = f"{proxy_host}:{proxy_port}"
            self.proxies = {"http": proxy, "https": proxy}

    def _create_session(self):
        """"""
        return requests.session()

    def start(self, n: int = 3):
        """
        Start rest client with session count n.
        """
        if self._active:
            return

        self._active = True
        self._pool = Pool(n)
        self._pool.apply_async(self._run)

    def stop(self):
        """
        Stop rest client immediately.
        """
        self._active = False

    def join(self):
        """
        Wait till all requests are processed.
        """
        self._queue.join()

    def add_request(
        self,
        method: str,
        path: str,
        callback: Callable,
        params: dict = None,
        data: dict = None,
        headers: dict = None,
        on_failed: Callable = None,
        on_error: Callable = None,
        extra: Any = None,
    ):
        """
        Add a new request.
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param callback: callback function if 2xx status, type: (dict, Request)
        :param params: dict for query string
        :param data: dict for body
        :param headers: dict for headers
        :param on_failed: callback function if Non-2xx status, type, type: (code, dict, Request)
        :param on_error: callback function when catching Python exception, type: (etype, evalue, tb, Request)
        :param extra: Any extra data which can be used when handling callback
        :return: Request
        """
        request = Request(
            method,
            path,
            params,
            data,
            headers,
            callback,
            on_failed,
            on_error,
            extra,
        )
        self._queue.put(request)
        return request

    def _run(self):
        try:
            session = self._create_session()
            while self._active:
                try:
                    request = self._queue.get(timeout=1)
                    try:
                        self._process_request(request, session)
                    finally:
                        self._queue.task_done()
                except Empty:
                    pass
        except:  # noqa
            et, ev, tb = sys.exc_info()
            self.on_error(et, ev, tb, None)

    def sign(self, request: Request):
        """
        This function is called before sending any request out.
        Please implement signature method here.
        @:return (request)
        """
        return request

    def on_failed(self, status_code: int, request: Request):
        """
        Default on_failed handler for Non-2xx response.
        """
        sys.stderr.write(str(request))

    def on_error(
        self,
        exception_type: type,
        exception_value: Exception,
        tb,
        request: Optional[Request],
    ):
        """
        Default on_error handler for Python exception.
        """
        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )
        sys.excepthook(exception_type, exception_value, tb)

    def exception_detail(
        self,
        exception_type: type,
        exception_value: Exception,
        tb,
        request: Optional[Request],
    ):
        text = "[{}]: Unhandled RestClient Error:{}\n".format(
            datetime.now().isoformat(), exception_type
        )
        text += "request:{}\n".format(request)
        text += "Exception trace: \n"
        text += "".join(
            traceback.format_exception(exception_type, exception_value, tb)
        )
        return text

    def _process_request(
        self, request: Request, session: requests.Session
    ):
        """
        Sending request to server and get result.
        """
        # noinspection PyBroadException
        try:
            request = self.sign(request)

            url = self.make_full_url(request.path)

            response = session.request(
                request.method,
                url,
                headers=request.headers,
                params=request.params,
                data=request.data,
                proxies=self.proxies,
            )
            request.response = response

            status_code = response.status_code
            if status_code // 100 == 2:  # 2xx都算成功，尽管交易所都用200
                jsonBody = response.json()
                request.callback(jsonBody, request)
                request.status = RequestStatus.success
            else:
                request.status = RequestStatus.failed

                if request.on_failed:
                    request.on_failed(status_code, request)
                else:
                    self.on_failed(status_code, request)
        except:  # noqa
            request.status = RequestStatus.error
            t, v, tb = sys.exc_info()
            if request.on_error:
                request.on_error(t, v, tb, request)
            else:
                self.on_error(t, v, tb, request)

    def make_full_url(self, path: str):
        """
        Make relative api path into full url.
        eg: make_full_url('/get') == 'http://xxxxx/get'
        """
        url = self.url_base + path
        return url

    def request(
        self,
        method: str,
        path: str,
        params: dict = None,
        data: dict = None,
        headers: dict = None,
    ):
        """
        Add a new request.
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: 
        :param params: dict for query string
        :param data: dict for body
        :param headers: dict for headers
        :return: requests.Response
        """
        request = Request(
            method,
            path,
            params,
            data,
            headers
        )
        request = self.sign(request)

        url = self.make_full_url(request.path)

        response = requests.request(
            request.method,
            url,
            headers=request.headers,
            params=request.params,
            data=request.data,
            proxies=self.proxies,
        )
        return response

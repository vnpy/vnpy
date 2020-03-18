import json
import logging
import multiprocessing
import os
import sys
import traceback
import uuid
from datetime import datetime
from enum import Enum
from multiprocessing.dummy import Pool
from threading import Lock, Thread
from types import TracebackType
from typing import Any, Callable, List, Optional, Type, Union
from vnpy.trader.utility import get_file_logger

import requests


class RequestStatus(Enum):
    ready = 0  # Request created
    success = 1  # Request successful (status code 2xx)
    failed = 2  # Request failed (status code not 2xx)
    error = 3  # Exception raised


pool: multiprocessing.pool.Pool = Pool(os.cpu_count() * 20)

CALLBACK_TYPE = Callable[[dict, "Request"], Any]
ON_FAILED_TYPE = Callable[[int, "Request"], Any]
ON_ERROR_TYPE = Callable[[Type, Exception, TracebackType, "Request"], Any]
CONNECTED_TYPE = Callable[["Request"], Any]


class Request(object):
    """
    Request object for status check.
    """

    def __init__(
        self,
        method: str,
        path: str,
        params: dict,
        data: Union[dict, str, bytes],
        headers: dict,
        callback: CALLBACK_TYPE = None,
        on_failed: ON_FAILED_TYPE = None,
        on_error: ON_ERROR_TYPE = None,
        stream: bool = False,
        on_connected: CONNECTED_TYPE = None,  # for streaming request
        extra: Any = None,
        client: "RestClient" = None,
    ):
        """"""
        self.method = method
        self.path = path
        self.callback = callback
        self.params = params
        self.data = data
        self.headers = headers

        self.stream = stream
        self.on_connected = on_connected
        self.processing_line: Optional[str] = ''

        self.on_failed = on_failed
        self.on_error = on_error
        self.extra = extra

        self.response: Optional[requests.Response] = None
        self.status = RequestStatus.ready
        self.client: "RestClient" = client

    def __str__(self):
        if self.response is None:
            status_code = "terminated"
        else:
            status_code = self.response.status_code

        if self.stream:
            response = self.processing_line
        else:
            if self.response is None:
                response = None
            else:
                response = self.response.text

        return (
            "request: {method} {path} {http_code}: \n"
            "full_url: {full_url}\n"
            "status: {status}\n"
            "headers: {headers}\n"
            "params: {params}\n"
            "data: {data}\n"
            "response: {response}\n".format(
                full_url=self.client.make_full_url(self.path),
                status=self.status.name,
                method=self.method,
                path=self.path,
                http_code=status_code,
                headers=self.headers,
                params=self.params,
                data=self.data,
                response=response,
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

    class Session:

        def __init__(self, client: "RestClient", session: requests.Session):
            self.client = client
            self.session = session

        def __enter__(self):
            return self.session

        def __exit__(self, exc_type, exc_val, exc_tb):
            with self.client._sessions_lock:
                self.client._sessions.append(self.session)

    def __init__(self):
        """
        """
        self.url_base = ''  # type: str
        self._active = False
        self.logger: Optional[logging.Logger] = None

        self.proxies = None

        self._tasks_lock = Lock()
        self._tasks: List[multiprocessing.pool.AsyncResult] = []
        self._sessions_lock = Lock()
        self._sessions: List[requests.Session] = []

        self._streams_lock = Lock()
        self._streams: List[Thread] = []

    @property
    def alive(self):
        return self._active

    def init(self,
             url_base: str,
             proxy_host: str = "",
             proxy_port: int = 0,
             log_path: Optional[str] = None,
             ):
        """
        Init rest client with url_base which is the API root address.
        e.g. 'https://www.bitmex.com/api/v1/'
        :param url_base:
        :param proxy_host:
        :param proxy_port:
        :param log_path: optional. file to save log.
        """
        self.url_base = url_base

        if log_path is not None:
            self.logger = get_file_logger(log_path)
            self.logger.setLevel(logging.DEBUG)

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

    def stop(self):
        """
        Stop rest client immediately.
        """
        self._active = False

    def join(self):
        """
        Wait till all requests are processed.
        """
        for task in self._tasks:
            task.wait()

    def add_streaming_request(
        self,
        method: str,
        path: str,
        callback: CALLBACK_TYPE,
        params: dict = None,
        data: Union[dict, str, bytes] = None,
        headers: dict = None,
        on_connected: CONNECTED_TYPE = None,
        on_failed: ON_FAILED_TYPE = None,
        on_error: ON_ERROR_TYPE = None,
        extra: Any = None,
    ):
        """
        See add_request for usage.
        """
        request = Request(
            method=method,
            path=path,
            params=params,
            data=data,
            headers=headers,
            callback=callback,
            on_failed=on_failed,
            on_error=on_error,
            extra=extra,
            client=self,
            stream=True,
            on_connected=on_connected,
        )
        # stream task should not push to thread pool
        # because it is usually no return.
        th = Thread(
            target=self._process_stream_request,
            args=[request, ],
        )
        th.start()
        return request

    def add_request(
        self,
        method: str,
        path: str,
        callback: CALLBACK_TYPE,
        params: dict = None,
        data: Union[dict, str, bytes] = None,
        headers: dict = None,
        on_failed: ON_FAILED_TYPE = None,
        on_error: ON_ERROR_TYPE = None,
        extra: Any = None,
    ):
        """
        Add a new request.
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path:
        :param callback: callback function if 2xx status, type: (dict, Request)
        :param params: dict for query string
        :param data: Http body. If it is a dict, it will be converted to form-data. Otherwise, it will be converted to bytes.
        :param headers: dict for headers
        :param on_failed: callback function if Non-2xx status, type, type: (code, Request)
        :param on_error: callback function when catching Python exception, type: (etype, evalue, tb, Request)
        :param extra: Any extra data which can be used when handling callback
        :return: Request
        """
        request = Request(
            method=method,
            path=path,
            params=params,
            data=data,
            headers=headers,
            callback=callback,
            on_failed=on_failed,
            on_error=on_error,
            extra=extra,
            client=self,
        )
        task = pool.apply_async(
            self._process_request,
            args=[request, ],
            callback=self._clean_finished_tasks,
            # error_callback=lambda e: self.on_error(type(e), e, e.__traceback__, request),
        )
        self._push_task(task)
        return request

    def _push_task(self, task):
        with self._tasks_lock:
            self._tasks.append(task)

    def _clean_finished_tasks(self, result: None):
        with self._tasks_lock:
            not_finished_tasks = [i for i in self._tasks if not i.ready()]
            self._tasks = not_finished_tasks

    def _clean_finished_streams(self):
        with self._streams_lock:
            not_finished_streams = [i for i in self._streams if i.is_alive()]
            self._streams = not_finished_streams

    def _get_session(self):
        with self._sessions_lock:
            if self._sessions:
                return self.Session(self, self._sessions.pop())
            else:
                return self.Session(self, self._create_session())

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

    def is_request_success(self, data: dict, request: "Request"):
        """
        check if a request succeed
        default behavior is returning True
        :return True if succeed.
        """
        return True

    def _process_stream_request(self, request: Request):
        """
        Sending request to server and get result.
        """
        self._process_request(request)
        self._clean_finished_streams()

    def _log(self, msg, *args):
        logger = self.logger
        if logger:
            logger.debug(msg, *args)

    def _process_request(
        self, request: Request
    ):
        """
        Sending request to server and get result.
        """
        try:
            with self._get_session() as session:
                request = self.sign(request)
                url = self.make_full_url(request.path)

                # send request
                uid = uuid.uuid4()
                stream = request.stream
                method = request.method
                headers = request.headers
                params = request.params
                data = request.data
                self._log("[%s] sending request %s %s, headers:%s, params:%s, data:%s",
                          uid, method, url,
                          headers, params, data)
                response = session.request(
                    method,
                    url,
                    headers=headers,
                    params=params,
                    data=data,
                    proxies=self.proxies,
                    stream=stream,
                )
                request.response = response
                status_code = response.status_code

                self._log("[%s] received response from %s:%s", uid, method, url)

                # check result & call corresponding callbacks
                if not stream:  # normal API:
                    # just call callback with all contents received.
                    if status_code // 100 == 2:  # 2xx codes are all successful
                        if status_code == 204:
                            json_body = None
                        else:
                            json_body = response.json()
                        self._process_json_body(json_body, request)
                    else:
                        if request.on_failed:
                            request.status = RequestStatus.failed
                            request.on_failed(status_code, request)
                        else:
                            self.on_failed(status_code, request)
                else:  # streaming API:
                    if request.on_connected:
                        request.on_connected(request)
                    # split response by lines, and call one callback for each line.
                    for line in response.iter_lines(chunk_size=None):
                        if line:
                            request.processing_line = line
                            json_body = json.loads(line)
                            self._process_json_body(json_body, request)
                    request.status = RequestStatus.success
        except Exception:
            request.status = RequestStatus.error
            t, v, tb = sys.exc_info()
            if request.on_error:
                request.on_error(t, v, tb, request)
            else:
                self.on_error(t, v, tb, request)

    def _process_json_body(self, json_body: Optional[dict], request: "Request"):
        status_code = request.response.status_code
        if self.is_request_success(json_body, request):
            request.status = RequestStatus.success
            request.callback(json_body, request)
        else:
            request.status = RequestStatus.failed
            if request.on_failed:
                request.on_failed(status_code, request)
            else:
                self.on_failed(status_code, request)

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
            headers,
            client=self,
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

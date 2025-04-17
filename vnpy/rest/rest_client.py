import sys
import traceback
from datetime import datetime
from enum import Enum
from multiprocessing.dummy import Pool
from queue import Empty, Queue
from typing import Callable, Optional, Union, Type
from types import TracebackType

import requests


CALLBACK_TYPE = Callable[[dict, "Request"], object]
ON_FAILED_TYPE = Callable[[int, "Request"], object]
ON_ERROR_TYPE = Callable[[Type, Exception, TracebackType, "Request"], object]


class RequestStatus(Enum):
    """
    Request status enum.
    """

    ready = 0       # Request created
    success = 1     # Request successful (status code 2xx)
    failed = 2      # Request failed (status code not 2xx)
    error = 3       # Exception raised


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
        extra: object = None,
    ) -> None:
        """"""
        self.method: str = method
        self.path: str = path
        self.callback: CALLBACK_TYPE = callback
        self.params: dict = params
        self.data: Union[dict, str, bytes] = data
        self.headers: dict = headers

        self.on_failed: ON_FAILED_TYPE = on_failed
        self.on_error: ON_ERROR_TYPE = on_error
        self.extra: object = extra

        self.response: requests.Response = None
        self.status: RequestStatus = RequestStatus.ready

    def __str__(self) -> str:
        """"""
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

    def __init__(self) -> None:
        """"""
        self.url_base: str = ""
        self.active: bool = False

        self.queue: Queue = Queue()
        self.pool: Pool = None

        self.proxies: dict = None

    def init(
        self,
        url_base: str,
        proxy_host: str = "",
        proxy_port: int = 0
    ) -> None:
        """
        Init rest client with url_base which is the API root address.
        """
        self.url_base = url_base

        if proxy_host and proxy_port:
            proxy: str = f"http://{proxy_host}:{proxy_port}"
            self.proxies = {"http": proxy, "https": proxy}

    def start(self, session_count: int = 5) -> None:
        """
        Start rest client with session_count number of threads.
        """
        if self.active:
            return

        self.active = True
        self.pool = Pool(session_count)
        self.pool.apply_async(self.run)

    def stop(self) -> None:
        """
        Stop rest client immediately.
        """
        self.active = False

    def join(self) -> None:
        """
        Wait till all requests are processed.
        """
        self.queue.join()

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
        extra: object = None,
    ) -> Request:
        """
        Add a new request.
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: url path for query
        :param callback: callback function if 2xx status, type: (dict, Request)
        :param params: dict for query string
        :param data: Http body. If it is a dict, it will be converted to form-data. Otherwise, it will be converted to bytes.
        :param headers: dict for headers
        :param on_failed: callback function if Non-2xx status, type, type: (code, dict, Request)
        :param on_error: callback function when catching Python exception, type: (etype, evalue, tb, Request)
        :param extra: object extra data which can be used when handling callback
        :return: Request
        """
        request: Request = Request(
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
        self.queue.put(request)
        return request

    def run(self) -> None:
        """"""
        try:
            session: requests.Session = requests.session()
            while self.active:
                try:
                    request: Request = self.queue.get(timeout=1)
                    try:
                        self.process_request(request, session)
                    finally:
                        self.queue.task_done()
                except Empty:
                    pass
        except Exception:
            et, ev, tb = sys.exc_info()
            self.on_error(et, ev, tb, None)

    def sign(self, request: Request) -> RequestStatus:
        """
        This function is called before sending object request out.
        Please implement signature method here.
        """
        return request

    def on_failed(self, status_code: int, request: Request) -> None:
        """
        Default on_failed handler for Non-2xx response.
        """
        print("RestClient on failed" + "-" * 10)
        print(str(request))

    def on_error(
        self,
        exception_type: type,
        exception_value: Exception,
        tb: TracebackType,
        request: Optional[Request],
    ) -> None:
        """
        Default on_error handler for Python exception.
        """
        try:
            print("RestClient on error" + "-" * 10)
            print(self.exception_detail(exception_type, exception_value, tb, request))
        except Exception:
            traceback.print_exc()

    def exception_detail(
        self,
        exception_type: type,
        exception_value: Exception,
        tb: TracebackType,
        request: Optional[Request],
    ) -> str:
        text: str = "[{}]: Unhandled RestClient Error:{}\n".format(
            datetime.now().isoformat(), exception_type
        )
        text += "request:{}\n".format(request)
        text += "Exception trace: \n"
        text += "".join(
            traceback.format_exception(exception_type, exception_value, tb)
        )
        return text

    def process_request(self, request: Request, session: requests.Session) -> None:
        """
        Sending request to server and get result.
        """
        try:
            request = self.sign(request)

            url: str = self.make_full_url(request.path)

            response: requests.Response = session.request(
                request.method,
                url,
                headers=request.headers,
                params=request.params,
                data=request.data,
                proxies=self.proxies,
            )
            request.response = response

            status_code: int = response.status_code
            if status_code // 100 == 2:  # 2xx codes are all successful
                json_body: dict = None
                if status_code != 204:
                    json_body = response.json()

                request.callback(json_body, request)
                request.status = RequestStatus.success
            else:
                request.status = RequestStatus.failed

                if request.on_failed:
                    request.on_failed(status_code, request)
                else:
                    self.on_failed(status_code, request)
        except Exception:
            request.status = RequestStatus.error
            t, v, tb = sys.exc_info()
            if request.on_error:
                request.on_error(t, v, tb, request)
            else:
                self.on_error(t, v, tb, request)

    def make_full_url(self, path: str) -> str:
        """
        Make relative api path into full url.
        eg: make_full_url("/get") == "http://xxxxx/get"
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
    ) -> requests.Response:
        """
        Add a new request.
        :param method: GET, POST, PUT, DELETE, QUERY
        :param path: url path for query
        :param params: dict for query string
        :param data: dict for body
        :param headers: dict for headers
        :return: requests.Response
        """
        request: Request = Request(
            method,
            path,
            params,
            data,
            headers
        )
        request = self.sign(request)

        url: str = self.make_full_url(request.path)

        response: requests.Response = requests.request(
            request.method,
            url,
            headers=request.headers,
            params=request.params,
            data=request.data,
            proxies=self.proxies,
        )
        return response

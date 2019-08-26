import sys
import sys
import traceback
from datetime import datetime
from enum import Enum
from typing import Any, Callable, Optional, Union

import aiohttp
import requests

from vnpy.api.asyncio.async_executor import loop, wrap_as_sync, create_async_task


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
        data: Union[dict, str, bytes],
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

        self.response: Optional[aiohttp.ClientResponse] = None
        self.status = RequestStatus.ready

    def __str__(self):
        if self.response is None:
            status_code = "terminated"
        else:
            status_code = self.response.status

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

        self.requests_proxies = None
        self.aiohttp_proxy = None

        self._session: Optional[aiohttp.ClientSession] = None

    def init(self, url_base: str, proxy_host: str = "", proxy_port: int = 0):
        """
        Init rest client with url_base which is the API root address.
        e.g. 'https://www.bitmex.com/api/v1/'
        """
        self.url_base = url_base

        if proxy_host and proxy_port:
            proxy = f"{proxy_host}:{proxy_port}"
            self.requests_proxies = {"http": proxy, "https": proxy}
            self.aiohttp_proxy = f'http://{proxy}'

        self._session = aiohttp.ClientSession(loop=loop)

    def start(self, _):
        pass

    def stop(self):
        """
        Since low level implementation is aiohttp, stop() will wait until connection is closed().
        :note: this funciton blocks now!
        """
        wrap_as_sync(self._session.close())()

    def join(self):
        """
        Since low level implementation is aiohttp, join() is useless.
        """
        pass

    def add_request(
        self,
        method: str,
        path: str,
        callback: Callable,
        params: dict = None,
        data: Union[dict, str, bytes] = None,
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
        :param data: Http body. If it is a dict, it will be converted to form-data. Otherwise, it will be converted to bytes.
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
        create_async_task(self._process_request(request))
        return request

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

    async def _process_request(
        self, request: Request,
    ):
        """
        Sending request to server and get result.
        """
        try:
            request = self.sign(request)

            url = self.make_full_url(request.path)

            response: aiohttp.ClientResponse = await self._session.request(
                method=request.method,
                url=url,
                headers=request.headers,
                params=request.params,
                data=request.data,
                proxy=self.aiohttp_proxy,
            )
            response.json = wrap_as_sync(response.json())
            request.response = response
            status_code = response.status
            if status_code // 100 == 2:  # 2xx codes are all successful
                if status_code == 204:
                    json_body = None
                else:
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
            proxies=self.requests_proxies,
        )
        return response

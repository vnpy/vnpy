import json
import sys
from dataclasses import dataclass
from datetime import datetime
from threading import Lock
from typing import Dict, List, Optional, TYPE_CHECKING, Tuple

from requests import ConnectionError

from vnpy.api.rest import Request
from vnpy.trader.constant import Direction, Exchange, Interval, Offset, Product, Status
from vnpy.trader.object import AccountData, BarData, CancelRequest, ContractData, OrderRequest, \
    PositionData, OrderData
from .oanda_common import (INTERVAL_VT2OANDA, ORDER_TYPE_VT2OANDA,
                           STATUS_OANDA2VT, parse_time, INTERVAL_VT2OANDA_DELTA, parse_datetime)

if TYPE_CHECKING:
    from vnpy.gateway.oanda import OandaGateway
from vnpy.api.rest import RestClient

_ = lambda x: x  # noqa


class OandaApiBase(RestClient):
    """
    Oanda Base API
    """
    def __init__(self, gateway: "OandaGateway"):
        super().__init__()
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = b""

    def sign(self, request):
        """
        Generate BitMEX signature.
        """
        if request.data:
            request.data = json.dumps(request.data)
        request.headers = {
            "Authorization": f"Bearer {self.key}",
            "Content-Type": "application/json",
        }
        return request

    def is_request_success(self, data: dict, request: "Request"):
        # message should be check too
        # but checking only this is enough for us.
        return super().is_request_success(data, request) and 'errorMessage' not in data

    def on_error(
        self, exception_type: type, exception_value: Exception, tb, request: Request
    ):
        """
        Callback to handler request exception.
        """
        msg = f"触发异常，状态码：{exception_type}，信息：{exception_value}"
        self.gateway.write_log(msg)

        sys.stderr.write(
            self.exception_detail(exception_type, exception_value, tb, request)
        )


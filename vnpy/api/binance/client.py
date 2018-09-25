#!/usr/bin/env python
# coding=utf-8

import hashlib
import hmac
import requests
import six
import time
import sys
from .exceptions import BinanceAPIException, BinanceRequestException, BinanceWithdrawException

if six.PY2:
    from urllib import urlencode
elif six.PY3:
    from urllib.parse import urlencode


class Client(object):

    API_URL = 'https://api.binance.com/api'
    WITHDRAW_API_URL = 'https://api.binance.com/wapi'
    WEBSITE_URL = 'https://www.binance.com'
    PUBLIC_API_VERSION = 'v1'
    PRIVATE_API_VERSION = 'v3'
    WITHDRAW_API_VERSION = 'v3'

    SYMBOL_TYPE_SPOT = 'SPOT'

    ORDER_STATUS_NEW = 'NEW'
    ORDER_STATUS_PARTIALLY_FILLED = 'PARTIALLY_FILLED'
    ORDER_STATUS_FILLED = 'FILLED'
    ORDER_STATUS_CANCELED = 'CANCELED'
    ORDER_STATUS_PENDING_CANCEL = 'PENDING_CANCEL'
    ORDER_STATUS_REJECTED = 'REJECTED'
    ORDER_STATUS_EXPIRED = 'EXPIRED'

    KLINE_INTERVAL_1MINUTE = '1m'
    KLINE_INTERVAL_3MINUTE = '3m'
    KLINE_INTERVAL_5MINUTE = '5m'
    KLINE_INTERVAL_15MINUTE = '15m'
    KLINE_INTERVAL_30MINUTE = '30m'
    KLINE_INTERVAL_1HOUR = '1h'
    KLINE_INTERVAL_2HOUR = '2h'
    KLINE_INTERVAL_4HOUR = '4h'
    KLINE_INTERVAL_6HOUR = '6h'
    KLINE_INTERVAL_8HOUR = '8h'
    KLINE_INTERVAL_12HOUR = '12h'
    KLINE_INTERVAL_1DAY = '1d'
    KLINE_INTERVAL_3DAY = '3d'
    KLINE_INTERVAL_1WEEK = '1w'
    KLINE_INTERVAL_1MONTH = '1M'

    SIDE_BUY = 'BUY'
    SIDE_SELL = 'SELL'

    ORDER_TYPE_LIMIT = 'LIMIT'
    ORDER_TYPE_MARKET = 'MARKET'
    ORDER_TYPE_STOP_LOSS = 'STOP_LOSS'
    ORDER_TYPE_STOP_LOSS_LIMIT = 'STOP_LOSS_LIMIT'
    ORDER_TYPE_TAKE_PROFIT = 'TAKE_PROFIT'
    ORDER_TYPE_TAKE_PROFIT_LIMIT = 'TAKE_PROFIT_LIMIT'
    ORDER_TYPE_LIMIT_MAKER = 'LIMIT_MAKER'

    TIME_IN_FORCE_GTC = 'GTC'  # Good till cancelled
    TIME_IN_FORCE_IOC = 'IOC'  # Immediate or cancel
    TIME_IN_FORCE_FOK = 'FOK'  # Fill or kill

    ORDER_RESP_TYPE_ACK = 'ACK'
    ORDER_RESP_TYPE_RESULT = 'RESULT'
    ORDER_RESP_TYPE_FULL = 'FULL'

    def __init__(self, api_key, api_secret, api=None):
        """Binance API Client constructor

        :param api_key: Api Key
        :type api_key: str.
        :param api_secret: Api Secret
        :type api_secret: str.

        """

        self.API_KEY = api_key
        self.API_SECRET = api_secret
        self.api = api
        self.DEBUG = False
        self.session = self._init_session()

        # init DNS and SSL cert
        self.ping()


    def writeLog(self, content):
        content = 'client ' + content
        if not self.api:
            print(content)
            return
        if not hasattr(self.api, 'writeLog'):
            print(content)
            return

        self.api.writeLog(content)

    def writeError(self, content, error_id=0):
        content = 'client ' + content
        if not self.api:
            print(u'{},error_id:{}'.format(content, error_id) ,file=sys.stderr)
            return

        if not hasattr(self.api, 'writeError'):
            print(u'{},error_id:{}'.format(content, error_id), file=sys.stderr)
            return

        self.api.writeError(content, error_id)

    def _init_session(self):
        session = requests.session()
        session.headers.update({'Accept': 'application/json',
                                'User-Agent': 'binance/python',
                                'X-MBX-APIKEY': self.API_KEY})
        return session

    def _create_api_uri(self, path, signed=True, version=PUBLIC_API_VERSION):
        v = self.PRIVATE_API_VERSION if signed else version
        return self.API_URL + '/' + v + '/' + path

    def _create_withdraw_api_uri(self, path):
        return self.WITHDRAW_API_URL + '/' + self.WITHDRAW_API_VERSION + '/' + path

    def _create_website_uri(self, path):
        return self.WEBSITE_URL + '/' + path

    def _generate_signature(self, data):
        query_string = urlencode(data)
        m = hmac.new(self.API_SECRET.encode('utf-8'), query_string.encode('utf-8'), hashlib.sha256)

        return m.hexdigest()

    def _order_params(self, data):
        """Convert params to list with signature as last element

        :param data:
        :return:

        """
        has_signature = False
        params = []
        for key, value in data.items():
            if key == 'signature':
                has_signature = True
            else:
                params.append((key, value))
        if has_signature:
            params.append(('signature', data['signature']))
        return params

    def _request(self, method, uri, signed, force_params=False, **kwargs):
        data = kwargs.get('data', None)
        if data is None:
            kwargs['data'] = data

        if data and isinstance(data, dict):
            kwargs['data'] = data
        if signed:
            # generate signature
            kwargs['data']['recvWindow'] = 5000
            kwargs['data']['timestamp'] = int(time.time() * 1000)
            kwargs['data']['signature'] = self._generate_signature(kwargs['data'])

        if data and (method == 'get' or force_params):
            kwargs['params'] = self._order_params(kwargs['data'])
            del(kwargs['data'])

        # kwargs["verify"] = False  # I don't know whay this is error
        if self.DEBUG:
            self.writeLog('_request:method:{} uri:{},{}'.format(method, uri, kwargs))

        response = getattr(self.session, method)(uri, **kwargs )

        if self.DEBUG:
            self.writeLog(str(response))

        return self._handle_response(response , uri , **kwargs )

    def _request_api(self, method, path, signed=False, version=PUBLIC_API_VERSION, **kwargs):
        uri = self._create_api_uri(path, signed, version)
        return self._request(method, uri, signed, **kwargs)

    def _request_withdraw_api(self, method, path, signed=False, **kwargs):
        uri = self._create_withdraw_api_uri(path)

        return self._request(method, uri, signed, True, **kwargs)

    def _request_website(self, method, path, signed=False, **kwargs):
        uri = self._create_website_uri(path)

        return self._request(method, uri, signed, **kwargs)

    def _handle_response(self, response , uri , **kwargs ):
        """Internal helper for handling API responses from the Binance server.
        Raises the appropriate exceptions when necessary; otherwise, returns the
        response.
        """
        if not str(response.status_code).startswith('2'):
            raise BinanceAPIException(response , uri , **kwargs  )
        try:
            return response.json()
        except ValueError:
            raise BinanceRequestException('Invalid Response: %s' % response.text , uri , **kwargs )

    def _get(self, path, signed=False, version=PUBLIC_API_VERSION, **kwargs):
        return self._request_api('get', path, signed, version, **kwargs)

    def _post(self, path, signed=False, version=PUBLIC_API_VERSION, **kwargs):
        return self._request_api('post', path, signed, version, **kwargs)

    def _put(self, path, signed=False, version=PUBLIC_API_VERSION, **kwargs):
        return self._request_api('put', path, signed, version, **kwargs)

    def _delete(self, path, signed=False, version=PUBLIC_API_VERSION, **kwargs):
        return self._request_api('delete', path, signed, version, **kwargs)

    # Exchange Endpoints

    def get_products(self):
        """Return list of products currently listed on Binance

        Use get_exchange_info() call instead

        :returns: list - List of product dictionaries

        :raises: BinanceResponseException, BinanceAPIException

        """

        products = self._request_website('get', 'exchange/public/product')
        return products

    def get_exchange_info(self):
        """Return rate limits and list of symbols

        :returns: list - List of product dictionaries

        .. code-block:: python

            {
                "timezone": "UTC",
                "serverTime": 1508631584636,
                "rateLimits": [
                    {
                        "rateLimitType": "REQUESTS",
                        "interval": "MINUTE",
                        "limit": 1200
                    },
                    {
                        "rateLimitType": "ORDERS",
                        "interval": "SECOND",
                        "limit": 10
                    },
                    {
                        "rateLimitType": "ORDERS",
                        "interval": "DAY",
                        "limit": 100000
                    }
                ],
                "exchangeFilters": [],
                "symbols": [
                    {
                        "symbol": "ETHBTC",
                        "status": "TRADING",
                        "baseAsset": "ETH",
                        "baseAssetPrecision": 8,
                        "quoteAsset": "BTC",
                        "quotePrecision": 8,
                        "orderTypes": ["LIMIT", "MARKET"],
                        "icebergAllowed": false,
                        "filters": [
                            {
                                "filterType": "PRICE_FILTER",
                                "minPrice": "0.00000100",
                                "maxPrice": "100000.00000000",
                                "tickSize": "0.00000100"
                            }, {
                                "filterType": "LOT_SIZE",
                                "minQty": "0.00100000",
                                "maxQty": "100000.00000000",
                                "stepSize": "0.00100000"
                            }, {
                                "filterType": "MIN_NOTIONAL",
                                "minNotional": "0.00100000"
                            }
                        ]
                    }
                ]
            }

        :raises: BinanceResponseException, BinanceAPIException

        """

        return self._get('exchangeInfo')

    # General Endpoints

    def ping(self):
        """Test connectivity to the Rest API.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#test-connectivity

        :returns: Empty array

        .. code-block:: python

            {}

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ping')

    def get_server_time(self):
        """Test connectivity to the Rest API and get the current server time.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#check-server-time

        :returns: Current server time

        .. code-block:: python

            {
                "serverTime": 1499827319559
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('time')

    # Market Data Endpoints

    def get_all_tickers(self):
        """Latest price for all symbols.

        https://www.binance.com/restapipub.html#symbols-price-ticker

        :returns: List of market tickers

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "price": "4.00000200"
                },
                {
                    "symbol": "ETHBTC",
                    "price": "0.07946600"
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ticker/allPrices')

    def get_orderbook_tickers(self):
        """Best price/qty on the order book for all symbols.

        https://www.binance.com/restapipub.html#symbols-order-book-ticker

        :returns: List of order book market entries

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "bidPrice": "4.00000000",
                    "bidQty": "431.00000000",
                    "askPrice": "4.00000200",
                    "askQty": "9.00000000"
                },
                {
                    "symbol": "ETHBTC",
                    "bidPrice": "0.07946700",
                    "bidQty": "9.00000000",
                    "askPrice": "100000.00000000",
                    "askQty": "1000.00000000"
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ticker/allBookTickers')

    def get_order_book(self, **params):
        """Get the Order Book for the market

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#order-book

        :param symbol: required
        :type symbol: str
        :param limit:  Default 100; max 100
        :type limit: int

        :returns: API response

        .. code-block:: python

            {
                "lastUpdateId": 1027024,
                "bids": [
                    [
                        "4.00000000",     # PRICE
                        "431.00000000",   # QTY
                        []                # Can be ignored
                    ]
                ],
                "asks": [
                    [
                        "4.00000200",
                        "12.00000000",
                        []
                    ]
                ]
            }

        :raises: BinanceResponseException, BinanceAPIException

        """

        return self._get('depth', data=params)

    def get_recent_trades(self, **params):
        """Get recent trades (up to last 500).

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#recent-trades-list

        :param symbol: required
        :type symbol: str
        :param limit:  Default 500; max 500.
        :type limit: int

        :returns: API response

        .. code-block:: python

            [
                {
                    "id": 28457,
                    "price": "4.00000100",
                    "qty": "12.00000000",
                    "time": 1499865549590,
                    "isBuyerMaker": true,
                    "isBestMatch": true
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('trades', data=params)

    def get_historical_trades(self, **params):
        """Get older trades.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#recent-trades-list

        :param symbol: required
        :type symbol: str
        :param limit:  Default 500; max 500.
        :type limit: int
        :param fromId:  TradeId to fetch from. Default gets most recent trades.
        :type fromId: str

        :returns: API response

        .. code-block:: python

            [
                {
                    "id": 28457,
                    "price": "4.00000100",
                    "qty": "12.00000000",
                    "time": 1499865549590,
                    "isBuyerMaker": true,
                    "isBestMatch": true
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('historicalTrades', data=params)

    def get_aggregate_trades(self, **params):
        """Get compressed, aggregate trades. Trades that fill at the time,
        from the same order, with the same price will have the quantity aggregated.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#compressedaggregate-trades-list

        :param symbol: required
        :type symbol: str
        :param fromId:  ID to get aggregate trades from INCLUSIVE.
        :type fromId: str
        :param startTime: Timestamp in ms to get aggregate trades from INCLUSIVE.
        :type startTime: int
        :param endTime: Timestamp in ms to get aggregate trades until INCLUSIVE.
        :type endTime: int
        :param limit:  Default 500; max 500.
        :type limit: int

        :returns: API response

        .. code-block:: python

            [
                {
                    "a": 26129,         # Aggregate tradeId
                    "p": "0.01633102",  # Price
                    "q": "4.70443515",  # Quantity
                    "f": 27781,         # First tradeId
                    "l": 27781,         # Last tradeId
                    "T": 1498793709153, # Timestamp
                    "m": true,          # Was the buyer the maker?
                    "M": true           # Was the trade the best price match?
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('aggTrades', data=params)

    def get_klines(self, **params):
        """Kline/candlestick bars for a symbol. Klines are uniquely identified by their open time.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#klinecandlestick-data

        :param symbol: required
        :type symbol: str
        :param interval: -
        :type interval: enum
        :param limit: - Default 500; max 500.
        :type limit: int
        :param startTime:
        :type startTime: int
        :param endTime:
        :type endTime: int

        :returns: API response

        .. code-block:: python

            [
                [
                    1499040000000,      # Open time
                    "0.01634790",       # Open
                    "0.80000000",       # High
                    "0.01575800",       # Low
                    "0.01577100",       # Close
                    "148976.11427815",  # Volume
                    1499644799999,      # Close time
                    "2434.19055334",    # Quote asset volume
                    308,                # Number of trades
                    "1756.87402397",    # Taker buy base asset volume
                    "28.46694368",      # Taker buy quote asset volume
                    "17928899.62484339" # Can be ignored
                ]
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('klines', data=params)

    def get_ticker(self, **params):
        """24 hour price change statistics.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#24hr-ticker-price-change-statistics

        :param symbol:
        :type symbol: str

        :returns: API response

        .. code-block:: python

            {
                "priceChange": "-94.99999800",
                "priceChangePercent": "-95.960",
                "weightedAvgPrice": "0.29628482",
                "prevClosePrice": "0.10002000",
                "lastPrice": "4.00000200",
                "bidPrice": "4.00000000",
                "askPrice": "4.00000200",
                "openPrice": "99.00000000",
                "highPrice": "100.00000000",
                "lowPrice": "0.10000000",
                "volume": "8913.30000000",
                "openTime": 1499783499040,
                "closeTime": 1499869899040,
                "fristId": 28385,   # First tradeId
                "lastId": 28460,    # Last tradeId
                "count": 76         # Trade count
            }

        OR

        .. code-block:: python

            [
                {
                    "priceChange": "-94.99999800",
                    "priceChangePercent": "-95.960",
                    "weightedAvgPrice": "0.29628482",
                    "prevClosePrice": "0.10002000",
                    "lastPrice": "4.00000200",
                    "bidPrice": "4.00000000",
                    "askPrice": "4.00000200",
                    "openPrice": "99.00000000",
                    "highPrice": "100.00000000",
                    "lowPrice": "0.10000000",
                    "volume": "8913.30000000",
                    "openTime": 1499783499040,
                    "closeTime": 1499869899040,
                    "fristId": 28385,   # First tradeId
                    "lastId": 28460,    # Last tradeId
                    "count": 76         # Trade count
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ticker/24hr', data=params)

    def get_symbol_ticker(self, **params):
        """Latest price for a symbol or symbols.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#24hr-ticker-price-change-statistics

        :param symbol:
        :type symbol: str

        :returns: API response

        .. code-block:: python

            {
                "symbol": "LTCBTC",
                "price": "4.00000200"
            }

        OR

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "price": "4.00000200"
                },
                {
                    "symbol": "ETHBTC",
                    "price": "0.07946600"
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ticker/price', data=params, version=self.PRIVATE_API_VERSION)

    def get_orderbook_ticker(self, **params):
        """Latest price for a symbol or symbols.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#symbol-order-book-ticker

        :param symbol:
        :type symbol: str

        :returns: API response

        .. code-block:: python

            {
                "symbol": "LTCBTC",
                "bidPrice": "4.00000000",
                "bidQty": "431.00000000",
                "askPrice": "4.00000200",
                "askQty": "9.00000000"
            }

        OR

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "bidPrice": "4.00000000",
                    "bidQty": "431.00000000",
                    "askPrice": "4.00000200",
                    "askQty": "9.00000000"
                },
                {
                    "symbol": "ETHBTC",
                    "bidPrice": "0.07946700",
                    "bidQty": "9.00000000",
                    "askPrice": "100000.00000000",
                    "askQty": "1000.00000000"
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('ticker/bookTicker', data=params, version=self.PRIVATE_API_VERSION)

    # Account Endpoints

    def create_order(self, **params):
        """Send in a new order

        Any order with an icebergQty MUST have timeInForce set to GTC.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#new-order--trade

        :param symbol: required
        :type symbol: str
        :param side: required
        :type side: enum
        :param type: required
        :type type: enum
        :param timeInForce: required if limit order
        :type timeInForce: enum
        :param quantity: required
        :type quantity: decimal
        :param price: required
        :type price: decimal
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param icebergQty: Used with LIMIT, STOP_LOSS_LIMIT, and TAKE_PROFIT_LIMIT to create an iceberg order.
        :type icebergQty: decimal
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        Response ACK:

        .. code-block:: python

            {
                "symbol":"LTCBTC",
                "orderId": 1,
                "clientOrderId": "myOrder1" # Will be newClientOrderId
                "transactTime": 1499827319559
            }

        Response RESULT:

        .. code-block:: python

            {
                "symbol": "BTCUSDT",
                "orderId": 28,
                "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
                "transactTime": 1507725176595,
                "price": "0.00000000",
                "origQty": "10.00000000",
                "executedQty": "10.00000000",
                "status": "FILLED",
                "timeInForce": "GTC",
                "type": "MARKET",
                "side": "SELL"
            }

        Response FULL:

        .. code-block:: python

            {
                "symbol": "BTCUSDT",
                "orderId": 28,
                "clientOrderId": "6gCrw2kRUAF9CvJDGP16IP",
                "transactTime": 1507725176595,
                "price": "0.00000000",
                "origQty": "10.00000000",
                "executedQty": "10.00000000",
                "status": "FILLED",
                "timeInForce": "GTC",
                "type": "MARKET",
                "side": "SELL",
                "fills": [
                    {
                        "price": "4000.00000000",
                        "qty": "1.00000000",
                        "commission": "4.00000000",
                        "commissionAsset": "USDT"
                    },
                    {
                        "price": "3999.00000000",
                        "qty": "5.00000000",
                        "commission": "19.99500000",
                        "commissionAsset": "USDT"
                    },
                    {
                        "price": "3998.00000000",
                        "qty": "2.00000000",
                        "commission": "7.99600000",
                        "commissionAsset": "USDT"
                    },
                    {
                        "price": "3997.00000000",
                        "qty": "1.00000000",
                        "commission": "3.99700000",
                        "commissionAsset": "USDT"
                    },
                    {
                        "price": "3995.00000000",
                        "qty": "1.00000000",
                        "commission": "3.99500000",
                        "commissionAsset": "USDT"
                    }
                ]
            }

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        return self._post('order', True, data=params)

    def order_limit(self, timeInForce=TIME_IN_FORCE_GTC, **params):
        """Send in a new limit order

        Any order with an icebergQty MUST have timeInForce set to GTC.

        :param symbol: required
        :type symbol: str
        :param side: required
        :type side: enum
        :param quantity: required
        :type quantity: decimal
        :param price: required
        :type price: decimal
        :param timeInForce: default Good till cancelled
        :type timeInForce: enum
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param icebergQty: Used with LIMIT, STOP_LOSS_LIMIT, and TAKE_PROFIT_LIMIT to create an iceberg order.
        :type icebergQty: decimal
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'type': self.ORDER_TYPE_LIMIT,
            'timeInForce': timeInForce
        })
        return self.create_order(**params)

    def order_limit_buy(self, timeInForce=TIME_IN_FORCE_GTC, **params):
        """Send in a new limit buy order

        Any order with an icebergQty MUST have timeInForce set to GTC.

        :param symbol: required
        :type symbol: str
        :param quantity: required
        :type quantity: decimal
        :param price: required
        :type price: decimal
        :param timeInForce: default Good till cancelled
        :type timeInForce: enum
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param stopPrice: Used with stop orders
        :type stopPrice: decimal
        :param icebergQty: Used with iceberg orders
        :type icebergQty: decimal
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'side': self.SIDE_BUY,
        })
        return self.order_limit(timeInForce=timeInForce, **params)

    def order_limit_sell(self, timeInForce=TIME_IN_FORCE_GTC, **params):
        """Send in a new limit sell order

        :param symbol: required
        :type symbol: str
        :param quantity: required
        :type quantity: decimal
        :param price: required
        :type price: decimal
        :param timeInForce: default Good till cancelled
        :type timeInForce: enum
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param stopPrice: Used with stop orders
        :type stopPrice: decimal
        :param icebergQty: Used with iceberg orders
        :type icebergQty: decimal

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'side': self.SIDE_SELL
        })
        return self.order_limit(timeInForce=timeInForce, **params)

    def order_market(self, **params):
        """Send in a new market order

        :param symbol: required
        :type symbol: str
        :param side: required
        :type side: enum
        :param quantity: required
        :type quantity: decimal
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'type': self.ORDER_TYPE_MARKET
        })
        return self.create_order(**params)

    def order_market_buy(self, **params):
        """Send in a new market buy order

        :param symbol: required
        :type symbol: str
        :param quantity: required
        :type quantity: decimal
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'side': self.SIDE_BUY
        })
        return self.order_market(**params)

    def order_market_sell(self, **params):
        """Send in a new market sell order

        :param symbol: required
        :type symbol: str
        :param quantity: required
        :type quantity: decimal
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum

        :returns: API response

        See order endpoint for full response options

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException

        """
        params.update({
            'side': self.SIDE_SELL
        })
        return self.order_market(**params)

    def create_test_order(self, **params):
        """Test new order creation and signature/recvWindow long. Creates and validates a new order but does not send it into the matching engine.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#test-new-order-trade

        :param symbol: required
        :type symbol: str
        :param side: required
        :type side: enum
        :param type: required
        :type type: enum
        :param timeInForce: required if limit order
        :type timeInForce: enum
        :param quantity: required
        :type quantity: decimal
        :param price: required
        :type price: decimal
        :param newClientOrderId: A unique id for the order. Automatically generated if not sent.
        :type newClientOrderId: str
        :param icebergQty: Used with iceberg orders
        :type icebergQty: decimal
        :param newOrderRespType: Set the response JSON. ACK, RESULT, or FULL; default: RESULT.
        :type newOrderRespType: enum
        :param recvWindow: The number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {}

        :raises: BinanceResponseException, BinanceAPIException, BinanceOrderException, BinanceOrderMinAmountException, BinanceOrderMinPriceException, BinanceOrderMinTotalException, BinanceOrderUnknownSymbolException, BinanceOrderInactiveSymbolException


        """
        return self._post('order/test', True, data=params)

    def get_order(self, **params):
        """Check an order's status. Either orderId or origClientOrderId must be sent.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#query-order-user_data

        :param symbol: required
        :type symbol: str
        :param orderId: The unique order id
        :type orderId: int
        :param origClientOrderId: optional
        :type origClientOrderId: str
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "symbol": "LTCBTC",
                "orderId": 1,
                "clientOrderId": "myOrder1",
                "price": "0.1",
                "origQty": "1.0",
                "executedQty": "0.0",
                "status": "NEW",
                "timeInForce": "GTC",
                "type": "LIMIT",
                "side": "BUY",
                "stopPrice": "0.0",
                "icebergQty": "0.0",
                "time": 1499827319559
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('order', True, data=params)

    def get_all_orders(self, **params):
        """Get all account orders; active, canceled, or filled.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#all-orders-user_data

        :param symbol: required
        :type symbol: str
        :param orderId: The unique order id
        :type orderId: int
        :param limit: Default 500; max 500.
        :type limit: int
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "orderId": 1,
                    "clientOrderId": "myOrder1",
                    "price": "0.1",
                    "origQty": "1.0",
                    "executedQty": "0.0",
                    "status": "NEW",
                    "timeInForce": "GTC",
                    "type": "LIMIT",
                    "side": "BUY",
                    "stopPrice": "0.0",
                    "icebergQty": "0.0",
                    "time": 1499827319559
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('allOrders', True, data=params)

    def cancel_order(self, **params):
        """Cancel an active order. Either orderId or origClientOrderId must be sent.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#cancel-order-trade

        :param symbol: required
        :type symbol: str
        :param orderId: The unique order id
        :type orderId: int
        :param origClientOrderId: optional
        :type origClientOrderId: str
        :param newClientOrderId: Used to uniquely identify this cancel. Automatically generated by default.
        :type newClientOrderId: str
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "symbol": "LTCBTC",
                "origClientOrderId": "myOrder1",
                "orderId": 1,
                "clientOrderId": "cancelMyOrder1"
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._delete('order', True, data=params)

    def get_open_orders(self, **params):
        """Get all open orders on a symbol.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#current-open-orders-user_data

        :param symbol: required
        :type symbol: str
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            [
                {
                    "symbol": "LTCBTC",
                    "orderId": 1,
                    "clientOrderId": "myOrder1",
                    "price": "0.1",
                    "origQty": "1.0",
                    "executedQty": "0.0",
                    "status": "NEW",
                    "timeInForce": "GTC",
                    "type": "LIMIT",
                    "side": "BUY",
                    "stopPrice": "0.0",
                    "icebergQty": "0.0",
                    "time": 1499827319559
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('openOrders', True, data=params)

    # User Stream Endpoints
    def get_account(self, **params):
        """Get current account information.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#account-information-user_data

        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "makerCommission": 15,
                "takerCommission": 15,
                "buyerCommission": 0,
                "sellerCommission": 0,
                "canTrade": true,
                "canWithdraw": true,
                "canDeposit": true,
                "balances": [
                    {
                        "asset": "BTC",
                        "free": "4723846.89208129",
                        "locked": "0.00000000"
                    },
                    {
                        "asset": "LTC",
                        "free": "4763368.68006011",
                        "locked": "0.00000000"
                    }
                ]
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('account', True, data=params)

    def get_my_trades(self, **params):
        """Get trades for a specific symbol.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#account-trade-list-user_data

        :param symbol: required
        :type symbol: str
        :param limit: Default 500; max 500.
        :type limit: int
        :param fromId: TradeId to fetch from. Default gets most recent trades.
        :type fromId: int
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            [
                {
                    "id": 28457,
                    "price": "4.00000100",
                    "qty": "12.00000000",
                    "commission": "10.10000000",
                    "commissionAsset": "BNB",
                    "time": 1499865549590,
                    "isBuyer": true,
                    "isMaker": false,
                    "isBestMatch": true
                }
            ]

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._get('myTrades', True, data=params)

    # Withdraw Endpoints

    def withdraw(self, **params):
        """Submit a withdraw request.

        https://www.binance.com/restapipub.html

        Assumptions:

        - You must have Withdraw permissions enabled on your API key
        - You must have withdrawn to the address specified through the website and approved the transaction via email

        :param asset: required
        :type asset: str
        :type address: required
        :type address: str
        :param amount: required
        :type amount: decimal
        :param name: Description of the address - optional
        :type name: str
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "msg": "success",
                "success": true
            }

        :raises: BinanceResponseException, BinanceAPIException, BinanceWithdrawException

        """
        res = self._request_withdraw_api('post', 'withdraw.html', True, data=params)
        if not res['success']:
            raise BinanceWithdrawException(res['msg'])
        return res

    def get_deposit_history(self, **params):
        """Fetch deposit history.

        https://www.binance.com/restapipub.html

        :param asset: optional
        :type asset: str
        :type status: 0(0:pending,1:success) optional
        :type status: int
        :param startTime: optional
        :type startTime: long
        :param endTime: optional
        :type endTime: long
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "depositList": [
                    {
                        "insertTime": 1508198532000,
                        "amount": 0.04670582,
                        "asset": "ETH",
                        "status": 1
                    }
                ],
                "success": true
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._request_withdraw_api('get', 'depositHistory.html', True, data=params)

    def get_withdraw_history(self, **params):
        """Fetch withdraw history.

        https://www.binance.com/restapipub.html

        :param asset: optional
        :type asset: str
        :type status: 0(0:Email Sent,1:Cancelled 2:Awaiting Approval 3:Rejected 4:Processing 5:Failure 6Completed) optional
        :type status: int
        :param startTime: optional
        :type startTime: long
        :param endTime: optional
        :type endTime: long
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "withdrawList": [
                    {
                        "amount": 1,
                        "address": "0x6915f16f8791d0a1cc2bf47c13a6b2a92000504b",
                        "asset": "ETH",
                        "applyTime": 1508198532000
                        "status": 4
                    },
                    {
                        "amount": 0.005,
                        "address": "0x6915f16f8791d0a1cc2bf47c13a6b2a92000504b",
                        "txId": "0x80aaabed54bdab3f6de5868f89929a2371ad21d666f20f7393d1a3389fad95a1",
                        "asset": "ETH",
                        "applyTime": 1508198532000,
                        "status": 4
                    }
                ],
                "success": true
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._request_withdraw_api('get', 'withdrawHistory.html', True, data=params)

    def get_deposit_address(self, **params):
        """Fetch a deposit address for a symbol

        https://www.binance.com/restapipub.html

        :param asset: required
        :type asset: str
        :param recvWindow: the number of milliseconds the request is valid for
        :type recvWindow: int

        :returns: API response

        .. code-block:: python

            {
                "address": "0x6915f16f8791d0a1cc2bf47c13a6b2a92000504b",
                "success": true,
                "addressTag": "1231212",
                "asset": "BNB"
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._request_withdraw_api('get', 'depositAddress.html', True, data=params)

    # User Stream Endpoints

    def stream_get_listen_key(self):
        """Start a new user data stream and return the listen key
        If a stream already exists it should return the same key.
        If the stream becomes invalid a new key is returned.

        Can be used to keep the user stream alive.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#start-user-data-stream-user_stream

        :returns: API response

        .. code-block:: python

            {
                "listenKey": "pqia91ma19a5s61cv6a81va65sdf19v8a65a1a5s61cv6a81va65sdf19v8a65a1"
            }

        :raises: BinanceResponseException, BinanceAPIException

        """
        res = self._post('userDataStream', False, data={})
        return res['listenKey']

    def stream_keepalive(self, **params):
        """PING a user data stream to prevent a time out.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#keepalive-user-data-stream-user_stream

        :param listenKey: required
        :type listenKey: str

        :returns: API response

        .. code-block:: python

            {}

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._put('userDataStream', False, data=params)

    def stream_close(self, **params):
        """Close out a user data stream.

        https://github.com/binance-exchange/binance-official-api-docs/blob/master/rest-api.md#close-user-data-stream-user_stream

        :returns: API response

        .. code-block:: python

            {}

        :raises: BinanceResponseException, BinanceAPIException

        """
        return self._delete('userDataStream', False, data=params)

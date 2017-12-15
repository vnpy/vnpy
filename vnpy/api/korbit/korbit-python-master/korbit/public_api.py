# -*- coding: utf-8 -*-

import requests
import json
import logging
try:
    from urllib.parse import urljoin
except ImportError:
    from urlparse import urljoin


class PublicAPI:
    def __init__(self, production=True, version="v1", timeout=20):
        self.__host = production and "https://api.korbit.co.kr/%s/" % version \
                      or "https://api.korbit-test.com/%s/" % version
        self.__timeout = timeout

    # https://apidocs.korbit.co.kr/#public
    def ticker(self, currency_pair="btc_krw"):
        params = {
            'currency_pair': currency_pair
        }
        return self.request_get("ticker", params=params)

    def detailed_ticker(self, currency_pair="btc_krw"):
        params = {
            'currency_pair': currency_pair
        }
        return self.request_get("ticker/detailed", params=params)

    def orderbook(self, currency_pair="btc_krw", category="all", group=True):
        params = {
            'group': group,
            'category': category,
            'currency_pair': currency_pair
        }
        return self.request_get("orderbook", params=params)

    def bids_orderbook(self, currency_pair="btc_krw", group=True):
        return self.orderbook(currency_pair=currency_pair, category="bid", group=group)

    def asks_orderbook(self, currency_pair="btc_krw", group=True):
        return self.orderbook(currency_pair=currency_pair, category="ask", group=group)

    def list_of_filled_orders(self, currency_pair="btc_krw", interval="hour"):
        params = {
            'time': interval,
            'currency_pair': currency_pair
        }
        return self.request_get("transactions", params=params)

    def constants(self):
        return self.request_get("constants")

    def request_get(self, path, headers=None, params=None):
        print urljoin(self.host, path)
        response = requests.get(urljoin(self.host, path), headers=headers, params=params, timeout=self.__timeout)
        print response
        try:
            return response.json()
        except json.decoder.JSONDecodeError as e:
            logging.error("exception: {}, response_text: {}".format(e, response.text))
            return response.text

    def request_post(self, path, headers=None, data=None):
        print urljoin(self.host, path) , headers , data 
        response = requests.post(urljoin(self.host, path), headers=headers, data=data, timeout=self.__timeout)
        print response
        try:
            return response.json()
        except json.decoder.JSONDecodeError as e:
            logging.error("exception: {}, response_text: {}".format(e, response.text))
            return response.text

    @property
    def host(self):
        return self.__host

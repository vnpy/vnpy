# -*- coding: utf-8 -*-
from __future__ import print_function
from __future__ import absolute_import
import time
from .public_api import PublicAPI


class PrivateAPI(PublicAPI):
    def __init__(self, client_id, secret, production=True, version="v1", timeout=20):
        try:
            super(self.__class__, self).__init__(production, version, timeout)
        except TypeError:
            PublicAPI.__init__(self, production, version, timeout)
        self.__client_id = client_id
        self.__secret = secret
        self.__token = {}

    # https://apidocs.korbit.co.kr/#authentication
    def create_token_directly(self, username, password):
        payload = {
            'client_id': self.__client_id,
            'client_secret': self.__secret,
            'username': username,
            'password': password,
            'grant_type': "password"
        }
        self.__token = self.request_post("oauth2/access_token", data=payload)
        return self.__token

    def set_token(self, token):
        self.__token = token

    def refresh_token(self):
        payload = {
            'client_id': self.__client_id,
            'client_secret': self.__secret,
            'refresh_token': self.__token['refresh_token'],
            'grant_type': "refresh_token"
        }
        self.__token = self.request_post("oauth2/access_token", data=payload)
        return self.__token

    def get_user_info(self):
        return self.request_get("user/info", headers=self.headers)

    @property
    def headers(self):
        return {
            'Accept': 'application/json',
            'Authorization': "{} {}".format(self.__token['token_type'], self.__token['access_token'])
        }

    # https://apidocs.korbit.co.kr/#exchange
    def bid_order(self, bid_type, coin_amount=None, price=None, fiat_amount=None, currency_pair="btc_krw"):
        payload = {
            'type': bid_type,
            'currency_pair': currency_pair,
            'price': price,
            'coin_amount': coin_amount,
            'fiat_amount': fiat_amount,
            'nonce': self.nonce
        }
        #return self.request_post("user/orders/buy", headers=self.headers, data=payload)
        return self.request_post("user/orders/buy", headers=self.headers, data=payload)

    def market_bid_order(self, fiat_amount, currency_pair="btc_krw"):
        return self.bid_order('market', fiat_amount=fiat_amount, currency_pair=currency_pair)

    def limit_bid_order(self, coin_amount, price, currency_pair="btc_krw"):
        return self.bid_order('limit', coin_amount=coin_amount, price=price, currency_pair=currency_pair)

    def ask_order(self, ask_type, coin_amount, price=None, currency_pair="btc_krw"):
        payload = {
            'type': ask_type,
            'currency_pair': currency_pair,
            'price': price,
            'coin_amount': coin_amount,
            'nonce': self.nonce
        }
        return self.request_post("user/orders/sell", headers=self.headers, data=payload)

    def market_ask_order(self, coin_amount, currency_pair="btc_krw"):
        return self.ask_order('market', coin_amount=coin_amount, currency_pair=currency_pair)

    def limit_ask_order(self, coin_amount, price, currency_pair="btc_krw"):
        return self.ask_order('limit', coin_amount, price, currency_pair)

    def cancel_order(self, ids, currency_pair="btc_krw"):
        payload = {
            'id': ids,
            'currency_pair': currency_pair,
            'nonce': self.nonce
        }
        return self.request_post("user/orders/cancel", headers=self.headers, data=payload)

    def list_open_orders(self, offset=0, limit=10, currency_pair="btc_krw"):
        params = {
            'currency_pair': currency_pair,
            'offset': offset,
            'limit': limit
        }
        return self.request_get("user/orders/open", headers=self.headers, params=params)

    def view_exchange_orders(self, offset=0, limit=10, currency_pair="btc_krw"):
        params = {
            'currency_pair': currency_pair,
            'offset': offset,
            'limit': limit
        }
        print("user/orders" , self.headers , params)
        return self.request_get("user/orders", headers=self.headers, params=params)

    def view_transfers(self, offset=0, limit=10, currency="btc"):
        params = {
            'currency': currency,
            'offset': offset,
            'limit': limit
        }
        return self.request_get("user/transfers", headers=self.headers, params=params)

    def trading_volume_and_fees(self, currency_pair="all"):
        params = {
            'currency_pair': currency_pair
        }
        return self.request_get("user/volume", headers=self.headers, params=params)

    # https://apidocs.korbit.co.kr/#wallet
    def user_balances(self):
        return self.request_get("user/balances", headers=self.headers)

    def user_accounts(self):
        return self.request_get("user/accounts", headers=self.headers)

    def retrieve_wallet_status(self, currency_pair="btc_krw"):
        params = {
            'currency_pair': currency_pair
        }
        return self.request_get("user/wallet", headers=self.headers, params=params)

    def assign_btc_address(self, currency="btc"):
        payload = {
            'currency': currency,
            'nonce': self.nonce
        }
        return self.request_post("user/coins/address/assign", headers=self.headers, data=payload)

    def request_btc_withdrawal(self, address, amount, currency="btc"):
        payload = {
            'address': address,
            'amount': amount,
            'currency': currency,
            'nonce': self.nonce
        }
        return self.request_post("user/coins/out", headers=self.headers, data=payload)

    def status_of_btc_deposit_and_transfer(self, transfer_id="", currency="btc"):
        params = {
            'currency': currency
        }
        if transfer_id != "":
            params['id'] = transfer_id

        return self.request_get("user/coins/status", headers=self.headers, params=params)

    def cancel_btc_transfer_request(self, transfer_id, currency="btc"):
        payload = {
            'id': transfer_id,
            'currency': currency,
            'nonce': self.nonce
        }
        return self.request_post("user/coins/out/cancel", headers=self.headers, data=payload)

    @property
    def nonce(self):
        return int(time.time() * 1000)

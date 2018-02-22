# -*- coding: utf-8 -*-

from .private_api import PrivateAPI, PublicAPI

__public = PublicAPI()
ticker = __public.ticker
detailed_ticker = __public.detailed_ticker
orderbook = __public.orderbook
asks_orderbook = __public.asks_orderbook
bids_orderbook = __public.bids_orderbook
list_of_filled_orders = __public.list_of_filled_orders
constants = __public.constants

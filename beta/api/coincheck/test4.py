# encoding: utf-8

from vncoincheck import *

def test():

	api = DataApiSocket()
	api.connect("wss://ws-api.coincheck.com")

	sleep(2)
	api.sendOrderbookRequest()

	api.sendTradesRequest()

	raw_input()

if __name__ == '__main__':
    test()
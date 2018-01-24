"""
FXCM Trading RESTful API example.
"""
import json
import time
import requests
from socketIO_client import SocketIO
from prompt_toolkit import prompt
from threading import Thread
import signal
import sys
import io
from datetime import datetime

socketIO = None
UPDATES = {}
SYMBOLS = {}
COLLECTIONS = None
ACCESS_TOKEN = "48055b5d9afac0a300143ac067ce04cd2430a434"
TRADING_API_URL = 'https://api-demo.fxcm.com:443'
WEBSOCKET_PORT = 443


list = ['Offer','Account','Order','OpenPosition','Summary','Properties', 'ClosedPosition']
order_list = []
logFile = "H:/Projects/RESTAPI-master/nodejs/PythonLog.txt"

def timestamp():
    output = str(datetime.now().strftime('%Y%m%d-%H:%M:%S.%f')[:-3])
    return output

def logging(mess, t):
    ts = timestamp()

    with io.FileIO(logFile, "a") as file:
        file.write('\n' +ts + ": " +t + " ==>"  +'\n')
        for key in mess:
            file.write(str(key) +" - " +str(mess[key]) +'\n')
                	
def request_processor(method, params):
    """ Trading server request help function. """

    headers = {
	    'User-Agent': 'request',
		'Authorization': bearer_access_token,
        'Accept': 'application/json',
        'Content-Type': 'application/x-www-form-urlencoded'
    }
    rresp = requests.get(TRADING_API_URL + method, headers=headers, params=params)
    if rresp.status_code == 200:
        data = rresp.json()
        if data["response"]["executed"] is True:
            return True, data
        return False, data["response"]["error"]
    else:
        return False, rresp.status_code

def post_request_processor(method, params):
    """ Trading server request help function. """

    headers = {
	    'User-Agent': 'request',
		'Authorization': bearer_access_token,
        'Accept': 'application/json',
        'Content-Type': 'application/x-www-form-urlencoded'
    }
    rresp = requests.post(TRADING_API_URL + method, headers=headers, data=params)
    if rresp.status_code == 200:
        data = rresp.json()
        if data["response"]["executed"] is True:
            return True, data
        return False, data["response"]["error"]
    else:
        return False, rresp.status_code

def create_bearer_token(t,s):
    bt = "Bearer " +s +t
    return bt

def on_price_update(msg):
    md = json.loads(msg)
    SYMBOLS[md["Symbol"]] = md
    print(SYMBOLS, "SYMBOLS")
    #logging(SYMBOLS, "SYMBOLS")

def on_message(msg):
    message = json.loads(msg)
    UPDATES[message["t"]] = message
    print(UPDATES, "UPDATES")
    #logging(UPDATES, "UPDATES")

def on_error(ws, error):
    print (error)

def on_close():
    print ('Websocket closed.')

def on_connect():
    ### Get models
    status, response = request_processor('/trading/get_model', {'models': list})
    if status is True:
        COLLECTIONS = response
        print("*" * 50)
        print (COLLECTIONS["accounts"])
        print("*" * 50)
    else:
        print(status)
        print ("Error processing request /trading/get_model: " +str(response))
    ### Subscribe message updates
    status, response = post_request_processor('/trading/subscribe', {'models': order_list})
    if status is True:
        for item in order_list:
            socketIO.on(item, on_message)
    else:
        print ("Error processing request: /trading/subscribe: " + response)		

    thr = Thread(target=cli, args=(1, COLLECTIONS))
    try:
        thr.setDaemon(True)
        thr.start()
        socketIO.wait()
    except (KeyboardInterrupt, SystemExit):
        thr.join(0)
        sys.exit(1)

		
def subscribe_prices(symbol):
    status, response = post_request_processor('/subscribe', {'pairs': symbol})
    if status is True:
        socketIO.on(symbol, on_price_update)
    else:
        print ("Error processing request: /subscribe: " + response)

def unsubscribe_prices(symbol):
    status, response = post_request_processor('/unsubscribe', {'pairs': symbol})
    if status is True:
        socketIO.on(symbol, on_price_update)
    else:
        print ("Error processing request: /unsubscribe: " + response)

def cli(args, COLLECTIONS):
    while True:
        try:
            inp = prompt(u'> ')
        except KeyboardInterrupt:
            print ("Press Ctrl+c again to quit.")
            sys.exit(1)
        if not inp:
            continue
        try:
            if len(inp) > 3 and inp[0:3] == 'run':
                cmd = json.loads(inp[4:])
                command = cmd["c"]
                if command == 'book':
                    for symbol in SYMBOLS:
                        price = SYMBOLS[symbol]
                        print (price)

                elif command == 'show':
                    if cmd["opt"] == 'offers':
                        for offer in COLLECTIONS['offers']:
                            ###print ('{}, {}, {}, {}, {}'.format(offer['currency'], offer['sell'], offer['buy'], offer['offerId'], offer['ratePrecision']))
                            print (offer)

                    elif cmd["opt"] == 'orders':
                        for order in COLLECTIONS['orders']:
                            print (order)

                    elif cmd["opt"] == 'updates':
                        for obj in UPDATES:
                            print (obj)

                    elif cmd["opt"] == 'accounts':
                        for obj in COLLECTIONS['accounts']:
                            print (obj)

                    elif cmd["opt"] == 'open_positions':
                        for obj in COLLECTIONS['open_positions']:
                            print (obj)

                    elif cmd["opt"] == 'closed_positions':
                        for obj in COLLECTIONS['closed_positions']:
                            print (obj)

                    elif cmd["opt"] == 'summary':
                        for obj in COLLECTIONS['summary']:
                            print (obj)

                    elif cmd["opt"] == 'properties':
                        for obj in COLLECTIONS['properties']:
                            print (obj)

                    elif cmd["opt"] == 'LeverageProfile':
                        for obj in COLLECTIONS['LeverageProfile']:
                            print (obj)
							
                elif command == 'subscribe':
                    for symbol in cmd["opt"]:
                        subscribe_prices(symbol)

                elif command == 'unsubscribe':
                    for symbol in cmd["opt"]:
                        unsubscribe_prices(symbol)

                elif command == 'market_order':
                    status, response = post_request_processor('/trading/open_trade', {
                        'account_id': cmd['account_id'],
                        'symbol': cmd['symbol'],
                        'side': cmd['side'],
                        'amount': cmd['amount'],
                        'at_market': 0,
                        'order_type': 'AtMarket',
                        'time_in_force': cmd['time_in_force']
                    })
                    if status is True:
                        print ('market_order has been executed: {}'.format(response))
                    else:
                        print ('market_order execution error: {}'.format(response))
						
                elif command == 'market_range':
                    status, response = post_request_processor('/trading/open_trade', {
                        'account_id': cmd['account_id'],
                        'symbol': cmd['symbol'],
                        'side': cmd['side'],
                        'amount': cmd['amount'],
                        'order_type': 'MarketRange',
						'at_market': 1
                    })
                    if status is True:
                        print ('market_order has been executed: {}'.format(response))
                    else:
                        print ('market_order execution error: {}'.format(response))
						
                elif command == 'close_trade':
                    status, response = post_request_processor('/trading/close_trade', {
                        'trade_id': cmd['trade_id'],
                        'rate': 0,
                        'amount': cmd['amount'],
                        'at_market': 0,
                        'order_type': 'AtMarket',
                        'time_in_force': cmd['time_in_force']
                    })
                    if status is True:
                        print ('close_trade has been executed: {}'.format(response))
                    else:
                        print ('close_trade execution error: {}'.format(response))

                elif command == 'create_entry_order':
                    status, response = post_request_processor('/trading/create_entry_order', {
                        'account_id': cmd['account_id'],
                        'symbol': cmd['symbol'],
                        'is_buy': cmd['side'],
                        'rate': cmd['rate'],
                        'is_in_pips': 0,
                        'amount': cmd['amount'],
                        'order_type': 'AtMarket',
                        'time_in_force': cmd['time_in_force']
                    })
                    if status is True:
                        print ('create_entry_order has been executed: {}'.format(response))
                    else:
                        print ('create_entry_order execution error: {}'.format(response))

                elif command == 'change_order':
                    status, response = post_request_processor('/trading/change_order', {
                        'order_id': cmd['order_id'],
                        'rate': cmd['rate'],
                        'range': cmd['range'],
                        'amount': cmd['amount'],
                        'trailing_step': cmd['trailing_step']
                    })
                    if status is True:
                        print ('change_order has been executed: {}'.format(response))
                    else:
                        print ('change_order execution error: {}'.format(response))

                elif command == 'delete_order':
                    status, response = post_request_processor('/trading/delete_order', {
                        'order_id': cmd['order_id']
                    })
                    if status is True:
                        print ('delete_order has been executed: {}'.format(response))
                    else:
                        print ('delete_order execution error: {}'.format(response))

                elif command == 'get_instruments':
                    status, response = request_processor('/trading/get_instruments', {})
                    if status is True:
                        print ('get_instruments has been executed: {}'.format(response))
                    else:
                        print ('get_instruments execution error: {}'.format(response))

                elif command == 'simple_oco':
                    status, response = request_processor('/trading/simple_oco', {
					'account_id': cmd['account_id'],
					'symbol': cmd['symbol'],
					'amount': cmd['amount'],
                    'time_in_force': cmd['time_in_force'],
                    'is_buy': cmd['is_buy'],
                    'rate': cmd['rate'],
                    'is_buy2': cmd['is_buy2'],
                    'rate2': cmd['rate2']
					})
                    if status is True:
                        print ('simple_oco has been executed: {}'.format(response))
                    else:
                        print ('simple_oco execution error: {}'.format(response))
						
                elif command == 'add_to_oco':
                    status, response = request_processor('/trading/add_to_oco', {
					orderIds: cmd.orderIds,
					ocoBulkId: cmd.ocoBulkId
					})
                    if status is True:
                        print ('add_to_oco has been executed: {}'.format(response))
                    else:
                        print ('add_to_oco execution error: {}'.format(response))
						
                elif command == 'remove_from_oco':
                    status, response = request_processor('/trading/remove_from_oco', {
					orderIds: cmd.orderIds
					})
                    if status is True:
                        print ('remove_from_oco has been executed: {}'.format(response))
                    else:
                        print ('remove_from_oco execution error: {}'.format(response))
						
                elif command == 'edit_oco':
                    status, response = request_processor('/trading/edit_oco', {
					ocoBulkId: cmd.ocoBulkId,
					addOrderIds: cmd.addOrderIds,
                    removeOrderIds: cmd.removeOrderIds
					})
                    if status is True:
                        print ('edit_oco has been executed: {}'.format(response))
                    else:
                        print ('edit_oco execution error: {}'.format(response))
						
                elif command == 'change_trade_stop_limit':
                    status, response = request_processor('/trading/change_trade_stop_limit', {
                    trade_id: cmd.trade_id,
                    is_stop: cmd.is_stop,
                    rate: cmd.rate,
                    is_in_pips: cmd.is_in_pips,
                    trailing_step: cmd.trailing_step
					})
                    if status is True:
                        print ('change_trade_stop_limit has been executed: {}'.format(response))
                    else:
                        print ('change_trade_stop_limit execution error: {}'.format(response))
						
                elif command == 'change_order_stop_limit':
                    status, response = request_processor('/trading/change_order_stop_limit', {
                    order_id: cmd.order_id,
                    is_stop: cmd.is_stop,
                    rate: cmd.rate,
                    is_in_pips: cmd.is_in_pips,
                    trailing_step: cmd.trailing_step
					})
                    if status is True:
                        print ('change_order_stop_limit has been executed: {}'.format(response))
                    else:
                        print ('change_order_stop_limit execution error: {}'.format(response))
						
                elif command == 'change_net_stop_limit':
                    status, response = request_processor('/trading/change_net_stop_limit', {
                    account_id: cmd.account_id,
                    symbol: cmd.symbol,
                    is_buy: cmd.is_buy,
                    is_stop: cmd.is_stop,
                    rate: cmd.rate,
                    trailing_step: cmd.trailing_step
					})
                    if status is True:
                        print ('change_net_stop_limit has been executed: {}'.format(response))
                    else:
                        print ('change_net_stop_limit execution error: {}'.format(response))
						
                elif command == 'close_all_for_symbol':
                    status, response = request_processor('/trading/close_all_for_symbol', {
                    account_id: cmd.account_id,
                    forSymbol: cmd.forSymbol,
                    symbol: cmd.symbol,
                    order_type: cmd.order_type,
                    time_in_force: cmd.time_in_force
					})
                    if status is True:
                        print ('close_all_for_symbol has been executed: {}'.format(response))
                    else:
                        print ('close_all_for_symbol execution error: {}'.format(response))
						
                elif command == 'candles':
                    req="/"+command+"/"+str(cmd['instrumentid'])+"/"+str(cmd['periodid'])
                    status, response = request_processor(req, {
                        'num': cmd['num'],
						'from': cmd['from'],
                        'to': cmd['to']
                    })
                    if status is True:
                        print ('has been executed: {}'.format(response))
                    else:
                        print ('execution error: {}'.format(response))	

						
                else:
                    print ("Unknown command: " + command)
            else:
                print ('Unknown command.')
        except ValueError:
            print ('Invalid command')
### Main

if __name__ == '__main__':
    #signal.getsignal(signal.SIGINT, exit_gracefully)

        COLLECTIONS = {}
        print '000'
        socketIO = SocketIO(TRADING_API_URL, WEBSOCKET_PORT, params={'access_token': ACCESS_TOKEN, 'agent': "leiwang-rest-api"})
        print 1
        #print (socketIO._engineIO_session.id)
        bearer_access_token = create_bearer_token(ACCESS_TOKEN, socketIO._engineIO_session.id)
        print (bearer_access_token)
        socketIO.on('disconnec', on_close)
        socketIO.on('connect', on_connect)
        socketIO.wait()

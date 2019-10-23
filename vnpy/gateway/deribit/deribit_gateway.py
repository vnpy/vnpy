from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    PositionData,
    AccountData,
    ContractData,
    OrderRequest,
    CancelRequest,
    SubscribeRequest,
    HistoryRequest,
)
from vnpy.trader.constant import (
    Direction,
    Exchange,
    OrderType,
    Product,
    Status,
    Interval,
    OptionType
)
from vnpy.event import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.api.websocket import WebsocketClient
from vnpy.trader.event import EVENT_TIMER
from vnpy.event import Event

from time import sleep
from datetime import datetime
from copy import copy

WS_HOST = 'wss：//www.deribit.com/ws/api/v2'
SANDBOX_WEBSOCKET_HOST = 'wss://testapp.deribit.com/ws/api/v2'

PRODUCT_DERIBIT2VT = {
    "future":Product.FUTURES,
    "option":Product.OPTION
}
OPTIONTYPE_DERIBIT2VT = {
    "call":OptionType.CALL,
    "put":OptionType.PUT
}
DIRECTION_VT2DERIBIT = {Direction.LONG: "buy", Direction.SHORT: "sell"}
ORDERTYPE_VT2DERIBIT = {
    OrderType.LIMIT: "limit",
    OrderType.MARKET: "market",
}
ORDERTYPE_DERIBIT2VT = {v: k for k, v in ORDERTYPE_VT2DERIBIT.items()}
DIRECTION_DERIBIT2VT = {v: k for k, v in DIRECTION_VT2DERIBIT.items()}
STATUS_DERIBIT2VT = {
    "open":Status.NOTTRADED,
    "filled":Status.ALLTRADED,
    "rejected":Status.REJECTED,
    "cancelled":Status.CANCELLED,
}

class DeribitGateway(BaseGateway):
    """"""
    default_setting = {
        "user_id":"",
        "secret":"",
        "proxy_host":"",
        "proxy_port":"",
        "server": ["SAND_BOX","REAL"],
    }

    exchanges = [Exchange.DERIBIT]

    def __init__(self,event_engine):
        """"""
        super(DeribitGateway,self).__init__(event_engine, "DERIBIT")

        self.ws_api = DeribitWebsocketApi(self)

    def connect(self, setting: dict):
        """"""
        key = setting["user_id"]
        secret = setting["secret"]
        proxy_host = setting["proxy_host"]
        proxy_port = setting["proxy_port"]
        server = setting['server']

        if proxy_port.isdigit():
            proxy_port = int(proxy_port)
        else:
            proxy_port = 0

        self.ws_api.connect(
            key,
            secret,
            server,
            proxy_host,
            proxy_port,
        )
    
    def subscribe(self, req: SubscribeRequest):
        """"""
        self.ws_api.subscribe(req)

    def send_order(self, req:OrderRequest):
        """"""
        return self.ws_api.send_order(req)
    
    def cancel_order(self, req: CancelRequest):
        """"""
        return self.ws_api.cancel_order(req)

    def query_account(self):
        """"""
        self.ws_api.query_account()

    def query_position(self):
        """
        Query holding positions.
        """
        self.ws_api.query_position()

    def query_history(self, req: HistoryRequest):
        """
        Query bar history data.
        """
        pass

    def init_query(self):
        """"""
        pass

    def process_timer_event(self, event: Event):
        """"""
        pass

    def close(self):
        """"""
        self.ws_api.stop()


class DeribitWebsocketApi(WebsocketClient):
    """"""
    def __init__(self,gateway: BaseGateway):
        """"""
        super(DeribitWebsocketApi, self).__init__()
        self.gateway = gateway
        self.gateway_name = gateway.gateway_name

        self.key = ""
        self.secret = ""
        self.access_token = ""

        self.id = 1
        self.id_callback = {}

        self.callbacks = {
            "ticker":self.on_ticker,
            "book":self.on_orderbook,
            "user":self.on_user_change,
        }

        self.ticks = {}

        self.asks = {}
        self.bids = {}

        self.query_ins_done = False
        self.query_pos_done = False
        self.query_acc_done = False

    def connect(
        self,
        key: str,
        secret: str,
        server: str,
        proxy_host: str,
        proxy_port: int
    ):
        """"""
        self.gateway.write_log("开始连接ws接口")
        self.key = key
        self.secret = secret.encode()

        if server == "REAL":
            self.init(WEBSOCKET_HOST, proxy_host, proxy_port)
        else:
            self.init(SANDBOX_WEBSOCKET_HOST, proxy_host, proxy_port)
    
        self.start()
        sleep(5)

        self.init_query()

        self.gateway.write_log("Deribit接口连接成功")

    def init_query(self):
        """"""
        self.query_instrument()
        self.wait_instrument()

        self.get_access_token()
        self.wait_access_token()

        self.query_position()
        self.wait_position()

        self.query_account()
        self.wait_account()

    def subscribe(self,req: SubscribeRequest):
        """"""
        symbol = req.symbol 
        self.ticks[symbol] = TickData(
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=Exchange.DERIBIT,
            datetime=datetime.now(),
        )

        channels = [
            "ticker." + symbol + ".raw",
            "user.changes." + symbol + ".raw",
            "book." + symbol + ".raw",
        ]
        msg = {
            "jsonrpc": "2.0",
            "method": "private/subscribe",
            "id": self.id,
            "params": {
                "channels": channels,
                "access_token":self.access_token}
        }
        self.id += 1

        self.send_packet(msg)

    def send_order(self,req: OrderRequest):
        """"""
        orderid = self.id 
        order = req.create_order_data(orderid,self.gateway_name)
        self.gateway.on_order(order)

        side = DIRECTION_VT2DERIBIT[req.direction]
        symbol = req.symbol
        order_type = ORDERTYPE_VT2DERIBIT[req.type]

        msg = {
            "jsonrpc" : "2.0",
            "id" : self.id,
            "method" : "private/"+side,
            "params" : {
                "instrument_name" : symbol,
                "amount" : req.volume,
                "type" : order_type,
                "label" : orderid,
            }
        }
        self.id += 1

        if req.type == OrderType.LIMIT:
            msg['params']['price'] = req.price

        self.send_packet(msg)

        return order.vt_orderid
    
    def cancel_order(self,req: CancelRequest):
        """"""

        msg = {
            "jsonrpc" : "2.0",
            "id" : self.id,
            "method" : "private/cancel",
            "params" : {
                "order_id" : req.orderid,
                "access_token":self.access_token,
            }
        }
        self.id_callback[self.id] = self.on_cancel_order
        self.id += 1

        self.send_packet(msg)
        
    def cancel_order(self, req: CancelRequest):
        """"""
        pass

    def get_access_token(self):
        """
        use the access key and secret to get access token
        """
        msg = {
            "jsonrpc": "2.0",
            "id": self.id,
            "method": "public/auth",
            "params": {
                "grant_type": "client_credentials",
                "client_id": self.key,
                "client_secret": self.secret.decode()
            }
        }
        self.id_callback[self.id] = self.on_access_token
        self.id += 1

        self.send_packet(msg)

    def query_instrument(self):
        """"""        
        msg_btc = {
            "jsonrpc" : "2.0",
            "id" : self.id,
            "method" : "public/get_instruments",
            "params" : {
                "currency" : "BTC",
                "expired" : False,
            }
        }
        self.id_callback[self.id] = self.on_query_instrument
        self.id += 1
        msg_eth = {
            "jsonrpc" : "2.0",
            "id" : self.id,
            "method" : "public/get_instruments",
            "params" : {
                "currency" : "ETH",
                "expired" : False
            }
        }
        self.id_callback[self.id] = self.on_query_instrument
        self.id += 1

        self.send_packet(msg_btc)        
        self.send_packet(msg_eth)

    def query_account(self):
        """"""
        for curr in ['BTC','ETH']:
            msg = {
                "jsonrpc" : "2.0",
                "id" : self.id,
                "method" : "private/get_deposits",
                "params" : {
                    "currency" : curr,
                    "access_token":self.access_token,
                    
                }
            }
            self.send_packet(msg)

            self.id_callback[self.id] = self.on_query_account
            self.id += 1

    def query_position(self):
        """"""
        for kind in ['future','option']:
            for curr in ['BTC','ETH']:
                msg = {
                    "jsonrpc" : "2.0",
                    "id" : self.id,
                    "method" : "private/get_positions",
                    "params" : {
                        "currency" : curr,
                        "kind" : kind,
                        "access_token":self.access_token,
                    }
                }
                self.send_packet(msg)
            
                self.id_callback[self.id] = self.on_query_position
                self.id += 1

    def on_packet(self, packet: dict):
        """
        callback when data is received and unpacked
        """        
        if 'id' in packet.keys():
            packet_id = packet['id']
            if packet_id in self.id_callback.keys():
                callback = self.id_callback[packet_id]
                callback(packet)
        elif 'params' in packet.keys():
            channel = packet["params"]["channel"]
            kind = channel.split(".")[0]
            callback = self.callbacks[kind]
            callback(packet)

    def on_access_token(self,packet: dict):
        """"""
        data = packet['result']
        self.access_token = data['access_token']                
    
    def on_query_instrument(self,packet: list):
        """"""
        data = packet['result']
        for d in data:
            product = PRODUCT_DERIBIT2VT[d['kind']]
            if product == Product.FUTURES:
                contract = ContractData(
                    symbol=d['instrument_name'],
                    exchange=Exchange.DERIBIT,
                    name=d['instrument_name'],
                    product=product,
                    pricetick=d['tick_size'],
                    size=d['contract_size'],
                    min_volume=d['min_trade_amount'],
                    net_position=True,
                    history_data=False,
                    gateway_name=self.gateway_name,
                )
            else:
                expiry = datetime.fromtimestamp(d['expiration_timestamp']/1000)
                option_type = OPTIONTYPE_DERIBIT2VT[d['option_type']]
                contract = ContractData(
                    symbol=d['instrument_name'],
                    exchange=Exchange.DERIBIT,
                    name=d['instrument_name'],
                    product=product,
                    pricetick=d['tick_size'],
                    size=d['contract_size'],
                    min_volume=d['min_trade_amount'],
                    option_strike=d['strike'],
                    option_underlying=d['base_currency'],
                    option_type=option_type,
                    option_expiry=expiry,
                    gateway_name=self.gateway_name,
                )
            
            self.gateway.on_contract(contract)

        self.query_ins_done = True

    def on_query_position(self,packet: list):
        """"""
        data = packet['result']
        for pos in data:
            position = PositionData(
                symbol=pos['instrument_name'],
                exchange=Exchange.DERIBIT,
                direction=Direction.NET,
                volume=pos['size'],
                pnl=float(pos['floating_profit_loss']),
                gateway_name=self.gateway_name,
            )
            self.gateway.on_position(position)
        
        self.query_pos_done = True

    def on_query_account(self,packet: dict):
        """"""
        data = packet['result']
        data = data['data']
        for account in data:
            Account = AccountData(
                gateway_name = self.gateway_name,
                accountid=account['address'],
                balance=account['amount'],
            )
            self.gateway.on_account(copy(Account))

        self.query_acc_done = True

    def on_cancel_order(self,packet: dict):
        """"""
        data = packet['result']
        order = OrderData(
            symbol = data['instrument_name'],
            exchange=Exchange.DERIBIT,
            type=ORDERTYPE_DERIBIT2VT[data['order_type']],
            orderid=orderid,
            direction=DIRECTION_DERIBIT2VT[data['direction']],
            price=float(data['price']),
            volume=float(data['amount']),
            traded=float(data['filled_amount']),
            time=str(datetime.fromtimestamp(data['last_update_timestamp']/1000)),
            status=STATUS_DERIBIT2VT[data['order_state']],
            gateway_name=self.gateway_name,
        )

        self.gateway.on_order(copy(order))

    def on_user_change(self,packet: dict):
        """"""
        data = packet['params']['data']

        trades = data['trades']
        positions = data['positions']
        orders = data['orders']

        if orders:
            for order in orders:
                self._on_order(order)

        if trades:
            for trade in trades:
                self._on_trade(trade,orders[0]['order_id'])

        if positions:
            for position in positions:
                self._on_position(position)          

    def _on_order(self,data: dict):
        """"""
        orderid = data['label']
        sysid = data['order_id']

        order = OrderData(
            symbol = data['instrument_name'],
            exchange=Exchange.DERIBIT,
            type=ORDERTYPE_DERIBIT2VT[data['order_type']],
            orderid=orderid,
            direction=DIRECTION_DERIBIT2VT[data['direction']],
            price=float(data['price']),
            volume=float(data['amount']),
            traded=float(data['filled_amount']),
            time=str(datetime.fromtimestamp(data['last_update_timestamp']/1000)),
            status=STATUS_DERIBIT2VT[data['order_state']],
            gateway_name=self.gateway_name,
        )

        self.gateway.on_order(copy(order))

    def _on_trade(self,data: list,orderid):
        """"""
        trade = TradeData(
            symbol=data['instrument_name'],
            exchange=Exchange.DERIBIT,
            orderid=orderid,
            tradeid=data['trade_id'],
            direction=DIRECTION_DERIBIT2VT[data['direction']],
            price=float(data['price']),
            volume=float(data['amount']),
            time=str(datetime.fromtimestamp(data['timestamp']/1000)),
            gateway_name=self.gateway_name,
            )

        self.gateway.on_trade(trade)

    def _on_position(self,data: dict):
        """"""
        pos = PositionData(
            symbol=data['instrument_name'],
            exchange=Exchange.DERIBIT,
            direction=Direction.NET,
            volume=data['size'],
            price=data['settlement_price'],
            pnl=float(data['floating_profit_loss']),
            gateway_name=self.gateway_name,
        )

        self.gateway.on_position(pos)
    
    def on_ticker(self,packet: dict):
        """"""
        data = packet['params']['data']
        symbol = data['instrument_name']
        tick = self.ticks.get(symbol,None)
        if not tick:
            return 

        tick.bid_price_1 = data['best_bid_price']
        tick.bid_volume_1 = data['best_bid_amount']
        tick.ask_price_1 = data['best_ask_price']
        tick.ask_volume_1 = data['best_ask_amount']
        tick.high_price = data['stats']['high']
        tick.low_price = data['stats']['low']
        tick.volume = data['stats']['volume']
        tick.datetime = datetime.fromtimestamp(data['timestamp']/1000)

        self.gateway.on_tick(copy(tick))
    
    def on_orderbook(self,packet: dict):
        """"""
        data = packet['params']['data']
        if 'prev_change_id' not in data.keys():
            self.on_book_snapshot(packet)
        else:
            self.on_book_change(packet)

    def on_book_snapshot(self,packet: dict):
        """"""
        ins = packet['params']['data']['instrument_name']
        asks = packet['params']['data']['asks']
        bids = packet['params']['data']['bids']

        self.asks[ins] = {}
        self.bids[ins] = {}
        Asks = self.asks[ins]
        Bids = self.bids[ins]

        for ask in asks:
            Asks[ask[1]] = ask[2]

        for bid in bids:
            Bids[bid[1]] = bid[2]
    
    def on_book_change(self,packet: dict):
        """"""
        ins = packet['params']['data']['instrument_name']
        asks = packet['params']['data']['asks']
        bids = packet['params']['data']['bids']      
        
        Asks = self.asks[ins]
        Bids = self.bids[ins]

        if(len(asks)):
            for ask in asks:
                if ask[0] == 'new':
                    Asks[ask[1]] = ask[2]
                elif ask[0] == 'delete':
                    del Asks[ask[1]]
                else:
                    Asks[ask[1]] = ask[2]

        if(len(bids)):
            for bid in bids:
                if bid[0] == 'new':
                    Bids[bid[1]] = bid[2]
                elif bid[0] == 'delete':
                    del Bids[bid[1]]
                else:
                    Bids[bid[1]] = bid[2]

        tick = self.ticks[ins]

        bids_keys = Bids.keys()
        bids_keys = sorted(bids_keys, reverse=True)
        tick.bid_price_1 = bids_keys[0]
        tick.bid_price_2 = bids_keys[1]
        tick.bid_price_3 = bids_keys[2]
        tick.bid_price_4 = bids_keys[3]
        tick.bid_price_5 = bids_keys[4]
        tick.bid_volume_1 = Bids[bids_keys[0]]
        tick.bid_volume_2 = Bids[bids_keys[1]]
        tick.bid_volume_3 = Bids[bids_keys[2]]
        tick.bid_volume_4 = Bids[bids_keys[3]]
        tick.bid_volume_5 = Bids[bids_keys[4]]

        asks_keys = Asks.keys()
        asks_keys = sorted(asks_keys)
        tick.ask_price_1 = asks_keys[0]
        tick.ask_price_2 = asks_keys[1]
        tick.ask_price_3 = asks_keys[2]
        tick.ask_price_4 = asks_keys[3]
        tick.ask_price_5 = asks_keys[4]
        tick.ask_volume_1 = Asks[asks_keys[0]]
        tick.ask_volume_2 = Asks[asks_keys[1]]
        tick.ask_volume_3 = Asks[asks_keys[2]]
        tick.ask_volume_4 = Asks[asks_keys[3]]
        tick.ask_volume_5 = Asks[asks_keys[4]]

        tick.datetime = datetime.fromtimestamp(packet['params']['data']['timestamp']/1000)

        self.gateway.on_tick(copy(tick))

    def wait_access_token(self):
        """"""
        while not self.access_token:
            sleep(0.5)
    
    def wait_instrument(self):
        """"""
        while not self.query_ins_done:
            sleep(0.5)

        self.gateway.write_log("合约信息查询成功")

    def wait_position(self):
        """"""
        while not self.query_pos_done:
            sleep(0.5)

        self.gateway.write_log("持仓查询成功")

    def wait_account(self):
        """"""
        while not self.query_acc_done:
            sleep(0.5)

        self.gateway.write_log("账户查询成功")
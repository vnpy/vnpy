import functools
import traceback

from copy import copy
from time import sleep
from pandas import DataFrame, merge
from datetime import datetime
from multiprocessing.dummy import Pool
from queue import Empty, Queue

from tigeropen.tiger_open_config import TigerOpenClientConfig
from tigeropen.common.consts import Language, Market, QuoteKeyType, SecurityType
from tigeropen.quote.quote_client import QuoteClient
from tigeropen.trade.trade_client import TradeClient
from tigeropen.trade.domain.order import OrderStatus
from tigeropen.push.push_client import PushClient
from tigeropen.common.exceptions import ApiException
from tigeropen.common.util.contract_utils import stock_contract, future_contract

from vnpy.trader.constant import Direction, Product, Status, OrderType, Exchange
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    TickData,
    OrderData,
    TradeData,
    AccountData,
    ContractData,
    PositionData,
    SubscribeRequest,
    OrderRequest,
    CancelRequest,
)

PRODUCT_VT2TIGER = {
    Product.EQUITY: "STK",
    Product.OPTION: "OPT",
    Product.WARRANT: "WAR",
    Product.WARRANT: "IOPT",
    Product.FUTURES: "FUT",
    Product.OPTION: "FOP",
    Product.FOREX: "CASH",
}

DIRECTION_VT2TIGER = {
    Direction.LONG: "BUY",
    Direction.SHORT: "SELL",
}

DIRECTION_TIGER2VT = {
    "BUY": Direction.LONG,
    "SELL": Direction.SHORT,
    "sell": Direction.SHORT,
}

ORDERTYPE_VT2TIGER = {
    OrderType.LIMIT: "LMT",
    OrderType.MARKET: "MKT",
}

STATUS_TIGER2VT = {
    OrderStatus.PENDING_NEW: Status.SUBMITTING,
    OrderStatus.NEW: Status.SUBMITTING,
    OrderStatus.HELD: Status.SUBMITTING,
    OrderStatus.PARTIALLY_FILLED: Status.PARTTRADED,
    OrderStatus.FILLED: Status.ALLTRADED,
    OrderStatus.CANCELLED: Status.CANCELLED,
    OrderStatus.PENDING_CANCEL: Status.CANCELLED,
    OrderStatus.REJECTED: Status.REJECTED,
    OrderStatus.EXPIRED: Status.REJECTED
}


class TigerGateway(BaseGateway):
    """"""
    default_setting = {
        "tiger_id": "",
        "account": "",
        "服务器": ["标准", "环球", "仿真"],
        "private_key": "",
    }
    # 在 VNTRADER 中展示的交易所列表
    exchanges = [
        Exchange.SEHK,
        Exchange.SMART,
        Exchange.SSE,
        Exchange.SZSE,
        Exchange.CFE,
        Exchange.ECBOT,
        Exchange.CMECRYPTO,
        Exchange.CFE,
        Exchange.GLOBEX,
        Exchange.NYMEX,
        Exchange.SGX,
        Exchange.HKFE
    ]

    def __init__(self, event_engine):
        """Constructor"""
        super(TigerGateway, self).__init__(event_engine, "TIGER")

        self.tiger_id = ""
        self.account = ""
        self.server = ""
        self.language = ""

        self.client_config = None
        self.quote_client = None
        self.push_client = None

        self.local_id = 1000000
        self.tradeid = 0

        self.active = False
        self.queue = Queue()
        self.pool = None

        self.ID_TIGER2VT = {}
        self.ID_VT2TIGER = {}
        self.ticks = {}
        self.trades = set()
        self.contracts = {}
        self.symbol_names = {}
        self.vt_tiger_symbol_map = {}

        self.push_connected = False
        self.subscribed_symbols = set()

    def run(self):
        """"""
        while self.active:
            try:
                func, args = self.queue.get(timeout=0.1)
                func(*args)
            except Empty:
                pass
            except Exception:
                self.write_log('方法%s调用失败，参数为%s' % (func.__name__, args))

    def add_task(self, func, *args):
        """"""
        self.queue.put((func, [*args]))

    def connect(self, setting: dict):
        """"""
        self.private_key = setting["private_key"]
        self.tiger_id = setting["tiger_id"]
        self.server = setting["服务器"]
        self.account = setting["account"]
        self.languege = Language.zh_CN

        # Start thread pool for REST call
        self.active = True
        self.pool = Pool(5)
        self.pool.apply_async(self.run)

        # Put connect task into quque.
        self.init_client_config()
        self.add_task(self.connect_quote)
        self.add_task(self.connect_trade)
        self.add_task(self.connect_push)

    def init_client_config(self):
        """"""
        self.client_config = TigerOpenClientConfig(sandbox_debug=False)
        self.client_config.private_key = self.private_key
        self.client_config.tiger_id = self.tiger_id
        self.client_config.account = self.account
        self.client_config.language = self.language

    def connect_quote(self):
        """
        Connect to market data server.
        """
        try:
            self.quote_client = QuoteClient(self.client_config)
            self.symbol_names = dict(
                self.quote_client.get_symbol_names(lang=Language.zh_CN))
            self.query_contract()
        except ApiException:
            self.write_log("查询合约失败")
            return

        self.write_log("行情接口连接成功")

    def connect_trade(self):
        """
        Connect to trade server.
        """
        self.write_log('查询交易接口')
        self.trade_client = TradeClient(self.client_config)
        try:
            self.add_task(self.query_order)
            self.add_task(self.query_position)
            self.add_task(self.query_account)
        except ApiException:
            self.write_log("交易接口连接失败")
            return

        self.write_log("交易接口连接成功")

    def connect_push(self):
        """
        Connect to push server.
        """
        protocol, host, port = self.client_config.socket_host_port
        self.push_client = PushClient(host, port, (protocol == "ssl"))

        self.push_client.quote_changed = self.on_quote_change
        self.push_client.asset_changed = self.on_asset_change
        self.push_client.position_changed = self.on_position_change
        self.push_client.order_changed = self.on_order_change
        self.push_client.connect_callback = self.on_push_connected
        self.push_client.disconnect_callback = self.on_disconnected

        self.push_client.connect(
            self.client_config.tiger_id, self.client_config.private_key)

    def subscribe(self, req: SubscribeRequest):
        """"""
        self.subscribed_symbols.add(req.symbol)

        if self.push_connected:
            self.push_client.subscribe_quote(
                symbols=[req.symbol], quote_key_type=QuoteKeyType.ALL)

    def on_push_connected(self):
        """"""
        self.push_connected = True
        self.write_log("推送接口连接成功")

        self.push_client.subscribe_asset(account=self.account)
        self.push_client.subscribe_position(account=self.account)
        self.push_client.subscribe_order(account=self.account)

        self.push_client.subscribe_quote(list(self.subscribed_symbols))

    def on_disconnected(self):
        self.write_log('推送接口断开链接')
        self.push_connected = False

    def on_quote_change(self, tiger_symbol: str, data: list, trading: bool):
        """"""
        data = dict(data)
        symbol, exchange = self.get_vt_symbol_exchange(tiger_symbol)

        # 如果只推送了时间戳，或只推送了 timeline，不向策略中推送新的tick事件
        if 'latest_price' not in data and 'bid_price' not in data.keys():
            return

        tick = self.ticks.get(symbol, None)
        if not tick:
            tick = TickData(
                symbol=symbol,
                exchange=exchange,
                gateway_name=self.gateway_name,
                datetime=datetime.now(),
                name=symbol,
            )
            self.ticks[symbol] = tick
        # 本地止损单的设计依赖于 limit up 与limit down（张跌停价格）。目前 TIGEROPEN 中没有提供。
        # 所以这里用 high low 来代替 limit up 与 limit down
        tick.datetime = datetime.fromtimestamp(int(data["timestamp"]) / 1000)
        tick.volume = data.get("volume", tick.volume)
        tick.ask_volume_1 = data.get("ask_size", tick.ask_volume_1)
        tick.bid_volume_1 = data.get("bid_size", tick.bid_volume_1)
        tick.pre_close = data.get("prev_close", tick.pre_close)
        tick.last_price = data.get("latest_price", tick.last_price)
        tick.open_price = data.get("open", tick.open_price)
        tick.high_price = data.get("high", tick.high_price)
        tick.low_price = data.get("low", tick.low_price)
        tick.ask_price_1 = data.get("ask_price", tick.ask_price_1)
        tick.bid_price_1 = data.get("bid_price", tick.bid_price_1)
        tick.limit_down = tick.low_price
        tick.limit_up = tick.high_price

        self.on_tick(copy(tick))

    def on_asset_change(self, tiger_account: str, data: list):
        """"""
        data = dict(data)
        if "net_liquidation" not in data:
            return
        segment = data.get('segment')
        # 环球账户， 只推送summary的信息，含股票期货
        if segment == 'summary' or segment is None:
            account = tiger_account
        # 标准账户有『子账户』的概念， 分别推送股票与期货账户的信息
        elif segment == 'S':
            account = 'Security'
        elif segment == 'C':
            account = 'Commodity'

        account = AccountData(
            accountid=account,
            balance=round(data["net_liquidation"], 2),
            frozen=0.0,
            gateway_name=self.gateway_name,
        )
        self.on_account(account)

    def on_position_change(self, tiger_account: str, data: list):
        """"""
        if tiger_account != self.account:
            return
        data = dict(data)
        symbol = data.get('identifier')
        symbol, exchange = self.get_vt_symbol_exchange(symbol)

        pos = PositionData(
            symbol=symbol,
            exchange=exchange,
            direction=Direction.NET,
            volume=int(data["quantity"]),
            frozen=0.0,
            price=round(data["average_cost"], 2),
            pnl=round(data["unrealized_pnl"], 2),
            gateway_name=self.gateway_name,
        )
        self.on_position(pos)

    def on_order_change(self, tiger_account: str, data: list):
        """"""
        # 处理订阅了多个账户的情况
        if tiger_account != self.account:
            return
        data = dict(data)
        symbol = data.get('identifier')
        symbol, exchange = self.get_vt_symbol_exchange(symbol)
        status = STATUS_TIGER2VT[data["status"]]
        order_time = data.get('order_time')
        order = OrderData(
            symbol=symbol,
            exchange=exchange,
            orderid=self.ID_TIGER2VT.get(
                str(data["id"]), self.get_new_local_id()),
            direction=DIRECTION_TIGER2VT[data.get('action')],
            price=data.get("limit_price", 0),
            volume=data["quantity"],
            traded=data["filled"],
            status=status,
            time=datetime.fromtimestamp(
                order_time / 1000).strftime("%H:%M:%S") if order_time else datetime.now().strftime("%H:%M:%S"),
            gateway_name=self.gateway_name,
        )
        self.ID_TIGER2VT[str(data["id"])] = order.orderid
        self.on_order(order)

        if status == Status.ALLTRADED:
            self.tradeid += 1

            trade = TradeData(
                symbol=symbol,
                exchange=exchange,
                direction=DIRECTION_TIGER2VT[data.get('action')],
                tradeid=self.tradeid,
                orderid=self.ID_TIGER2VT[str(data["id"])],
                price=data["avg_fill_price"],
                volume=data["filled"],
                time=datetime.fromtimestamp(
                    order_time / 1000).strftime("%H:%M:%S") if order_time else datetime.now().strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            self.on_trade(trade)

    def get_new_local_id(self):
        self.local_id += 1
        return self.local_id

    def send_order(self, req: OrderRequest):
        """"""
        local_id = self.get_new_local_id()
        order = req.create_order_data(local_id, self.gateway_name)

        self.on_order(order)
        self.add_task(self._send_order, req, local_id)
        return order.vt_orderid

    def _send_order(self, req: OrderRequest, local_id):
        """"""
        try:  # 主要处理一些API层面的校验带来的异常，如下单价格错误。
            contract = self.get_trading_contract(req.symbol)
            order = self.trade_client.create_order(
                account=self.account,
                contract=contract,
                action=DIRECTION_VT2TIGER[req.direction],
                order_type=ORDERTYPE_VT2TIGER[req.type],
                quantity=int(req.volume),
                limit_price=round(req.price, 2),
            )

            self.trade_client.place_order(order)
            self.ID_TIGER2VT[str(order.id)] = local_id
            self.ID_VT2TIGER[local_id] = str(order.id)
        except Exception:
            # 一些订单会在API层面被拒掉，不会推送订单的回报，这里模拟一个订单回报。
            # 目前 gateway 只实现了 mkt 和 limit 两种类型的订单，使用其他类型的订单也会出现异常。
            # 这时本地的订单已经存在了， 所以返回一个状态为rejected的虚拟订单
            symbol, exchange = self.get_vt_symbol_exchange(req.symbol)

            mock_order = OrderData(
                symbol=symbol,
                exchange=exchange,
                orderid=local_id,
                direction=DIRECTION_TIGER2VT[order.action],
                price=order.limit_price,
                volume=order.quantity,
                traded=0,
                status=Status.REJECTED,
                time=datetime.now().strftime("%H:%M:%S"),
                gateway_name=self.gateway_name,
            )
            self.on_order(mock_order)
            self.write_log("发单失败")
            traceback.print_exc()

    def cancel_order(self, req: CancelRequest):
        """"""
        self.add_task(self._cancel_order, req)

    def _cancel_order(self, req: CancelRequest):
        """"""
        try:
            id = self.ID_VT2TIGER[req.orderid]
            data = self.trade_client.cancel_order(id=id)
            if not data:
                self.write_log("撤单成功")
        except ApiException:
            self.write_log(f"撤单请求提交失败：{req.orderid}")
            traceback.print_exc()
        except Exception:
            self.write_log('撤单失败，id:%s' % (req.orderid))

    def query_contract(self):
        """"""
        self.write_log('开始查询合约信息')
        # HK Stock
        try:
            symbols_names_HK = self.quote_client.get_symbol_names(
                lang=Language.zh_CN, market=Market.HK)
            contract_names_HK = DataFrame(
                symbols_names_HK, columns=["symbol", "name"])

            contractList = list(contract_names_HK["symbol"])
            i, n = 0, len(contractList)
            result = DataFrame()
            while i < n:
                i += 50
                c = contractList[i - 50:i]
                r = self.quote_client.get_trade_metas(c)
                result = result.append(r)
            self.write_log(f'港股的合约数量： {len(symbols_names_HK)}')
        except:
            self.write_log('查询港股合约失败')

        contract_detail_HK = result.sort_values(by="symbol", ascending=True)
        contract_HK = merge(
            contract_names_HK, contract_detail_HK, how="left", on="symbol")

        for ix, row in contract_HK.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SEHK,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                min_volume=row["lot_size"],
                pricetick=row["min_tick"],
                net_position=True,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.contracts[contract.vt_symbol] = contract
            self.vt_tiger_symbol_map.update(
                {contract.symbol: (Exchange.SEHK, stock_contract(contract.symbol, currency='HKD'))})
        self.write_log('初始化港股合约完成')

        # US Stock
        symbols_names_US = self.quote_client.get_symbol_names(
            lang=Language.zh_CN, market=Market.US)
        contract_US = DataFrame(symbols_names_US, columns=["symbol", "name"])

        for ix, row in contract_US.iterrows():
            contract = ContractData(
                symbol=row["symbol"],
                exchange=Exchange.SMART,
                name=row["name"],
                product=Product.EQUITY,
                size=1,
                min_volume=1,
                pricetick=0.001,
                gateway_name=self.gateway_name,
            )
            self.on_contract(contract)
            self.vt_tiger_symbol_map.update(
                {contract.symbol: (Exchange.SMART, stock_contract(
                    contract.symbol, currency='USD'))}
            )
            self.contracts[contract.vt_symbol] = contract
        self.write_log('初始化美股合约完成')

        # Future contracts
        exchanges = self.quote_client.get_future_exchanges(
            sec_type=SecurityType.FUT, lang=Language.zh_CN)
        exchanges_list = exchanges['code']
        contract_futures = DataFrame()
        for e in exchanges_list:
            exchange_contract = self.quote_client.get_future_contracts(
                e, lang=Language.zh_CN)
            if len(exchange_contract) != 0:
                contract_futures = contract_futures.append(exchange_contract)

        for ix, row in contract_futures.iterrows():
            contract = ContractData(
                symbol=row.loc['contract_code'],
                exchange=Exchange(row.loc['exchange']),
                name=row.loc['name'],
                product=Product.FUTURES,
                size=1,
                min_volume=1,
                pricetick=0.001,
                gateway_name=self.gateway_name
            )
            self.on_contract(contract)
            self.vt_tiger_symbol_map.update(
                {contract.symbol: (contract.exchange,
                                   future_contract(
                                       symbol=row.type,
                                       currency=row.currency,
                                       expiry=row.last_trading_date,
                                       exchange=row.exchange,
                                       multiplier=row.multiplier,
                                   ))}
            )
            self.contracts[contract.vt_symbol] = contract
        self.write_log('初始化期货合约完成')

    def query_account(self):
        self.write_log('开始查询账户信息')
        try:
            assets = self.trade_client.get_assets(segment=True)
        except ApiException:
            self.write_log("查询资金失败")
            return

        for i in assets:
            account = AccountData(
                accountid=self.account,
                balance=round(i.summary.net_liquidation, 2),
                frozen=0.0,
                gateway_name=self.gateway_name,
            )
            # 下面两个账户仅作 vntrader 展示使用。
            # 环球账户的资产信息可以通过 summary 获取，标准账户需要区分股票和期货Segment， 且没有合并的summary信息。
            sec_account = AccountData(
                accountid='Security',
                balance=round(i.segments.get('S').net_liquidation, 2),
                frozen=0.0,
                gateway_name=self.gateway_name,
            )

            com_account = AccountData(
                accountid='Commodity',
                balance=round(i.segments.get('C').net_liquidation, 2),
                frozen=0.0,
                gateway_name=self.gateway_name,
            )

            self.on_account(account)
            self.on_account(sec_account)
            self.on_account(com_account)
        self.write_log('账户信息查询完成')

    def query_position(self):
        """"""
        self.write_log('开始查询持仓信息')
        try:
            # 分别查询股票和期货的持仓
            stock_position = self.trade_client.get_positions(
                sec_type=SecurityType.STK)
            future_position = self.trade_client.get_positions(
                sec_type=SecurityType.FUT)
            positions = stock_position + future_position

        except ApiException:
            self.write_log("查询持仓失败")
            return

        for i in positions:
            try:
                symbol, exchange = self.get_vt_symbol_exchange(
                    i.contract.identifier)

                pos = PositionData(
                    symbol=symbol,
                    exchange=exchange,
                    direction=Direction.NET,
                    volume=int(i.quantity),
                    frozen=0.0,
                    price=i.average_cost,
                    pnl=float(i.unrealized_pnl),
                    gateway_name=self.gateway_name,
                )

                self.on_position(pos)
            except:
                self.write_log('处理持仓失败，symbol: %s' % (i.contract.identifier))
        self.write_log('持仓信息查询完成')

    def query_order(self):
        self.write_log('开始查询历史订单信息')
        try:
            # 需要分别查询股票和期货的订单
            stock_data = self.trade_client.get_orders(
                account=self.account, sec_type=SecurityType.STK)
            future_data = self.trade_client.get_orders(
                account=self.account, sec_type=SecurityType.FUT)
            data = stock_data + future_data
            data = sorted(data, key=lambda x: x.order_time, reverse=False)
        except:
            traceback.print_exc()
            self.write_log("查询订单失败")
            return

        self.process_order(data)
        self.process_deal(data)
        self.write_log('历史订单处理完成')

    def close(self):
        """"""
        self.active = False

        if self.push_client:
            # 退出前先进行退订操作，避免下次打开时的订阅异常
            try:
                self.push_client.unsubscribe_asset()
                self.push_client.unsubscribe_position()
                self.push_client.unsubscribe_order()
                self.push_client.unsubscribe_quote(
                    symbols=self.subscribed_symbols)
                self.push_client.disconnect()
            except:
                pass

    def process_order(self, data):
        """"""
        for i in data:
            try:
                symbol = i.contract.identifier
                symbol, exchange = self.get_vt_symbol_exchange(symbol)
                local_id = self.get_new_local_id()

                order = OrderData(
                    symbol=symbol,
                    exchange=exchange,
                    orderid=local_id,
                    direction=DIRECTION_TIGER2VT[i.action],
                    price=i.limit_price if i.limit_price else 0.0,
                    volume=i.quantity,
                    traded=i.filled,
                    status=STATUS_TIGER2VT[i.status],
                    time=datetime.fromtimestamp(
                        i.order_time / 1000).strftime("%H:%M:%S"),
                    gateway_name=self.gateway_name,
                )
                self.ID_TIGER2VT[str(i.id)] = local_id
                self.on_order(order)
            except:
                pass

        self.ID_VT2TIGER = {v: k for k, v in self.ID_TIGER2VT.items()}

    def process_deal(self, data):
        """
        Process trade data for both query and update.
        """
        for i in data:
            if i.status == OrderStatus.PARTIALLY_FILLED or i.status == OrderStatus.FILLED:
                try:
                    # symbol = contract2symbol(i.contract)
                    symbol = i.contract.identifier
                    symbol, exchange = self.get_vt_symbol_exchange(symbol)
                    self.tradeid += 1

                    trade = TradeData(
                        symbol=symbol,
                        exchange=exchange,
                        direction=DIRECTION_TIGER2VT[i.action],
                        tradeid=self.tradeid,
                        orderid=self.ID_TIGER2VT[str(i.id)],
                        price=i.avg_fill_price,
                        volume=i.filled,
                        time=datetime.fromtimestamp(
                            i.trade_time / 1000).strftime("%H:%M:%S"),
                        gateway_name=self.gateway_name,
                    )

                    self.on_trade(trade)
                except:
                    pass

    def get_vt_symbol_exchange(self, symbol):
        try:
            exchange = self.vt_tiger_symbol_map.get(symbol)[0]
        except:
            self.write_log('can not get symbol %s' % (symbol))
        return symbol, exchange

    def get_trading_contract(self, symbol):
        try:
            return self.vt_tiger_symbol_map.get(symbol)[1]
        except:
            self.write_log(
                'cannot get traidng contract for symbol %s' % (symbol))

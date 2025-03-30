# encoding: UTF-8
import time
import logging
from typing import Optional
from vnpy.event.engine import EVENT_TIMER, Event
from vnpy.trader.constant import Status
from vnpy.trader.engine import BaseEngine
from vnpy.trader.event import EVENT_ACCOUNT, EVENT_BAR, EVENT_ORDER, EVENT_TRADE
from vnpy.trader.object import AccountData, CancelRequest, ContractData, OrderData, OrderRequest, TradeData
from vnpy.trader.constant import Direction, Exchange, Interval, Offset, Status, Product, OptionType, OrderType
from pathlib import Path
from vnpy.trader.app import BaseApp

class SimpleOrderStrategyEngine(BaseEngine):
    setting_filename = "gateway_test_setting.json"
    gateway_name = "BINANCE_SPOT"
    reference = "test"
    engine_name = "SimpleOrderStrategyEngine"

    def __init__(self, main_engine, event_engine):
        """"""
        super().__init__(main_engine, event_engine, engine_name=self.engine_name)

        self.trades = {}
        self.accounts = {}
        self.orders = {}

    def init_engine(self):
        self.register_event()

    def register_event(self):
        self.event_engine.register(EVENT_TRADE, self.on_trade)
        self.event_engine.register(EVENT_ACCOUNT, self.on_account)
        self.event_engine.register(EVENT_ORDER, self.on_order)

    def place_order(self,
                    quote_asset: str,
                    base_asset: str,
                    direction,
                    price: float,
                    type,
                    volume: float
                    ):
        assert volume > 0, "Order volume must be positive"

        symbol = quote_asset + base_asset
        order_req = OrderRequest(
            symbol=symbol,
            exchange=Exchange.BINANCE,
            direction=direction,
            type=type,
            price=price,
            volume=volume,
            reference=self.reference
        )
        vt_order_id = self.main_engine.send_order(order_req, gateway_name=self.gateway_name)

        self.orders[vt_order_id] = None

        vt_account_id = f"{self.gateway_name}.{quote_asset.upper()}"
        if vt_account_id not in self.accounts:
            self.accounts[vt_account_id] = None

        self.write_log(f"Placed order: {vt_order_id}")

        return vt_order_id

    def cancel_order(self, vt_order_id: str):
        order = self.orders.get(vt_order_id)
        if order:
            cancel_req = CancelRequest(orderid=order.orderid, symbol=order.symbol, exchange=order.exchange)
            self.main_engine.cancel_order(cancel_req, gateway_name=self.gateway_name)
            self.write_log(f"Cancel request sent for order: {vt_order_id}")
        else:
            self.write_log(f"Order {vt_order_id} not found for cancellation.", level=logging.WARNING)

    def test_impossible_order_and_cancel(self):
        # Step 1: Place an order at an impossible price
        vt_order_id = self.place_order(
            quote_asset="eth",
            base_asset="usdt",
            direction=Direction.LONG,
            price=1900,
            type=OrderType.LIMIT,
            volume=0.01
        )

        time.sleep(10)  # Wait for order to be processed

        # Step 2: Check if the order is active
        order: OrderData = self.orders[vt_order_id]
        assert order is not None, f"Order {vt_order_id} not found"
        assert order.status == Status.NOTTRADED, f"Expected NOTTRADED, got {order.status}"

        self.write_log(f"Test: Order {order.symbol} is still active at {order.price}.")

        # Step 3: Cancel the order
        self.cancel_order(vt_order_id)

        time.sleep(5)  # Wait for order to be processed

        # Step 4: Check if the order is cancelled

        order = self.orders[vt_order_id]

        assert order.status == Status.CANCELLED, f"Expected CANCELLED, got {order.status}"

        self.write_log(f"Test: Order {order.symbol} was successfully cancelled.")

    def test_full_trade_cycle(self):
        # Step 1: Place a limit order near market price to increase chance of execution
        vt_order_id_long = self.place_order(
            quote_asset="eth",
            base_asset="usdt",
            price=0,
            volume=0.005,
            direction=Direction.LONG,
            type=OrderType.MARKET,

        )

        vt_account_id = f"{self.gateway_name}.ETH"

        time.sleep(5)

        account: AccountData = self.accounts[vt_account_id]
        assert account is not None, f"Account {vt_account_id} not found"

        # Step 2: Wait and check if the order gets executed

        assert account.balance > 0, "Market order is unfilled"

        # Step 3: Place a sell order
        print("account.balance",account.balance)
        vt_order_id_short = self.place_order(
            quote_asset="eth",
            base_asset="usdt",
            direction=Direction.SHORT,
            price=0,
            type=OrderType.MARKET,
            volume=account.balance
        )

        time.sleep(5)

        # Step 4: Wait and check if the sell order gets executed
        account: AccountData = self.accounts[vt_account_id]
        assert account is not None, f"Account {vt_account_id} not found after sell"
        assert account.balance <= 0.001, "Sell order is not executed"

    def on_order(self, event: Event):
        order = event.data

        if order.reference == self.reference:
            self.orders[order.vt_orderid] = order

    def on_trade(self, event: Event):
        trade = event.data

        if trade.vt_orderid in self.orders:
            self.trades[trade.vt_tradeid] = trade

    def on_account(self, event: Event):
        account = event.data

        if account.vt_accountid in self.accounts:
            self.accounts[account.vt_accountid] = account

    def write_log(self, msg: str, level=logging.INFO) -> None:
        """输出日志"""
        self.main_engine.write_log(msg, source='TEST_ENGINE', level=level)

    def run_all_tests(self):
        # self.write_log("Running test: test_impossible_order_and_cancel")
        # self.test_impossible_order_and_cancel()
        self.write_log("Running test: test_full_trade_cycle")
        self.test_full_trade_cycle()
        self.write_log("All tests completed successfully.")

class SimpleOrderStrategyApp(BaseApp):
    """"""
    app_name = 'SimpleOrderStrategyApp'
    # app_module = __module__
    app_module = None
    app_path = Path(__file__).parent
    display_name = "下单策略测试引擎"
    engine_class = SimpleOrderStrategyEngine
    widget_name = "SimpleOrderStrategy"
    # icon_name = "recorder.ico"

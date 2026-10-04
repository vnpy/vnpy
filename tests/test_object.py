from datetime import datetime

from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product, Status
from vnpy.trader.object import (
    AccountData,
    BarData,
    CancelRequest,
    ContractData,
    HistoryRequest,
    OrderData,
    OrderRequest,
    PositionData,
    QuoteData,
    QuoteRequest,
    SubscribeRequest,
    TickData,
    TradeData,
)


def test_vt_symbol_joins_symbol_and_exchange() -> None:
    moment: datetime = datetime(2024, 1, 2, 9, 0)
    tick: TickData = TickData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        datetime=moment,
    )
    bar: BarData = BarData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        datetime=moment,
    )
    contract: ContractData = ContractData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        name="rb",
        product=Product.FUTURES,
        size=10,
        pricetick=1,
    )
    subscribe: SubscribeRequest = SubscribeRequest(symbol="rb2410", exchange=Exchange.SHFE)
    cancel: CancelRequest = CancelRequest(orderid="1001", symbol="rb2410", exchange=Exchange.SHFE)
    history: HistoryRequest = HistoryRequest(
        symbol="rb2410",
        exchange=Exchange.SHFE,
        start=moment,
    )

    assert tick.vt_symbol == "rb2410.SHFE"
    assert bar.vt_symbol == "rb2410.SHFE"
    assert contract.vt_symbol == "rb2410.SHFE"
    assert subscribe.vt_symbol == "rb2410.SHFE"
    assert cancel.vt_symbol == "rb2410.SHFE"
    assert history.vt_symbol == "rb2410.SHFE"


def test_order_request_builds_order_identity() -> None:
    request: OrderRequest = OrderRequest(
        symbol="rb2410",
        exchange=Exchange.SHFE,
        direction=Direction.LONG,
        type=OrderType.LIMIT,
        volume=2,
        price=3500,
        offset=Offset.OPEN,
    )
    order: OrderData = request.create_order_data("1001", "CTP")
    cancel: CancelRequest = order.create_cancel_request()

    assert request.vt_symbol == "rb2410.SHFE"
    assert order.gateway_name == "CTP"
    assert order.orderid == "1001"
    assert order.vt_symbol == "rb2410.SHFE"
    assert order.vt_orderid == "CTP.1001"
    assert order.direction == Direction.LONG
    assert order.offset == Offset.OPEN
    assert order.volume == 2
    assert cancel.orderid == "1001"
    assert cancel.symbol == "rb2410"
    assert cancel.exchange == Exchange.SHFE
    assert cancel.vt_symbol == "rb2410.SHFE"


def test_trade_and_quote_ids_include_gateway() -> None:
    trade: TradeData = TradeData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        orderid="1001",
        tradeid="9",
        direction=Direction.LONG,
    )
    quote: QuoteData = QuoteData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        quoteid="q1",
    )
    quote_request: QuoteRequest = QuoteRequest(
        symbol="rb2410",
        exchange=Exchange.SHFE,
        bid_price=3499,
        bid_volume=1,
        ask_price=3501,
        ask_volume=1,
    )
    created: QuoteData = quote_request.create_quote_data("q1", "CTP")

    assert trade.vt_symbol == "rb2410.SHFE"
    assert trade.vt_orderid == "CTP.1001"
    assert trade.vt_tradeid == "CTP.9"
    assert quote.vt_symbol == "rb2410.SHFE"
    assert quote.vt_quoteid == "CTP.q1"
    assert quote_request.vt_symbol == "rb2410.SHFE"
    assert created.vt_quoteid == "CTP.q1"
    assert created.vt_symbol == "rb2410.SHFE"


def test_position_and_account_ids() -> None:
    position: PositionData = PositionData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        direction=Direction.SHORT,
    )
    account: AccountData = AccountData(
        gateway_name="CTP",
        accountid="acc",
        balance=1000,
        frozen=100,
    )

    assert position.vt_symbol == "rb2410.SHFE"
    assert position.vt_positionid == f"CTP.rb2410.SHFE.{Direction.SHORT.value}"
    assert account.vt_accountid == "CTP.acc"
    assert account.available == 900


def test_order_is_active_for_working_statuses() -> None:
    order: OrderData = OrderData(
        gateway_name="CTP",
        symbol="rb2410",
        exchange=Exchange.SHFE,
        orderid="1001",
        status=Status.SUBMITTING,
    )

    assert order.is_active()
    order.status = Status.NOTTRADED
    assert order.is_active()
    order.status = Status.PARTTRADED
    assert order.is_active()
    order.status = Status.ALLTRADED
    assert not order.is_active()
    order.status = Status.CANCELLED
    assert not order.is_active()
    order.status = Status.REJECTED
    assert not order.is_active()

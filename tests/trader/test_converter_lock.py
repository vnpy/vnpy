from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product
from vnpy.trader.converter import PositionHolding
from vnpy.trader.object import ContractData, OrderRequest, PositionData


def make_holding(exchange: Exchange) -> PositionHolding:
    """Create a PositionHolding for the given exchange."""
    contract = ContractData(
        gateway_name="CTP",
        symbol="IF2609",
        exchange=exchange,
        name="IF2609",
        product=Product.FUTURES,
        size=300,
        pricetick=0.2,
    )
    return PositionHolding(contract)


def make_close_request(exchange: Exchange, volume: float) -> OrderRequest:
    """Create a short close order request."""
    return OrderRequest(
        symbol="IF2609",
        exchange=exchange,
        direction=Direction.SHORT,
        type=OrderType.LIMIT,
        volume=volume,
        offset=Offset.CLOSE,
    )


def test_lock_close_with_td_and_yd_available() -> None:
    """Close request should close available yesterday position instead of opening."""
    holding = make_holding(Exchange.CFFEX)
    holding.update_position(PositionData(
        gateway_name="CTP",
        symbol="IF2609",
        exchange=Exchange.CFFEX,
        direction=Direction.LONG,
        volume=10,
        yd_volume=5,
    ))

    converted = holding.convert_order_request_lock(make_close_request(Exchange.CFFEX, 5))

    assert len(converted) == 1
    assert converted[0].offset == Offset.CLOSE
    assert converted[0].volume == 5


def test_lock_close_with_td_only() -> None:
    """Close request should be converted to open when only today position exists."""
    holding = make_holding(Exchange.CFFEX)
    holding.update_position(PositionData(
        gateway_name="CTP",
        symbol="IF2609",
        exchange=Exchange.CFFEX,
        direction=Direction.LONG,
        volume=5,
        yd_volume=0,
    ))

    converted = holding.convert_order_request_lock(make_close_request(Exchange.CFFEX, 5))

    assert len(converted) == 1
    assert converted[0].offset == Offset.OPEN
    assert converted[0].volume == 5


def test_lock_close_with_td_and_yd_partial() -> None:
    """Close request larger than yesterday position should close then open remainder."""
    holding = make_holding(Exchange.CFFEX)
    holding.update_position(PositionData(
        gateway_name="CTP",
        symbol="IF2609",
        exchange=Exchange.CFFEX,
        direction=Direction.LONG,
        volume=15,
        yd_volume=10,
    ))

    converted = holding.convert_order_request_lock(make_close_request(Exchange.CFFEX, 12))

    assert len(converted) == 2
    assert converted[0].offset == Offset.CLOSE
    assert converted[0].volume == 10
    assert converted[1].offset == Offset.OPEN
    assert converted[1].volume == 2


def test_lock_close_shfe_uses_close_yesterday() -> None:
    """SHFE lock close should keep using CLOSEYESTERDAY for yesterday position."""
    holding = make_holding(Exchange.SHFE)
    holding.update_position(PositionData(
        gateway_name="CTP",
        symbol="rb2610",
        exchange=Exchange.SHFE,
        direction=Direction.LONG,
        volume=10,
        yd_volume=5,
    ))

    converted = holding.convert_order_request_lock(make_close_request(Exchange.SHFE, 5))

    assert len(converted) == 1
    assert converted[0].offset == Offset.CLOSEYESTERDAY
    assert converted[0].volume == 5

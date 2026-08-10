import pytest

from vnpy.trader.constant import (
    Direction,
    Exchange,
    Offset,
    OrderType,
    Product,
    Status,
)
from vnpy.trader.converter import PositionHolding
from vnpy.trader.object import ContractData, OrderData, OrderRequest, PositionData


def create_holding() -> PositionHolding:
    contract = ContractData(
        gateway_name="CTP",
        symbol="rb",
        exchange=Exchange.SHFE,
        name="Rebar",
        product=Product.FUTURES,
        size=10,
        pricetick=1,
    )
    return PositionHolding(contract)


def create_close_order(
    direction: Direction,
    volume: float,
    traded: float = 0,
) -> OrderData:
    return OrderData(
        gateway_name="CTP",
        symbol="rb",
        exchange=Exchange.SHFE,
        orderid="1",
        direction=direction,
        offset=Offset.CLOSETODAY,
        type=OrderType.LIMIT,
        volume=volume,
        traded=traded,
        status=Status.PARTTRADED if traded > 0 else Status.NOTTRADED,
    )


def create_position(direction: Direction, volume: float) -> PositionData:
    return PositionData(
        gateway_name="CTP",
        symbol="rb",
        exchange=Exchange.SHFE,
        direction=direction,
        volume=volume,
        yd_volume=0,
    )


@pytest.mark.parametrize(
    ("position_direction", "order_direction", "td_frozen", "pos_frozen"),
    [
        (Direction.LONG, Direction.SHORT, "long_td_frozen", "long_pos_frozen"),
        (Direction.SHORT, Direction.LONG, "short_td_frozen", "short_pos_frozen"),
    ],
)
def test_position_update_recalculates_frozen_for_existing_order(
    position_direction: Direction,
    order_direction: Direction,
    td_frozen: str,
    pos_frozen: str,
) -> None:
    holding = create_holding()
    order = create_close_order(order_direction, volume=5, traded=2)

    holding.update_order(order)
    holding.update_position(create_position(position_direction, volume=5))

    assert len(holding.active_orders) == 1
    assert getattr(holding, td_frozen) == 3
    assert getattr(holding, pos_frozen) == 3


def test_position_update_caps_frozen_at_reduced_position() -> None:
    holding = create_holding()
    holding.update_position(create_position(Direction.LONG, volume=10))
    holding.update_order(create_close_order(Direction.SHORT, volume=8))

    holding.update_position(create_position(Direction.LONG, volume=5))

    assert holding.long_td_frozen == 5
    assert holding.long_pos_frozen == 5


def test_shfe_fully_frozen_position_rejects_additional_close() -> None:
    holding = create_holding()
    holding.update_order(create_close_order(Direction.SHORT, volume=5))
    holding.update_position(create_position(Direction.LONG, volume=5))
    request = OrderRequest(
        symbol="rb",
        exchange=Exchange.SHFE,
        direction=Direction.SHORT,
        type=OrderType.LIMIT,
        volume=5,
        offset=Offset.CLOSE,
    )

    converted = holding.convert_order_request_shfe(request)

    assert holding.long_pos_frozen == holding.long_pos == 5
    assert converted == []

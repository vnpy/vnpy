from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product
from vnpy.trader.converter import OffsetConverter, PositionHolding
from vnpy.trader.object import ContractData, OrderRequest


class ContractBook:
    def __init__(self, contract: ContractData | None) -> None:
        self.contract: ContractData | None = contract

    def get_contract(self, vt_symbol: str) -> ContractData | None:
        if self.contract is not None and vt_symbol == self.contract.vt_symbol:
            return self.contract
        return None


def make_contract(exchange: Exchange, net_position: bool = False) -> ContractData:
    return ContractData(
        gateway_name="FAKE",
        symbol="rb2410",
        exchange=exchange,
        name="rb",
        product=Product.FUTURES,
        size=10,
        pricetick=1,
        net_position=net_position,
    )


def make_request(
    exchange: Exchange,
    direction: Direction,
    volume: float,
    offset: Offset = Offset.CLOSE,
) -> OrderRequest:
    return OrderRequest(
        symbol="rb2410",
        exchange=exchange,
        direction=direction,
        type=OrderType.LIMIT,
        volume=volume,
        price=3500,
        offset=offset,
    )


def shfe_converter(
    today: float,
    yesterday: float,
    today_frozen: float = 0,
    yesterday_frozen: float = 0,
) -> OffsetConverter:
    contract: ContractData = make_contract(Exchange.SHFE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.short_td = today
    holding.short_yd = yesterday
    holding.short_pos = today + yesterday
    holding.short_td_frozen = today_frozen
    holding.short_yd_frozen = yesterday_frozen
    holding.short_pos_frozen = today_frozen + yesterday_frozen
    return converter


def order_parts(requests: list[OrderRequest]) -> list[tuple[Offset, float]]:
    return [(req.offset, req.volume) for req in requests]


def test_shfe_close_splits_today_then_yesterday() -> None:
    converter: OffsetConverter = shfe_converter(today=3, yesterday=5)

    today_only: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 2)
    assert order_parts(converter.convert_order_request(today_only, lock=False)) == [
        (Offset.CLOSETODAY, 2)
    ]
    assert today_only.offset == Offset.CLOSE

    split: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 5)
    assert order_parts(converter.convert_order_request(split, lock=False)) == [
        (Offset.CLOSETODAY, 3),
        (Offset.CLOSEYESTERDAY, 2),
    ]
    assert split.offset == Offset.CLOSE

    too_large: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 9)
    assert converter.convert_order_request(too_large, lock=False) == []

    opened: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 1, Offset.OPEN)
    assert converter.convert_order_request(opened, lock=False) == [opened]


def test_shfe_close_uses_yesterday_when_today_is_empty() -> None:
    converter: OffsetConverter = shfe_converter(today=0, yesterday=5)
    request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 2)

    assert order_parts(converter.convert_order_request(request, lock=False)) == [
        (Offset.CLOSEYESTERDAY, 2)
    ]


def test_shfe_close_subtracts_frozen_volume() -> None:
    converter: OffsetConverter = shfe_converter(
        today=3,
        yesterday=5,
        today_frozen=1,
        yesterday_frozen=2,
    )
    request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 4)

    assert order_parts(converter.convert_order_request(request, lock=False)) == [
        (Offset.CLOSETODAY, 2),
        (Offset.CLOSEYESTERDAY, 2),
    ]

    blocked: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 6)
    assert converter.convert_order_request(blocked, lock=False) == []


def test_shfe_short_close_uses_long_position() -> None:
    contract: ContractData = make_contract(Exchange.SHFE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.long_td = 4
    holding.long_yd = 6
    holding.long_pos = 10

    request: OrderRequest = make_request(Exchange.SHFE, Direction.SHORT, 7)
    assert order_parts(converter.convert_order_request(request, lock=False)) == [
        (Offset.CLOSETODAY, 4),
        (Offset.CLOSEYESTERDAY, 3),
    ]


def test_dce_close_stays_close() -> None:
    contract: ContractData = make_contract(Exchange.DCE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.long_td = 10
    holding.long_yd = 0
    holding.long_pos = 10

    request: OrderRequest = make_request(Exchange.DCE, Direction.SHORT, 4)
    assert converter.convert_order_request(request, lock=False, net=False) == [request]
    assert request.offset == Offset.CLOSE


def test_net_position_and_missing_contract_skip_conversion() -> None:
    net_contract: ContractData = make_contract(Exchange.SHFE, net_position=True)
    net_converter: OffsetConverter = OffsetConverter(ContractBook(net_contract))
    net_request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 5)
    assert net_converter.convert_order_request(net_request, lock=False) == [net_request]

    missing: OffsetConverter = OffsetConverter(ContractBook(None))
    missing_request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 1)
    assert missing.convert_order_request(missing_request, lock=False) == [missing_request]

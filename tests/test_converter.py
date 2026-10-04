from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product, Status
from vnpy.trader.converter import OffsetConverter, PositionHolding
from vnpy.trader.object import ContractData, OrderData, OrderRequest, TradeData


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


def ine_converter(today: float, yesterday: float) -> OffsetConverter:
    contract: ContractData = make_contract(Exchange.INE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.short_td = today
    holding.short_yd = yesterday
    holding.short_pos = today + yesterday
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


def test_ine_close_splits_today_then_yesterday() -> None:
    # 能源中心与上期所同一套今昨拆分。
    converter: OffsetConverter = ine_converter(today=3, yesterday=5)

    today_only: OrderRequest = make_request(Exchange.INE, Direction.LONG, 2)
    assert order_parts(converter.convert_order_request(today_only, lock=False)) == [
        (Offset.CLOSETODAY, 2)
    ]

    split: OrderRequest = make_request(Exchange.INE, Direction.LONG, 4)
    assert order_parts(converter.convert_order_request(split, lock=False)) == [
        (Offset.CLOSETODAY, 3),
        (Offset.CLOSEYESTERDAY, 1),
    ]

    too_large: OrderRequest = make_request(Exchange.INE, Direction.LONG, 9)
    assert converter.convert_order_request(too_large, lock=False) == []


def test_lock_dce_opens_when_opponent_has_today_position() -> None:
    # 对手今仓大于 0 时锁仓只开仓，不看请求里的 offset。
    contract: ContractData = make_contract(Exchange.DCE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.short_td = 4
    holding.short_yd = 2
    holding.short_pos = 6

    close_request: OrderRequest = make_request(Exchange.DCE, Direction.LONG, 3, Offset.CLOSE)
    yesterday_request: OrderRequest = make_request(
        Exchange.DCE,
        Direction.LONG,
        3,
        Offset.CLOSEYESTERDAY,
    )
    assert order_parts(converter.convert_order_request(close_request, lock=True)) == [
        (Offset.OPEN, 3)
    ]
    assert order_parts(converter.convert_order_request(yesterday_request, lock=True)) == [
        (Offset.OPEN, 3)
    ]
    assert close_request.offset == Offset.CLOSE
    assert yesterday_request.offset == Offset.CLOSEYESTERDAY


def test_lock_shfe_closes_yesterday_then_opens() -> None:
    # 上期所锁仓：今仓为 0 时先平昨仓，剩余数量再开仓。
    contract: ContractData = make_contract(Exchange.SHFE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.short_td = 0
    holding.short_yd = 3
    holding.short_pos = 3

    request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 5)
    assert order_parts(converter.convert_order_request(request, lock=True)) == [
        (Offset.CLOSEYESTERDAY, 3),
        (Offset.OPEN, 2),
    ]


def test_net_shfe_closes_today_yesterday_then_opens() -> None:
    contract: ContractData = make_contract(Exchange.SHFE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.short_td = 2
    holding.short_yd = 3
    holding.short_pos = 5

    request: OrderRequest = make_request(Exchange.SHFE, Direction.LONG, 6)
    assert order_parts(converter.convert_order_request(request, lock=False, net=True)) == [
        (Offset.CLOSETODAY, 2),
        (Offset.CLOSEYESTERDAY, 3),
        (Offset.OPEN, 1),
    ]


def test_net_dce_closes_position_then_opens() -> None:
    # 净仓先平对手持仓。大商所平仓不拆今昨。
    contract: ContractData = make_contract(Exchange.DCE)
    converter: OffsetConverter = OffsetConverter(ContractBook(contract))
    holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
    assert holding is not None
    holding.long_td = 4
    holding.long_yd = 0
    holding.long_pos = 4

    request: OrderRequest = make_request(Exchange.DCE, Direction.SHORT, 7)
    assert order_parts(converter.convert_order_request(request, lock=False, net=True)) == [
        (Offset.CLOSE, 4),
        (Offset.OPEN, 3),
    ]


def make_close_trade(exchange: Exchange, volume: float) -> TradeData:
    return TradeData(
        gateway_name="FAKE",
        symbol="rb2410",
        exchange=exchange,
        orderid="1",
        tradeid="1",
        direction=Direction.LONG,
        offset=Offset.CLOSE,
        volume=volume,
    )


def test_update_trade_shfe_close_reduces_yesterday_only() -> None:
    # 上期所 Offset.CLOSE 只减昨仓，不动今仓。
    holding: PositionHolding = PositionHolding(make_contract(Exchange.SHFE))
    holding.short_td = 4
    holding.short_yd = 6
    holding.short_pos = 10

    holding.update_trade(make_close_trade(Exchange.SHFE, 2))

    assert holding.short_td == 4
    assert holding.short_yd == 4
    assert holding.short_pos == 8


def test_update_trade_dce_close_reduces_today_then_yesterday() -> None:
    # 大商所 Offset.CLOSE 先减今仓，今仓不够再减昨仓。
    holding: PositionHolding = PositionHolding(make_contract(Exchange.DCE))
    holding.short_td = 2
    holding.short_yd = 5
    holding.short_pos = 7

    holding.update_trade(make_close_trade(Exchange.DCE, 4))

    assert holding.short_td == 0
    assert holding.short_yd == 3
    assert holding.short_pos == 3


def test_calculate_frozen_close_fills_today_then_yesterday() -> None:
    # 平仓冻结先占今仓，超出部分计入昨仓冻结。
    holding: PositionHolding = PositionHolding(make_contract(Exchange.DCE))
    holding.long_td = 2
    holding.long_yd = 5
    holding.long_pos = 7
    order: OrderData = OrderData(
        gateway_name="FAKE",
        symbol="rb2410",
        exchange=Exchange.DCE,
        orderid="1",
        direction=Direction.SHORT,
        offset=Offset.CLOSE,
        volume=4,
        traded=0,
        status=Status.NOTTRADED,
    )
    holding.active_orders[order.vt_orderid] = order

    holding.calculate_frozen()

    assert holding.long_td_frozen == 2
    assert holding.long_yd_frozen == 2
    assert holding.long_pos_frozen == 4

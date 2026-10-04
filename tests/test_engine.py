import time
from collections.abc import Callable

from vnpy.event import EventEngine
from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product
from vnpy.trader.converter import OffsetConverter, PositionHolding
from vnpy.trader.engine import BaseEngine, MainEngine, OmsEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import (
    CancelRequest,
    ContractData,
    OrderRequest,
    PositionData,
    SubscribeRequest,
)


class FakeGateway(BaseGateway):
    default_name: str = "FAKE"
    exchanges: list[Exchange] = [Exchange.SHFE]

    def __init__(self, event_engine: EventEngine, gateway_name: str) -> None:
        super().__init__(event_engine, gateway_name)
        self.orders: list[OrderRequest] = []
        self.cancels: list[CancelRequest] = []

    def connect(self, setting: dict[str, str | int | float | bool]) -> None:
        return

    def close(self) -> None:
        return

    def subscribe(self, req: SubscribeRequest) -> None:
        return

    def send_order(self, req: OrderRequest) -> str:
        self.orders.append(req)
        return f"{self.gateway_name}.1"

    def cancel_order(self, req: CancelRequest) -> None:
        self.cancels.append(req)

    def query_account(self) -> None:
        return

    def query_position(self) -> None:
        return


def test_main_engine_routes_send_and_cancel_to_gateway() -> None:
    main_engine: MainEngine = MainEngine()
    try:
        gateway: BaseGateway = main_engine.add_gateway(FakeGateway)
        assert isinstance(gateway, FakeGateway)
        assert main_engine.exchanges == [Exchange.SHFE]

        request: OrderRequest = OrderRequest(
            symbol="rb2410",
            exchange=Exchange.SHFE,
            direction=Direction.LONG,
            type=OrderType.LIMIT,
            volume=1,
            price=3000,
            offset=Offset.OPEN,
        )
        vt_orderid: str = main_engine.send_order(request, FakeGateway.default_name)
        assert vt_orderid == "FAKE.1"
        assert gateway.orders == [request]

        cancel: CancelRequest = CancelRequest(
            orderid="1",
            symbol="rb2410",
            exchange=Exchange.SHFE,
        )
        main_engine.cancel_order(cancel, FakeGateway.default_name)
        assert gateway.cancels == [cancel]

        assert main_engine.send_order(request, "MISSING") == ""
        assert gateway.orders == [request]
    finally:
        main_engine.close()


def wait_until(ready: Callable[[], bool]) -> None:
    deadline: float = time.monotonic() + 2
    while time.monotonic() < deadline:
        if ready():
            return
        time.sleep(0.01)
    raise AssertionError("合约或持仓事件没有进入 OmsEngine")


def publish_shfe_short(gateway: FakeGateway, oms: OmsEngine) -> None:
    contract: ContractData = ContractData(
        gateway_name=FakeGateway.default_name,
        symbol="rb2410",
        exchange=Exchange.SHFE,
        name="rb",
        product=Product.FUTURES,
        size=10,
        pricetick=1,
    )
    position: PositionData = PositionData(
        gateway_name=FakeGateway.default_name,
        symbol="rb2410",
        exchange=Exchange.SHFE,
        direction=Direction.SHORT,
        volume=8,
        yd_volume=5,
    )
    gateway.on_contract(contract)
    gateway.on_position(position)

    def position_loaded() -> bool:
        converter: OffsetConverter | None = oms.get_converter(FakeGateway.default_name)
        if converter is None:
            return False
        holding: PositionHolding | None = converter.get_position_holding(contract.vt_symbol)
        if holding is None:
            return False
        return holding.short_td == 3 and holding.short_yd == 5

    wait_until(position_loaded)


def shfe_close_request() -> OrderRequest:
    return OrderRequest(
        symbol="rb2410",
        exchange=Exchange.SHFE,
        direction=Direction.LONG,
        type=OrderType.LIMIT,
        volume=5,
        price=3500,
        offset=Offset.CLOSE,
    )


def test_oms_convert_order_request_splits_only_after_contract() -> None:
    main_engine: MainEngine = MainEngine()
    try:
        gateway: BaseGateway = main_engine.add_gateway(FakeGateway)
        assert isinstance(gateway, FakeGateway)
        oms_engine: BaseEngine | None = main_engine.get_engine("oms")
        assert isinstance(oms_engine, OmsEngine)
        request: OrderRequest = shfe_close_request()

        # 尚未收到该网关合约事件时，没有转换器，请求原样返回。
        passthrough: list[OrderRequest] = oms_engine.convert_order_request(
            request,
            FakeGateway.default_name,
            False,
            False,
        )
        assert passthrough == [request]
        assert passthrough[0] is request

        publish_shfe_short(gateway, oms_engine)
        converted: list[OrderRequest] = oms_engine.convert_order_request(
            request,
            FakeGateway.default_name,
            False,
            False,
        )
        parts: list[tuple[Offset, float]] = [
            (item.offset, item.volume) for item in converted
        ]
        assert parts == [
            (Offset.CLOSETODAY, 3),
            (Offset.CLOSEYESTERDAY, 2),
        ]
    finally:
        main_engine.close()


def test_send_order_keeps_one_gateway_order_when_conversion_splits() -> None:
    main_engine: MainEngine = MainEngine()
    try:
        gateway: BaseGateway = main_engine.add_gateway(FakeGateway)
        assert isinstance(gateway, FakeGateway)
        oms_engine: BaseEngine | None = main_engine.get_engine("oms")
        assert isinstance(oms_engine, OmsEngine)
        request: OrderRequest = shfe_close_request()
        publish_shfe_short(gateway, oms_engine)

        converted: list[OrderRequest] = oms_engine.convert_order_request(
            request,
            FakeGateway.default_name,
            False,
            False,
        )
        assert len(converted) == 2

        vt_orderid: str = main_engine.send_order(request, FakeGateway.default_name)
        # 转换结果有两腿，send_order 仍只把原始请求交给网关一次。
        assert vt_orderid == "FAKE.1"
        assert gateway.orders == [request]
    finally:
        main_engine.close()

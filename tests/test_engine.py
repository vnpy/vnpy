from vnpy.event import EventEngine
from vnpy.trader.constant import Direction, Exchange, Offset, OrderType
from vnpy.trader.engine import MainEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import CancelRequest, OrderRequest, SubscribeRequest


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

"""Tests for OKX instIdCode order-operation compatibility."""

from __future__ import annotations

from types import SimpleNamespace

from vnpy.trader.constant import Direction, Exchange, Offset, OrderType, Product
from vnpy.trader.object import CancelRequest, ContractData, OrderRequest
from vnpy_okx.okx_gateway import PrivateApi, RestApi
from vnpy_rest import Request


class FakeGateway:
    """Small gateway double for OKX websocket unit tests."""

    gateway_name = "OKX"

    def __init__(self, contract: ContractData | None = None) -> None:
        self.contract = contract
        self.local_orderids: set[str] = set()
        self.logs: list[str] = []
        self.orders = []
        self.contracts: list[ContractData] = []

    def get_contract_by_symbol(self, symbol: str) -> ContractData | None:
        if self.contract and self.contract.symbol == symbol:
            return self.contract
        return None

    def on_contract(self, contract: ContractData) -> None:
        self.contracts.append(contract)

    def on_order(self, order) -> None:
        self.orders.append(order)

    def write_log(self, msg: str) -> None:
        self.logs.append(msg)


def test_contract_query_preserves_inst_id_code() -> None:
    gateway = FakeGateway()
    api = RestApi(gateway)

    api.on_query_contract(
        {
            "data": [
                {
                    "instId": "DOGE-USDT-SWAP",
                    "instIdCode": 123456,
                    "instType": "SWAP",
                    "ctVal": "1000",
                    "tickSz": "0.00001",
                    "minSz": "0.01",
                }
            ]
        },
        SimpleNamespace(params={"instType": "SWAP"}),
    )

    contract = gateway.contracts[0]
    assert contract.extra == {"instIdCode": 123456}


def test_public_request_uses_simulated_header_when_demo() -> None:
    gateway = FakeGateway()
    api = RestApi(gateway)
    api.simulated = True
    request = Request(
        method="GET",
        path="/api/v5/public/instruments",
        params={"instType": "SWAP"},
        data=None,
        headers=None,
    )

    signed = api.sign(request)

    assert signed.headers == {"x-simulated-trading": "1"}


def test_contract_query_skips_malformed_demo_future_symbol() -> None:
    gateway = FakeGateway()
    api = RestApi(gateway)

    api.on_query_contract(
        {
            "data": [
                {
                    "instId": "TESTING-USDT",
                    "instIdCode": None,
                    "instType": "FUTURES",
                    "ctVal": "",
                    "tickSz": "",
                    "minSz": "",
                }
            ]
        },
        SimpleNamespace(params={"instType": "FUTURES"}),
    )

    assert gateway.contracts == []


def test_private_order_payload_uses_inst_id_code() -> None:
    contract = ContractData(
        symbol="DOGEUSDT_SWAP_OKX",
        exchange=Exchange.GLOBAL,
        name="DOGE-USDT-SWAP",
        product=Product.SWAP,
        size=1000,
        pricetick=0.00001,
        gateway_name="OKX",
    )
    contract.extra = {"instIdCode": 123456}
    gateway = FakeGateway(contract)
    api = PrivateApi(gateway)
    api.connect_time = 260517170000

    packets = []
    api.send_packet = packets.append
    req = OrderRequest(
        symbol=contract.symbol,
        exchange=Exchange.GLOBAL,
        direction=Direction.SHORT,
        type=OrderType.LIMIT,
        volume=1,
        price=0.11,
        offset=Offset.OPEN,
    )

    vt_orderid = api.send_order(req)

    assert vt_orderid.startswith("OKX.")
    arg = packets[0]["args"][0]
    assert arg["instIdCode"] == 123456
    assert "instId" not in arg


def test_private_order_rejects_contract_without_inst_id_code() -> None:
    contract = ContractData(
        symbol="DOGEUSDT_SWAP_OKX",
        exchange=Exchange.GLOBAL,
        name="DOGE-USDT-SWAP",
        product=Product.SWAP,
        size=1000,
        pricetick=0.00001,
        gateway_name="OKX",
    )
    gateway = FakeGateway(contract)
    api = PrivateApi(gateway)
    api.send_packet = lambda _packet: None

    req = OrderRequest(
        symbol=contract.symbol,
        exchange=Exchange.GLOBAL,
        direction=Direction.SHORT,
        type=OrderType.LIMIT,
        volume=1,
        price=0.11,
        offset=Offset.OPEN,
    )

    assert api.send_order(req) == ""
    assert gateway.orders == []
    assert any("instIdCode missing" in msg for msg in gateway.logs)


def test_private_cancel_payload_uses_inst_id_code() -> None:
    contract = ContractData(
        symbol="DOGEUSDT_SWAP_OKX",
        exchange=Exchange.GLOBAL,
        name="DOGE-USDT-SWAP",
        product=Product.SWAP,
        size=1000,
        pricetick=0.00001,
        gateway_name="OKX",
    )
    contract.extra = {"instIdCode": 123456}
    gateway = FakeGateway(contract)
    gateway.local_orderids.add("local1")
    api = PrivateApi(gateway)

    packets = []
    api.send_packet = packets.append
    api.cancel_order(
        CancelRequest(
            orderid="local1",
            symbol=contract.symbol,
            exchange=Exchange.GLOBAL,
        )
    )

    arg = packets[0]["args"][0]
    assert arg["instIdCode"] == 123456
    assert "instId" not in arg
    assert arg["clOrdId"] == "local1"

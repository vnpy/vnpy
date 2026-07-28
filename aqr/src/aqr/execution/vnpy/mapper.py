from __future__ import annotations

from vnpy.trader.constant import Direction, Exchange, Offset, OrderType
from vnpy.trader.object import CancelRequest, OrderRequest

from aqr.domain.order import CancelOrderCommand, OrderKind, Side, SubmitOrderCommand

_ORDER_TYPE_MAP = {
    OrderKind.LIMIT: OrderType.LIMIT,
    OrderKind.MARKET: OrderType.MARKET,
}


def map_to_vnpy_order_request(command: SubmitOrderCommand) -> OrderRequest:
    try:
        exchange = Exchange(command.exchange)
    except ValueError as exc:
        raise ValueError(f"unsupported vn.py exchange: {command.exchange}") from exc

    if command.order_type is OrderKind.LIMIT and command.limit_price is None:
        raise ValueError("LIMIT order requires limit_price")

    return OrderRequest(
        symbol=command.symbol,
        exchange=exchange,
        direction=Direction.LONG if command.side is Side.BUY else Direction.SHORT,
        type=_ORDER_TYPE_MAP[command.order_type],
        volume=command.quantity,
        price=float(command.limit_price or 0),
        offset=Offset.OPEN if command.side is Side.BUY else Offset.CLOSE,
        reference=command.client_order_id,
    )


def map_to_vnpy_cancel_request(command: CancelOrderCommand) -> CancelRequest:
    external_order_id = command.external_order_id.split(".", 1)[-1]
    return CancelRequest(
        orderid=external_order_id,
        symbol=command.symbol,
        exchange=Exchange(command.exchange),
    )

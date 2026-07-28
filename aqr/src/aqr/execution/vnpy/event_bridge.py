from __future__ import annotations

from datetime import UTC, datetime
from decimal import Decimal
from threading import Lock
from time import time_ns
from typing import Protocol

from vnpy.event import Event, EventEngine
from vnpy.trader.constant import Direction, Status
from vnpy.trader.event import EVENT_ACCOUNT, EVENT_ORDER, EVENT_POSITION, EVENT_TRADE
from vnpy.trader.object import AccountData, OrderData, PositionData, TradeData

from aqr.domain.order import OrderEventType, Side, SubmitOrderCommand
from aqr.domain.trade import TradeFill
from aqr.execution.events import OrderEvent
from aqr.execution.vnpy.kill_switch import KillSwitch


class EventLedger(Protocol):
    def append_order_event(self, event: OrderEvent) -> bool: ...

    def append_trade_fill(self, fill: TradeFill) -> bool: ...

    def save_position_snapshot(self, position: PositionData) -> None: ...

    def save_account_snapshot(self, account: AccountData) -> None: ...

    def acknowledge_order_command(self, client_order_id: str) -> None: ...


_STATUS_MAP = {
    Status.SUBMITTING: OrderEventType.ORDER_SUBMITTING,
    Status.NOTTRADED: OrderEventType.ORDER_ACCEPTED,
    Status.PARTTRADED: OrderEventType.ORDER_PARTIALLY_FILLED,
    Status.ALLTRADED: OrderEventType.ORDER_FILLED,
    Status.CANCELLED: OrderEventType.ORDER_CANCELLED,
    Status.REJECTED: OrderEventType.ORDER_REJECTED,
}


class ExecutionEventBridge:
    def __init__(
        self,
        event_engine: EventEngine,
        ledger: EventLedger,
        kill_switch: KillSwitch | None = None,
    ) -> None:
        self.event_engine = event_engine
        self.ledger = ledger
        self.kill_switch = kill_switch
        self._sequence_lock = Lock()
        self._last_sequence = 0
        self._external_to_client: dict[str, str] = {}
        self._positions: dict[tuple[str, Direction], PositionData] = {}

    def start(self) -> None:
        self.event_engine.register(EVENT_ORDER, self.on_order)
        self.event_engine.register(EVENT_TRADE, self.on_trade)
        self.event_engine.register(EVENT_POSITION, self.on_position)
        self.event_engine.register(EVENT_ACCOUNT, self.on_account)

    def stop(self) -> None:
        self.event_engine.unregister(EVENT_ORDER, self.on_order)
        self.event_engine.unregister(EVENT_TRADE, self.on_trade)
        self.event_engine.unregister(EVENT_POSITION, self.on_position)
        self.event_engine.unregister(EVENT_ACCOUNT, self.on_account)

    def record_submission_result(
        self,
        command: SubmitOrderCommand,
        gateway_name: str,
        external_order_id: str,
    ) -> None:
        event_type = (
            OrderEventType.ORDER_SUBMITTED
            if external_order_id
            else OrderEventType.ORDER_REJECTED
        )
        if external_order_id:
            self._external_to_client[external_order_id] = command.client_order_id
        self.ledger.append_order_event(
            OrderEvent(
                client_order_id=command.client_order_id,
                gateway_name=gateway_name,
                external_order_id=external_order_id or None,
                event_type=event_type,
                event_time=datetime.now(UTC),
                event_sequence=self._next_sequence(),
                traded_quantity=0,
                remaining_quantity=command.quantity,
                price=command.limit_price,
                raw_payload={"command_id": str(command.command_id)},
                deduplication_key=(
                    f"submission:{command.command_id}:{external_order_id or 'REJECTED'}"
                ),
            )
        )

    def record_submission_started(
        self, command: SubmitOrderCommand, gateway_name: str
    ) -> None:
        self.ledger.append_order_event(
            OrderEvent(
                client_order_id=command.client_order_id,
                gateway_name=gateway_name,
                event_type=OrderEventType.ORDER_SUBMITTING,
                event_time=datetime.now(UTC),
                event_sequence=self._next_sequence(),
                traded_quantity=0,
                remaining_quantity=command.quantity,
                price=command.limit_price,
                raw_payload={"command_id": str(command.command_id)},
                deduplication_key=f"submitting:{command.command_id}",
            )
        )

    def record_submission_unknown(
        self,
        command: SubmitOrderCommand,
        gateway_name: str,
        reason: str,
    ) -> None:
        self.ledger.append_order_event(
            OrderEvent(
                client_order_id=command.client_order_id,
                gateway_name=gateway_name,
                event_type=OrderEventType.ORDER_UNKNOWN,
                event_time=datetime.now(UTC),
                event_sequence=self._next_sequence(),
                traded_quantity=0,
                remaining_quantity=command.quantity,
                price=command.limit_price,
                raw_payload={
                    "command_id": str(command.command_id),
                    "reason": reason,
                },
                deduplication_key=f"submission-unknown:{command.command_id}",
            )
        )

    def on_order(self, event: Event) -> None:
        order: OrderData = event.data
        client_order_id = (
            order.reference
            or self._external_to_client.get(order.vt_orderid)
            or f"EXTERNAL_UNKNOWN:{order.vt_orderid}"
        )
        if client_order_id.startswith("EXTERNAL_UNKNOWN:") and self.kill_switch:
            self.kill_switch.halt(
                f"unknown external order detected: {order.vt_orderid}"
            )
        self._external_to_client[order.vt_orderid] = client_order_id
        if not client_order_id.startswith("EXTERNAL_UNKNOWN:"):
            self.ledger.acknowledge_order_command(client_order_id)
        event_type = _STATUS_MAP[order.status]
        event_time = order.datetime or datetime.now(UTC)
        self.ledger.append_order_event(
            OrderEvent(
                client_order_id=client_order_id,
                gateway_name=order.gateway_name,
                external_order_id=order.vt_orderid,
                event_type=event_type,
                event_time=event_time,
                event_sequence=self._next_sequence(),
                traded_quantity=int(order.traded),
                remaining_quantity=int(order.volume - order.traded),
                price=Decimal(str(order.price)),
                raw_payload=self._serialize_order(order),
                deduplication_key=(
                    f"{order.vt_orderid}:{order.status.name}:{order.traded}:"
                    f"{event_time.isoformat()}"
                ),
            )
        )

    def on_trade(self, event: Event) -> None:
        trade: TradeData = event.data
        client_order_id = self._external_to_client.get(
            trade.vt_orderid, f"EXTERNAL_UNKNOWN:{trade.vt_orderid}"
        )
        self.ledger.append_trade_fill(
            TradeFill(
                client_order_id=client_order_id,
                gateway_name=trade.gateway_name,
                external_order_id=trade.vt_orderid,
                external_trade_id=trade.vt_tradeid,
                symbol=trade.vt_symbol,
                side=Side.BUY if trade.direction is Direction.LONG else Side.SELL,
                quantity=int(trade.volume),
                price=Decimal(str(trade.price)),
                trade_time=trade.datetime or datetime.now(UTC),
            )
        )

    def on_position(self, event: Event) -> None:
        position: PositionData = event.data
        if position.direction is Direction.NET:
            self.ledger.save_position_snapshot(position)
            return

        self._positions[(position.vt_symbol, position.direction)] = position
        long_position = self._positions.get((position.vt_symbol, Direction.LONG))
        short_position = self._positions.get((position.vt_symbol, Direction.SHORT))
        long_volume = long_position.volume if long_position else 0
        short_volume = short_position.volume if short_position else 0
        net_volume = long_volume - short_volume
        net_frozen = (long_position.frozen if long_position else 0) + (
            short_position.frozen if short_position else 0
        )
        source = long_position if net_volume >= 0 else short_position
        net_position = PositionData(
            symbol=position.symbol,
            exchange=position.exchange,
            direction=Direction.NET,
            volume=abs(net_volume),
            frozen=net_frozen,
            price=source.price if source else 0,
            pnl=sum(
                item.pnl
                for item in (long_position, short_position)
                if item is not None
            ),
            gateway_name=position.gateway_name,
        )
        self.ledger.save_position_snapshot(net_position)

    def on_account(self, event: Event) -> None:
        self.ledger.save_account_snapshot(event.data)

    def _next_sequence(self) -> int:
        with self._sequence_lock:
            self._last_sequence = max(time_ns(), self._last_sequence + 1)
            return self._last_sequence

    @staticmethod
    def _serialize_order(order: OrderData) -> dict:
        return {
            "symbol": order.symbol,
            "exchange": order.exchange.value,
            "orderid": order.orderid,
            "type": order.type.name,
            "direction": order.direction.name if order.direction else None,
            "price": order.price,
            "volume": order.volume,
            "traded": order.traded,
            "status": order.status.name,
            "reference": order.reference,
        }

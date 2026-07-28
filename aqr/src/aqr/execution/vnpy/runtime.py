from __future__ import annotations

from datetime import UTC, datetime

from vnpy.trader.constant import Direction
from vnpy.trader.engine import MainEngine

from aqr.domain.order import CancelOrderCommand, SubmitOrderCommand
from aqr.execution.contracts import OrderSubmissionRejected, OrderSubmissionUnknown
from aqr.execution.vnpy.event_bridge import ExecutionEventBridge
from aqr.execution.vnpy.gateway_router import GatewayRouter
from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.execution.vnpy.mapper import (
    map_to_vnpy_cancel_request,
    map_to_vnpy_order_request,
)
from aqr.reconciliation.service import GatewaySnapshot


class VnpyExecutionRuntime:
    def __init__(
        self,
        main_engine: MainEngine,
        gateway_router: GatewayRouter,
        event_bridge: ExecutionEventBridge,
        kill_switch: KillSwitch,
    ) -> None:
        self.main_engine = main_engine
        self.gateway_router = gateway_router
        self.event_bridge = event_bridge
        self.kill_switch = kill_switch

    def start(self) -> None:
        return

    def stop(self) -> None:
        self.main_engine.close()

    def submit_order(self, command: SubmitOrderCommand) -> None:
        self.kill_switch.assert_can_trade(command.account_id, command.symbol)
        request = map_to_vnpy_order_request(command)
        gateway_name = self.gateway_router.route(command)
        self.event_bridge.record_submission_started(command, gateway_name)
        try:
            external_order_id = self.main_engine.send_order(request, gateway_name)
        except Exception as exc:
            self._record_unknown_and_halt(command, gateway_name, str(exc))
            raise OrderSubmissionUnknown(
                f"Gateway submission outcome is unknown: {exc}"
            ) from exc

        if not external_order_id:
            self.event_bridge.record_submission_result(
                command=command,
                gateway_name=gateway_name,
                external_order_id="",
            )
            raise OrderSubmissionRejected("vn.py/risk manager rejected the order")

        try:
            self.event_bridge.record_submission_result(
                command=command,
                gateway_name=gateway_name,
                external_order_id=external_order_id,
            )
        except Exception as exc:
            self._record_unknown_and_halt(command, gateway_name, str(exc))
            raise OrderSubmissionUnknown(
                f"order was sent but its result could not be persisted: {exc}"
            ) from exc

    def cancel_order(self, command: CancelOrderCommand) -> None:
        request = map_to_vnpy_cancel_request(command)
        self.main_engine.cancel_order(request, command.gateway_name)

    def query_account(self, account_id: str) -> None:
        self._query_gateway("query_account", account_id)

    def query_positions(self, account_id: str) -> None:
        self._query_gateway("query_position", account_id)

    def query_orders(self, account_id: str) -> None:
        del account_id
        # Many vn.py gateways expose order snapshots through push callbacks only.
        self.main_engine.get_all_orders()

    def query_trades(self, account_id: str) -> None:
        del account_id
        self.main_engine.get_all_trades()

    def capture_reconciliation_snapshot(
        self, account_id: str
    ) -> GatewaySnapshot:
        gateway_name = self.gateway_router.account_gateways.get(
            account_id, self.gateway_router.default_gateway
        )
        if gateway_name == "PAPER":
            return self._capture_paper_snapshot()

        gateway = self.main_engine.get_gateway(gateway_name)
        if gateway is None:
            raise RuntimeError(
                f"Gateway is not connected for reconciliation: {gateway_name}"
            )
        self.query_account(account_id)
        self.query_positions(account_id)
        self.query_orders(account_id)
        self.query_trades(account_id)
        raise RuntimeError(
            "Gateway query completion barrier is unavailable; refusing stale reconciliation"
        )

    def _query_gateway(self, method_name: str, account_id: str) -> None:
        gateway = self.gateway_router.account_gateways.get(
            account_id, self.gateway_router.default_gateway
        )
        target = self.main_engine.get_gateway(gateway)
        if target is None:
            raise RuntimeError(f"gateway is unavailable: {gateway}")
        method = getattr(target, method_name, None)
        if method is None:
            raise NotImplementedError(f"{gateway} does not implement {method_name}")
        method()

    def _capture_paper_snapshot(self) -> GatewaySnapshot:
        paper_engine = self.main_engine.get_engine("PaperAccount")
        if paper_engine is None:
            raise RuntimeError("PaperAccount engine is unavailable")

        positions: dict[str, int] = {}
        for position in getattr(paper_engine, "positions", {}).values():
            quantity = int(position.volume)
            if position.direction is Direction.SHORT:
                quantity = -quantity
            positions[position.vt_symbol] = (
                positions.get(position.vt_symbol, 0) + quantity
            )

        active_order_ids: set[str] = set()
        for symbol_orders in getattr(paper_engine, "active_orders", {}).values():
            for order in symbol_orders.values():
                active_order_ids.add(
                    order.reference
                    or f"EXTERNAL_UNKNOWN:{order.vt_orderid}"
                )

        return GatewaySnapshot(
            positions=positions,
            active_order_ids=active_order_ids,
            captured_at=datetime.now(UTC),
        )

    def _record_unknown_and_halt(
        self,
        command: SubmitOrderCommand,
        gateway_name: str,
        reason: str,
    ) -> None:
        try:
            self.event_bridge.record_submission_unknown(
                command=command,
                gateway_name=gateway_name,
                reason=reason,
            )
        except Exception:
            # The account is still halted below; the original submission error
            # remains the most useful exception for the caller.
            pass
        finally:
            self.kill_switch.halt(
                f"unknown order submission: {command.client_order_id}",
                account_id=command.account_id,
                symbol=command.symbol,
            )

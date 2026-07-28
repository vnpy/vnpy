from __future__ import annotations

from datetime import UTC, datetime, timedelta
from decimal import Decimal
from time import time_ns
from typing import TYPE_CHECKING
from uuid import UUID, uuid4

from sqlalchemy import Select, select
from sqlalchemy.exc import IntegrityError
from sqlalchemy.orm import Session, sessionmaker

from aqr.domain.order import (
    ActualOrderStatus,
    OrderEventType,
    OrderIntent,
    OrderIntentStatus,
    TradingEnvironment,
)

if TYPE_CHECKING:
    from vnpy.trader.object import AccountData, PositionData
from aqr.domain.trade import TradeFill
from aqr.execution.events import OrderEvent
from aqr.execution.order_state_machine import InvalidOrderTransition, transition
from aqr.execution.outbox import command_from_intent
from aqr.persistence.models import (
    AccountSnapshotModel,
    CommandOutboxModel,
    OrderEventModel,
    OrderIntentModel,
    OrderProjectionModel,
    PositionProjectionModel,
    ReconciliationDiffModel,
    ReconciliationRunModel,
    TradeFillModel,
)


class SqlAlchemyExecutionRepository:
    """PostgreSQL implementation of the transactional order ledger."""

    def __init__(
        self,
        session_factory: sessionmaker[Session],
        *,
        environment: TradingEnvironment = TradingEnvironment.PAPER,
        account_id: str = "A01",
    ) -> None:
        self._session_factory = session_factory
        self.environment = environment
        self.account_id = account_id

    def create_order_with_command(self, intent: OrderIntent) -> tuple[UUID, UUID]:
        with self._session_factory() as session:
            existing = self._existing_order_ids(session, intent)
            if existing is not None:
                return existing

        self._assert_executable(intent)
        command_id = uuid4()
        try:
            with self._session_factory.begin() as session:
                session.add(
                    OrderIntentModel(
                        order_intent_id=intent.order_intent_id,
                        client_order_id=intent.client_order_id,
                        environment=intent.environment.value,
                        account_id=intent.account_id,
                        strategy_id=intent.strategy_id,
                        trade_date=intent.trade_date,
                        symbol=intent.symbol,
                        exchange=intent.exchange,
                        side=intent.side.value,
                        order_type=intent.order_type.value,
                        target_quantity=intent.target_quantity,
                        limit_price=intent.limit_price,
                        risk_run_id=intent.risk_run_id,
                        status=intent.status.value,
                        expires_at=intent.expires_at,
                        created_at=intent.created_at,
                    )
                )
                session.add(
                    CommandOutboxModel(
                        command_id=command_id,
                        aggregate_type="ORDER_INTENT",
                        aggregate_id=intent.order_intent_id,
                        command_type="SEND_ORDER",
                        payload_json=command_from_intent(intent, command_id),
                        status="PENDING",
                    )
                )
                created_event = OrderEventModel(
                    client_order_id=intent.client_order_id,
                    gateway_name="AQR",
                    event_type=OrderEventType.ORDER_CREATED.value,
                    event_time=intent.created_at,
                    event_sequence=0,
                    traded_quantity=0,
                    remaining_quantity=intent.target_quantity,
                    price=intent.limit_price,
                    raw_payload={"order_intent_id": str(intent.order_intent_id)},
                    deduplication_key=f"intent:{intent.order_intent_id}",
                    received_at=intent.created_at,
                )
                session.add(created_event)
                session.flush()
                session.add(
                    OrderProjectionModel(
                        client_order_id=intent.client_order_id,
                        account_id=intent.account_id,
                        symbol=f"{intent.symbol}.{intent.exchange}",
                        gateway_name="AQR",
                        status=ActualOrderStatus.CREATED.value,
                        ordered_quantity=intent.target_quantity,
                        traded_quantity=0,
                        last_event_id=created_event.event_id,
                        last_event_sequence=0,
                        updated_at=intent.created_at,
                    )
                )
            return intent.order_intent_id, command_id
        except IntegrityError:
            with self._session_factory() as session:
                existing = self._existing_order_ids(session, intent)
                if existing is None:
                    raise
                return existing

    def claim_pending(self, worker_id: str, limit: int = 20) -> list[dict]:
        now = datetime.now(UTC)
        statement: Select[tuple[CommandOutboxModel]] = (
            select(CommandOutboxModel)
            .where(
                CommandOutboxModel.status == "PENDING",
                (CommandOutboxModel.next_retry_at.is_(None))
                | (CommandOutboxModel.next_retry_at <= now),
            )
            .order_by(CommandOutboxModel.created_at)
            .limit(limit)
            .with_for_update(skip_locked=True)
        )
        with self._session_factory.begin() as session:
            rows = list(session.scalars(statement))
            for row in rows:
                row.status = "CLAIMED"
                row.claimed_by = worker_id
                row.claimed_at = now
            return [
                {
                    "command_id": row.command_id,
                    "command_type": row.command_type,
                    "payload": dict(row.payload_json),
                }
                for row in rows
            ]

    def mark_sent(self, command_id: UUID) -> None:
        self._set_status(command_id, "SENT", only_from={"CLAIMED"})

    def mark_acknowledged(self, command_id: UUID) -> None:
        self._set_status(command_id, "ACKNOWLEDGED", completed=True)

    def mark_failed(self, command_id: UUID, error: str) -> None:
        del error  # error details belong in audit.system_alert
        self._set_status(
            command_id,
            "FAILED",
            completed=True,
            only_from={"PENDING", "CLAIMED", "SENT"},
        )

    def release_for_retry(
        self, command_id: UUID, error: str, retry_delay: timedelta
    ) -> None:
        del error  # error details belong in audit.system_alert
        with self._session_factory.begin() as session:
            row = session.get(CommandOutboxModel, command_id, with_for_update=True)
            if row is None:
                raise KeyError(command_id)
            row.status = "PENDING"
            row.retry_count += 1
            row.next_retry_at = datetime.now(UTC) + retry_delay
            row.claimed_by = None
            row.claimed_at = None

    def recover_stale_claims(
        self,
        cutoff: datetime,
        worker_id: str | None = None,
    ) -> list[dict]:
        terminal = {
            ActualOrderStatus.FILLED.value,
            ActualOrderStatus.REJECTED.value,
            ActualOrderStatus.CANCELLED.value,
            ActualOrderStatus.EXPIRED.value,
        }
        ambiguous: list[dict] = []
        statement = (
            select(
                CommandOutboxModel,
                OrderIntentModel,
                OrderProjectionModel,
            )
            .join(
                OrderIntentModel,
                OrderIntentModel.order_intent_id == CommandOutboxModel.aggregate_id,
            )
            .join(
                OrderProjectionModel,
                OrderProjectionModel.client_order_id
                == OrderIntentModel.client_order_id,
            )
            .where(
                CommandOutboxModel.status == "CLAIMED",
                CommandOutboxModel.claimed_at <= cutoff,
            )
            .with_for_update(skip_locked=True)
        )
        if worker_id is not None:
            statement = statement.where(
                CommandOutboxModel.claimed_by == worker_id
            )
        now = datetime.now(UTC)
        with self._session_factory.begin() as session:
            for command, intent, projection in session.execute(statement):
                if projection.status == ActualOrderStatus.CREATED.value:
                    command.status = "PENDING"
                    command.retry_count += 1
                    command.next_retry_at = now
                    command.claimed_by = None
                    command.claimed_at = None
                    continue

                if projection.status in terminal:
                    command.status = "ACKNOWLEDGED"
                    command.completed_at = now
                    continue

                command.status = "FAILED"
                command.completed_at = now
                unknown_event = OrderEvent(
                    client_order_id=intent.client_order_id,
                    gateway_name=projection.gateway_name,
                    external_order_id=projection.external_order_id,
                    event_type=OrderEventType.ORDER_UNKNOWN,
                    event_time=now,
                    event_sequence=max(
                        time_ns(), projection.last_event_sequence + 1
                    ),
                    traded_quantity=projection.traded_quantity,
                    remaining_quantity=max(
                        0,
                        projection.ordered_quantity
                        - projection.traded_quantity,
                    ),
                    raw_payload={
                        "reason": "STALE_OUTBOX_CLAIM",
                        "command_id": str(command.command_id),
                    },
                    deduplication_key=f"stale-claim:{command.command_id}",
                )
                session.add(
                    OrderEventModel(
                        event_id=unknown_event.event_id,
                        client_order_id=unknown_event.client_order_id,
                        gateway_name=unknown_event.gateway_name,
                        external_order_id=unknown_event.external_order_id,
                        event_type=unknown_event.event_type.value,
                        event_time=unknown_event.event_time,
                        event_sequence=unknown_event.event_sequence,
                        traded_quantity=unknown_event.traded_quantity,
                        remaining_quantity=unknown_event.remaining_quantity,
                        price=unknown_event.price,
                        raw_payload=unknown_event.raw_payload,
                        deduplication_key=unknown_event.deduplication_key,
                        received_at=unknown_event.received_at,
                    )
                )
                self._apply_order_projection(session, unknown_event)
                ambiguous.append(
                    {
                        "command_id": command.command_id,
                        "client_order_id": intent.client_order_id,
                        "account_id": intent.account_id,
                        "symbol": intent.symbol,
                    }
                )
        return ambiguous

    def append_order_event(self, event: OrderEvent) -> bool:
        try:
            with self._session_factory.begin() as session:
                event_model = OrderEventModel(
                        event_id=event.event_id,
                        client_order_id=event.client_order_id,
                        gateway_name=event.gateway_name,
                        external_order_id=event.external_order_id,
                        event_type=event.event_type.value,
                        event_time=event.event_time,
                        event_sequence=event.event_sequence,
                        traded_quantity=event.traded_quantity,
                        remaining_quantity=event.remaining_quantity,
                        price=event.price,
                        raw_payload=event.raw_payload,
                        deduplication_key=event.deduplication_key,
                        received_at=event.received_at,
                    )
                session.add(event_model)
                self._apply_order_projection(session, event)
            return True
        except IntegrityError:
            return False

    def append_trade_fill(self, fill: TradeFill) -> bool:
        try:
            with self._session_factory.begin() as session:
                session.add(
                    TradeFillModel(
                        fill_id=fill.fill_id,
                        client_order_id=fill.client_order_id,
                        gateway_name=fill.gateway_name,
                        external_order_id=fill.external_order_id,
                        external_trade_id=fill.external_trade_id,
                        symbol=fill.symbol,
                        side=fill.side.value,
                        quantity=fill.quantity,
                        price=fill.price,
                        commission=fill.commission,
                        tax=fill.tax,
                        trade_time=fill.trade_time,
                        received_at=fill.received_at,
                    )
                )
            return True
        except IntegrityError:
            return False

    def save_position_snapshot(self, position: PositionData) -> None:
        now = datetime.now(UTC)
        with self._session_factory.begin() as session:
            row = session.scalar(
                select(PositionProjectionModel)
                .where(
                    PositionProjectionModel.environment == self.environment.value,
                    PositionProjectionModel.account_id == self.account_id,
                    PositionProjectionModel.symbol == position.vt_symbol,
                )
                .with_for_update()
            )
            available = max(0, int(position.volume - position.frozen))
            values = {
                "total_quantity": int(position.volume),
                "available_quantity": available,
                "frozen_quantity": int(position.frozen),
                "average_cost": Decimal(str(position.price)),
                "market_value": Decimal("0"),
                "updated_at": now,
            }
            if row is None:
                session.add(
                    PositionProjectionModel(
                        environment=self.environment.value,
                        account_id=self.account_id,
                        symbol=position.vt_symbol,
                        **values,
                    )
                )
            else:
                for key, value in values.items():
                    setattr(row, key, value)

    def save_account_snapshot(self, account: AccountData) -> None:
        now = datetime.now(UTC)
        with self._session_factory.begin() as session:
            session.add(
                AccountSnapshotModel(
                    environment=self.environment.value,
                    account_id=self.account_id,
                    balance=Decimal(str(account.balance)),
                    available=Decimal(str(account.available)),
                    frozen=Decimal(str(account.frozen)),
                    gateway_name=account.gateway_name,
                    snapshot_at=now,
                )
            )

    def acknowledge_order_command(self, client_order_id: str) -> None:
        now = datetime.now(UTC)
        with self._session_factory.begin() as session:
            intent_id = session.scalar(
                select(OrderIntentModel.order_intent_id).where(
                    OrderIntentModel.client_order_id == client_order_id,
                    OrderIntentModel.account_id == self.account_id,
                )
            )
            if intent_id is None:
                return
            command = session.scalar(
                select(CommandOutboxModel)
                .where(
                    CommandOutboxModel.aggregate_id == intent_id,
                    CommandOutboxModel.command_type == "SEND_ORDER",
                )
                .with_for_update()
            )
            if command and command.status in {"CLAIMED", "SENT"}:
                command.status = "ACKNOWLEDGED"
                command.completed_at = now

    def load_position_quantities(self) -> dict[str, int]:
        with self._session_factory() as session:
            rows = session.execute(
                select(
                    PositionProjectionModel.symbol,
                    PositionProjectionModel.total_quantity,
                ).where(
                    PositionProjectionModel.environment == self.environment.value,
                    PositionProjectionModel.account_id == self.account_id,
                )
            )
            return {symbol: int(quantity) for symbol, quantity in rows}

    def load_open_order_ids(self) -> set[str]:
        gateway_active = {
            ActualOrderStatus.SUBMITTED.value,
            ActualOrderStatus.ACCEPTED.value,
            ActualOrderStatus.PARTIALLY_FILLED.value,
            ActualOrderStatus.UNKNOWN.value,
        }
        with self._session_factory() as session:
            return set(
                session.scalars(
                    select(OrderProjectionModel.client_order_id).where(
                        OrderProjectionModel.account_id == self.account_id,
                        OrderProjectionModel.status.in_(gateway_active),
                    )
                )
            )

    def load_unknown_order_ids(self) -> set[str]:
        with self._session_factory() as session:
            return set(
                session.scalars(
                    select(OrderProjectionModel.client_order_id).where(
                        OrderProjectionModel.account_id == self.account_id,
                        OrderProjectionModel.status
                        == ActualOrderStatus.UNKNOWN.value,
                    )
                )
            )

    def record_reconciliation(
        self, reason: str, diffs: list, passed: bool
    ) -> UUID:
        now = datetime.now(UTC)
        reconciliation_id = uuid4()
        with self._session_factory.begin() as session:
            session.add(
                ReconciliationRunModel(
                    reconciliation_id=reconciliation_id,
                    environment=self.environment.value,
                    account_id=self.account_id,
                    reason=reason,
                    started_at=now,
                    completed_at=now,
                    status="PASSED" if passed else "FAILED",
                    gateway_snapshot_time=now,
                    internal_snapshot_time=now,
                )
            )
            for diff in diffs:
                session.add(
                    ReconciliationDiffModel(
                        reconciliation_id=reconciliation_id,
                        entity_type=diff.entity_type,
                        symbol=diff.symbol,
                        field_name=diff.field_name,
                        internal_value=diff.internal_value,
                        gateway_value=diff.gateway_value,
                        severity=diff.severity.value,
                        resolution_status="OPEN",
                    )
                )
        return reconciliation_id

    def find_acknowledgement_timeouts(self, cutoff: datetime) -> list[dict]:
        with self._session_factory() as session:
            rows = session.execute(
                select(CommandOutboxModel, OrderIntentModel)
                .join(
                    OrderIntentModel,
                    OrderIntentModel.order_intent_id
                    == CommandOutboxModel.aggregate_id,
                )
                .where(
                    CommandOutboxModel.status == "SENT",
                    CommandOutboxModel.claimed_at <= cutoff,
                )
            )
            return [
                {
                    "command_id": command.command_id,
                    "client_order_id": intent.client_order_id,
                    "account_id": intent.account_id,
                    "symbol": intent.symbol,
                    "gateway_name": "PAPER",
                    "quantity": intent.target_quantity,
                }
                for command, intent in rows
            ]

    def mark_acknowledgement_timeout(self, command_id: UUID) -> None:
        self._set_status(command_id, "FAILED", completed=True, only_from={"SENT"})

    def _set_status(
        self,
        command_id: UUID,
        status: str,
        *,
        completed: bool = False,
        only_from: set[str] | None = None,
    ) -> None:
        with self._session_factory.begin() as session:
            row = session.get(CommandOutboxModel, command_id, with_for_update=True)
            if row is None:
                raise KeyError(command_id)
            if only_from is not None and row.status not in only_from:
                return
            row.status = status
            if completed:
                row.completed_at = datetime.now(UTC)

    @staticmethod
    def _assert_executable(intent: OrderIntent) -> None:
        if intent.status not in {
            OrderIntentStatus.RISK_APPROVED,
            OrderIntentStatus.READY,
        }:
            raise ValueError(f"order intent is not executable: {intent.status}")
        if intent.expires_at and intent.expires_at <= datetime.now(UTC):
            raise ValueError("order intent has expired")

    @staticmethod
    def _assert_same_intent(
        existing: OrderIntentModel,
        requested: OrderIntent,
    ) -> None:
        comparable = {
            "environment": requested.environment.value,
            "account_id": requested.account_id,
            "strategy_id": requested.strategy_id,
            "trade_date": requested.trade_date,
            "symbol": requested.symbol,
            "exchange": requested.exchange,
            "side": requested.side.value,
            "order_type": requested.order_type.value,
            "target_quantity": requested.target_quantity,
            "limit_price": requested.limit_price,
            "risk_run_id": requested.risk_run_id,
        }
        if any(
            getattr(existing, field) != value
            for field, value in comparable.items()
        ):
            raise ValueError(
                "client_order_id is already bound to a different order intent"
            )

    def _existing_order_ids(
        self,
        session: Session,
        intent: OrderIntent,
    ) -> tuple[UUID, UUID] | None:
        existing = session.scalar(
            select(OrderIntentModel).where(
                OrderIntentModel.account_id == intent.account_id,
                OrderIntentModel.client_order_id == intent.client_order_id,
            )
        )
        if existing is None:
            return None
        self._assert_same_intent(existing, intent)
        command = session.scalar(
            select(CommandOutboxModel).where(
                CommandOutboxModel.aggregate_id == existing.order_intent_id
            )
        )
        if command is None:
            raise RuntimeError("idempotent order exists without outbox command")
        return existing.order_intent_id, command.command_id

    @staticmethod
    def _apply_order_projection(session: Session, event: OrderEvent) -> None:
        row = session.get(
            OrderProjectionModel, event.client_order_id, with_for_update=True
        )
        if row is None:
            # Unknown external orders are deliberately persisted as UNKNOWN.
            session.add(
                OrderProjectionModel(
                    client_order_id=event.client_order_id,
                    account_id="UNKNOWN",
                    symbol=str(event.raw_payload.get("symbol", "UNKNOWN")),
                    gateway_name=event.gateway_name,
                    external_order_id=event.external_order_id,
                    status=ActualOrderStatus.UNKNOWN.value,
                    ordered_quantity=event.traded_quantity + event.remaining_quantity,
                    traded_quantity=event.traded_quantity,
                    average_fill_price=event.price,
                    last_event_id=event.event_id,
                    last_event_sequence=event.event_sequence,
                    updated_at=event.event_time,
                )
            )
            return

        if event.event_sequence <= row.last_event_sequence:
            return

        target_map = {
            OrderEventType.ORDER_CREATED: ActualOrderStatus.CREATED,
            OrderEventType.ORDER_SUBMITTING: ActualOrderStatus.SUBMITTING,
            OrderEventType.ORDER_SUBMITTED: ActualOrderStatus.SUBMITTED,
            OrderEventType.ORDER_ACCEPTED: ActualOrderStatus.ACCEPTED,
            OrderEventType.ORDER_PARTIALLY_FILLED: ActualOrderStatus.PARTIALLY_FILLED,
            OrderEventType.ORDER_FILLED: ActualOrderStatus.FILLED,
            OrderEventType.ORDER_REJECTED: ActualOrderStatus.REJECTED,
            OrderEventType.ORDER_CANCELLED: ActualOrderStatus.CANCELLED,
            OrderEventType.ORDER_EXPIRED: ActualOrderStatus.EXPIRED,
            OrderEventType.ORDER_UNKNOWN: ActualOrderStatus.UNKNOWN,
        }
        target = target_map.get(event.event_type)
        if target is not None:
            try:
                next_status = transition(ActualOrderStatus(row.status), target)
            except InvalidOrderTransition:
                current = ActualOrderStatus(row.status)
                if current in {
                    ActualOrderStatus.FILLED,
                    ActualOrderStatus.REJECTED,
                    ActualOrderStatus.CANCELLED,
                    ActualOrderStatus.EXPIRED,
                }:
                    next_status = current
                else:
                    next_status = ActualOrderStatus.UNKNOWN
            row.status = next_status.value

        row.gateway_name = event.gateway_name
        row.external_order_id = event.external_order_id or row.external_order_id
        row.traded_quantity = max(row.traded_quantity, event.traded_quantity)
        if event.traded_quantity and event.price:
            row.average_fill_price = event.price
        row.last_event_id = event.event_id
        row.last_event_sequence = event.event_sequence
        row.updated_at = event.event_time

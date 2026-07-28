from __future__ import annotations

from datetime import date, datetime
from decimal import Decimal
from uuid import UUID, uuid4

from sqlalchemy import (
    BigInteger,
    Date,
    DateTime,
    ForeignKey,
    Index,
    Integer,
    Numeric,
    String,
    Text,
    UniqueConstraint,
    func,
)
from sqlalchemy.dialects.postgresql import JSONB
from sqlalchemy.orm import DeclarativeBase, Mapped, mapped_column
from sqlalchemy.types import Uuid


class Base(DeclarativeBase):
    pass


class OrderIntentModel(Base):
    __tablename__ = "order_intent"
    __table_args__ = (
        UniqueConstraint("account_id", "client_order_id", name="uq_order_intent_client"),
        {"schema": "execution"},
    )

    order_intent_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    client_order_id: Mapped[str] = mapped_column(String(160), nullable=False)
    environment: Mapped[str] = mapped_column(String(16), nullable=False)
    account_id: Mapped[str] = mapped_column(String(64), nullable=False)
    strategy_id: Mapped[str] = mapped_column(String(64), nullable=False)
    trade_date: Mapped[date] = mapped_column(Date, nullable=False)
    symbol: Mapped[str] = mapped_column(String(32), nullable=False)
    exchange: Mapped[str] = mapped_column(String(16), nullable=False)
    side: Mapped[str] = mapped_column(String(8), nullable=False)
    order_type: Mapped[str] = mapped_column(String(16), nullable=False)
    target_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    limit_price: Mapped[Decimal | None] = mapped_column(Numeric(20, 6))
    risk_run_id: Mapped[UUID] = mapped_column(Uuid, nullable=False)
    status: Mapped[str] = mapped_column(String(32), nullable=False)
    expires_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))
    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )


class CommandOutboxModel(Base):
    __tablename__ = "command_outbox"
    __table_args__ = (
        Index("ix_command_outbox_pending", "status", "next_retry_at", "created_at"),
        {"schema": "execution"},
    )

    command_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    aggregate_type: Mapped[str] = mapped_column(String(32), nullable=False)
    aggregate_id: Mapped[UUID] = mapped_column(Uuid, nullable=False)
    command_type: Mapped[str] = mapped_column(String(32), nullable=False)
    payload_json: Mapped[dict] = mapped_column(JSONB, nullable=False)
    status: Mapped[str] = mapped_column(String(20), nullable=False, default="PENDING")
    retry_count: Mapped[int] = mapped_column(Integer, nullable=False, default=0)
    next_retry_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))
    claimed_by: Mapped[str | None] = mapped_column(String(128))
    claimed_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))
    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )
    completed_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))


class OrderEventModel(Base):
    __tablename__ = "order_event"
    __table_args__ = (
        UniqueConstraint(
            "gateway_name", "deduplication_key", name="uq_order_event_dedup"
        ),
        Index("ix_order_event_client_sequence", "client_order_id", "event_sequence"),
        {"schema": "execution"},
    )

    event_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    client_order_id: Mapped[str] = mapped_column(String(160), nullable=False)
    gateway_name: Mapped[str] = mapped_column(String(64), nullable=False)
    external_order_id: Mapped[str | None] = mapped_column(String(128))
    event_type: Mapped[str] = mapped_column(String(40), nullable=False)
    event_time: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)
    event_sequence: Mapped[int] = mapped_column(BigInteger, nullable=False)
    traded_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False, default=0)
    remaining_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False, default=0)
    price: Mapped[Decimal | None] = mapped_column(Numeric(20, 6))
    raw_payload: Mapped[dict] = mapped_column(JSONB, nullable=False)
    deduplication_key: Mapped[str] = mapped_column(String(256), nullable=False)
    received_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )


class OrderProjectionModel(Base):
    __tablename__ = "order_projection"
    __table_args__ = {"schema": "execution"}

    client_order_id: Mapped[str] = mapped_column(String(160), primary_key=True)
    account_id: Mapped[str] = mapped_column(String(64), nullable=False)
    symbol: Mapped[str] = mapped_column(String(32), nullable=False)
    gateway_name: Mapped[str] = mapped_column(String(64), nullable=False)
    external_order_id: Mapped[str | None] = mapped_column(String(128))
    status: Mapped[str] = mapped_column(String(32), nullable=False)
    ordered_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    traded_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False, default=0)
    average_fill_price: Mapped[Decimal | None] = mapped_column(Numeric(20, 6))
    last_event_id: Mapped[UUID] = mapped_column(Uuid, nullable=False)
    last_event_sequence: Mapped[int] = mapped_column(BigInteger, nullable=False)
    updated_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)


class TradeFillModel(Base):
    __tablename__ = "trade_fill"
    __table_args__ = (
        UniqueConstraint(
            "gateway_name", "external_trade_id", name="uq_trade_fill_external"
        ),
        {"schema": "execution"},
    )

    fill_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    client_order_id: Mapped[str] = mapped_column(String(160), nullable=False)
    gateway_name: Mapped[str] = mapped_column(String(64), nullable=False)
    external_order_id: Mapped[str] = mapped_column(String(128), nullable=False)
    external_trade_id: Mapped[str] = mapped_column(String(128), nullable=False)
    symbol: Mapped[str] = mapped_column(String(32), nullable=False)
    side: Mapped[str] = mapped_column(String(8), nullable=False)
    quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    price: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    commission: Mapped[Decimal] = mapped_column(
        Numeric(20, 6), nullable=False, default=Decimal("0")
    )
    tax: Mapped[Decimal] = mapped_column(
        Numeric(20, 6), nullable=False, default=Decimal("0")
    )
    trade_time: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)
    received_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )


class PositionProjectionModel(Base):
    __tablename__ = "position_projection"
    __table_args__ = (
        UniqueConstraint(
            "environment", "account_id", "symbol", name="uq_position_projection"
        ),
        {"schema": "execution"},
    )

    position_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    environment: Mapped[str] = mapped_column(String(16), nullable=False)
    account_id: Mapped[str] = mapped_column(String(64), nullable=False)
    symbol: Mapped[str] = mapped_column(String(32), nullable=False)
    total_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    available_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    frozen_quantity: Mapped[int] = mapped_column(BigInteger, nullable=False)
    average_cost: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    market_value: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    last_event_id: Mapped[UUID | None] = mapped_column(Uuid)
    updated_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)


class AccountSnapshotModel(Base):
    __tablename__ = "account_snapshot"
    __table_args__ = (
        Index("ix_account_snapshot_lookup", "environment", "account_id", "snapshot_at"),
        {"schema": "execution"},
    )

    snapshot_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    environment: Mapped[str] = mapped_column(String(16), nullable=False)
    account_id: Mapped[str] = mapped_column(String(64), nullable=False)
    balance: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    available: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    frozen: Mapped[Decimal] = mapped_column(Numeric(20, 6), nullable=False)
    gateway_name: Mapped[str] = mapped_column(String(64), nullable=False)
    snapshot_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)
    received_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )


class ReconciliationRunModel(Base):
    __tablename__ = "run"
    __table_args__ = {"schema": "reconciliation"}

    reconciliation_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    environment: Mapped[str] = mapped_column(String(16), nullable=False)
    account_id: Mapped[str] = mapped_column(String(64), nullable=False)
    reason: Mapped[str] = mapped_column(String(64), nullable=False)
    started_at: Mapped[datetime] = mapped_column(DateTime(timezone=True), nullable=False)
    completed_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))
    status: Mapped[str] = mapped_column(String(32), nullable=False)
    gateway_snapshot_time: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))
    internal_snapshot_time: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))


class ReconciliationDiffModel(Base):
    __tablename__ = "diff"
    __table_args__ = {"schema": "reconciliation"}

    diff_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    reconciliation_id: Mapped[UUID] = mapped_column(
        Uuid,
        ForeignKey("reconciliation.run.reconciliation_id", ondelete="CASCADE"),
        nullable=False,
    )
    entity_type: Mapped[str] = mapped_column(String(32), nullable=False)
    symbol: Mapped[str | None] = mapped_column(String(32))
    field_name: Mapped[str] = mapped_column(String(64), nullable=False)
    internal_value: Mapped[str | None] = mapped_column(Text)
    gateway_value: Mapped[str | None] = mapped_column(Text)
    severity: Mapped[str] = mapped_column(String(16), nullable=False)
    resolution_status: Mapped[str] = mapped_column(String(24), nullable=False)
    resolution_note: Mapped[str | None] = mapped_column(Text)


class SystemAlertModel(Base):
    __tablename__ = "system_alert"
    __table_args__ = {"schema": "audit"}

    alert_id: Mapped[UUID] = mapped_column(Uuid, primary_key=True, default=uuid4)
    severity: Mapped[str] = mapped_column(String(16), nullable=False)
    source: Mapped[str] = mapped_column(String(64), nullable=False)
    code: Mapped[str] = mapped_column(String(64), nullable=False)
    message: Mapped[str] = mapped_column(Text, nullable=False)
    context_json: Mapped[dict] = mapped_column(JSONB, nullable=False)
    created_at: Mapped[datetime] = mapped_column(
        DateTime(timezone=True), nullable=False, server_default=func.now()
    )
    acknowledged_at: Mapped[datetime | None] = mapped_column(DateTime(timezone=True))

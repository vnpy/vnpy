"""Phase 0 execution ledger

Revision ID: 0001_phase0
Revises:
Create Date: 2026-07-27
"""

import sqlalchemy as sa
from alembic import op
from sqlalchemy.dialects import postgresql

revision = "0001_phase0"
down_revision = None
branch_labels = None
depends_on = None

SCHEMAS = (
    "meta",
    "market",
    "research",
    "signal",
    "portfolio",
    "risk",
    "execution",
    "reconciliation",
    "audit",
)


def upgrade() -> None:
    for schema in SCHEMAS:
        op.execute(f'CREATE SCHEMA IF NOT EXISTS "{schema}"')

    op.create_table(
        "order_intent",
        sa.Column("order_intent_id", sa.Uuid(), nullable=False),
        sa.Column("client_order_id", sa.String(length=160), nullable=False),
        sa.Column("environment", sa.String(length=16), nullable=False),
        sa.Column("account_id", sa.String(length=64), nullable=False),
        sa.Column("strategy_id", sa.String(length=64), nullable=False),
        sa.Column("trade_date", sa.Date(), nullable=False),
        sa.Column("symbol", sa.String(length=32), nullable=False),
        sa.Column("exchange", sa.String(length=16), nullable=False),
        sa.Column("side", sa.String(length=8), nullable=False),
        sa.Column("order_type", sa.String(length=16), nullable=False),
        sa.Column("target_quantity", sa.BigInteger(), nullable=False),
        sa.Column("limit_price", sa.Numeric(precision=20, scale=6), nullable=True),
        sa.Column("risk_run_id", sa.Uuid(), nullable=False),
        sa.Column("status", sa.String(length=32), nullable=False),
        sa.Column("expires_at", sa.DateTime(timezone=True), nullable=True),
        sa.Column(
            "created_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.PrimaryKeyConstraint("order_intent_id"),
        sa.UniqueConstraint(
            "account_id",
            "client_order_id",
            name="uq_order_intent_client",
        ),
        schema="execution",
    )

    op.create_table(
        "command_outbox",
        sa.Column("command_id", sa.Uuid(), nullable=False),
        sa.Column("aggregate_type", sa.String(length=32), nullable=False),
        sa.Column("aggregate_id", sa.Uuid(), nullable=False),
        sa.Column("command_type", sa.String(length=32), nullable=False),
        sa.Column(
            "payload_json",
            postgresql.JSONB(astext_type=sa.Text()),
            nullable=False,
        ),
        sa.Column("status", sa.String(length=20), nullable=False),
        sa.Column("retry_count", sa.Integer(), nullable=False),
        sa.Column("next_retry_at", sa.DateTime(timezone=True), nullable=True),
        sa.Column("claimed_by", sa.String(length=128), nullable=True),
        sa.Column("claimed_at", sa.DateTime(timezone=True), nullable=True),
        sa.Column(
            "created_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.Column("completed_at", sa.DateTime(timezone=True), nullable=True),
        sa.PrimaryKeyConstraint("command_id"),
        schema="execution",
    )
    op.create_index(
        "ix_command_outbox_pending",
        "command_outbox",
        ["status", "next_retry_at", "created_at"],
        unique=False,
        schema="execution",
    )

    op.create_table(
        "order_event",
        sa.Column("event_id", sa.Uuid(), nullable=False),
        sa.Column("client_order_id", sa.String(length=160), nullable=False),
        sa.Column("gateway_name", sa.String(length=64), nullable=False),
        sa.Column("external_order_id", sa.String(length=128), nullable=True),
        sa.Column("event_type", sa.String(length=40), nullable=False),
        sa.Column("event_time", sa.DateTime(timezone=True), nullable=False),
        sa.Column("event_sequence", sa.BigInteger(), nullable=False),
        sa.Column("traded_quantity", sa.BigInteger(), nullable=False),
        sa.Column("remaining_quantity", sa.BigInteger(), nullable=False),
        sa.Column("price", sa.Numeric(precision=20, scale=6), nullable=True),
        sa.Column(
            "raw_payload",
            postgresql.JSONB(astext_type=sa.Text()),
            nullable=False,
        ),
        sa.Column("deduplication_key", sa.String(length=256), nullable=False),
        sa.Column(
            "received_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.PrimaryKeyConstraint("event_id"),
        sa.UniqueConstraint(
            "gateway_name",
            "deduplication_key",
            name="uq_order_event_dedup",
        ),
        schema="execution",
    )
    op.create_index(
        "ix_order_event_client_sequence",
        "order_event",
        ["client_order_id", "event_sequence"],
        unique=False,
        schema="execution",
    )

    op.create_table(
        "order_projection",
        sa.Column("client_order_id", sa.String(length=160), nullable=False),
        sa.Column("account_id", sa.String(length=64), nullable=False),
        sa.Column("symbol", sa.String(length=32), nullable=False),
        sa.Column("gateway_name", sa.String(length=64), nullable=False),
        sa.Column("external_order_id", sa.String(length=128), nullable=True),
        sa.Column("status", sa.String(length=32), nullable=False),
        sa.Column("ordered_quantity", sa.BigInteger(), nullable=False),
        sa.Column("traded_quantity", sa.BigInteger(), nullable=False),
        sa.Column(
            "average_fill_price",
            sa.Numeric(precision=20, scale=6),
            nullable=True,
        ),
        sa.Column("last_event_id", sa.Uuid(), nullable=False),
        sa.Column("last_event_sequence", sa.BigInteger(), nullable=False),
        sa.Column("updated_at", sa.DateTime(timezone=True), nullable=False),
        sa.PrimaryKeyConstraint("client_order_id"),
        schema="execution",
    )

    op.create_table(
        "trade_fill",
        sa.Column("fill_id", sa.Uuid(), nullable=False),
        sa.Column("client_order_id", sa.String(length=160), nullable=False),
        sa.Column("gateway_name", sa.String(length=64), nullable=False),
        sa.Column("external_order_id", sa.String(length=128), nullable=False),
        sa.Column("external_trade_id", sa.String(length=128), nullable=False),
        sa.Column("symbol", sa.String(length=32), nullable=False),
        sa.Column("side", sa.String(length=8), nullable=False),
        sa.Column("quantity", sa.BigInteger(), nullable=False),
        sa.Column("price", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column(
            "commission",
            sa.Numeric(precision=20, scale=6),
            nullable=False,
        ),
        sa.Column("tax", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("trade_time", sa.DateTime(timezone=True), nullable=False),
        sa.Column(
            "received_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.PrimaryKeyConstraint("fill_id"),
        sa.UniqueConstraint(
            "gateway_name",
            "external_trade_id",
            name="uq_trade_fill_external",
        ),
        schema="execution",
    )

    op.create_table(
        "position_projection",
        sa.Column("position_id", sa.Uuid(), nullable=False),
        sa.Column("environment", sa.String(length=16), nullable=False),
        sa.Column("account_id", sa.String(length=64), nullable=False),
        sa.Column("symbol", sa.String(length=32), nullable=False),
        sa.Column("total_quantity", sa.BigInteger(), nullable=False),
        sa.Column("available_quantity", sa.BigInteger(), nullable=False),
        sa.Column("frozen_quantity", sa.BigInteger(), nullable=False),
        sa.Column("average_cost", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("market_value", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("last_event_id", sa.Uuid(), nullable=True),
        sa.Column("updated_at", sa.DateTime(timezone=True), nullable=False),
        sa.PrimaryKeyConstraint("position_id"),
        sa.UniqueConstraint(
            "environment",
            "account_id",
            "symbol",
            name="uq_position_projection",
        ),
        schema="execution",
    )

    op.create_table(
        "account_snapshot",
        sa.Column("snapshot_id", sa.Uuid(), nullable=False),
        sa.Column("environment", sa.String(length=16), nullable=False),
        sa.Column("account_id", sa.String(length=64), nullable=False),
        sa.Column("balance", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("available", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("frozen", sa.Numeric(precision=20, scale=6), nullable=False),
        sa.Column("gateway_name", sa.String(length=64), nullable=False),
        sa.Column("snapshot_at", sa.DateTime(timezone=True), nullable=False),
        sa.Column(
            "received_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.PrimaryKeyConstraint("snapshot_id"),
        schema="execution",
    )
    op.create_index(
        "ix_account_snapshot_lookup",
        "account_snapshot",
        ["environment", "account_id", "snapshot_at"],
        unique=False,
        schema="execution",
    )

    op.create_table(
        "run",
        sa.Column("reconciliation_id", sa.Uuid(), nullable=False),
        sa.Column("environment", sa.String(length=16), nullable=False),
        sa.Column("account_id", sa.String(length=64), nullable=False),
        sa.Column("reason", sa.String(length=64), nullable=False),
        sa.Column("started_at", sa.DateTime(timezone=True), nullable=False),
        sa.Column("completed_at", sa.DateTime(timezone=True), nullable=True),
        sa.Column("status", sa.String(length=32), nullable=False),
        sa.Column(
            "gateway_snapshot_time",
            sa.DateTime(timezone=True),
            nullable=True,
        ),
        sa.Column(
            "internal_snapshot_time",
            sa.DateTime(timezone=True),
            nullable=True,
        ),
        sa.PrimaryKeyConstraint("reconciliation_id"),
        schema="reconciliation",
    )

    op.create_table(
        "diff",
        sa.Column("diff_id", sa.Uuid(), nullable=False),
        sa.Column("reconciliation_id", sa.Uuid(), nullable=False),
        sa.Column("entity_type", sa.String(length=32), nullable=False),
        sa.Column("symbol", sa.String(length=32), nullable=True),
        sa.Column("field_name", sa.String(length=64), nullable=False),
        sa.Column("internal_value", sa.Text(), nullable=True),
        sa.Column("gateway_value", sa.Text(), nullable=True),
        sa.Column("severity", sa.String(length=16), nullable=False),
        sa.Column("resolution_status", sa.String(length=24), nullable=False),
        sa.Column("resolution_note", sa.Text(), nullable=True),
        sa.ForeignKeyConstraint(
            ["reconciliation_id"],
            ["reconciliation.run.reconciliation_id"],
            ondelete="CASCADE",
        ),
        sa.PrimaryKeyConstraint("diff_id"),
        schema="reconciliation",
    )

    op.create_table(
        "system_alert",
        sa.Column("alert_id", sa.Uuid(), nullable=False),
        sa.Column("severity", sa.String(length=16), nullable=False),
        sa.Column("source", sa.String(length=64), nullable=False),
        sa.Column("code", sa.String(length=64), nullable=False),
        sa.Column("message", sa.Text(), nullable=False),
        sa.Column(
            "context_json",
            postgresql.JSONB(astext_type=sa.Text()),
            nullable=False,
        ),
        sa.Column(
            "created_at",
            sa.DateTime(timezone=True),
            server_default=sa.text("now()"),
            nullable=False,
        ),
        sa.Column("acknowledged_at", sa.DateTime(timezone=True), nullable=True),
        sa.PrimaryKeyConstraint("alert_id"),
        schema="audit",
    )


def downgrade() -> None:
    op.drop_table("system_alert", schema="audit")
    op.drop_table("diff", schema="reconciliation")
    op.drop_table("run", schema="reconciliation")
    op.drop_index(
        "ix_account_snapshot_lookup",
        table_name="account_snapshot",
        schema="execution",
    )
    op.drop_table("account_snapshot", schema="execution")
    op.drop_table("position_projection", schema="execution")
    op.drop_table("trade_fill", schema="execution")
    op.drop_table("order_projection", schema="execution")
    op.drop_index(
        "ix_order_event_client_sequence",
        table_name="order_event",
        schema="execution",
    )
    op.drop_table("order_event", schema="execution")
    op.drop_index(
        "ix_command_outbox_pending",
        table_name="command_outbox",
        schema="execution",
    )
    op.drop_table("command_outbox", schema="execution")
    op.drop_table("order_intent", schema="execution")

    for schema in reversed(SCHEMAS):
        op.execute(f'DROP SCHEMA IF EXISTS "{schema}"')

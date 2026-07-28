import os
from datetime import UTC, date, datetime
from decimal import Decimal
from uuid import uuid4

import pytest
from sqlalchemy import delete, select

from aqr.domain.order import (
    OrderEventType,
    OrderIntent,
    OrderKind,
    Side,
    TradingEnvironment,
)
from aqr.execution.events import OrderEvent
from aqr.execution.repositories.sqlalchemy import SqlAlchemyExecutionRepository
from aqr.persistence.database import build_engine, build_session_factory
from aqr.persistence.models import (
    CommandOutboxModel,
    OrderEventModel,
    OrderIntentModel,
    OrderProjectionModel,
)


@pytest.mark.skipif(
    not os.getenv("AQR_DATABASE_URL"), reason="AQR_DATABASE_URL is not configured"
)
def test_transactional_outbox_is_idempotent_in_postgres() -> None:
    client_order_id = f"TEST-A01-S01-20260727-600519-SSE-BUY-{uuid4().hex[:8]}"
    intent = OrderIntent(
        client_order_id=client_order_id,
        environment=TradingEnvironment.PAPER,
        account_id="A01",
        strategy_id="S01",
        trade_date=date(2026, 7, 27),
        symbol="600519",
        exchange="SSE",
        side=Side.BUY,
        order_type=OrderKind.LIMIT,
        target_quantity=100,
        limit_price=Decimal("1500"),
        risk_run_id=uuid4(),
    )
    engine = build_engine(os.environ["AQR_DATABASE_URL"])
    factory = build_session_factory(engine)
    repository = SqlAlchemyExecutionRepository(factory)

    try:
        first = repository.create_order_with_command(intent)
        second = repository.create_order_with_command(intent)
        assert first == second
        assert repository.load_open_order_ids() == set()

        repository.claim_pending("integration-worker")
        assert repository.recover_stale_claims(
            datetime.now(UTC), "integration-worker"
        ) == []
        repository.claim_pending("integration-worker")
        repository.append_order_event(
            OrderEvent(
                client_order_id=client_order_id,
                gateway_name="PAPER",
                event_type=OrderEventType.ORDER_SUBMITTING,
                event_time=datetime.now(UTC),
                event_sequence=1,
                traded_quantity=0,
                remaining_quantity=100,
                raw_payload={},
                deduplication_key=f"submitting:{client_order_id}",
            )
        )
        ambiguous = repository.recover_stale_claims(
            datetime.now(UTC), "integration-worker"
        )
        assert len(ambiguous) == 1
        assert repository.load_unknown_order_ids() == {client_order_id}

        with factory() as session:
            assert session.scalar(
                select(OrderIntentModel).where(
                    OrderIntentModel.client_order_id == client_order_id
                )
            )
            assert session.scalar(
                select(CommandOutboxModel).where(
                    CommandOutboxModel.aggregate_id == intent.order_intent_id
                )
            )
            projection = session.get(OrderProjectionModel, client_order_id)
            assert projection is not None
            assert projection.status == "UNKNOWN"
    finally:
        with factory.begin() as session:
            session.execute(
                delete(CommandOutboxModel).where(
                    CommandOutboxModel.aggregate_id == intent.order_intent_id
                )
            )
            session.execute(
                delete(OrderEventModel).where(
                    OrderEventModel.client_order_id == client_order_id
                )
            )
            session.execute(
                delete(OrderProjectionModel).where(
                    OrderProjectionModel.client_order_id == client_order_id
                )
            )
            session.execute(
                delete(OrderIntentModel).where(
                    OrderIntentModel.client_order_id == client_order_id
                )
            )
        engine.dispose()

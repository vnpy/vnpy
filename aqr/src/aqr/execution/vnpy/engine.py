from __future__ import annotations

from datetime import UTC, datetime, timedelta

from vnpy.event import EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine

from aqr.config import Settings
from aqr.execution.repositories.sqlalchemy import SqlAlchemyExecutionRepository
from aqr.execution.vnpy.ack_monitor import OrderAcknowledgementMonitor
from aqr.execution.vnpy.command_consumer import OutboxCommandConsumer
from aqr.execution.vnpy.event_bridge import ExecutionEventBridge
from aqr.execution.vnpy.gateway_router import GatewayRouter
from aqr.execution.vnpy.heartbeat import HeartbeatMonitor
from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.execution.vnpy.runtime import VnpyExecutionRuntime
from aqr.persistence.database import (
    build_engine,
    build_session_factory,
    database_is_ready,
)
from aqr.reconciliation.scheduler import ReconciliationScheduler
from aqr.reconciliation.service import ReconciliationService

APP_NAME = "AqrExecution"


class AqrExecutionEngine(BaseEngine):
    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        super().__init__(main_engine, event_engine, APP_NAME)
        self.settings = Settings()
        self.kill_switch = KillSwitch()
        self.heartbeat = HeartbeatMonitor(
            timedelta(seconds=self.settings.heartbeat_timeout_seconds)
        )

        self.db_engine = build_engine(self.settings.database_url)
        self.session_factory = build_session_factory(self.db_engine)
        self.repository = SqlAlchemyExecutionRepository(
            self.session_factory,
            environment=self.settings.environment,
            account_id=self.settings.account_id,
        )
        self.event_bridge = ExecutionEventBridge(
            event_engine, self.repository, self.kill_switch
        )
        self.runtime = VnpyExecutionRuntime(
            main_engine,
            GatewayRouter(default_gateway=self.settings.gateway_name),
            self.event_bridge,
            self.kill_switch,
        )
        self.consumer = OutboxCommandConsumer(
            self.repository,
            self.runtime,
            self.kill_switch,
            worker_id=self.settings.worker_id,
            poll_seconds=self.settings.outbox_poll_seconds,
            claim_timeout_seconds=self.settings.outbox_claim_timeout_seconds,
        )
        self.ack_monitor = OrderAcknowledgementMonitor(
            self.repository,
            self.kill_switch,
            timeout_seconds=self.settings.order_ack_timeout_seconds,
        )
        self.reconciliation = ReconciliationService(
            self.runtime,
            self.repository,
            self.kill_switch,
            account_id=self.settings.account_id,
            max_snapshot_age_seconds=(
                self.settings.reconciliation_snapshot_max_age_seconds
            ),
        )
        self.reconciliation_scheduler = ReconciliationScheduler(
            self.reconciliation,
            self.kill_switch,
            interval_seconds=self.settings.reconciliation_interval_seconds,
        )
        self.event_bridge.start()

    def start(self) -> None:
        if not database_is_ready(self.db_engine):
            self.kill_switch.halt("PostgreSQL unavailable")
            raise RuntimeError("PostgreSQL is unavailable; execution fails closed")
        ambiguous = self.repository.recover_stale_claims(
            datetime.now(UTC),
            self.settings.worker_id,
        )
        if ambiguous:
            self.kill_switch.halt(
                "ambiguous Outbox claim recovered as UNKNOWN"
            )
            raise RuntimeError(
                f"ambiguous Outbox claims require reconciliation: {ambiguous}"
            )
        result = self.reconciliation.startup_reconcile()
        if not result.passed:
            raise RuntimeError(f"startup reconciliation failed: {result.diffs}")
        self.consumer.start()
        self.ack_monitor.start()
        self.reconciliation_scheduler.start()

    def close(self) -> None:
        self.reconciliation_scheduler.stop()
        self.ack_monitor.stop()
        self.consumer.stop()
        self.event_bridge.stop()
        self.db_engine.dispose()

import os
import time
from datetime import UTC, date, datetime
from decimal import Decimal
from uuid import uuid4

from vnpy.event import Event, EventEngine
from vnpy.trader.constant import Exchange, Product
from vnpy.trader.engine import MainEngine
from vnpy.trader.event import EVENT_CONTRACT, EVENT_TICK
from vnpy.trader.object import ContractData, TickData
from vnpy_paperaccount import PaperAccountApp
from vnpy_paperaccount.engine import PaperEngine
from vnpy_riskmanager import RiskManagerApp

from aqr.domain.order import (
    OrderIntent,
    OrderKind,
    Side,
    TradingEnvironment,
)
from aqr.execution.repositories.memory import InMemoryExecutionRepository
from aqr.execution.vnpy.command_consumer import OutboxCommandConsumer
from aqr.execution.vnpy.event_bridge import ExecutionEventBridge
from aqr.execution.vnpy.gateway_router import GatewayRouter
from aqr.execution.vnpy.kill_switch import KillSwitch
from aqr.execution.vnpy.runtime import VnpyExecutionRuntime


def wait_until(predicate, timeout: float = 3) -> None:
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        if predicate():
            return
        time.sleep(0.02)
    raise AssertionError("timed out waiting for vn.py event")


def test_real_vnpy_paperaccount_order_fill_pipeline(tmp_path) -> None:
    original_cwd = os.getcwd()
    old_data_file = PaperEngine.data_filename
    old_setting_file = PaperEngine.setting_filename
    PaperEngine.data_filename = str(tmp_path / "paper_data.json")
    PaperEngine.setting_filename = str(tmp_path / "paper_settings.json")

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    repository = InMemoryExecutionRepository()
    switch = KillSwitch()
    bridge = ExecutionEventBridge(event_engine, repository, switch)
    try:
        main_engine.add_app(PaperAccountApp)
        main_engine.add_app(RiskManagerApp)
        bridge.start()
        switch.resume("test startup reconciliation passed")
        runtime = VnpyExecutionRuntime(
            main_engine,
            GatewayRouter(default_gateway="PAPER"),
            bridge,
            switch,
        )
        consumer = OutboxCommandConsumer(
            repository, runtime, switch, worker_id="paper-e2e"
        )

        event_engine.put(
            Event(
                EVENT_CONTRACT,
                ContractData(
                    symbol="600519",
                    exchange=Exchange.SSE,
                    name="贵州茅台",
                    product=Product.EQUITY,
                    size=1,
                    pricetick=0.01,
                    min_volume=100,
                    gateway_name="TESTDATA",
                ),
            )
        )
        wait_until(lambda: main_engine.get_contract("600519.SSE") is not None)

        intent = OrderIntent(
            client_order_id=f"PAPER-A01-E2E-{uuid4().hex[:8]}",
            environment=TradingEnvironment.PAPER,
            account_id="A01",
            strategy_id="E2E",
            trade_date=date.today(),
            symbol="600519",
            exchange="SSE",
            side=Side.BUY,
            order_type=OrderKind.LIMIT,
            target_quantity=100,
            limit_price=Decimal("10.00"),
            risk_run_id=uuid4(),
        )
        repository.create_order_with_command(intent)
        assert consumer.poll_once() == 1

        event_engine.put(
            Event(
                EVENT_TICK,
                TickData(
                    symbol="600519",
                    exchange=Exchange.SSE,
                    datetime=datetime.now(UTC),
                    last_price=9.90,
                    ask_price_1=9.90,
                    ask_volume_1=10_000,
                    bid_price_1=9.89,
                    bid_volume_1=10_000,
                    gateway_name="TESTDATA",
                ),
            )
        )
        wait_until(lambda: len(repository.trade_fills) == 1)
        wait_until(lambda: repository.positions.get("600519.SSE") == 100)

        snapshot = runtime.capture_reconciliation_snapshot("A01")
        assert snapshot.positions == {"600519.SSE": 100}
        assert snapshot.active_order_ids == set()
        assert repository.trade_fills[0].quantity == 100
        assert repository.trade_fills[0].price == Decimal("9.9")
        assert repository.commands[next(iter(repository.commands))]["status"] == (
            "ACKNOWLEDGED"
        )
    finally:
        bridge.stop()
        main_engine.close()
        PaperEngine.data_filename = old_data_file
        PaperEngine.setting_filename = old_setting_file
        os.chdir(original_cwd)

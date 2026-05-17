"""Tests for auto-trading runtime wiring."""

from __future__ import annotations

import json
from types import SimpleNamespace

import pytest

from run_auto_trading import (
    STRATEGY_NAME,
    TELEGRAM_STRATEGY_CLASS_NAME,
    apply_risk_settings,
    build_okx_connect_config,
    is_strategy_config_match,
)
from vnpy.trader.setting import SETTINGS


def test_auto_trading_uses_telegram_strategy_class() -> None:
    assert TELEGRAM_STRATEGY_CLASS_NAME == "DoubleMATelegramStrategy"


def test_apply_risk_settings_overlays_runtime_settings(monkeypatch) -> None:
    monkeypatch.setitem(SETTINGS, "risk.max_order_value_usdt", 200.0)
    monkeypatch.setitem(SETTINGS, "risk.max_order_value_pct", 0.0)

    apply_risk_settings(
        {
            "risk": {
                "max_order_value_usdt": 1000.0,
                "max_order_value_pct": 0.1,
            }
        }
    )

    assert SETTINGS["risk.max_order_value_usdt"] == 1000.0
    assert SETTINGS["risk.max_order_value_pct"] == 0.1


def test_setup_strategy_registers_telegram_strategy_class(monkeypatch, tmp_path) -> None:
    import run_auto_trading

    cfg = {
        "telegram": {"bot_token": "", "chat_id": ""},
        "strategy": {
            "vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL",
            "setting": {"fast_window": 10, "slow_window": 20},
        },
        "backtest": {"capital": 10000},
    }
    cfg_path = tmp_path / "trading_config.json"
    cfg_path.write_text(json.dumps(cfg), encoding="utf-8")

    class FakeCtaEngine:
        def __init__(self) -> None:
            self.classes = {}
            self.added = None
            self.strategies = {}

        def init_engine(self) -> None:
            pass

        def add_strategy(self, **kwargs) -> None:
            self.added = kwargs
            self.strategies[kwargs["strategy_name"]] = SimpleNamespace(
                vt_symbol=kwargs["vt_symbol"],
                trading=False,
                telegram=None,
                get_parameters=lambda: kwargs["setting"],
            )

    fake_cta = FakeCtaEngine()
    fake_main = SimpleNamespace(
        add_app=lambda _app: None,
        get_engine=lambda _name: fake_cta,
        get_contract=lambda _vt_symbol: object(),
        get_gateway=lambda _gateway: SimpleNamespace(public_api=SimpleNamespace(connected=True)),
        subscribe=lambda _req, _gateway: None,
    )

    monkeypatch.setattr(run_auto_trading, "TelegramTradeBot", lambda _path: object())
    system = run_auto_trading.AutoTradingSystem(config_path=str(cfg_path))
    system.main_engine = fake_main

    try:
        system.setup_strategy()
    finally:
        system.event_engine.stop()

    assert "DoubleMATelegramStrategy" in fake_cta.classes
    assert fake_cta.added["class_name"] == "DoubleMATelegramStrategy"


def test_build_okx_connect_config_accepts_private_connect_file() -> None:
    config = {
        "API Key": "key",
        "Secret Key": "secret",
        "Passphrase": "pass",
        "Server": "DEMO",
    }

    connect_config, simulated = build_okx_connect_config(config, {})

    assert simulated is True
    assert connect_config == {
        "API Key": "key",
        "Secret Key": "secret",
        "Passphrase": "pass",
        "Server": "DEMO",
        "Proxy Host": "",
        "Proxy Port": 0,
        "Spread Trading": "False",
        "Margin Currency": "",
    }


def test_build_okx_connect_config_maps_public_config_keys() -> None:
    app_config = {
        "okx": {
            "api_key": "key",
            "api_secret": "secret",
            "passphrase": "pass",
            "use_simulated": True,
            "proxy": "127.0.0.1",
            "proxy_port": 7890,
        }
    }

    connect_config, simulated = build_okx_connect_config(None, app_config)

    assert simulated is True
    assert connect_config["Secret Key"] == "secret"
    assert connect_config["Proxy Host"] == "127.0.0.1"
    assert connect_config["Spread Trading"] == "False"


def test_strategy_config_match_detects_stale_class_and_symbol() -> None:
    class DoubleMaStrategy:
        vt_symbol = "DOGE-USDT-SWAP.GLOBAL"

    stale = DoubleMaStrategy()

    assert not is_strategy_config_match(
        stale,
        class_name=TELEGRAM_STRATEGY_CLASS_NAME,
        vt_symbol="DOGEUSDT_SWAP_OKX.GLOBAL",
        setting={"fast_window": 18, "slow_window": 20},
    )


def test_upsert_strategy_removes_stale_doublema(monkeypatch, tmp_path) -> None:
    import run_auto_trading

    cfg = {
        "telegram": {"bot_token": "", "chat_id": ""},
        "approval": {"enabled": False, "timeout_seconds": 1},
        "notification": {"mode": "notify_only"},
        "strategy": {
            "vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL",
            "setting": {"fast_window": 18, "slow_window": 20},
        },
        "backtest": {"capital": 10000},
    }
    cfg_path = tmp_path / "trading_config.json"
    cfg_path.write_text(json.dumps(cfg), encoding="utf-8")

    class StaleStrategy:
        vt_symbol = "DOGE-USDT-SWAP.GLOBAL"
        trading = False

        def __init__(self) -> None:
            self.setting = {"fast_window": 18, "slow_window": 20}

    class FakeCtaEngine:
        def __init__(self) -> None:
            self.classes = {}
            self.strategies = {STRATEGY_NAME: StaleStrategy()}
            self.removed = []
            self.added = []

        def remove_strategy(self, strategy_name: str) -> bool:
            self.removed.append(strategy_name)
            self.strategies.pop(strategy_name)
            return True

        def add_strategy(self, **kwargs) -> None:
            self.added.append(kwargs)
            self.strategies[kwargs["strategy_name"]] = SimpleNamespace(
                vt_symbol=kwargs["vt_symbol"],
                trading=False,
                setting=kwargs["setting"],
                telegram=None,
            )

    monkeypatch.setattr(run_auto_trading, "TelegramTradeBot", lambda _path: object())
    system = run_auto_trading.AutoTradingSystem(config_path=str(cfg_path), okx_config_path=str(tmp_path / "missing.json"))
    cta_engine = FakeCtaEngine()

    try:
        system.upsert_strategy(cta_engine)
    finally:
        system.main_engine.close()

    assert cta_engine.removed == [STRATEGY_NAME]
    assert cta_engine.added[0]["class_name"] == TELEGRAM_STRATEGY_CLASS_NAME


def test_wait_for_contract_times_out(monkeypatch, tmp_path) -> None:
    import run_auto_trading

    cfg = {
        "telegram": {"bot_token": "", "chat_id": ""},
        "approval": {"enabled": False, "timeout_seconds": 1},
        "notification": {"mode": "notify_only"},
        "strategy": {"vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL", "setting": {}},
        "backtest": {"capital": 10000},
    }
    cfg_path = tmp_path / "trading_config.json"
    cfg_path.write_text(json.dumps(cfg), encoding="utf-8")

    monkeypatch.setattr(run_auto_trading, "TelegramTradeBot", lambda _path: object())
    system = run_auto_trading.AutoTradingSystem(config_path=str(cfg_path), okx_config_path=str(tmp_path / "missing.json"))
    system.main_engine = SimpleNamespace(get_contract=lambda _vt_symbol: None)

    try:
        with pytest.raises(TimeoutError):
            system.wait_for_contract("DOGEUSDT_SWAP_OKX.GLOBAL", timeout=0.01, interval=0.001)
    finally:
        system.event_engine.stop()

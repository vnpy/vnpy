"""Tests for auto-trading runtime wiring."""

from __future__ import annotations

import json
from types import SimpleNamespace

import pytest

from run_auto_trading import (
    STRATEGY_NAME,
    TELEGRAM_STRATEGY_CLASS_NAME,
    apply_risk_settings,
    build_strategy_signal_key,
    build_okx_connect_config,
    format_strategy_label,
    get_strategy_spec,
    is_strategy_config_match,
    validate_strategy_safety,
)
from vnpy.trader.setting import SETTINGS


def test_auto_trading_uses_telegram_strategy_class() -> None:
    assert TELEGRAM_STRATEGY_CLASS_NAME == "DoubleMATelegramStrategy"


def test_get_strategy_spec_defaults_to_legacy_doublema() -> None:
    spec = get_strategy_spec(
        {
            "strategy": {
                "vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL",
                "setting": {"fast_window": 10, "slow_window": 20},
            }
        }
    )

    assert spec == {
        "class_name": TELEGRAM_STRATEGY_CLASS_NAME,
        "strategy_name": STRATEGY_NAME,
        "vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL",
        "setting": {"fast_window": 10, "slow_window": 20},
    }


def test_get_strategy_spec_accepts_chan_strategy_config() -> None:
    spec = get_strategy_spec(
        {
            "strategy": {
                "class_name": "ChanStrategy",
                "strategy_name": "Chan_Auto",
                "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
                "setting": {"trade_enabled": False, "fixed_size": 1},
            }
        }
    )

    assert spec == {
        "class_name": "ChanStrategy",
        "strategy_name": "Chan_Auto",
        "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
        "setting": {"trade_enabled": False, "fixed_size": 1},
    }


def test_validate_strategy_safety_allows_chan_signal_only_without_risk_caps() -> None:
    validate_strategy_safety(
        {
            "strategy": {
                "class_name": "ChanStrategy",
                "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
                "setting": {"trade_enabled": False},
            },
            "risk": {"enabled": False},
        }
    )


def test_validate_strategy_safety_rejects_live_chan_without_risk_caps() -> None:
    with pytest.raises(ValueError, match="ChanStrategy live trading requires risk.enabled=true"):
        validate_strategy_safety(
            {
                "strategy": {
                    "class_name": "ChanStrategy",
                    "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
                    "setting": {"trade_enabled": True},
                },
                "risk": {"enabled": False},
            }
        )


def test_validate_strategy_safety_rejects_live_chan_without_position_cap() -> None:
    with pytest.raises(ValueError, match="max_position"):
        validate_strategy_safety(
            {
                "strategy": {
                    "class_name": "ChanStrategy",
                    "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
                    "setting": {"trade_enabled": True},
                },
                "risk": {
                    "enabled": True,
                    "max_order_value_usdt": 100,
                    "max_daily_loss_pct": 0.01,
                },
            }
        )


def test_format_strategy_label_handles_chan_without_doublema_windows() -> None:
    label = format_strategy_label(
        {
            "class_name": "ChanStrategy",
            "setting": {"trade_enabled": False, "fixed_size": 1},
        }
    )

    assert label == "ChanStrategy ({'trade_enabled': False, 'fixed_size': 1})"


def test_build_strategy_signal_key_is_stable_for_deduplication() -> None:
    key = build_strategy_signal_key(
        {
            "type": "third_buy",
            "confirmed_index": 12,
            "bar_datetime": "2026-05-22T12:00:00+08:00",
            "reason": "ignored",
        }
    )

    assert key == "third_buy:12:2026-05-22T12:00:00+08:00"


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
    assert "ChanStrategy" in fake_cta.classes
    assert fake_cta.added["class_name"] == "DoubleMATelegramStrategy"


def test_setup_strategy_registers_configured_chan_strategy(monkeypatch, tmp_path) -> None:
    import run_auto_trading

    cfg = {
        "telegram": {"bot_token": "", "chat_id": ""},
        "strategy": {
            "class_name": "ChanStrategy",
            "strategy_name": "Chan_Auto",
            "vt_symbol": "BTCUSDT_SWAP_OKX.GLOBAL",
            "setting": {"trade_enabled": False, "fixed_size": 1},
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

    assert "ChanStrategy" in fake_cta.classes
    assert fake_cta.added["class_name"] == "ChanStrategy"
    assert fake_cta.added["strategy_name"] == "Chan_Auto"


def test_notify_strategy_signal_deduplicates_messages() -> None:
    import run_auto_trading

    messages: list[str] = []
    system = run_auto_trading.AutoTradingSystem.__new__(
        run_auto_trading.AutoTradingSystem
    )
    system.telegram = SimpleNamespace(submit_message=lambda msg: messages.append(msg))
    system.state = {"latest_error": ""}
    system.last_notified_strategy_signal_key = ""
    signal = {
        "type": "third_buy",
        "candidate_index": 10,
        "confirmed_index": 12,
        "stop_price": 0.1,
        "bar_datetime": "2026-05-22T12:00:00+08:00",
        "bar_close_price": 0.12,
        "trade_enabled": False,
        "reason": "回踩确认",
    }

    system.notify_strategy_signal("Chan_Auto", "DOGEUSDT_SWAP_OKX.GLOBAL", signal)
    system.notify_strategy_signal("Chan_Auto", "DOGEUSDT_SWAP_OKX.GLOBAL", signal)

    assert len(messages) == 1
    assert "Chan_Auto" in messages[0]
    assert "third_buy" in messages[0]


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

from __future__ import annotations

from types import SimpleNamespace

from vnpy_ctabacktester.engine import BacktesterEngine


class DummyMainEngine:
    def __init__(self) -> None:
        self._contracts = [
            SimpleNamespace(
                vt_symbol="BTC.USDT",
                name="Bitcoin",
                gateway_name="OKX",
                size=0.001,
                pricetick=0.1,
                min_volume=0.001,
            ),
            SimpleNamespace(
                vt_symbol="IF88.CFFEX",
                name="IF Main",
                gateway_name="CTP",
                size=300,
                pricetick=0.2,
                min_volume=1,
            ),
        ]

    def get_all_gateway_names(self) -> list[str]:
        return ["OKX", "CTP"]

    def get_all_contracts(self) -> list[SimpleNamespace]:
        return self._contracts

    def get_contract(self, vt_symbol: str) -> SimpleNamespace | None:
        for contract in self._contracts:
            if contract.vt_symbol == vt_symbol:
                return contract
        return None


def make_engine() -> BacktesterEngine:
    engine = BacktesterEngine.__new__(BacktesterEngine)
    engine.main_engine = DummyMainEngine()  # type: ignore[attr-defined]
    engine.default_channel_profile = {
        "rate": 0.0,
        "slippage": 0.0,
        "size": 1.0,
        "pricetick": 0.01,
    }
    engine._channel_profiles = {
        "OKX": {
            "rate": 0.0005,
            "slippage": 0.3,
            "size": 1.0,
            "pricetick": 0.01,
        }
    }
    engine._contract_profiles = {}
    return engine


def test_get_contract_candidates_by_gateway() -> None:
    engine = make_engine()

    okx_symbols = engine.get_contract_candidates("OKX")
    ctp_symbols = engine.get_contract_candidates("CTP")

    assert okx_symbols == ["BTC.USDT"]
    assert ctp_symbols == ["IF88.CFFEX"]


def test_resolve_contract_profile_uses_contract_and_channel() -> None:
    engine = make_engine()

    profile = engine.resolve_contract_profile("BTC.USDT", "OKX")

    assert profile["rate"] == 0.0005
    assert profile["slippage"] == 0.3
    assert profile["size"] == 0.001
    assert profile["pricetick"] == 0.1
    assert profile["min_volume"] == 0.001
    assert profile["source"] == "contract+channel"


def test_resolve_contract_profile_falls_back_to_defaults_when_contract_missing() -> None:
    engine = make_engine()

    profile = engine.resolve_contract_profile("UNKNOWN.TEST", "MISSING")

    assert profile["rate"] == 0.0
    assert profile["slippage"] == 0.0
    assert profile["size"] == 1.0
    assert profile["pricetick"] == 0.01
    assert profile["source"] == "default"


def test_resolve_contract_profile_uses_contract_profile_when_missing_contract() -> None:
    engine = make_engine()
    engine._contract_profiles = {
        "DOGEUSDT_SWAP_OKX.GLOBAL": {
            "rate": 0.0008,
            "slippage": 0.5,
            "size": 10,
            "pricetick": 0.001,
            "min_volume": 1,
        }
    }

    profile = engine.resolve_contract_profile("DOGEUSDT_SWAP_OKX.GLOBAL", "")

    assert profile["rate"] == 0.0008
    assert profile["slippage"] == 0.5
    assert profile["size"] == 10
    assert profile["pricetick"] == 0.001
    assert profile["min_volume"] == 1
    assert profile["source"] == "profile"


def test_resolve_contract_profile_keeps_explicit_zero_cost_values() -> None:
    engine = make_engine()
    engine._contract_profiles = {
        "ZERO.TEST": {
            "rate": 0.0,
            "slippage": 0.0,
            "size": 10,
            "pricetick": 0.01,
            "min_volume": 1,
        }
    }

    profile = engine.resolve_contract_profile("ZERO.TEST", "OKX")

    assert profile["rate"] == 0.0
    assert profile["slippage"] == 0.0
    assert profile["source"] == "profile"


def test_upsert_contract_profile_preserves_cost_and_updates_contract_meta() -> None:
    engine = make_engine()
    vt_symbol = "DOGEUSD_SWAP_OKX.GLOBAL"
    engine._contract_profiles[vt_symbol] = {
        "rate": 0.0008,
        "slippage": 0.5,
        "size": 1,
        "pricetick": 0.01,
        "min_volume": 1,
    }
    contract = SimpleNamespace(
        vt_symbol=vt_symbol,
        gateway_name="OKX",
        size=10.0,
        pricetick=1e-05,
        min_volume=1.0,
    )

    engine.upsert_contract_profile(contract, persist=False)

    profile = engine._contract_profiles[vt_symbol]
    assert profile["rate"] == 0.0008
    assert profile["slippage"] == 0.5
    assert profile["size"] == 10.0
    assert profile["pricetick"] == 1e-05
    assert profile["min_volume"] == 1.0
    assert profile["gateway_name"] == "OKX"

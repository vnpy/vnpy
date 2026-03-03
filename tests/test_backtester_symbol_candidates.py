from __future__ import annotations

from types import SimpleNamespace

from vnpy_ctabacktester.symbols import build_symbol_candidates, is_valid_vt_symbol


def test_build_symbol_candidates_keeps_history_when_no_contracts() -> None:
    history = [
        {"symbol": "IF88.CFFEX"},
        {"symbol": "rb2405.SHFE"},
    ]

    candidates = build_symbol_candidates(
        history_records=history,
        contract_symbols=[],
        gateway_name="CTP",
        contract_lookup=lambda symbol: None,
        has_contracts=False,
    )

    assert candidates == ["IF88.CFFEX", "rb2405.SHFE"]


def test_build_symbol_candidates_filters_history_when_contracts_available() -> None:
    history = [
        {"symbol": "IF88.CFFEX"},
        {"symbol": "rb2405.SHFE"},
    ]

    contracts = {
        "IF88.CFFEX": SimpleNamespace(gateway_name="CTP"),
        "rb2405.SHFE": SimpleNamespace(gateway_name="CTP2"),
    }

    candidates = build_symbol_candidates(
        history_records=history,
        contract_symbols=["IF88.CFFEX"],
        gateway_name="CTP",
        contract_lookup=lambda symbol: contracts.get(symbol),
        has_contracts=True,
    )

    assert candidates == ["IF88.CFFEX"]


def test_build_symbol_candidates_merges_without_duplicates() -> None:
    history = [{"symbol": "IF88.CFFEX"}]

    candidates = build_symbol_candidates(
        history_records=history,
        contract_symbols=["IF88.CFFEX", "IC88.CFFEX"],
        gateway_name="",
        contract_lookup=lambda symbol: None,
        has_contracts=True,
    )

    assert candidates == ["IF88.CFFEX", "IC88.CFFEX"]


def test_build_symbol_candidates_drops_stale_history_when_contracts_ready() -> None:
    history = [{"symbol": "DOGEUSDT_SWAP_OKX.GLOBAL"}]
    contracts = {
        "DOGEUSD_SWAP_OKX.GLOBAL": SimpleNamespace(gateway_name="OKX"),
    }

    candidates = build_symbol_candidates(
        history_records=history,
        contract_symbols=["DOGEUSD_SWAP_OKX.GLOBAL"],
        gateway_name="",
        contract_lookup=lambda symbol: contracts.get(symbol),
        has_contracts=True,
    )

    assert candidates == ["DOGEUSD_SWAP_OKX.GLOBAL"]


def test_is_valid_vt_symbol() -> None:
    assert is_valid_vt_symbol("IF88.CFFEX") is True
    assert is_valid_vt_symbol("rb2405.SHFE") is True
    assert is_valid_vt_symbol("bad_symbol") is False
    assert is_valid_vt_symbol("IF88.BAD") is False

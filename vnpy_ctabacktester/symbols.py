from __future__ import annotations

from typing import Callable, Iterable, Any

from vnpy.trader.constant import Exchange


def is_valid_vt_symbol(vt_symbol: str) -> bool:
    """
    Return True if vt_symbol is in <symbol>.<exchange> format and exchange is valid.
    """
    vt_symbol = vt_symbol.strip()
    if not vt_symbol or "." not in vt_symbol:
        return False

    symbol, exchange = vt_symbol.split(".", 1)
    if not symbol or not exchange:
        return False

    return exchange in Exchange.__members__


def build_symbol_candidates(
    history_records: list[dict],
    contract_symbols: Iterable[str],
    gateway_name: str,
    contract_lookup: Callable[[str], Any] | None,
    has_contracts: bool,
) -> list[str]:
    """
    Merge history and contract symbols, preserving order and removing duplicates.

    When contracts are not available yet, keep history symbols even if a gateway
    filter is selected so the dropdown is not empty.
    """
    history_symbols: list[str] = []

    for record in history_records:
        symbol: str = str(record.get("symbol", "")).strip()
        if not symbol:
            continue

        if not has_contracts:
            history_symbols.append(symbol)
            continue

        if contract_lookup:
            contract = contract_lookup(symbol)
        else:
            contract = None

        if not contract:
            continue

        if gateway_name and getattr(contract, "gateway_name", "") != gateway_name:
            continue

        history_symbols.append(symbol)

    merged: list[str] = []
    seen: set[str] = set()
    for symbol in list(history_symbols) + list(contract_symbols):
        if symbol in seen:
            continue
        seen.add(symbol)
        merged.append(symbol)

    return merged

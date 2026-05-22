"""Tests for the event-driven Telegram approval flow (no polling, no blocking)."""

from __future__ import annotations

import asyncio
import json
import time
from pathlib import Path
from unittest.mock import AsyncMock, MagicMock, patch

import pytest


def _make_bot(tmp_path: Path, timeout: float = 2.0, mode: str = "approval_required"):
    cfg = {
        "telegram": {"bot_token": "fake-token", "chat_id": "12345"},
        "approval": {"enabled": mode == "approval_required", "timeout_seconds": timeout},
        "notification": {"mode": mode},
    }
    cfg_path = tmp_path / "cfg.json"
    cfg_path.write_text(json.dumps(cfg))

    with patch("telegram_notifier.Bot") as fake_bot_cls:
        fake_bot_cls.return_value = MagicMock()
        from telegram_notifier import TelegramTradeBot

        tb = TelegramTradeBot(str(cfg_path))
    tb.send_message = AsyncMock()
    return tb


def _signal_info(trade_id: str) -> dict:
    return {
        "trade_id": trade_id,
        "strategy_name": "unit",
        "vt_symbol": "DOGEUSDT_SWAP_OKX.GLOBAL",
        "timestamp": "2026-04-19 00:00:00",
        "params": {"fast_window": 10, "slow_window": 20},
        "backtest": {
            "total_return": 0,
            "sharpe_ratio": 0,
            "max_drawdown": 0,
            "win_rate": 0,
        },
        "logic": "",
        "direction": "买入",
        "price": 0.1,
        "volume": 1,
        "current_pos": 0,
    }


def test_approval_resolves_via_event(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path)

    async def scenario():
        trade_id = "T1"

        async def approver():
            await asyncio.sleep(0.05)
            bot._resolve_approval(trade_id, True)

        start = time.monotonic()
        approved, _ = await asyncio.gather(
            bot.send_trade_signal(trade_id, _signal_info(trade_id)),
            approver(),
        )
        elapsed = time.monotonic() - start
        return approved, elapsed

    approved, elapsed = asyncio.run(scenario())
    assert approved is True
    assert elapsed < 0.8, f"approval took too long ({elapsed:.2f}s)"


def test_rejection_resolves_via_event(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path)

    async def scenario():
        trade_id = "T2"

        async def rejecter():
            await asyncio.sleep(0.05)
            bot._resolve_approval(trade_id, False)

        approved, _ = await asyncio.gather(
            bot.send_trade_signal(trade_id, _signal_info(trade_id)),
            rejecter(),
        )
        return approved

    assert asyncio.run(scenario()) is False


def test_timeout_returns_false(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, timeout=0.1)

    async def scenario():
        approved = await bot.send_trade_signal("T3", _signal_info("T3"))
        return approved

    assert asyncio.run(scenario()) is False
    # state is cleaned up so a new signal with the same id would work cleanly
    assert "T3" not in bot.pending_approvals
    assert "T3" not in bot.approval_events


def test_approval_disabled_auto_approves(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path)
    bot.approval_enabled = False

    async def scenario():
        return await bot.send_trade_signal("T4", _signal_info("T4"))

    assert asyncio.run(scenario()) is True


def test_notify_only_sends_signal_without_waiting(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, mode="notify_only")

    async def scenario():
        start = time.monotonic()
        approved = await bot.send_trade_signal("T5", _signal_info("T5"))
        elapsed = time.monotonic() - start
        return approved, elapsed

    approved, elapsed = asyncio.run(scenario())

    assert approved is True
    assert elapsed < 0.2
    bot.send_message.assert_awaited()
    assert "T5" not in bot.pending_approvals


def test_notify_only_message_does_not_show_approval_commands(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, mode="notify_only")

    msg = bot._format_trade_message(_signal_info("T5"))

    assert "/approve" not in msg
    assert "/reject" not in msg
    assert "通知模式" in msg


def test_approval_required_message_shows_approval_commands(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, mode="approval_required")

    msg = bot._format_trade_message(_signal_info("T6"))

    assert "/approve T6" in msg
    assert "/reject T6" in msg


def test_trade_message_escapes_html_and_missing_backtest(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, mode="notify_only")
    info = _signal_info("T<6>")
    info["logic"] = "快线1 < 慢线2 > check"
    info["backtest"] = {}

    msg = bot._format_trade_message(info)

    assert "T&lt;6&gt;" in msg
    assert "快线1 &lt; 慢线2 &gt; check" in msg
    assert "总收益: 0%" in msg


def test_shared_notifier_submit_uses_running_loop(tmp_path: Path) -> None:
    bot = _make_bot(tmp_path, mode="notify_only")

    async def scenario():
        bot.loop = asyncio.get_running_loop()
        future = bot.submit_message("hello")
        await asyncio.wrap_future(future)

    asyncio.run(scenario())

    bot.send_message.assert_awaited_with("hello")


def test_notifier_noops_without_telegram_credentials(tmp_path: Path) -> None:
    cfg = {
        "telegram": {"bot_token": "", "chat_id": ""},
        "approval": {"enabled": False, "timeout_seconds": 1},
        "notification": {"mode": "notify_only"},
    }
    cfg_path = tmp_path / "cfg.json"
    cfg_path.write_text(json.dumps(cfg))

    from telegram_notifier import TelegramTradeBot

    bot = TelegramTradeBot(str(cfg_path))

    async def scenario() -> None:
        await bot.start()
        await bot.send_message("hello")
        await bot.stop()

    asyncio.run(scenario())
    assert bot.enabled is False

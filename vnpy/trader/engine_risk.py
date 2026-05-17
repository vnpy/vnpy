"""
Risk engine: hard circuit breakers that can veto orders before they reach a gateway.

Three tiers of protection, all driven by SETTINGS["risk.*"]:
  1. max_order_value_usdt  — reject single orders whose notional exceeds the cap.
  2. max_daily_loss_pct    — once today's drawdown vs UTC-day-open exceeds the limit,
                             block new opens (closes still allowed) until the next day.
  3. max_drawdown_pct      — once equity drops below (peak * (1 - pct)), block all
                             new opens until operator manually resumes.

Wire-up in run_auto_trading.py:

    main_engine.add_engine(RiskEngine)

CtaEngine picks the engine up by name ("risk") and calls check_order() before every
live submission.
"""

from __future__ import annotations

from datetime import datetime, timezone
from typing import Any

from vnpy.event import Event, EventEngine

from .engine import BaseEngine, MainEngine
from .event import EVENT_ACCOUNT, EVENT_TRADE
from .object import AccountData, TradeData
from .setting import SETTINGS


ENGINE_NAME = "risk"


class RiskEngine(BaseEngine):
    """Circuit breakers driven by account equity events."""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        super().__init__(main_engine, event_engine, ENGINE_NAME)

        self.enabled: bool = bool(SETTINGS.get("risk.enabled", True))
        self.account_currency: str = str(SETTINGS.get("risk.account_currency", "USDT")).upper()
        self.max_daily_loss_pct: float = float(SETTINGS.get("risk.max_daily_loss_pct", 0.03))
        self.max_drawdown_pct: float = float(SETTINGS.get("risk.max_drawdown_pct", 0.10))
        self.max_order_value_usdt: float = float(SETTINGS.get("risk.max_order_value_usdt", 200.0))
        self.max_order_value_pct: float = float(SETTINGS.get("risk.max_order_value_pct", 0.0))

        self.day_start_equity: float | None = None
        self.day_start_date: str | None = None
        self.peak_equity: float = 0.0
        self.current_equity: float = 0.0

        self.daily_halt: bool = False
        self.drawdown_halt: bool = False

        self.last_rejection_reason: str = ""

        self.event_engine.register(EVENT_ACCOUNT, self._on_account)
        self.event_engine.register(EVENT_TRADE, self._on_trade)

    def _today_utc(self) -> str:
        return datetime.now(timezone.utc).strftime("%Y-%m-%d")

    def _on_account(self, event: Event) -> None:
        account: AccountData = event.data
        if self.account_currency and account.accountid.upper() != self.account_currency:
            return

        equity = float(account.balance)
        if equity <= 0:
            return

        self.current_equity = equity

        today = self._today_utc()
        if self.day_start_equity is None or self.day_start_date != today:
            self.day_start_equity = equity
            self.day_start_date = today
            self.daily_halt = False

        if equity > self.peak_equity:
            self.peak_equity = equity

        self._recheck_halts()

    def _on_trade(self, event: Event) -> None:
        # Trade events don't directly move equity (gateway sends AccountData on fill),
        # but we keep the hook so future extensions (per-strategy PnL) slot in here.
        _trade: TradeData = event.data

    def _recheck_halts(self) -> None:
        if self.day_start_equity and self.current_equity > 0:
            daily_loss = (self.day_start_equity - self.current_equity) / self.day_start_equity
            if daily_loss >= self.max_daily_loss_pct and not self.daily_halt:
                self.daily_halt = True
                self._log(
                    f"daily-loss halt triggered: "
                    f"loss={daily_loss:.2%} >= {self.max_daily_loss_pct:.2%}"
                )

        if self.peak_equity > 0 and self.current_equity > 0:
            drawdown = (self.peak_equity - self.current_equity) / self.peak_equity
            if drawdown >= self.max_drawdown_pct and not self.drawdown_halt:
                self.drawdown_halt = True
                self._log(
                    f"peak-drawdown halt triggered: "
                    f"dd={drawdown:.2%} >= {self.max_drawdown_pct:.2%}"
                )

    def _log(self, msg: str) -> None:
        self.main_engine.write_log(f"[RiskEngine] {msg}", ENGINE_NAME)

    def check_order(
        self,
        strategy: Any,
        direction: Any,
        price: float,
        volume: float,
        is_close: bool = False,
        contract: Any | None = None,
    ) -> bool:
        """
        Return True to allow the order, False to veto.

        `is_close` semantics: closing trades bypass the daily-loss halt (letting the
        system exit risk when already on halt), but still respect the drawdown halt
        and per-order size cap. Callers compute is_close from strategy.pos direction.
        """
        self.last_rejection_reason = ""

        if not self.enabled:
            return True

        contract_size = float(getattr(contract, "size", 1) or 1)
        notional = abs(price * volume * contract_size)
        if self.max_order_value_usdt > 0 and notional > self.max_order_value_usdt:
            self.last_rejection_reason = (
                f"order notional {notional:.2f} USDT > cap {self.max_order_value_usdt:.2f}"
            )
            self._log(self.last_rejection_reason)
            return False

        pct_cap = self.current_equity * self.max_order_value_pct
        if pct_cap > 0 and notional > pct_cap:
            self.last_rejection_reason = (
                f"order notional {notional:.2f} USDT > pct cap {pct_cap:.2f}"
            )
            self._log(self.last_rejection_reason)
            return False

        if self.drawdown_halt:
            self.last_rejection_reason = "peak-drawdown halt active, new opens blocked"
            self._log(f"reject {strategy.strategy_name}: {self.last_rejection_reason}")
            return False

        if self.daily_halt and not is_close:
            self.last_rejection_reason = "daily-loss halt active, new opens blocked until UTC 0"
            self._log(f"reject {strategy.strategy_name}: {self.last_rejection_reason}")
            return False

        return True

    def reset_drawdown_halt(self) -> None:
        """Operator-callable resume after reviewing the account."""
        self.drawdown_halt = False
        self.peak_equity = max(self.peak_equity, self.current_equity)
        self._log("drawdown halt manually reset")

    def snapshot(self) -> dict:
        return {
            "enabled": self.enabled,
            "current_equity": self.current_equity,
            "day_start_equity": self.day_start_equity,
            "peak_equity": self.peak_equity,
            "daily_halt": self.daily_halt,
            "drawdown_halt": self.drawdown_halt,
        }

import pytest

from aqr.execution.vnpy.kill_switch import KillSwitch, TradingHalted


def test_starts_halted_until_reconciliation() -> None:
    switch = KillSwitch()
    with pytest.raises(TradingHalted, match="startup reconciliation"):
        switch.assert_can_trade("A01")


def test_resume_requires_audit_reason() -> None:
    switch = KillSwitch()
    with pytest.raises(ValueError):
        switch.resume("")
    switch.resume("reconciliation passed")
    switch.assert_can_trade("A01")


def test_account_halt_is_scoped() -> None:
    switch = KillSwitch()
    switch.resume("startup passed")
    switch.halt("gateway disconnected", account_id="A01")
    with pytest.raises(TradingHalted):
        switch.assert_can_trade("A01")
    switch.assert_can_trade("A02")

"""Tests for OKX auto-trading process-control shell entrypoint."""

from __future__ import annotations

import subprocess
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "okx_auto_trading.sh"


def test_okx_auto_trading_help_succeeds() -> None:
    proc = subprocess.run(
        [str(SCRIPT), "--help"],
        check=False,
        capture_output=True,
        text=True,
    )

    assert proc.returncode == 0
    assert "start|stop|status|restart|health|tail" in proc.stdout


def test_okx_auto_trading_rejects_unknown_command() -> None:
    proc = subprocess.run(
        [str(SCRIPT), "nonsense"],
        check=False,
        capture_output=True,
        text=True,
    )

    assert proc.returncode == 2
    assert "Unknown command" in proc.stderr

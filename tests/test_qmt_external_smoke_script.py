"""Tests for the QMT external smoke shell entrypoint."""

from __future__ import annotations

import os
import subprocess
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "qmt_external_smoke.sh"


def test_qmt_external_smoke_help_succeeds() -> None:
    proc = subprocess.run(
        [str(SCRIPT), "--help"],
        check=False,
        capture_output=True,
        text=True,
    )

    assert proc.returncode == 0
    assert "/rebalance dry_run idempotency" in proc.stdout


def test_qmt_external_smoke_requires_token_by_default() -> None:
    env = os.environ.copy()
    env.pop("QMT_BRIDGE_TOKEN", None)

    proc = subprocess.run(
        [str(SCRIPT)],
        check=False,
        capture_output=True,
        text=True,
        env=env,
    )

    assert proc.returncode == 2
    assert "QMT bridge token is required" in proc.stderr

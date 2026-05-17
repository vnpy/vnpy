"""Tests for the QMT bridge remote-control shell entrypoint."""

from __future__ import annotations

import subprocess
from pathlib import Path


SCRIPT = Path(__file__).resolve().parents[1] / "scripts" / "qmt_bridge_remote.sh"


def test_qmt_bridge_remote_help_succeeds() -> None:
    proc = subprocess.run(
        [str(SCRIPT), "--help"],
        check=False,
        capture_output=True,
        text=True,
    )

    assert proc.returncode == 0
    assert "start the interactive Windows task" in proc.stdout


def test_qmt_bridge_remote_rejects_unknown_command() -> None:
    proc = subprocess.run(
        [str(SCRIPT), "nonsense"],
        check=False,
        capture_output=True,
        text=True,
    )

    assert proc.returncode == 2
    assert "Unknown command" in proc.stderr

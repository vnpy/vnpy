"""Local health check for the OKX auto-trading process."""

from __future__ import annotations

import argparse
import json
import os
import subprocess
from collections.abc import Callable
from datetime import datetime
from pathlib import Path
from typing import Any

from vnpy.trader.utility import get_file_path


DEFAULT_STATE_PATH = get_file_path("okx_auto_state.json")
DEFAULT_PID_PATH = get_file_path("okx_auto_trading.pid")
MAX_TICK_AGE_SECONDS = 180.0


def load_state(path: Path = DEFAULT_STATE_PATH) -> dict[str, Any]:
    """Load runtime state or return empty state when missing/unreadable."""
    try:
        return json.loads(path.read_text(encoding="utf-8"))
    except FileNotFoundError:
        return {}
    except json.JSONDecodeError as exc:
        return {"latest_error": f"invalid state json: {exc}"}


def process_alive(pid: int) -> bool:
    """Return whether a local process id appears alive."""
    if pid <= 0:
        return False
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    except PermissionError:
        return True
    return True


def list_auto_trading_pids() -> list[int]:
    """Return local run_auto_trading.py process ids from the process table."""
    try:
        output = subprocess.check_output(
            ["ps", "-axo", "pid=,command="],
            text=True,
            stderr=subprocess.DEVNULL,
        )
    except (OSError, subprocess.SubprocessError):
        return []

    pids: list[int] = []
    for line in output.splitlines():
        stripped = line.strip()
        if "run_auto_trading.py" not in stripped:
            continue
        if "rg " in stripped or "pytest" in stripped or "tmux " in stripped:
            continue
        pid_text = stripped.split(maxsplit=1)[0]
        try:
            pids.append(int(pid_text))
        except ValueError:
            continue
    return sorted(set(pids))


def _parse_iso(value: str) -> datetime | None:
    if not value:
        return None
    try:
        return datetime.fromisoformat(value)
    except ValueError:
        return None


def evaluate_health(
    state_path: Path = DEFAULT_STATE_PATH,
    pid_path: Path = DEFAULT_PID_PATH,
    now_iso: str | None = None,
    process_alive: Callable[[int], bool] = process_alive,
    auto_trading_pids: Callable[[], list[int]] = list_auto_trading_pids,
) -> dict[str, Any]:
    """Evaluate health from PID and state files."""
    state = load_state(state_path)
    reasons: list[str] = []

    state_pid = int(state.get("pid", 0) or 0) if str(state.get("pid", "")).isdigit() else 0
    pid_from_file = pid_path.exists()
    pid_source = "state"
    if pid_from_file:
        pid_text = pid_path.read_text(encoding="utf-8").strip()
    else:
        pid_text = str(state.get("pid", ""))

    try:
        pid = int(pid_text or state.get("pid", 0) or 0)
    except ValueError:
        pid = 0
        reasons.append("pid file invalid")

    selected_pid_alive = bool(pid and process_alive(pid))
    if pid_from_file and pid and not selected_pid_alive and state_pid and process_alive(state_pid):
        reasons.append("pid file stale")
        pid = state_pid
        pid_source = "state"
        selected_pid_alive = True
    elif pid_from_file:
        pid_source = "file"

    if pid and not selected_pid_alive:
        reasons.append("process not alive")

    if not state:
        reasons.append("state file missing")

    running_auto_pids = auto_trading_pids()
    if len(running_auto_pids) > 1:
        joined = ",".join(str(p) for p in running_auto_pids)
        reasons.append(f"multiple auto-trading processes: {joined}")

    if state.get("okx_server") != "DEMO":
        reasons.append("not running on OKX DEMO")
    if not state.get("contract_ready"):
        reasons.append("contract not ready")
    if not state.get("strategy_inited"):
        reasons.append("strategy not inited")
    if not state.get("strategy_trading"):
        reasons.append("strategy not trading")

    now = _parse_iso(now_iso or datetime.now().astimezone().isoformat())
    tick_time = _parse_iso(str(state.get("latest_tick_ts", "")))
    tick_age = None
    if now and tick_time:
        tick_age = max(0.0, (now - tick_time).total_seconds())
        if tick_age > MAX_TICK_AGE_SECONDS:
            reasons.append("latest tick too old")
    else:
        reasons.append("latest tick missing")

    if state.get("latest_error"):
        reasons.append("latest error present")
    if (
        state.get("strategy_class") == "ChanStrategy"
        and state.get("strategy_trade_enabled")
        and "latest_chan_signal" not in state
    ):
        reasons.append("Chan latest signal missing")

    status = "healthy" if not reasons else "degraded"
    if "process not alive" in reasons or "state file missing" in reasons:
        status = "down"
    elif reasons == ["pid file stale"]:
        status = "degraded_stale_pid"

    return {
        "status": status,
        "reasons": reasons,
        "pid": pid,
        "pid_source": pid_source,
        "auto_trading_pids": running_auto_pids,
        "state_path": str(state_path),
        "pid_path": str(pid_path),
        "tick_age_seconds": tick_age,
        "state": state,
    }


def main() -> int:
    parser = argparse.ArgumentParser(description="Check OKX auto-trading health")
    parser.add_argument("--state", type=Path, default=DEFAULT_STATE_PATH)
    parser.add_argument("--pid", type=Path, default=DEFAULT_PID_PATH)
    args = parser.parse_args()

    result = evaluate_health(args.state, args.pid)
    print(json.dumps(result, ensure_ascii=False, indent=2))
    return 0 if result["status"] == "healthy" else 1


if __name__ == "__main__":
    raise SystemExit(main())

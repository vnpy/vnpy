# Strategy Test Pipeline Implementation Plan

> **For Claude:** REQUIRED SUB-SKILL: Use superpowers:executing-plans to implement this plan task-by-task.

**Goal:** Build a reusable local strategy acceptance pipeline with Chan as the first supported strategy.

**Architecture:** Add a durable checklist document plus a small `tools/strategy_acceptance.py` runner. The runner uses an internal registry for strategy/gate definitions, delegates existing evidence to pytest and backtest helpers, and prints compact gate summaries without contacting external systems by default.

**Tech Stack:** Python 3.12, pytest, argparse, subprocess, vn.py database/backtesting utilities, existing Chan and OKX auto-trading tests.

---

### Task 1: Add Strategy Testing Pipeline Checklist

**Files:**
- Create: `docs/strategy_testing_pipeline.md`

**Step 1: Write the checklist document**

Create `docs/strategy_testing_pipeline.md` with these sections:

```markdown
# Strategy Testing Pipeline

## Purpose

Use this checklist to move a strategy from idea to paper, DEMO, or live
automation without confusing "it runs" with "it is ready."

## Delivery Levels

- Research prototype
- Backtest candidate
- Paper candidate
- DEMO order candidate
- Live candidate

## Gates

### 1. Idea Spec

Required evidence:

- entry rules
- exit rules
- invalidation rules
- sizing rules
- excluded regimes
- known unimplemented assumptions

### 2. Signal Cases

Required evidence:

- positive cases
- rejected lookalike cases
- boundary cases
- duplicate signal cases
- raw-bar end-to-end cases

### 3. Strategy Shell

Required evidence:

- signal-only mode
- one entry per logical signal
- no accidental de-duplication of different signals
- protective stops
- reverse exits
- max position checks

### 4. Backtest

Required evidence:

- strategy class/config
- symbol, interval, date range, bar count
- signal counts
- order/trade counts
- return, drawdown, Sharpe
- open-position status

### 5. Runtime Safety

Required evidence:

- runtime mode
- exchange server mode
- explicit trade-enabled flag
- risk caps
- health fields
- notification state

### 6. Paper And DEMO Review

Required evidence:

- signal-only run report
- DEMO order run report
- logs and health snapshots
- manual review decision

## Local Acceptance Command

Use:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

## Promotion Rule

A strategy can move to the next delivery level only when the current gate
passes and remaining risks are explicitly reported.
```

**Step 2: Verify formatting**

Run:

```bash
git diff --check -- docs/strategy_testing_pipeline.md
```

Expected: PASS.

**Step 3: Commit**

```bash
git add docs/strategy_testing_pipeline.md
git commit -m "[Add] Document strategy testing pipeline"
```

### Task 2: Add Acceptance Runner Test Skeleton

**Files:**
- Create: `tests/test_strategy_acceptance.py`

**Step 1: Write failing tests for registry and errors**

Create `tests/test_strategy_acceptance.py`:

```python
from __future__ import annotations

import pytest

from tools import strategy_acceptance


def test_registry_contains_chan_gates() -> None:
    gates = strategy_acceptance.get_strategy_gates("chan")

    assert set(gates) == {"unit", "strategy", "runtime", "backtest", "all"}


def test_unknown_strategy_fails() -> None:
    with pytest.raises(strategy_acceptance.AcceptanceError, match="unknown strategy"):
        strategy_acceptance.get_strategy_gates("missing")


def test_unknown_gate_fails() -> None:
    with pytest.raises(strategy_acceptance.AcceptanceError, match="unknown gate"):
        strategy_acceptance.resolve_gate_sequence("chan", "missing")


def test_all_gate_runs_in_order() -> None:
    sequence = strategy_acceptance.resolve_gate_sequence("chan", "all")

    assert sequence == ["unit", "strategy", "runtime", "backtest"]
```

**Step 2: Run tests to verify failure**

Run:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: FAIL because `tools.strategy_acceptance` does not exist.

**Step 3: Commit only the failing tests if following strict TDD checkpoints**

Do not commit a permanently failing branch unless the next task will be
implemented immediately. If committing per task is required, combine this task
with Task 3 in the same implementation checkpoint.

### Task 3: Implement Runner Registry And CLI Shell

**Files:**
- Create: `tools/strategy_acceptance.py`
- Test: `tests/test_strategy_acceptance.py`

**Step 1: Implement minimal registry**

Create `tools/strategy_acceptance.py`:

```python
from __future__ import annotations

import argparse
import subprocess
import sys
from collections.abc import Callable, Sequence
from dataclasses import dataclass
from pathlib import Path


REPO_ROOT = Path(__file__).resolve().parents[1]
PYTHON = REPO_ROOT / ".venv" / "bin" / "python"


class AcceptanceError(RuntimeError):
    """Raised when acceptance configuration or execution fails."""


@dataclass(frozen=True)
class GateResult:
    """Result for a single acceptance gate."""

    strategy: str
    gate: str
    passed: bool
    summary: str


CommandRunner = Callable[[Sequence[str]], subprocess.CompletedProcess[str]]


CHAN_UNIT_TESTS = [
    "tests/test_chan_objects.py",
    "tests/test_chan_cases.py",
    "tests/test_chan_normalizer.py",
    "tests/test_chan_fractal.py",
    "tests/test_chan_stroke.py",
    "tests/test_chan_segment.py",
    "tests/test_chan_pivot.py",
    "tests/test_chan_trend.py",
    "tests/test_chan_signal.py",
    "tests/test_chan_analyzer.py",
]

CHAN_STRATEGY_TESTS = [
    "tests/test_chan_strategy.py",
]

CHAN_RUNTIME_TESTS = [
    "tests/test_auto_trading_wiring.py",
    "tests/test_telegram_async.py",
    "tests/test_okx_auto_health.py",
    "tests/test_okx_auto_trading_script.py",
]

GATE_ORDER = ["unit", "strategy", "runtime", "backtest"]
STRATEGY_GATES = {
    "chan": {
        "unit": CHAN_UNIT_TESTS,
        "strategy": CHAN_STRATEGY_TESTS,
        "runtime": CHAN_RUNTIME_TESTS,
        "backtest": [],
        "all": [],
    }
}


def get_strategy_gates(strategy: str) -> dict[str, list[str]]:
    """Return gate definitions for a strategy."""

    try:
        return STRATEGY_GATES[strategy]
    except KeyError as exc:
        raise AcceptanceError(f"unknown strategy: {strategy}") from exc


def resolve_gate_sequence(strategy: str, gate: str) -> list[str]:
    """Resolve one gate or all gates into execution order."""

    gates = get_strategy_gates(strategy)
    if gate == "all":
        return list(GATE_ORDER)
    if gate not in gates:
        raise AcceptanceError(f"unknown gate: {gate}")
    return [gate]


def run_command(command: Sequence[str]) -> subprocess.CompletedProcess[str]:
    """Run a subprocess command from the repository root."""

    return subprocess.run(
        list(command),
        cwd=REPO_ROOT,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )


def run_pytest_gate(
    strategy: str,
    gate: str,
    files: Sequence[str],
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run a pytest-backed gate."""

    command = [str(PYTHON), "-m", "pytest", *files, "-q"]
    completed = runner(command)
    if completed.returncode != 0:
        output = completed.stdout.strip().splitlines()
        tail = "\n".join(output[-20:])
        raise AcceptanceError(
            f"{strategy}.{gate} failed with exit code {completed.returncode}\n{tail}"
        )
    return GateResult(
        strategy=strategy,
        gate=gate,
        passed=True,
        summary=f"{strategy}.{gate}: pytest passed for {len(files)} file(s)",
    )


def run_gate(
    strategy: str,
    gate: str,
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run one acceptance gate."""

    gates = get_strategy_gates(strategy)
    if gate == "backtest":
        return run_backtest_gate(strategy)
    files = gates[gate]
    return run_pytest_gate(strategy, gate, files, runner)


def run_backtest_gate(strategy: str) -> GateResult:
    """Placeholder for the Chan backtest gate."""

    if strategy != "chan":
        raise AcceptanceError(f"backtest gate is not implemented for {strategy}")
    return GateResult(
        strategy=strategy,
        gate="backtest",
        passed=True,
        summary="chan.backtest: placeholder passed",
    )


def build_parser() -> argparse.ArgumentParser:
    """Build CLI parser."""

    parser = argparse.ArgumentParser(description="Run strategy acceptance gates.")
    parser.add_argument("--strategy", required=True)
    parser.add_argument("--gate", required=True)
    return parser


def main(argv: Sequence[str] | None = None) -> int:
    """Run acceptance gates from CLI arguments."""

    parser = build_parser()
    args = parser.parse_args(argv)
    try:
        for gate in resolve_gate_sequence(args.strategy, args.gate):
            result = run_gate(args.strategy, gate)
            print(result.summary)
    except AcceptanceError as exc:
        print(str(exc), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
```

**Step 2: Run registry tests**

Run:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 3: Add tests for command execution with fake runner**

Append:

```python
import subprocess


def test_pytest_gate_uses_expected_command() -> None:
    seen: list[list[str]] = []

    def fake_runner(command):
        seen.append(list(command))
        return subprocess.CompletedProcess(command, 0, stdout="1 passed\n")

    result = strategy_acceptance.run_pytest_gate(
        "chan",
        "strategy",
        ["tests/test_chan_strategy.py"],
        runner=fake_runner,
    )

    assert result.passed is True
    assert seen[0][-3:] == ["tests/test_chan_strategy.py", "-q"]


def test_pytest_gate_failure_reports_tail() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(command, 1, stdout="line\nFAILED test\n")

    with pytest.raises(strategy_acceptance.AcceptanceError, match="FAILED test"):
        strategy_acceptance.run_pytest_gate(
            "chan",
            "strategy",
            ["tests/test_chan_strategy.py"],
            runner=fake_runner,
        )
```

**Step 4: Run tests again**

Run:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 5: Commit**

```bash
git add tools/strategy_acceptance.py tests/test_strategy_acceptance.py
git commit -m "[Add] Create strategy acceptance runner"
```

### Task 4: Implement Chan Backtest And Signal Diagnostic Gate

**Files:**
- Modify: `tools/strategy_acceptance.py`
- Test: `tests/test_strategy_acceptance.py`

**Step 1: Write failing tests for backtest command generation**

Add a helper in `tools/strategy_acceptance.py` and tests first:

```python
def test_chan_backtest_command_contains_config() -> None:
    command = strategy_acceptance.build_chan_backtest_command()

    assert "config/trading_config_chan_signal_only.example.json" in command
    assert command[0].endswith("python")
```

Run:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py::test_chan_backtest_command_contains_config -q
```

Expected: FAIL because `build_chan_backtest_command` does not exist.

**Step 2: Implement command helper and subprocess gate**

Replace the placeholder `run_backtest_gate` with a subprocess-backed gate:

```python
def build_chan_backtest_command() -> list[str]:
    """Build the Chan acceptance backtest command."""

    script = (
        "import asyncio\n"
        "from run_auto_trading import AutoTradingSystem\n"
        "\n"
        "async def main():\n"
        "    system = AutoTradingSystem("
        "config_path='config/trading_config_chan_signal_only.example.json')\n"
        "    try:\n"
        "        await system.run_backtest_report()\n"
        "        print('ACCEPTANCE_BACKTEST_REPORT', system.backtest_report)\n"
        "    finally:\n"
        "        system.main_engine.close()\n"
        "\n"
        "asyncio.run(main())\n"
    )
    return [str(PYTHON), "-c", script]


def run_backtest_gate(
    strategy: str,
    runner: CommandRunner = run_command,
) -> GateResult:
    """Run the configured strategy backtest gate."""

    if strategy != "chan":
        raise AcceptanceError(f"backtest gate is not implemented for {strategy}")
    completed = runner(build_chan_backtest_command())
    if completed.returncode != 0:
        output = completed.stdout.strip().splitlines()
        tail = "\n".join(output[-40:])
        raise AcceptanceError(
            f"{strategy}.backtest failed with exit code {completed.returncode}\n{tail}"
        )
    summary_line = _find_last_line(completed.stdout, "ACCEPTANCE_BACKTEST_REPORT")
    return GateResult(
        strategy=strategy,
        gate="backtest",
        passed=True,
        summary=summary_line or "chan.backtest: completed",
    )


def _find_last_line(output: str, marker: str) -> str:
    """Return the last output line containing marker."""

    matches = [line for line in output.splitlines() if marker in line]
    return matches[-1] if matches else ""
```

Update `run_gate`:

```python
if gate == "backtest":
    return run_backtest_gate(strategy, runner)
```

**Step 3: Add fake-runner backtest tests**

Add:

```python
def test_backtest_gate_extracts_report_line() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(
            command,
            0,
            stdout="noise\nACCEPTANCE_BACKTEST_REPORT {'trade_count': 7}\n",
        )

    result = strategy_acceptance.run_backtest_gate("chan", runner=fake_runner)

    assert result.passed is True
    assert "trade_count" in result.summary


def test_backtest_gate_failure_reports_tail() -> None:
    def fake_runner(command):
        return subprocess.CompletedProcess(command, 1, stdout="bad\nTraceback\n")

    with pytest.raises(strategy_acceptance.AcceptanceError, match="Traceback"):
        strategy_acceptance.run_backtest_gate("chan", runner=fake_runner)
```

**Step 4: Run focused tests**

Run:

```bash
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 5: Run real backtest gate**

Run:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate backtest
```

Expected: PASS and prints `ACCEPTANCE_BACKTEST_REPORT`.

**Step 6: Commit**

```bash
git add tools/strategy_acceptance.py tests/test_strategy_acceptance.py
git commit -m "[Add] Run Chan acceptance backtest"
```

### Task 5: Run Full Acceptance And Record Baseline

**Files:**
- Modify: `docs/strategy_testing_pipeline.md`
- Optionally modify: `docs/plans/2026-05-23-strategy-test-pipeline-design.md`

**Step 1: Run full local acceptance**

Run:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

Expected:

- `chan.unit` passes.
- `chan.strategy` passes.
- `chan.runtime` passes.
- `chan.backtest` passes and prints the backtest report line.

**Step 2: Record the Chan baseline**

Append to `docs/strategy_testing_pipeline.md`:

```markdown
## Current Chan Baseline

As of 2026-05-23, the local Chan acceptance baseline is:

- unit gate: passed
- strategy gate: passed
- runtime gate: passed
- backtest gate: passed
- canonical backtest: BTCUSDT_SWAP_OKX, 1h, 2025-05-23 to 2026-05-23
- expected trade count: 7
- expected total return: about -1.99%
- expected max drawdown: about -3.95%
- known gap: third-sell has synthetic coverage but no natural BTC 1h
  one-year trigger yet
```

Use the exact values from the command output if they differ.

**Step 3: Verify docs and runner**

Run:

```bash
git diff --check -- docs/strategy_testing_pipeline.md tools/strategy_acceptance.py tests/test_strategy_acceptance.py
.venv/bin/python -m pytest tests/test_strategy_acceptance.py -q
```

Expected: PASS.

**Step 4: Commit**

```bash
git add docs/strategy_testing_pipeline.md
git commit -m "[Add] Record Chan acceptance baseline"
```

### Task 6: Final Verification

**Files:**
- No new files unless a failure requires a fix.

**Step 1: Run strategy acceptance**

Run:

```bash
.venv/bin/python tools/strategy_acceptance.py --strategy chan --gate all
```

Expected: PASS.

**Step 2: Run focused pytest suite**

Run:

```bash
.venv/bin/python -m pytest \
  tests/test_strategy_acceptance.py \
  tests/test_chan_objects.py tests/test_chan_cases.py tests/test_chan_normalizer.py \
  tests/test_chan_fractal.py tests/test_chan_stroke.py tests/test_chan_segment.py \
  tests/test_chan_pivot.py tests/test_chan_trend.py tests/test_chan_signal.py \
  tests/test_chan_analyzer.py tests/test_chan_strategy.py \
  tests/test_auto_trading_wiring.py tests/test_telegram_async.py \
  tests/test_okx_auto_health.py tests/test_okx_auto_trading_script.py -q
```

Expected: PASS.

**Step 3: Run formatting check**

Run:

```bash
git diff --check
```

Expected: PASS.

**Step 4: Report status**

Report:

- files changed;
- acceptance command output;
- test command output;
- current Chan delivery level;
- first remaining gate before DEMO order automation.


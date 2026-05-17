"""Tests for external integration check helpers.

These tests do not contact real services. Real external probes live in
test_external_integrations.py and are skipped unless explicitly enabled.
"""

from __future__ import annotations

import pytest

from tools.external_checks import external_enabled, require_env


def test_external_enabled_accepts_truthy_values(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setenv("VNPY_RUN_EXTERNAL_TESTS", "1")

    assert external_enabled() is True


def test_external_enabled_defaults_to_false(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.delenv("VNPY_RUN_EXTERNAL_TESTS", raising=False)

    assert external_enabled() is False


def test_require_env_reports_missing_names(monkeypatch: pytest.MonkeyPatch) -> None:
    monkeypatch.setenv("PRESENT", "x")
    monkeypatch.delenv("MISSING", raising=False)

    with pytest.raises(RuntimeError, match="MISSING"):
        require_env("PRESENT", "MISSING")

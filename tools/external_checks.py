"""Helpers for opt-in external integration checks."""

from __future__ import annotations

import json
import os
import subprocess
from typing import Any
from urllib.error import HTTPError, URLError
from urllib.parse import urlencode
from urllib.request import Request, urlopen


TRUTHY = {"1", "true", "yes", "on"}


def external_enabled() -> bool:
    """Return whether real external probes should run."""
    return os.getenv("VNPY_RUN_EXTERNAL_TESTS", "").strip().lower() in TRUTHY


def execute_enabled() -> bool:
    """Return whether tests may place real simulated-account orders."""
    return os.getenv("VNPY_RUN_QMT_EXECUTE_TESTS", "").strip().lower() in TRUTHY


def require_env(*names: str) -> dict[str, str]:
    """Return required environment variables or raise with all missing names."""
    values = {name: os.getenv(name, "") for name in names}
    missing = [name for name, value in values.items() if not value]
    if missing:
        raise RuntimeError(f"missing environment variables: {', '.join(missing)}")
    return values


def http_json(
    url: str,
    method: str = "GET",
    payload: dict[str, Any] | None = None,
    headers: dict[str, str] | None = None,
    timeout: float = 10,
) -> dict[str, Any]:
    """Send HTTP request and parse an object JSON response."""
    raw = None
    req_headers = dict(headers or {})
    if payload is not None:
        raw = json.dumps(payload).encode("utf-8")
        req_headers.setdefault("Content-Type", "application/json")

    req = Request(url, data=raw, headers=req_headers, method=method)
    try:
        with urlopen(req, timeout=timeout) as resp:
            data = json.loads(resp.read().decode("utf-8"))
    except HTTPError as exc:
        body = exc.read().decode("utf-8", errors="replace")
        raise RuntimeError(f"HTTP {exc.code} from {url}: {body}") from exc
    except URLError as exc:
        raise RuntimeError(f"cannot reach {url}: {exc}") from exc

    if not isinstance(data, dict):
        raise RuntimeError(f"non-object JSON from {url}: {data!r}")
    return data


def check_qmt_health(qmt_url: str) -> dict[str, Any]:
    """Call QMT bridge /health."""
    return http_json(qmt_url.rstrip("/") + "/health")


def check_qmt_positions(qmt_url: str, token: str) -> dict[str, Any]:
    """Call QMT bridge /positions with bearer auth."""
    return http_json(
        qmt_url.rstrip("/") + "/positions",
        headers={"Authorization": f"Bearer {token}"},
    )


def check_qmt_rebalance(
    qmt_url: str,
    token: str,
    request_id: str,
    mode: str,
    weights: dict[str, float],
    prices: dict[str, float],
) -> dict[str, Any]:
    """Call QMT bridge /rebalance."""
    return http_json(
        qmt_url.rstrip("/") + "/rebalance",
        method="POST",
        payload={
            "request_id": request_id,
            "mode": mode,
            "weights": weights,
            "prices": prices,
        },
        headers={"Authorization": f"Bearer {token}"},
    )


def check_telegram_get_me(bot_token: str) -> dict[str, Any]:
    """Call Telegram getMe."""
    return http_json(f"https://api.telegram.org/bot{bot_token}/getMe")


def check_telegram_send_message(bot_token: str, chat_id: str, text: str) -> dict[str, Any]:
    """Send a real Telegram message."""
    url = f"https://api.telegram.org/bot{bot_token}/sendMessage"
    data = urlencode({"chat_id": chat_id, "text": text}).encode("utf-8")
    req = Request(url, data=data, method="POST")
    with urlopen(req, timeout=10) as resp:
        payload = json.loads(resp.read().decode("utf-8"))
    if not isinstance(payload, dict):
        raise RuntimeError(f"non-object JSON from Telegram: {payload!r}")
    return payload


def check_rdagent_cli() -> dict[str, Any]:
    """Check whether rdagent CLI is available."""
    proc = subprocess.run(
        ["rdagent", "--help"],
        check=False,
        capture_output=True,
        text=True,
        timeout=20,
    )
    return {
        "ok": proc.returncode == 0,
        "returncode": proc.returncode,
        "stdout": proc.stdout[:1000],
        "stderr": proc.stderr[:1000],
    }

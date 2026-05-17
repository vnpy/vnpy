#!/usr/bin/env python3
"""Generate and submit MVP rebalance plans."""

from __future__ import annotations

import argparse
from datetime import datetime
import json
import os
from pathlib import Path
from typing import Any
from urllib.request import Request, urlopen


DEFAULT_PLAN_DIR = Path(__file__).resolve().parent / "plans"


def today_str() -> str:
    """Return local date string used in plan ids."""
    return datetime.now().strftime("%Y%m%d")


def load_json_mapping(raw: str, name: str) -> dict[str, float]:
    """Parse a JSON object of numeric values."""
    data = json.loads(raw)
    if not isinstance(data, dict):
        raise ValueError(f"{name} must be a JSON object")
    return {str(k): float(v) for k, v in data.items()}


def save_plan(
    plan_id: str,
    weights: dict[str, float],
    prices: dict[str, float],
    plan_dir: Path = DEFAULT_PLAN_DIR,
) -> Path:
    """Persist a rebalance plan for later dry-run or execution."""
    plan_dir.mkdir(parents=True, exist_ok=True)
    path = plan_dir / f"{plan_id}.json"
    payload = {
        "plan_id": plan_id,
        "created_at": datetime.now().isoformat(timespec="seconds"),
        "weights": weights,
        "prices": prices,
    }
    path.write_text(json.dumps(payload, ensure_ascii=False, indent=2), encoding="utf-8")
    return path


def load_plan(path: str | Path) -> dict[str, Any]:
    """Load a previously saved rebalance plan."""
    with Path(path).open("r", encoding="utf-8") as f:
        data = json.load(f)
    if not isinstance(data, dict):
        raise ValueError("plan file must contain a JSON object")
    for key in ["plan_id", "weights", "prices"]:
        if key not in data:
            raise ValueError(f"plan file missing {key}")
    return data


def load_latest_plan(plan_dir: Path = DEFAULT_PLAN_DIR) -> dict[str, Any]:
    """Load the newest plan file from the plan directory."""
    plans = sorted(plan_dir.glob("*.json"), key=lambda p: p.stat().st_mtime, reverse=True)
    if not plans:
        raise FileNotFoundError(f"no plan files found in {plan_dir}")
    return load_plan(plans[0])


def call_qmt_rebalance(
    qmt_url: str,
    plan: dict[str, Any],
    mode: str,
    token: str = "",
    timeout: float = 10,
) -> dict[str, Any]:
    """Submit a saved plan to the Windows QMT bridge."""
    if mode not in {"dry_run", "execute"}:
        raise ValueError("mode must be dry_run or execute")

    body = {
        "request_id": f"{plan['plan_id']}-{mode}",
        "mode": mode,
        "weights": plan["weights"],
        "prices": plan["prices"],
    }
    raw = json.dumps(body).encode("utf-8")
    url = qmt_url.rstrip("/") + "/rebalance"
    headers = {"Content-Type": "application/json"}
    if token:
        headers["Authorization"] = f"Bearer {token}"

    req = Request(url, data=raw, headers=headers, method="POST")
    with urlopen(req, timeout=timeout) as resp:
        payload = json.loads(resp.read().decode("utf-8"))
    if not isinstance(payload, dict):
        raise ValueError("QMT bridge returned non-object JSON")
    return payload


def generate_plan_from_cli(args: argparse.Namespace) -> Path:
    """Generate a plan from explicit CLI weights/prices."""
    if not args.weights_json:
        raise ValueError("--weights-json is required until RD-Agent model export is wired")
    if not args.prices_json:
        raise ValueError("--prices-json is required until price fetching is wired")

    weights = load_json_mapping(args.weights_json, "weights")
    prices = load_json_mapping(args.prices_json, "prices")
    plan_id = args.plan_id or f"{today_str()}-manual"
    return save_plan(plan_id, weights, prices, Path(args.plan_dir))


def main() -> int:
    parser = argparse.ArgumentParser(description="Generate or submit MVP rebalance plans")
    parser.add_argument("--generate", action="store_true", help="generate and save a plan")
    parser.add_argument("--submit", action="store_true", help="submit a saved plan")
    parser.add_argument("--mode", choices=["dry_run", "execute"], default="dry_run")
    parser.add_argument("--plan", default="", help="plan file path; defaults to latest")
    parser.add_argument("--plan-id", default="")
    parser.add_argument("--plan-dir", default=str(DEFAULT_PLAN_DIR))
    parser.add_argument("--weights-json", default="", help='e.g. {"510300.SH":0.01}')
    parser.add_argument("--prices-json", default="", help='e.g. {"510300.SH":4.0}')
    parser.add_argument("--qmt-url", default=os.getenv("QMT_URL", "http://127.0.0.1:18080"))
    parser.add_argument("--token", default=os.getenv("QMT_BRIDGE_TOKEN", ""))
    args = parser.parse_args()

    if args.generate == args.submit:
        parser.error("choose exactly one of --generate or --submit")

    if args.generate:
        path = generate_plan_from_cli(args)
        print(path)
        return 0

    plan = load_plan(args.plan) if args.plan else load_latest_plan(Path(args.plan_dir))
    response = call_qmt_rebalance(args.qmt_url, plan, args.mode, args.token)
    print(json.dumps(response, ensure_ascii=False, indent=2))
    return 0 if response.get("ok") else 1


if __name__ == "__main__":
    raise SystemExit(main())

"""Tests for local private trading configuration loading."""

from __future__ import annotations

import json
from pathlib import Path

from trading_config import load_trading_config, resolve_trading_config_path


def test_local_trading_config_takes_precedence(tmp_path: Path) -> None:
    public_cfg = tmp_path / "trading_config.json"
    local_cfg = tmp_path / "trading_config.local.json"

    public_cfg.write_text(
        json.dumps({"telegram": {"bot_token": "", "chat_id": ""}}),
        encoding="utf-8",
    )
    local_cfg.write_text(
        json.dumps({"telegram": {"bot_token": "private", "chat_id": "42"}}),
        encoding="utf-8",
    )

    assert resolve_trading_config_path(public_cfg) == local_cfg
    assert load_trading_config(public_cfg)["telegram"]["bot_token"] == "private"


def test_local_trading_config_merges_public_defaults(tmp_path: Path) -> None:
    public_cfg = tmp_path / "trading_config.json"
    local_cfg = tmp_path / "trading_config.local.json"

    public_cfg.write_text(
        json.dumps(
            {
                "telegram": {"bot_token": "", "chat_id": ""},
                "notification": {"mode": "notify_only"},
                "runtime": {"init_timeout": 180, "init_days": 3},
            }
        ),
        encoding="utf-8",
    )
    local_cfg.write_text(
        json.dumps({"telegram": {"bot_token": "private", "chat_id": "42"}}),
        encoding="utf-8",
    )

    config = load_trading_config(public_cfg)

    assert config["telegram"]["bot_token"] == "private"
    assert config["notification"]["mode"] == "notify_only"
    assert config["runtime"]["init_timeout"] == 180

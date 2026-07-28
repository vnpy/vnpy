from __future__ import annotations

import argparse
import os
from pathlib import Path

from alembic import command
from alembic.config import Config


def main() -> int:
    parser = argparse.ArgumentParser(description="AQR database migration utility")
    parser.add_argument("action", choices=("upgrade", "current", "history"))
    parser.add_argument("--revision", default="head")
    args = parser.parse_args()

    project_root = Path(__file__).resolve().parents[3]
    config = Config(project_root / "alembic.ini")
    if database_url := os.getenv("AQR_DATABASE_URL"):
        config.set_main_option("sqlalchemy.url", database_url.replace("%", "%%"))

    if args.action == "upgrade":
        command.upgrade(config, args.revision)
    elif args.action == "current":
        command.current(config)
    else:
        command.history(config)
    return 0

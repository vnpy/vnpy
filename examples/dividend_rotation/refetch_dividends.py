"""
Re-fetch dividend history with cash dividend + bonus/transfer share columns.

Use after fetch_data.py, or whenever the dividend CSV format changes.

Usage:
    python examples/dividend_rotation/refetch_dividends.py
"""

from time import sleep

import pandas as pd

from fetch_data import DIV_DIR, PRICE_DIR, fetch_dividend


def main() -> None:
    """Overwrite every cached dividend CSV with the full corporate-action data."""
    DIV_DIR.mkdir(parents=True, exist_ok=True)

    codes: list[str] = sorted(path.stem for path in PRICE_DIR.glob("*.csv"))
    print(f"待处理股票：{len(codes)}")

    i: int
    code: str
    for i, code in enumerate(codes, start=1):
        try:
            df = fetch_dividend(code)
            if not df.empty:
                df.to_csv(
                    DIV_DIR.joinpath(f"{code}.csv"),
                    index=False,
                    encoding="utf-8",
                )
        except Exception as exc:
            print(f"  {code} 失败：{exc}")

        if i % 50 == 0 or i == len(codes):
            print(f"  已处理 {i}/{len(codes)}")

        sleep(0.05)

    print("分红明细更新完成")


if __name__ == "__main__":
    main()

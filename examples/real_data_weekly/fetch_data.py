"""
Fetch real A-share daily bars from the public Eastmoney API.

No token is required. The script:
    1. Gets the current CSI 300 constituents (board BK0500)
    2. Fetches qfq-adjusted daily bars for the first N stocks
    3. Saves them to data/csi300_bars.csv

Usage:
    python examples/real_data_weekly/fetch_data.py
    python examples/real_data_weekly/fetch_data.py --limit 50 --start 20260601
"""

from argparse import ArgumentParser
from datetime import datetime
from pathlib import Path
from time import sleep

import pandas as pd
import requests


HEADERS: dict[str, str] = {
    "User-Agent": (
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/120.0 Safari/537.36"
    )
}

DATA_DIR: Path = Path(__file__).resolve().parent.joinpath("data")
DATA_PATH: Path = DATA_DIR.joinpath("csi300_bars.csv")

CONSTITUENT_URL: str = "https://push2.eastmoney.com/api/qt/clist/get"
KLINE_URL: str = "https://push2his.eastmoney.com/api/qt/stock/kline/get"


def to_secid(code: str) -> str | None:
    """Convert a stock code to the Eastmoney secid."""
    if code.startswith("6"):
        return f"1.{code}"
    if code.startswith(("0", "3")):
        return f"0.{code}"
    return None


def fetch_constituents(limit: int) -> list[str]:
    """Fetch the current CSI 300 constituent codes."""
    params: dict = {
        "pn": 1,
        "pz": 300,
        "po": 1,
        "np": 1,
        "fltt": 2,
        "invt": 2,
        "fid": "f3",
        "fs": "b:BK0500",
        "fields": "f12,f14",
    }

    response: requests.Response = requests.get(
        CONSTITUENT_URL, params=params, headers=HEADERS, timeout=20
    )
    response.raise_for_status()

    data: dict | None = response.json().get("data")
    if not data:
        raise RuntimeError("获取沪深300成分股失败")

    codes: list[str] = [item["f12"] for item in data["diff"]]
    return codes[:limit]


def fetch_bars(code: str, start: str, end: str) -> list[dict]:
    """Fetch qfq-adjusted daily bars for one stock."""
    secid: str | None = to_secid(code)
    if not secid:
        return []

    params: dict = {
        "secid": secid,
        "fields1": "f1,f2,f3,f4,f5,f6",
        "fields2": "f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61",
        "klt": "101",       # daily
        "fqt": "1",         # forward adjusted
        "beg": start,
        "end": end,
        "lmt": "1000",
    }

    last_error: Exception | None = None

    attempt: int
    for attempt in range(3):
        try:
            response = requests.get(
                KLINE_URL, params=params, headers=HEADERS, timeout=20
            )
            response.raise_for_status()

            data: dict | None = response.json().get("data")
            if not data:
                return []

            exchange: str = "SSE" if code.startswith("6") else "SZSE"
            rows: list[dict] = []

            line: str
            for line in data["klines"]:
                parts: list[str] = line.split(",")
                if len(parts) < 7:
                    continue

                rows.append({
                    "datetime": datetime.strptime(parts[0], "%Y-%m-%d"),
                    "symbol": code,
                    "exchange": exchange,
                    # Eastmoney volume is in lots (手), convert to shares
                    "open": float(parts[1]),
                    "close": float(parts[2]),
                    "high": float(parts[3]),
                    "low": float(parts[4]),
                    "volume": float(parts[5]) * 100,
                    "turnover": float(parts[6]),
                    "turnover_rate": float(parts[10]) if len(parts) > 10 else 0.0,
                })

            return rows
        except Exception as exc:
            last_error = exc
            sleep(0.5 * (attempt + 1))

    print(f"  跳过 {code}：{last_error}")
    return []


def main() -> None:
    """Fetch constituents and daily bars, then save a CSV."""
    parser: ArgumentParser = ArgumentParser()
    parser.add_argument("--limit", type=int, default=100, help="number of stocks")
    parser.add_argument("--start", default="20260601", help="start date YYYYMMDD")
    parser.add_argument("--end", default=None, help="end date YYYYMMDD")
    args = parser.parse_args()

    end: str = args.end or datetime.now().strftime("%Y%m%d")

    print(f"获取沪深300成分股，取前 {args.limit} 只……")
    codes: list[str] = fetch_constituents(args.limit)
    print(f"成分股数量：{len(codes)}")

    all_rows: list[dict] = []

    i: int
    code: str
    for i, code in enumerate(codes, start=1):
        rows: list[dict] = fetch_bars(code, args.start, end)
        all_rows.extend(rows)

        if i % 20 == 0 or i == len(codes):
            print(f"  已拉取 {i}/{len(codes)}，累计 {len(all_rows)} 条")

        sleep(0.05)

    if not all_rows:
        raise RuntimeError("没有拉取到任何行情数据")

    df: pd.DataFrame = pd.DataFrame(all_rows)
    df = df.sort_values(["symbol", "datetime"]).reset_index(drop=True)

    DATA_DIR.mkdir(parents=True, exist_ok=True)
    df.to_csv(DATA_PATH, index=False)

    print()
    print(f"已保存：{DATA_PATH}")
    print(f"股票数：{df['symbol'].nunique()}")
    print(f"日期范围：{df['datetime'].min().date()} ~ {df['datetime'].max().date()}")
    print(f"总行数：{len(df)}")


if __name__ == "__main__":
    main()

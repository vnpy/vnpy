"""
Fetch data for the "dividend low-vol + dividend value" monthly rotation strategy.

Sources:
    * Eastmoney public API: 10-year unadjusted daily bars + CSI 300 list
    * AkShare: historical financial indicators and dividend records

Outputs (cached, gitignored):
    data/prices/{code}.csv
    data/financial/{code}.csv
    data/dividend/{code}.csv
    data/index_000300.csv
    data/index_000922.csv

Usage:
    python examples/dividend_rotation/fetch_data.py
    python examples/dividend_rotation/fetch_data.py --limit 100
"""

from argparse import ArgumentParser
from datetime import datetime
from pathlib import Path
from time import sleep

import akshare as ak
import pandas as pd
import requests


BASE_DIR: Path = Path(__file__).resolve().parent
DATA_DIR: Path = BASE_DIR.joinpath("data")
PRICE_DIR: Path = DATA_DIR.joinpath("prices")
FIN_DIR: Path = DATA_DIR.joinpath("financial")
DIV_DIR: Path = DATA_DIR.joinpath("dividend")

HEADERS: dict[str, str] = {
    "User-Agent": (
        "Mozilla/5.0 (Windows NT 10.0; Win64; x64) "
        "AppleWebKit/537.36 (KHTML, like Gecko) "
        "Chrome/120.0 Safari/537.36"
    )
}

CONSTITUENT_URL: str = "https://push2.eastmoney.com/api/qt/clist/get"
KLINE_URL: str = "https://push2his.eastmoney.com/api/qt/stock/kline/get"


def to_secid(code: str) -> str | None:
    """Convert a stock code to Eastmoney secid."""
    if code.startswith("6"):
        return f"1.{code}"
    if code.startswith(("0", "3")):
        return f"0.{code}"
    return None


def fetch_constituents(limit: int) -> list[str]:
    """Fetch current CSI 300 constituents with pagination."""
    codes: list[str] = []
    page: int = 1

    while len(codes) < limit:
        params: dict = {
            "pn": page,
            "pz": 100,          # the endpoint caps each page at 100
            "po": 1,
            "np": 1,
            "fltt": 2,
            "invt": 2,
            "fid": "f12",       # stable sort by code
            "fs": "b:BK0500",
            "fields": "f12,f14",
        }
        response = requests.get(
            CONSTITUENT_URL, params=params, headers=HEADERS, timeout=20
        )
        response.raise_for_status()
        data = response.json().get("data")
        if not data or not data.get("diff"):
            break

        codes.extend(item["f12"] for item in data["diff"])
        page += 1

    # Deduplicate while preserving order
    unique_codes: list[str] = list(dict.fromkeys(codes))
    return unique_codes[:limit]


def fetch_kline(
    secid: str,
    start: str,
    end: str,
    fqt: str = "0",
) -> list[dict]:
    """Fetch daily bars. fqt=0 unadjusted, fqt=1 qfq."""
    params: dict = {
        "secid": secid,
        "fields1": "f1,f2,f3,f4,f5,f6",
        "fields2": "f51,f52,f53,f54,f55,f56,f57,f58,f59,f60,f61",
        "klt": "101",
        "fqt": fqt,
        "beg": start,
        "end": end,
        "lmt": "10000",
    }
    response = requests.get(
        KLINE_URL, params=params, headers=HEADERS, timeout=30
    )
    response.raise_for_status()
    data = response.json().get("data")
    if not data:
        return []

    rows: list[dict] = []
    line: str
    for line in data["klines"]:
        parts = line.split(",")
        if len(parts) < 7:
            continue
        rows.append({
            "date": parts[0],
            "open": float(parts[1]),
            "close": float(parts[2]),
            "high": float(parts[3]),
            "low": float(parts[4]),
            "volume": float(parts[5]) * 100,   # lots -> shares
            "amount": float(parts[6]),
            "turnover_rate": float(parts[10]) if len(parts) > 10 else 0.0,
        })
    return rows


def fetch_financial(code: str) -> pd.DataFrame:
    """Fetch historical financial indicators."""
    df = ak.stock_financial_analysis_indicator(
        symbol=code, start_year="2014"
    )
    keep = ["日期", "净资产收益率(%)", "主营业务收入增长率(%)",
            "净利润增长率(%)", "摊薄每股收益(元)"]
    existing = [c for c in keep if c in df.columns]
    return df[existing].copy()


def fetch_dividend(code: str) -> pd.DataFrame:
    """Fetch dividend / bonus-share history."""
    df = ak.stock_history_dividend_detail(symbol=code, indicator="分红")
    keep = ["除权除息日", "送股", "转增", "派息", "进度"]
    existing = [c for c in keep if c in df.columns]
    df = df[existing].copy()
    if "进度" in df.columns:
        df = df[df["进度"] == "实施"]
    return df


def save_index(secid: str, filename: str, start: str, end: str) -> None:
    """Save an index series."""
    rows = fetch_kline(secid, start, end)
    if rows:
        pd.DataFrame(rows).to_csv(
            DATA_DIR.joinpath(filename), index=False, encoding="utf-8"
        )


def main() -> None:
    """Fetch and cache all data."""
    parser = ArgumentParser()
    parser.add_argument("--limit", type=int, default=300)
    parser.add_argument("--start", default="20150101")
    parser.add_argument("--end", default=datetime.now().strftime("%Y%m%d"))
    parser.add_argument("--refresh", action="store_true")
    args = parser.parse_args()

    for folder in [PRICE_DIR, FIN_DIR, DIV_DIR]:
        folder.mkdir(parents=True, exist_ok=True)

    print("获取沪深300成分股……")
    codes = fetch_constituents(args.limit)
    print(f"股票数量：{len(codes)}")

    save_index("1.000300", "index_000300.csv", args.start, args.end)
    save_index("1.000015", "index_000015.csv", args.start, args.end)
    save_index("1.000922", "index_000922.csv", args.start, args.end)
    print("指数数据已保存")

    try:
        names = ak.stock_info_a_code_name()
        names.to_csv(
            DATA_DIR.joinpath("names.csv"), index=False, encoding="utf-8"
        )
        print("股票名称已保存")
    except Exception as exc:
        print(f"股票名称获取失败：{exc}")

    i: int
    code: str
    for i, code in enumerate(codes, start=1):
        price_path = PRICE_DIR.joinpath(f"{code}.csv")
        fin_path = FIN_DIR.joinpath(f"{code}.csv")
        div_path = DIV_DIR.joinpath(f"{code}.csv")

        try:
            if args.refresh or not price_path.exists():
                rows = fetch_kline(to_secid(code) or "", args.start, args.end)
                if rows:
                    pd.DataFrame(rows).to_csv(
                        price_path, index=False, encoding="utf-8"
                    )
                sleep(0.03)

            if args.refresh or not fin_path.exists():
                fin = fetch_financial(code)
                if not fin.empty:
                    fin.to_csv(fin_path, index=False, encoding="utf-8")
                sleep(0.05)

            if args.refresh or not div_path.exists():
                div = fetch_dividend(code)
                if not div.empty:
                    div.to_csv(div_path, index=False, encoding="utf-8")
                sleep(0.05)
        except Exception as exc:
            print(f"  {code} 失败：{exc}")

        if i % 20 == 0 or i == len(codes):
            print(f"  已处理 {i}/{len(codes)}")

    print("数据抓取完成")


if __name__ == "__main__":
    main()

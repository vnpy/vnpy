"""
Plot the backtest equity curve and drawdown.

Inputs:
    data/equity_curve.csv
    data/index_000300.csv
    data/index_000015.csv
    data/index_000922.csv

Outputs:
    data/equity_curve.png

Usage:
    python examples/dividend_rotation/plot_equity.py
"""

from pathlib import Path

import matplotlib

matplotlib.use("Agg")

import matplotlib.dates as mdates
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick
import pandas as pd


BASE_DIR: Path = Path(__file__).resolve().parent
DATA_DIR: Path = BASE_DIR.joinpath("data")

plt.rcParams["font.sans-serif"] = [
    "Microsoft YaHei",
    "SimHei",
    "Arial Unicode MS",
]
plt.rcParams["axes.unicode_minus"] = False


def load_index(filename: str, index: pd.DatetimeIndex) -> pd.Series:
    """Load an index close series aligned to the equity dates."""
    df = pd.read_csv(DATA_DIR.joinpath(filename), parse_dates=["date"])
    series = df.set_index("date")["close"].sort_index()
    return series.reindex(index).ffill()


def main() -> None:
    """Draw the cumulative return and drawdown chart."""
    equity_df = pd.read_csv(
        DATA_DIR.joinpath("equity_curve.csv"), parse_dates=["date"]
    )
    equity = equity_df.set_index("date")["equity"].sort_index()

    index = equity.index
    bench_300 = load_index("index_000300.csv", index)
    bench_015 = load_index("index_000015.csv", index)
    bench_922 = load_index("index_000922.csv", index)

    series = {
        "策略": equity,
        "沪深300": bench_300,
        "上证红利": bench_015,
        "中证红利": bench_922,
    }

    colors = {
        "策略": "#c0392b",
        "沪深300": "#7f8c8d",
        "上证红利": "#2980b9",
        "中证红利": "#27ae60",
    }

    fig, (ax1, ax2) = plt.subplots(
        2,
        1,
        figsize=(15, 8.5),
        sharex=True,
        gridspec_kw={"height_ratios": [3.2, 1.0]},
    )

    name: str
    s: pd.Series
    for name, s in series.items():
        cumulative = s / s.iloc[0] - 1.0
        cagr = (s.iloc[-1] / s.iloc[0]) ** (252.0 / len(s)) - 1.0
        ax1.plot(
            cumulative.index,
            cumulative.values,
            label=(
                f"{name}  累计 {cumulative.iloc[-1]:+.1%} "
                f"/ 年化 {cagr:+.1%}"
            ),
            color=colors[name],
            linewidth=2.4 if name == "策略" else 1.3,
            alpha=1.0 if name == "策略" else 0.85,
        )

    ax1.axhline(0, color="gray", linewidth=0.8, alpha=0.6)
    ax1.set_title(
        "红利低波 + 红利价值 月度轮动：累计增长率（2016-11 ~ 2026-11）",
        fontsize=16,
        pad=12,
    )
    ax1.set_ylabel("累计增长率", fontsize=12)
    ax1.yaxis.set_major_formatter(mtick.PercentFormatter(1.0))
    ax1.grid(True, alpha=0.25)
    ax1.legend(loc="upper left", fontsize=9, frameon=False)

    drawdown = equity / equity.cummax() - 1.0
    ax2.fill_between(
        drawdown.index,
        drawdown.values,
        0,
        color="#c0392b",
        alpha=0.25,
    )
    ax2.plot(
        drawdown.index,
        drawdown.values,
        color="#c0392b",
        linewidth=0.9,
    )
    ax2.set_ylabel("策略回撤", fontsize=12)
    ax2.yaxis.set_major_formatter(mtick.PercentFormatter(1.0))
    ax2.grid(True, alpha=0.25)
    ax2.annotate(
        f"最大回撤 {drawdown.min():.2%}",
        xy=(drawdown.idxmin(), drawdown.min()),
        xytext=(12, -18),
        textcoords="offset points",
        fontsize=10,
        color="#c0392b",
    )

    ax2.xaxis.set_major_locator(mdates.YearLocator())
    ax2.xaxis.set_major_formatter(mdates.DateFormatter("%Y"))
    fig.autofmt_xdate()
    fig.tight_layout()

    output = DATA_DIR.joinpath("equity_curve.png")
    fig.savefig(output, dpi=160, bbox_inches="tight")
    plt.close(fig)

    print(f"折线图已保存：{output}")

    # Interactive HTML with the same cumulative-growth-rate view
    try:
        import plotly.graph_objects as go

        html_fig = go.Figure()

        name: str
        s: pd.Series
        for name, s in series.items():
            growth = s / s.iloc[0] - 1.0
            cagr = (s.iloc[-1] / s.iloc[0]) ** (252.0 / len(s)) - 1.0
            html_fig.add_trace(go.Scatter(
                x=s.index,
                y=growth,
                mode="lines",
                name=(
                    f"{name}  累计 {growth.iloc[-1]:+.1%} "
                    f"/ 年化 {cagr:+.1%}"
                ),
            ))

        html_fig.add_hline(y=0, line_width=1, line_color="gray")
        html_fig.update_layout(
            title="红利低波 + 红利价值 月度轮动：累计增长率",
            xaxis_title="日期",
            yaxis_title="累计增长率",
            yaxis_tickformat=".0%",
            hovermode="x unified",
        )

        html_path = DATA_DIR.joinpath("equity_curve.html")
        try:
            html_fig.write_html(html_path)
        except PermissionError:
            html_path = DATA_DIR.joinpath("equity_curve_growth.html")
            html_fig.write_html(html_path)

        print(f"交互式图表已保存：{html_path}")
    except Exception as exc:
        print(f"HTML 图表生成失败：{exc}")


if __name__ == "__main__":
    main()

import re
from dataclasses import dataclass
from datetime import date

import numpy as np
import pandas as pd
import plotly.graph_objects as go  # type: ignore[import-untyped]
from pandas.tseries.offsets import CustomBusinessDay
from plotly.subplots import make_subplots  # type: ignore[import-untyped]
from scipy import stats
from statsmodels.regression.linear_model import OLS
from statsmodels.tools.tools import add_constant


# Plot style
_FIGURE_TEMPLATE = "ggplot2"
# coolwarm: Q1 red → Q10 blue; mid tints kept visible on gray.
_COOLWARM_Q1_TO_Q10: list[str] = [
    "#b40426",
    "#d95847",
    "#f18d6f",
    "#e8a07e",
    "#d4a08c",
    "#a8b8d4",
    "#8aabf0",
    "#6d92e8",
    "#5d7ce6",
    "#3b4cc0",
]
_HEATMAP_COLORSCALE = "RdBu_r"
# matplotlib SymmetricalLogScale defaults (base=10, linthresh=2, linscale=1).
_SYMLOG_BASE = 10.0
_SYMLOG_LINTHRESH = 2.0
_SYMLOG_LINSCALE = 1.0
# Soft green for Top-Bottom / IC / rank; light orange for wealth and cum IC.
_LINE_SOFT = "#6FA87A"
_LINE_ORANGE = "#E8A07E"
_BAND_FILL = "rgba(111, 168, 122, 0.18)"
_BASELINE = "#333333"
_TEXT = "#333333"
_TEXT_MUTED = "#555555"
_TABLE_HEADER = "#F0F2F4"
_LINE_WIDTH = 2.0
_BASELINE_WIDTH = 1.0
_BOX_OPACITY = 0.75
_FONT_TITLE = 18
_FONT_BODY = 11
_FONT_TABLE = 12
_FIGURE_HEIGHT = 5200
_FIGURE_WIDTH = 1280
_IC_HIST_BINS = 40


@dataclass(frozen=True)
class FactorMetrics:
    """Tear-sheet outputs: label metrics and 1D cumulative diagnostic series."""

    label_expression: str
    label_period: int
    date_start: pd.Timestamp
    date_end: pd.Timestamp
    sample_count: int
    asset_count: int
    quantile_count: int
    quantile_statistics: pd.DataFrame
    label_factor_returns: pd.Series
    label_quantile_mean: pd.Series
    label_quantile_by_date: pd.DataFrame
    alpha_beta: pd.DataFrame
    label_spread: pd.Series
    label_spread_stderr: pd.Series
    spread_mean: float
    ic: pd.Series
    ic_cumulative: pd.Series
    ic_mean: float
    ic_std: float
    ic_ir: float
    monthly_ic: pd.DataFrame
    quantile_turnover: pd.DataFrame
    rank_autocorrelation: pd.Series
    one_day_factor_returns: pd.Series
    one_day_quantile_returns: pd.Series


def prepare_factor_data(
    factor: pd.Series,
    label: pd.Series,
    prices: pd.DataFrame,
    quantiles: int = 10,
    filter_zscore: float | None = 20,
    max_loss: float = 0.35,
) -> pd.DataFrame:
    """Build clean factor data with ``label``, ``1D``, and quantile labels.

    ``label`` comes from ``AlphaDataset``. ``1D`` is close(t)->close(t+1) from
    ``prices`` (index=date, columns=asset). Rows missing ``label``, ``1D``, or
    finite ``factor`` are dropped together so quantile bins and 1D cumulative
    charts share one universe.

    ``filter_zscore`` applies only to the 1D diagnostic column: forward returns
    whose absolute z-score (full-sample mean and std over all 1D values) exceeds
    the threshold are set to NaN. It is not tradable preprocessing for ``label``
    or ``factor``. Pass ``None`` to disable.
    """
    initial_amount = float(len(factor.index))

    factor_copy = factor.copy()
    factor_copy.index = factor_copy.index.rename(["date", "asset"])
    factor_copy = factor_copy[np.isfinite(factor_copy)]

    label_copy = label.copy()
    label_copy.index = label_copy.index.rename(["date", "asset"])
    label_copy.name = "label"

    one_day = _compute_1d_forward_returns(factor_copy, prices, filter_zscore)

    merged_data = pd.DataFrame(
        {
            "factor": factor_copy,
            "label": label_copy,
            "1D": one_day,
        }
    )
    merged_data = merged_data.dropna()

    no_raise = max_loss != 0
    quantile_data = _quantize_factor(merged_data, quantiles, no_raise)
    merged_data["factor_quantile"] = quantile_data
    merged_data = merged_data.dropna()

    binning_amount = float(len(merged_data.index))
    tot_loss = (initial_amount - binning_amount) / initial_amount

    if tot_loss > max_loss:
        raise ValueError(
            f"max_loss ({max_loss * 100:.1f}%) exceeded "
            f"{tot_loss * 100:.1f}%, consider increasing it."
        )

    result = merged_data[["label", "1D", "factor", "factor_quantile"]]
    date_idx = result.index.names.index("date")
    date_level = result.index.levels[date_idx]
    existing_freq = getattr(date_level, "freq", None)
    if existing_freq is not None:
        freq: pd.DateOffset = existing_freq
    else:
        factor_dates = factor_copy.index.levels[factor_copy.index.names.index("date")]
        freq = _infer_trading_calendar(factor_dates, prices.index)
    # asfreq(freq) 只保留交易日，避免按自然日插周末空值。
    result.index.levels[date_idx].freq = freq
    return result


def compute_factor_metrics(
    factor_data: pd.DataFrame,
    label_expression: str,
) -> FactorMetrics:
    """Compute label metrics and 1D series for cumulative charts."""
    label_period = _extract_label_period(label_expression)

    quantile_statistics = _quantile_statistics_table(factor_data)
    label_factor_returns = _factor_returns_on_column(factor_data, "label")
    label_quantile_by_date, daily_stderr = _quantile_date_means_with_stderr(
        factor_data,
        "label",
    )
    label_quantile_mean = label_quantile_by_date.groupby(
        level="factor_quantile",
        observed=True,
    )["label"].mean()
    alpha_beta = _factor_alpha_beta_label(factor_data, label_factor_returns, label_period)

    upper_quant = int(factor_data["factor_quantile"].max())
    lower_quant = int(factor_data["factor_quantile"].min())
    label_spread_frame, label_spread_stderr_frame = _compute_mean_returns_spread(
        label_quantile_by_date,
        upper_quant,
        lower_quant,
        std_err=daily_stderr,
    )
    label_spread = label_spread_frame["label"]

    label_spread_stderr = label_spread_stderr_frame["label"]
    spread_mean = float(label_spread.mean())

    ic = _factor_information_coefficient_label(factor_data)
    ic_mean = float(ic.mean())
    ic_std = float(ic.std())
    if ic_std != 0.0:
        ic_ir = ic_mean / ic_std
    else:
        ic_ir = float("nan")
    ic_cumulative = ic.dropna().cumsum()
    monthly_ic = ic.resample("ME").mean().to_frame("label")

    quantile_factor = factor_data["factor_quantile"]
    quantile_labels = quantile_factor.sort_values().unique().tolist()
    turnover_frames = [
        _quantile_turnover(quantile_factor, int(bucket), label_period)
        for bucket in quantile_labels
    ]
    quantile_turnover = pd.concat(turnover_frames, axis=1)
    rank_autocorrelation = _factor_rank_autocorrelation(factor_data, label_period)

    one_day_factor_returns = _factor_returns_on_column(factor_data, "1D")
    one_day_quantile_by_date, _ = _quantile_date_means_with_stderr(factor_data, "1D")
    one_day_quantile_returns = one_day_quantile_by_date["1D"]

    date_level = factor_data.index.get_level_values("date")
    date_start = pd.Timestamp(date_level.min())
    date_end = pd.Timestamp(date_level.max())
    sample_count = int(len(factor_data.index))
    asset_count = int(factor_data.index.get_level_values("asset").nunique())
    quantile_count = int(factor_data["factor_quantile"].nunique())

    return FactorMetrics(
        label_expression=label_expression,
        label_period=label_period,
        date_start=date_start,
        date_end=date_end,
        sample_count=sample_count,
        asset_count=asset_count,
        quantile_count=quantile_count,
        quantile_statistics=quantile_statistics,
        label_factor_returns=label_factor_returns,
        label_quantile_mean=label_quantile_mean,
        label_quantile_by_date=label_quantile_by_date,
        alpha_beta=alpha_beta,
        label_spread=label_spread,
        label_spread_stderr=label_spread_stderr,
        spread_mean=spread_mean,
        ic=ic,
        ic_cumulative=ic_cumulative,
        ic_mean=ic_mean,
        ic_std=ic_std,
        ic_ir=ic_ir,
        monthly_ic=monthly_ic,
        quantile_turnover=quantile_turnover,
        rank_autocorrelation=rank_autocorrelation,
        one_day_factor_returns=one_day_factor_returns,
        one_day_quantile_returns=one_day_quantile_returns,
    )


def create_full_tear_sheet(
    metrics: FactorMetrics,
    factor_name: str = "因子",
) -> go.Figure:
    """Build a Plotly factor tear sheet from precomputed metrics.

    Args:
        metrics: Precomputed label metrics and 1D diagnostic series.
        factor_name: Display name for the factor or signal under analysis.

    Returns:
        A ``go.Figure`` ready for ``fig.show()``; this function does not display it.
    """
    subplot_titles = [
        "各分位累计收益表现（1D）",
        "因子加权累计收益表现（1D）",
        "各分位平均收益表现",
        "各分位收益分布",
        "多空收益差表现",
        "IC 表现",
        "月度 IC 表现",
        "IC 分布表现",
        "IC 正态 QQ 表现",
        "分位换手表现",
        "因子稳定性表现",
        "因子分位统计",
        "核心摘要",
    ]
    fig = make_subplots(
        rows=12,
        cols=2,
        subplot_titles=subplot_titles,
        vertical_spacing=0.024,
        horizontal_spacing=0.08,
        specs=[
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": True, "colspan": 2}, None],
            [{"type": "heatmap", "colspan": 2}, None],
            [{"secondary_y": False}, {"secondary_y": False}],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"secondary_y": False, "colspan": 2}, None],
            [{"type": "table", "colspan": 2}, None],
            [{"type": "table", "colspan": 2}, None],
        ],
    )

    quantile_cumulative = _add_quantile_cumulative(fig, metrics, row=1)

    wealth = metrics.one_day_factor_returns.add(1.0).cumprod()
    _add_line(
        fig,
        wealth,
        row=2,
        name="因子加权",
        color=_LINE_ORANGE,
        hover="日期=%{x}<br>累计收益=%{y:.4f}<extra></extra>",
    )
    if len(wealth.index) > 0:
        baseline = pd.Series([1.0, 1.0], index=[wealth.index[0], wealth.index[-1]])
        _add_line(
            fig,
            baseline,
            row=2,
            name="基准=1",
            color=_BASELINE,
            width=_BASELINE_WIDTH,
            hover="",
        )
        fig.data[-1].hoverinfo = "skip"

    means = metrics.label_quantile_mean.sort_index()
    mean_quantiles = _sorted_quantiles(means.index)
    mean_colors = _quantile_color_map(mean_quantiles)
    fig.add_trace(
        go.Bar(
            x=[f"Q{quantile}" for quantile in mean_quantiles],
            y=[float(means.loc[quantile]) for quantile in mean_quantiles],
            marker=dict(color=[mean_colors[quantile] for quantile in mean_quantiles]),
            name="平均 Label 收益",
            hovertemplate="分位=%{x}<br>均值=%{y:.4f}<extra></extra>",
            showlegend=False,
        ),
        row=3,
        col=1,
    )

    by_date = metrics.label_quantile_by_date.reset_index()
    box_quantiles = _sorted_quantiles(by_date["factor_quantile"].unique())
    box_colors = _quantile_color_map(box_quantiles)
    for quantile in box_quantiles:
        color = box_colors[quantile]
        mask = by_date["factor_quantile"] == quantile
        fig.add_trace(
            go.Box(
                y=by_date.loc[mask, "label"],
                name=f"Q{quantile}",
                marker=dict(color=color),
                line=dict(color=color),
                fillcolor=color,
                opacity=_BOX_OPACITY,
                boxmean=False,
                hovertemplate="分位=%{fullData.name}<br>Label=%{y:.4f}<extra></extra>",
                showlegend=False,
            ),
            row=4,
            col=1,
        )

    spread = metrics.label_spread
    _add_line(
        fig,
        spread,
        row=5,
        name="Top−Bottom",
        color=_LINE_SOFT,
        hover="日期=%{x}<br>Spread=%{y:.4f}<extra></extra>",
    )
    stderr = metrics.label_spread_stderr
    upper = spread + stderr
    lower = spread - stderr
    x_values = spread.index.tolist()
    fig.add_trace(
        go.Scatter(
            x=x_values + x_values[::-1],
            y=upper.values.tolist() + lower.values.tolist()[::-1],
            fill="toself",
            fillcolor=_BAND_FILL,
            line=dict(color="rgba(0,0,0,0)"),
            name="Spread 误差带",
            hoverinfo="skip",
            showlegend=False,
        ),
        row=5,
        col=1,
    )

    ic = metrics.ic.dropna()
    _add_line(
        fig,
        ic,
        row=6,
        name="日度 IC",
        color=_LINE_SOFT,
        hover="日期=%{x}<br>IC=%{y:.4f}<extra></extra>",
        secondary_y=False,
    )
    _add_line(
        fig,
        metrics.ic_cumulative,
        row=6,
        name="累计 IC",
        color=_LINE_ORANGE,
        hover="日期=%{x}<br>累计 IC=%{y:.4f}<extra></extra>",
        secondary_y=True,
    )

    _add_monthly_ic(fig, metrics, row=7)
    _add_ic_histogram(fig, metrics, row=8, col=1)
    _add_ic_qq(fig, metrics, row=8, col=2)
    ic_skew, ic_kurtosis, ic_jb_stat, ic_jb_pvalue = _ic_normality_stats(metrics.ic)

    turnover = metrics.quantile_turnover
    turn_quantiles = _sorted_quantiles(turnover.columns)
    turn_colors = _quantile_color_map(turn_quantiles)
    for quantile in turn_quantiles:
        _add_line(
            fig,
            turnover[quantile],
            row=9,
            name=f"Q{quantile}",
            color=turn_colors[quantile],
            hover=(
                "日期=%{x}<br>"
                f"分位={quantile}<br>"
                "换手率=%{y:.4f}<extra></extra>"
            ),
        )

    _add_line(
        fig,
        metrics.rank_autocorrelation,
        row=10,
        name="秩自相关",
        color=_LINE_SOFT,
        hover="日期=%{x}<br>自相关=%{y:.4f}<extra></extra>",
    )

    stats_frame = metrics.quantile_statistics
    stats_quantiles = _sorted_quantiles(stats_frame.index)
    ordered_stats = stats_frame.loc[stats_quantiles]
    _add_table(
        fig,
        11,
        ["分位", "最小", "最大", "均值", "标准差", "样本数", "占比"],
        [
            [f"Q{quantile}" for quantile in stats_quantiles],
            [_format_float(float(value), 4) for value in ordered_stats["min"]],
            [_format_float(float(value), 4) for value in ordered_stats["max"]],
            [_format_float(float(value), 4) for value in ordered_stats["mean"]],
            [_format_float(float(value), 4) for value in ordered_stats["std"]],
            [f"{int(value):,}" for value in ordered_stats["count"]],
            [f"{float(value):.2f}%" for value in ordered_stats["count %"]],
        ],
    )

    alpha_value = float(metrics.alpha_beta.loc["Ann. alpha", "label"])
    beta_value = float(metrics.alpha_beta.loc["beta", "label"])
    _add_table(
        fig,
        12,
        ["指标", "数值"],
        [
            [
                "Label 年化 Alpha",
                "Label Beta",
                "IC 均值",
                "IC 标准差",
                "IC IR",
                "IC 偏度",
                "IC 超额峰度",
                "Jarque-Bera 统计量",
                "Jarque-Bera p 值",
                "Top−Bottom Spread 均值",
            ],
            [
                f"{alpha_value * 100:.2f}%",
                _format_float(beta_value, 4),
                _format_float(metrics.ic_mean, 4),
                _format_float(metrics.ic_std, 4),
                _format_float(metrics.ic_ir, 4),
                _format_float(ic_skew, 4),
                _format_float(ic_kurtosis, 4),
                _format_float(ic_jb_stat, 4),
                _format_float(ic_jb_pvalue, 4),
                f"{metrics.spread_mean * 100:.2f}%",
            ],
        ],
        align=["left", "right"],
    )

    date_start = metrics.date_start.strftime("%Y-%m-%d")
    date_end = metrics.date_end.strftime("%Y-%m-%d")
    summary_text = (
        f"因子/信号：{factor_name}　|　"
        f"Label 表达式：{metrics.label_expression}<br>"
        f"分析区间：{date_start} ~ {date_end}　|　"
        f"样本数：{metrics.sample_count:,}　|　"
        f"资产数：{metrics.asset_count}　|　"
        f"分位数：{metrics.quantile_count}"
    )
    fig.update_layout(
        template=_FIGURE_TEMPLATE,
        title=dict(
            text=f"因子分析：{factor_name}",
            x=0.5,
            xanchor="center",
            font=dict(size=_FONT_TITLE, color=_TEXT),
        ),
        height=_FIGURE_HEIGHT,
        width=_FIGURE_WIDTH,
        hovermode="x unified",
        showlegend=False,
        margin=dict(t=140, b=60, r=40),
        font=dict(color=_TEXT),
    )
    fig.add_annotation(
        text=summary_text,
        xref="paper",
        yref="paper",
        x=0.0,
        y=1.08,
        showarrow=False,
        align="left",
        font=dict(size=_FONT_BODY, color=_TEXT_MUTED),
    )
    for row in (1, 2, 3, 4, 5, 6, 9, 10):
        fig.update_xaxes(showgrid=True, row=row, col=1)
        fig.update_yaxes(showgrid=True, row=row, col=1)
    for col in (1, 2):
        fig.update_xaxes(showgrid=True, row=8, col=col)
        fig.update_yaxes(showgrid=True, row=8, col=col)
    _apply_symlog_yaxis(fig, quantile_cumulative, row=1)
    return fig


def _infer_trading_calendar(
    factor_idx: pd.Index,
    prices_idx: pd.Index,
) -> CustomBusinessDay:
    """Infer a trading calendar from factor and price dates.

    Weekdays that never appear are dropped from the weekmask; missing weekdays
    inside the span become holidays.
    """
    full_idx = factor_idx.union(prices_idx)
    traded_weekdays: list[str] = []
    holidays: list[date] = []
    days_of_the_week = ["Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"]
    for day, day_str in enumerate(days_of_the_week):
        weekday_mask = full_idx.dayofweek == day
        if not weekday_mask.any():
            continue
        traded_weekdays.append(day_str)
        used_weekdays = full_idx[weekday_mask].normalize()
        all_weekdays = pd.date_range(
            full_idx.min(),
            full_idx.max(),
            freq=CustomBusinessDay(weekmask=day_str),
        ).normalize()
        missing = all_weekdays.difference(used_weekdays)
        holidays.extend(timestamp.date() for timestamp in missing)

    weekmask = " ".join(traded_weekdays)
    return CustomBusinessDay(weekmask=weekmask, holidays=holidays)


def _date_index_freq(index: pd.MultiIndex) -> pd.DateOffset | None:
    """Return the calendar frequency of the MultiIndex ``date`` level."""
    date_idx = index.names.index("date")
    return index.levels[date_idx].freq


def _compute_1d_forward_returns(
    factor: pd.Series,
    prices: pd.DataFrame,
    filter_zscore: float | None,
) -> pd.Series:
    """Compute 1D forward returns close(t)->close(t+1) aligned to factor index."""
    factor_dates = factor.index.get_level_values("date")
    if getattr(factor_dates, "tz", None) != prices.index.tz:
        raise ValueError(
            "The timezone of 'factor' is not the same as the timezone of 'prices'."
        )

    asset_names = factor.index.get_level_values("asset").unique()
    price_panel = prices.reindex(columns=asset_names)
    filled_prices = price_panel.ffill()
    period_returns = filled_prices.pct_change(1, fill_method=None)
    forward_returns = period_returns.shift(-1)

    if filter_zscore is not None:
        mask = abs(forward_returns - forward_returns.mean()) > (
            filter_zscore * forward_returns.std()
        )
        forward_returns = forward_returns.copy()
        forward_returns[mask] = np.nan

    one_day = forward_returns.stack()
    one_day.index.names = ["date", "asset"]
    one_day = one_day.reindex(factor.index)
    one_day.name = "1D"
    return one_day


def _daily_factor_quantiles(
    values: pd.Series,
    quantiles: int,
    no_raise: bool,
) -> pd.Series:
    """Assign one-day factor values into quantile buckets."""
    try:
        return pd.qcut(values, quantiles, labels=False) + 1
    except ValueError:
        if no_raise:
            return pd.Series(index=values.index, dtype=float)
        raise


def _quantize_factor(
    factor_data: pd.DataFrame,
    quantiles: int,
    no_raise: bool,
) -> pd.Series:
    """Assign period-wise factor quantiles via ``pd.qcut``."""
    pieces: list[pd.Series] = []
    for _, day_factor in factor_data.groupby(
        factor_data.index.get_level_values("date"),
        group_keys=False,
    )["factor"]:
        pieces.append(_daily_factor_quantiles(day_factor, quantiles, no_raise))
    factor_quantile = pd.concat(pieces)
    factor_quantile.name = "factor_quantile"
    return factor_quantile.dropna()


def _extract_label_period(label_expression: str) -> int:
    """Extract label observation horizon from two ``ts_delay(close, offset)`` terms.

    The horizon is the absolute offset difference in trading sessions (bars),
    not calendar days.
    """
    pattern = re.compile(
        r"ts_delay\s*\(\s*close\s*,\s*(-?\d+)\s*\)",
        re.IGNORECASE,
    )
    matches = pattern.findall(label_expression)
    if len(matches) != 2:
        raise ValueError(
            "label_expression must contain exactly two ts_delay(close, integer_offset) "
            f"terms; found {len(matches)}"
        )
    offset_a = int(matches[0])
    offset_b = int(matches[1])
    period = abs(offset_a - offset_b)
    if period == 0:
        raise ValueError("label period must be positive")
    return period


def _quantile_statistics_table(factor_data: pd.DataFrame) -> pd.DataFrame:
    """Build the quantile statistics table for a tear sheet."""
    quantile_stats = factor_data.groupby("factor_quantile", observed=True)["factor"].agg(
        ["min", "max", "mean", "std", "count"]
    )
    quantile_stats["count %"] = (
        quantile_stats["count"] / quantile_stats["count"].sum() * 100.0
    )
    return quantile_stats


def _factor_to_weights(group: pd.Series) -> pd.Series:
    """Build dollar-neutral weights from one cross-section of factor values."""
    weighted = group - group.mean()
    return weighted / weighted.abs().sum()


def _factor_returns_on_column(factor_data: pd.DataFrame, column: str) -> pd.Series:
    """Compute daily dollar-neutral factor portfolio returns on one column."""
    freq = _date_index_freq(factor_data.index)

    weights = factor_data.groupby(
        factor_data.index.get_level_values("date"),
        group_keys=False,
        observed=True,
    )["factor"].apply(_factor_to_weights)

    weighted_returns = factor_data[column].multiply(weights, axis=0)
    returns = weighted_returns.groupby(level="date").sum(min_count=1).asfreq(freq)
    returns.name = column
    return returns


def _quantile_date_means_with_stderr(
    factor_data: pd.DataFrame,
    column: str,
) -> tuple[pd.DataFrame, pd.DataFrame]:
    """Demeaned mean of ``column`` by quantile and date, plus daily stderr."""
    demeaned = factor_data[column].groupby(
        factor_data.index.get_level_values("date"),
        observed=True,
    ).transform(lambda day_values: day_values - day_values.mean())
    frame = pd.DataFrame(
        {
            "factor_quantile": factor_data["factor_quantile"],
            column: demeaned,
        }
    )
    grouped = frame.groupby(
        ["factor_quantile", frame.index.get_level_values("date")],
        observed=True,
    )[column]
    mean_ret = grouped.mean().to_frame(column)
    stderr = (grouped.std() / np.sqrt(grouped.count())).to_frame(column)
    return mean_ret, stderr


def _factor_alpha_beta_label(
    factor_data: pd.DataFrame,
    returns: pd.Series,
    label_period: int,
) -> pd.DataFrame:
    """Compute factor alpha and beta versus the universe mean label return.

    ``label_period`` is the session/observation horizon from ``label_expression``;
    it scales annualized alpha, not calendar days.
    """
    universe_ret = (
        factor_data.groupby(level="date", observed=True)["label"]
        .mean()
        .reindex(returns.index, axis=0)
    )

    x_values = universe_ret.values
    y_values = returns.values
    x_with_const = add_constant(x_values)

    reg_fit = OLS(y_values, x_with_const, missing="drop").fit()
    alpha_beta = pd.DataFrame(
        index=["Ann. alpha", "beta"],
        columns=["label"],
        dtype=np.float64,
    )
    try:
        alpha, beta = reg_fit.params
    except ValueError:
        alpha_beta.loc["Ann. alpha", "label"] = np.nan
        alpha_beta.loc["beta", "label"] = np.nan
    else:
        freq_adjust = pd.Timedelta("252Days") / pd.Timedelta(f"{label_period}D")
        alpha_beta.loc["Ann. alpha", "label"] = float((1 + alpha) ** freq_adjust - 1)
        alpha_beta.loc["beta", "label"] = float(beta)

    return alpha_beta


def _compute_mean_returns_spread(
    mean_returns: pd.DataFrame,
    upper_quant: int,
    lower_quant: int,
    std_err: pd.DataFrame,
) -> tuple[pd.DataFrame, pd.DataFrame]:
    """Compute top-minus-bottom quantile mean return spread."""
    mean_return_difference = mean_returns.xs(
        upper_quant, level="factor_quantile"
    ) - mean_returns.xs(lower_quant, level="factor_quantile")

    std1 = std_err.xs(upper_quant, level="factor_quantile")
    std2 = std_err.xs(lower_quant, level="factor_quantile")
    joint_std_err = np.sqrt(std1**2 + std2**2)
    return mean_return_difference, joint_std_err


def _spearman_ic_group(group: pd.DataFrame) -> float:
    """Compute Spearman IC for one date cross-section."""
    factor_values = group["factor"]
    label_values = group["label"]
    if label_values.isna().all() or factor_values.isna().all():
        return float("nan")
    return float(stats.spearmanr(label_values, factor_values)[0])


def _factor_information_coefficient_label(factor_data: pd.DataFrame) -> pd.Series:
    """Compute daily Spearman IC between factor and label."""
    freq = _date_index_freq(factor_data.index)

    ic = factor_data.groupby(
        factor_data.index.get_level_values("date"),
        observed=True,
    ).apply(_spearman_ic_group)
    ic.name = "label"
    return ic.asfreq(freq)


def _quantile_turnover(
    quantile_factor: pd.Series,
    quantile: int,
    period: int,
) -> pd.Series:
    """Compute turnover for one quantile bucket."""
    freq = _date_index_freq(quantile_factor.index)

    quant_names = quantile_factor[quantile_factor == quantile]
    quant_name_sets = (
        quant_names.groupby(level=["date"], observed=True)
        .apply(lambda values: set(values.index.get_level_values("asset")))
        .asfreq(freq)
    )
    # asfreq may insert non-set cells; treat them as empty membership.
    quant_name_sets = quant_name_sets.apply(
        lambda value: value if isinstance(value, set) else set()
    )

    name_shifted = quant_name_sets.shift(periods=period)
    new_names = (quant_name_sets - name_shifted).dropna()

    new_count = new_names.apply(len)
    name_count = quant_name_sets.apply(len).replace(0, 1)
    return (new_count / name_count).rename(quantile)


def _factor_rank_autocorrelation(
    factor_data: pd.DataFrame,
    period: int,
) -> pd.Series:
    """Compute rolling factor rank autocorrelation."""
    freq = _date_index_freq(factor_data.index)

    asset_ranks_by_day = (
        factor_data.groupby(level="date", observed=True)["factor"]
        .rank()
        .reset_index()
        .pivot(index="date", columns="asset", values="factor")
        .asfreq(freq)
    )

    asset_shifted = asset_ranks_by_day.shift(period)
    return asset_ranks_by_day.corrwith(asset_shifted, axis=1).rename("label").asfreq(freq)


def _quantile_color_map(quantiles: list[int]) -> dict[int, str]:
    """Map sorted quantile ids to coolwarm colors (low red, high blue)."""
    anchors = _COOLWARM_Q1_TO_Q10
    positions = np.linspace(0, len(anchors) - 1, len(quantiles))
    return {
        quantile: anchors[int(round(float(position)))]
        for quantile, position in zip(quantiles, positions, strict=True)
    }


def _symlog_transform(values: np.ndarray) -> np.ndarray:
    """Match matplotlib ``SymmetricalLogTransform`` (base=10, linthresh=2, linscale=1)."""
    arr = np.asarray(values, dtype=float)
    linscale_adj = _SYMLOG_LINSCALE / (1.0 - 1.0 / _SYMLOG_BASE)
    log_base = float(np.log(_SYMLOG_BASE))
    abs_a = np.abs(arr)
    with np.errstate(divide="ignore", invalid="ignore"):
        out = np.sign(arr) * _SYMLOG_LINTHRESH * (
            linscale_adj + np.log(abs_a / _SYMLOG_LINTHRESH) / log_base
        )
    inside = abs_a <= _SYMLOG_LINTHRESH
    return np.where(inside, arr * linscale_adj, out)


def _format_float(value: float, digits: int = 4) -> str:
    """Format a numeric scalar for table display."""
    if pd.isna(value):
        return "—"
    return f"{value:.{digits}f}"


def _sorted_quantiles(values: pd.Index | np.ndarray) -> list[int]:
    """Return quantile bucket ids in ascending order."""
    return sorted({int(value) for value in values.tolist()})


def _add_line(
    fig: go.Figure,
    series: pd.Series,
    *,
    row: int,
    name: str,
    color: str,
    hover: str,
    width: float = _LINE_WIDTH,
    secondary_y: bool | None = None,
) -> None:
    """Add one line series to a subplot."""
    trace = go.Scatter(
        x=series.index,
        y=series.values,
        mode="lines",
        name=name,
        line=dict(color=color, width=width),
        showlegend=False,
        hovertemplate=hover,
    )
    if secondary_y is None:
        fig.add_trace(trace, row=row, col=1)
    else:
        fig.add_trace(trace, row=row, col=1, secondary_y=secondary_y)


def _add_table(
    fig: go.Figure,
    row: int,
    headers: list[str],
    columns: list[list[str]],
    *,
    align: str | list[str] = "right",
) -> None:
    """Add one Plotly table subplot."""
    fig.add_trace(
        go.Table(
            header=dict(
                values=headers,
                fill_color=_TABLE_HEADER,
                align="center",
                font=dict(color=_TEXT, size=_FONT_TABLE),
            ),
            cells=dict(
                values=columns,
                align=align,
                font=dict(color=_TEXT, size=_FONT_BODY),
            ),
        ),
        row=row,
        col=1,
    )


def _add_quantile_cumulative(
    fig: go.Figure,
    metrics: FactorMetrics,
    row: int,
) -> pd.DataFrame:
    """Add 1D quantile cumulative lines in symlog space."""
    quantile_returns = metrics.one_day_quantile_returns.unstack(level="factor_quantile")
    quantile_returns = quantile_returns.sort_index(axis=1)
    cumulative = quantile_returns.add(1.0).cumprod()
    quantiles = _sorted_quantiles(cumulative.columns)
    color_map = _quantile_color_map(quantiles)
    for quantile in quantiles:
        series = cumulative[quantile]
        raw_values = series.to_numpy(dtype=float)
        fig.add_trace(
            go.Scatter(
                x=series.index,
                y=_symlog_transform(raw_values),
                customdata=raw_values,
                mode="lines",
                name=str(quantile),
                line=dict(color=color_map[quantile], width=_LINE_WIDTH),
                showlegend=False,
                hovertemplate=(
                    "日期=%{x}<br>"
                    f"分位={quantile}<br>"
                    "累计收益=%{customdata:.4f}<extra></extra>"
                ),
            ),
            row=row,
            col=1,
        )
    if len(cumulative.index) > 0:
        baseline_y = float(_symlog_transform(np.array([1.0]))[0])
        fig.add_trace(
            go.Scatter(
                x=[cumulative.index[0], cumulative.index[-1]],
                y=[baseline_y, baseline_y],
                mode="lines",
                name="基准=1",
                line=dict(color=_BASELINE, width=_BASELINE_WIDTH),
                showlegend=False,
                hoverinfo="skip",
            ),
            row=row,
            col=1,
        )
    return cumulative


def _apply_symlog_yaxis(fig: go.Figure, cumulative: pd.DataFrame, row: int) -> None:
    """Apply symlog Y: transform positions, keep linspace tick labels in data space."""
    values = cumulative.to_numpy(dtype=float)
    finite = values[np.isfinite(values)]
    if finite.size == 0:
        return
    ymin = float(np.min(finite))
    ymax = float(np.max(finite))
    if ymax <= ymin:
        return
    tick_data = np.linspace(ymin, ymax, 5)
    tick_pos = _symlog_transform(tick_data)
    range_pos = _symlog_transform(np.array([ymin, ymax], dtype=float))
    fig.update_yaxes(
        type="linear",
        title_text="累计收益",
        tickmode="array",
        tickvals=tick_pos.tolist(),
        ticktext=[f"{value:.3f}" for value in tick_data],
        range=[float(range_pos[0]), float(range_pos[1])],
        row=row,
        col=1,
    )


def _add_monthly_ic(fig: go.Figure, metrics: FactorMetrics, row: int) -> None:
    """Add monthly mean IC heatmap."""
    ic_series = metrics.monthly_ic["label"]
    years = sorted({index.year for index in ic_series.index})
    month_labels = [f"{month:02d}" for month in range(1, 13)]
    z_values: list[list[float | None]] = []
    text_values: list[list[str]] = []
    for year in years:
        row_values: list[float | None] = []
        row_text: list[str] = []
        for month in range(1, 13):
            mask = (ic_series.index.year == year) & (ic_series.index.month == month)
            matched = ic_series.loc[mask]
            if matched.empty:
                row_values.append(None)
                row_text.append("")
            else:
                value = float(matched.iloc[0])
                row_values.append(value)
                row_text.append(_format_float(value, 3))
        z_values.append(row_values)
        text_values.append(row_text)
    fig.add_trace(
        go.Heatmap(
            x=month_labels,
            y=[str(year) for year in years],
            z=z_values,
            text=text_values,
            texttemplate="%{text}",
            colorscale=_HEATMAP_COLORSCALE,
            zmid=0.0,
            showscale=False,
            hovertemplate="年=%{y}<br>月=%{x}<br>IC=%{z:.4f}<extra></extra>",
        ),
        row=row,
        col=1,
    )


def _ic_normality_stats(ic: pd.Series) -> tuple[float, float, float, float]:
    """Return IC skew, excess kurtosis, Jarque-Bera statistic and p-value."""
    values = ic.dropna().to_numpy(dtype=float)
    if values.size < 3:
        return float("nan"), float("nan"), float("nan"), float("nan")
    if float(np.std(values)) == 0.0:
        return 0.0, float("nan"), float("nan"), float("nan")
    skew = float(stats.skew(values))
    kurtosis = float(stats.kurtosis(values))
    jb_stat, jb_pvalue = stats.jarque_bera(values)
    return skew, kurtosis, float(jb_stat), float(jb_pvalue)


def _add_ic_histogram(
    fig: go.Figure,
    metrics: FactorMetrics,
    row: int,
    col: int,
) -> None:
    """Add daily IC histogram with a mean reference line."""
    ic = metrics.ic.dropna()
    values = ic.to_numpy(dtype=float)
    if values.size == 0:
        return
    fig.add_trace(
        go.Histogram(
            x=values,
            nbinsx=_IC_HIST_BINS,
            marker=dict(color=_LINE_SOFT),
            opacity=_BOX_OPACITY,
            name="IC 分布",
            showlegend=False,
            hovertemplate="IC=%{x:.4f}<br>计数=%{y}<extra></extra>",
        ),
        row=row,
        col=col,
    )
    mean_value = float(ic.mean())
    fig.add_vline(
        x=mean_value,
        line_dash="dash",
        line_color=_BASELINE,
        line_width=_BASELINE_WIDTH,
        row=row,
        col=col,
    )
    fig.update_xaxes(title_text="IC", range=[-1.0, 1.0], row=row, col=col)
    fig.update_yaxes(title_text="计数", row=row, col=col)


def _add_ic_qq(
    fig: go.Figure,
    metrics: FactorMetrics,
    row: int,
    col: int,
) -> None:
    """Add IC Q-Q plot against the normal distribution."""
    values = metrics.ic.dropna().to_numpy(dtype=float)
    if values.size < 3:
        return
    (osm, osr), fit_params = stats.probplot(values, dist="norm")
    slope = float(fit_params[0])
    intercept = float(fit_params[1])
    fig.add_trace(
        go.Scatter(
            x=osm,
            y=osr,
            mode="markers",
            name="样本分位",
            marker=dict(color=_LINE_SOFT, size=5),
            showlegend=False,
            hovertemplate="理论=%{x:.4f}<br>样本=%{y:.4f}<extra></extra>",
        ),
        row=row,
        col=col,
    )
    x_line = np.array([float(np.min(osm)), float(np.max(osm))], dtype=float)
    y_line = intercept + slope * x_line
    fig.add_trace(
        go.Scatter(
            x=x_line,
            y=y_line,
            mode="lines",
            name="正态参考线",
            line=dict(color=_LINE_ORANGE, width=_LINE_WIDTH),
            showlegend=False,
            hoverinfo="skip",
        ),
        row=row,
        col=col,
    )
    fig.update_xaxes(title_text="理论正态分位", row=row, col=col)
    fig.update_yaxes(title_text="样本 IC 分位", row=row, col=col)

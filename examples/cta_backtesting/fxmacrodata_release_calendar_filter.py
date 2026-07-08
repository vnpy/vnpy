"""Use FXMacroData release-calendar events in vn.py CTA backtests.

The public calendar endpoint can be loaded before a backtest and checked from a
CTA strategy's ``on_bar`` method. The example filters tier-one USD events so a
strategy can avoid initiating risk on major macro-release dates.
"""

from datetime import datetime
from datetime import timedelta
from datetime import timezone
import json
from typing import Any, Dict, Iterable, List, Set
from urllib.parse import urlencode
from urllib.request import urlopen


FXMD_CALENDAR_URL = "https://fxmacrodata.com/api/v1/calendar/{currency}"


def fetch_release_events(
    currency: str,
    start_date: str,
    end_date: str,
) -> List[Dict[str, Any]]:
    params = urlencode({"start_date": start_date, "end_date": end_date})
    url = f"{FXMD_CALENDAR_URL.format(currency=currency.upper())}?{params}"

    with urlopen(url, timeout=20) as response:
        payload = json.load(response)

    return payload.get("data", [])


def build_blackout_dates(
    events: Iterable[Dict[str, Any]],
    min_market_tier: int = 1,
    window_days: int = 0,
) -> Set[str]:
    blackout_dates: Set[str] = set()

    for event in events:
        if not event.get("release_date_confirmed"):
            continue

        market_tier = event.get("market_tier")
        if market_tier is None or int(market_tier) > min_market_tier:
            continue

        announcement_ts = event.get("announcement_datetime")
        if announcement_ts is None:
            continue

        event_date = datetime.fromtimestamp(
            int(announcement_ts),
            tz=timezone.utc,
        ).date()
        for offset in range(-window_days, window_days + 1):
            blackout_dates.add((event_date + timedelta(days=offset)).isoformat())

    return blackout_dates


def load_usd_tier_one_blackouts(start_date: str, end_date: str) -> Set[str]:
    events = fetch_release_events("USD", start_date, end_date)
    return build_blackout_dates(events, min_market_tier=1, window_days=0)


def should_trade(bar_datetime: datetime, blackout_dates: Set[str]) -> bool:
    return bar_datetime.date().isoformat() not in blackout_dates


# CTA strategy sketch:
#
# def on_init(self):
#     self.blackout_dates = load_usd_tier_one_blackouts("2026-07-01", "2026-07-31")
#
# def on_bar(self, bar):
#     if not should_trade(bar.datetime, self.blackout_dates):
#         return
#     ...

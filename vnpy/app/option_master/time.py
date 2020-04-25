from datetime import datetime, timedelta


ANNUAL_DAYS = 240

# For checking public holidays
PUBLIC_HOLIDAYS = set([
    datetime(2020, 1, 1),       # New Year

    datetime(2020, 1, 24),      # Spring Festival
    datetime(2020, 1, 25),
    datetime(2020, 1, 26),
    datetime(2020, 1, 27),
    datetime(2020, 1, 28),
    datetime(2020, 1, 29),
    datetime(2020, 1, 30),

    datetime(2020, 4, 4),       # Qingming Festval
    datetime(2020, 4, 5),
    datetime(2020, 4, 6),

    datetime(2020, 5, 1),       # Labour Day
    datetime(2020, 5, 2),
    datetime(2020, 5, 3),
    datetime(2020, 5, 4),
    datetime(2020, 5, 5),

    datetime(2020, 6, 25),      # Duanwu Festival
    datetime(2020, 6, 26),
    datetime(2020, 6, 27),

    datetime(2020, 10, 1),      # National Day
    datetime(2020, 10, 2),
    datetime(2020, 10, 3),
    datetime(2020, 10, 4),
    datetime(2020, 10, 5),
    datetime(2020, 10, 6),
    datetime(2020, 10, 7),
    datetime(2020, 10, 8),
])


def calculate_days_to_expiry(option_expiry: datetime) -> int:
    """"""
    current_dt = datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)
    days = 1

    while current_dt <= option_expiry:
        current_dt += timedelta(days=1)

        # Ignore weekends
        if current_dt.weekday() in [5, 6]:
            continue

        # Ignore public holidays
        if current_dt in PUBLIC_HOLIDAYS:
            continue

        days += 1

    return days

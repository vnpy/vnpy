def round_to(value: float, target: float):
    """
    Round price to price tick value.
    """
    rounded = int(round(value / target)) * target
    return rounded

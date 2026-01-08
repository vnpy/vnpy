def compute_anchored_range(
    right_ix: int,
    bar_count: int,
    anchor_ix: int,
    zoom_in: bool,
    min_bar_count: int,
    max_bar_count: int
) -> tuple[int, int]:
    """
    Compute new right index and bar count keeping anchor position stable.
    """
    if bar_count <= 0:
        return right_ix, bar_count

    factor = 1.2
    if zoom_in:
        new_bar_count = int(bar_count / factor)
    else:
        new_bar_count = int(bar_count * factor)

    new_bar_count = max(min_bar_count, min(new_bar_count, max_bar_count))
    if new_bar_count == bar_count:
        return right_ix, bar_count

    left_ix = right_ix - bar_count
    anchor_ratio = (anchor_ix - left_ix) / bar_count
    new_left_ix = anchor_ix - anchor_ratio * new_bar_count
    new_right_ix = new_left_ix + new_bar_count

    return int(new_right_ix), new_bar_count

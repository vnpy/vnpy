from vnpy.chart.zoom import compute_anchored_range


def test_compute_anchored_range_keeps_anchor() -> None:
    right_ix = 200
    bar_count = 100
    anchor_ix = 150
    new_right, new_count = compute_anchored_range(
        right_ix=right_ix,
        bar_count=bar_count,
        anchor_ix=anchor_ix,
        zoom_in=True,
        min_bar_count=100,
        max_bar_count=500
    )
    assert new_count <= bar_count
    assert new_right - new_count <= anchor_ix <= new_right

from datetime import datetime, timedelta

from PyQt5.QtCore import QTimer

from vnpy.chart.candle import CandleChart
from vnpy.trader.constant import Exchange, Interval
from vnpy.trader.database import database_manager
from vnpy.trader.ui import create_qapp


def main():
    """"""
    qapp = create_qapp()

    start = datetime.now() - timedelta(days=100)
    end = datetime.now()
    datas = database_manager.load_bar_data(
        "IF88", Exchange.CFFEX, Interval.MINUTE,
        start, end
    )

    assert len(datas) > 10
    i = 0

    def on_timer():
        add_one_data()

    def add_one_data():
        nonlocal i
        data = datas[i]
        chart.update_bar(data)

        i += 1

    chart = CandleChart()
    chart.showMaximized()

    for i in range(10):
        add_one_data()

    t = QTimer()
    t.timeout.connect(on_timer)
    t.start(1000)

    qapp.exec()


if __name__ == "__main__":
    main()


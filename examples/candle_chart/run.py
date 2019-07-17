from datetime import datetime

from vnpy.trader.ui import QtWidgets
from vnpy.chart import ChartWidget
from vnpy.trader.database import database_manager
from vnpy.trader.constant import Exchange, Interval

if __name__ == "__main__":
    app = QtWidgets.QApplication([])

    bars = database_manager.load_bar_data(
        "IF88",
        Exchange.CFFEX,
        interval=Interval.MINUTE,
        start=datetime(2019, 7, 1),
        end=datetime(2019, 7, 17)
    )

    widget = ChartWidget()
    widget.update_history(bars)
    widget.show()

    app.exec_()

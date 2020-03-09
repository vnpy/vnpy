from typing import Tuple, Dict
from functools import partial
from datetime import datetime

from vnpy.trader.ui import QtWidgets, QtCore
from vnpy.trader.engine import MainEngine, EventEngine
from vnpy.trader.constant import Interval, Exchange

from ..engine import APP_NAME, ManagerEngine


class ManagerWidget(QtWidgets.QWidget):
    """"""

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.engine: ManagerEngine = main_engine.get_engine(APP_NAME)

        self.tree_items: Dict[Tuple, QtWidgets.QTreeWidgetItem] = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle("数据管理")

        self.init_tree()
        self.init_table()

        refresh_button = QtWidgets.QPushButton("刷新")
        refresh_button.clicked.connect(self.refresh_tree)

        import_button = QtWidgets.QPushButton("加载数据")

        hbox1 = QtWidgets.QHBoxLayout()
        hbox1.addWidget(refresh_button)
        hbox1.addStretch()
        hbox1.addWidget(import_button)

        hbox2 = QtWidgets.QHBoxLayout()
        hbox2.addWidget(self.tree)
        hbox2.addWidget(self.table)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)

        self.setLayout(vbox)

    def init_tree(self) -> None:
        """"""
        labels = [
            "数据",
            "本地代码",
            "代码",
            "交易所",
            "数据量",
            "开始时间",
            "结束时间",
            ""
        ]

        self.tree = QtWidgets.QTreeWidget()
        self.tree.setColumnCount(len(labels))
        self.tree.setHeaderLabels(labels)

        root = QtWidgets.QTreeWidgetItem(self.tree)
        root.setText(0, "K线数据")
        root.setExpanded(True)

        self.minute_child = QtWidgets.QTreeWidgetItem()
        self.minute_child.setText(0, "分钟线")
        root.addChild(self.minute_child)

        self.hour_child = QtWidgets.QTreeWidgetItem()
        self.hour_child.setText(0, "小时线")
        root.addChild(self.hour_child)

        self.daily_child = QtWidgets.QTreeWidgetItem()
        self.daily_child.setText(0, "日线")
        root.addChild(self.daily_child)

    def init_table(self) -> None:
        """"""
        labels = [
            "时间",
            "开盘价",
            "最高价",
            "最低价",
            "收盘价",
            "成交量",
            "持仓量"
        ]

        self.table = QtWidgets.QTableWidget()
        self.table.setColumnCount(len(labels))
        self.table.setHorizontalHeaderLabels(labels)
        self.table.verticalHeader().setVisible(False)

    def refresh_tree(self) -> None:
        """"""
        data = self.engine.get_bar_data_available()

        for d in data:
            key = (d["symbol"], d["exchange"], d["interval"])
            item = self.tree_items.get(key, None)

            if not item:
                item = QtWidgets.QTreeWidgetItem()
                item.setText(1, ".".join([d["symbol"], d["exchange"]]))
                item.setText(2, d["symbol"])
                item.setText(3, d["exchange"])

                if d["interval"] == Interval.MINUTE:
                    self.minute_child.addChild(item)
                elif d["interval"] == Interval.HOUR:
                    self.hour_child.addChild(item)
                else:
                    self.daily_child.addChild(item)

                output_button = QtWidgets.QPushButton("导出数据")
                output_func = partial(
                    self.output_data,
                    d["symbol"],
                    Exchange(d["exchange"]),
                    Interval(d["interval"]),
                    d["start"],
                    d["end"]
                )
                output_button.clicked.connect(output_func)

                self.tree.setItemWidget(item, 7, output_button)

            item.setText(4, str(d["count"]))
            item.setText(5, d["start"].strftime("%Y-%m-%d %H:%M:%S"))
            item.setText(6, d["end"].strftime("%Y-%m-%d %H:%M:%S"))

        self.minute_child.setExpanded(True)
        self.hour_child.setExpanded(True)
        self.daily_child.setExpanded(True)

    def import_data(self) -> None:
        """"""
        pass

    def output_data(
        self,
        symbol: str,
        exchange: Exchange,
        interval: Interval,
        start: datetime,
        end: datetime
    ) -> None:
        """"""
        # Get output date range
        dialog = DateRangeDialog(start, end)
        n = dialog.exec_()
        if n != dialog.Accepted:
            return
        start, end = dialog.get_date_range()

        # Get output file path
        path, _ = QtWidgets.QFileDialog.getSaveFileName(
            self,
            "导出数据",
            "",
            "CSV(*.csv)"
        )
        if not path:
            return

        self.engine.output_data_to_csv(
            path,
            symbol,
            exchange,
            interval,
            start,
            end
        )

    def show(self) -> None:
        """"""
        self.showMaximized()


class DateRangeDialog(QtWidgets.QDialog):
    """"""

    def __init__(self, start: datetime, end: datetime, parent=None):
        """"""
        super().__init__(parent)

        self.setWindowTitle("选择数据区间")

        self.start_edit = QtWidgets.QDateEdit(
            QtCore.QDate(
                start.year,
                start.month,
                start.day
            )
        )
        self.end_edit = QtWidgets.QDateEdit(
            QtCore.QDate(
                end.year,
                end.month,
                end.day
            )
        )

        button = QtWidgets.QPushButton("确定")
        button.clicked.connect(self.accept)

        form = QtWidgets.QFormLayout()
        form.addRow("开始时间", self.start_edit)
        form.addRow("结束时间", self.end_edit)
        form.addRow(button)

        self.setLayout(form)

    def get_date_range(self) -> Tuple[datetime, datetime]:
        """"""
        start = self.start_edit.date().toPyDate()
        end = self.end_edit.date().toPyDate()
        return start, end

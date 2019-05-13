import numpy as np
import pyqtgraph as pg
from datetime import datetime, timedelta

from ..engine import (
    APP_NAME,
    EVENT_BACKTESTER_LOG,
    EVENT_BACKTESTER_BACKTESTING_FINISHED,
    EVENT_BACKTESTER_OPTIMIZATION_FINISHED,
    OptimizationSetting
)
from vnpy.trader.constant import Interval
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtWidgets, QtGui
from vnpy.event import Event, EventEngine


class BacktesterManager(QtWidgets.QWidget):
    """"""

    signal_log = QtCore.pyqtSignal(Event)
    signal_backtesting_finished = QtCore.pyqtSignal(Event)
    signal_optimization_finished = QtCore.pyqtSignal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__()

        self.main_engine = main_engine
        self.event_engine = event_engine

        self.backtester_engine = main_engine.get_engine(APP_NAME)
        self.class_names = []
        self.settings = {}

        self.target_display = ""

        self.init_strategy_settings()
        self.init_ui()
        self.register_event()
        self.backtester_engine.init_engine()

    def init_strategy_settings(self):
        """"""
        self.class_names = self.backtester_engine.get_strategy_class_names()

        for class_name in self.class_names:
            setting = self.backtester_engine.get_default_setting(class_name)
            self.settings[class_name] = setting

    def init_ui(self):
        """"""
        self.setWindowTitle("CTA回测")

        # Setting Part
        self.class_combo = QtWidgets.QComboBox()
        self.class_combo.addItems(self.class_names)

        self.symbol_line = QtWidgets.QLineEdit("IF88.CFFEX")

        self.interval_combo = QtWidgets.QComboBox()
        for inteval in Interval:
            self.interval_combo.addItem(inteval.value)

        end_dt = datetime.now()
        start_dt = end_dt - timedelta(days=3 * 365)

        self.start_date_edit = QtWidgets.QDateEdit(
            QtCore.QDate(
                start_dt.year,
                start_dt.month,
                start_dt.day
            )
        )
        self.end_date_edit = QtWidgets.QDateEdit(
            QtCore.QDate.currentDate()
        )

        self.rate_line = QtWidgets.QLineEdit("0.000025")
        self.slippage_line = QtWidgets.QLineEdit("0.2")
        self.size_line = QtWidgets.QLineEdit("300")
        self.pricetick_line = QtWidgets.QLineEdit("0.2")
        self.capital_line = QtWidgets.QLineEdit("1000000")

        backtesting_button = QtWidgets.QPushButton("开始回测")
        backtesting_button.clicked.connect(self.start_backtesting)

        optimization_button = QtWidgets.QPushButton("参数优化")
        optimization_button.clicked.connect(self.start_optimization)

        self.result_button = QtWidgets.QPushButton("优化结果")
        self.result_button.clicked.connect(self.show_optimization_result)
        self.result_button.setEnabled(False)

        downloading_button = QtWidgets.QPushButton("下载数据")
        downloading_button.clicked.connect(self.start_downloading)

        for button in [
            backtesting_button,
            optimization_button,
            downloading_button,
            self.result_button
        ]:
            button.setFixedHeight(button.sizeHint().height() * 2)

        form = QtWidgets.QFormLayout()
        form.addRow("交易策略", self.class_combo)
        form.addRow("本地代码", self.symbol_line)
        form.addRow("K线周期", self.interval_combo)
        form.addRow("开始日期", self.start_date_edit)
        form.addRow("结束日期", self.end_date_edit)
        form.addRow("手续费率", self.rate_line)
        form.addRow("交易滑点", self.slippage_line)
        form.addRow("合约乘数", self.size_line)
        form.addRow("价格跳动", self.pricetick_line)
        form.addRow("回测资金", self.capital_line)
        form.addRow(backtesting_button)

        left_vbox = QtWidgets.QVBoxLayout()
        left_vbox.addLayout(form)
        left_vbox.addWidget(downloading_button)
        left_vbox.addStretch()
        left_vbox.addWidget(optimization_button)
        left_vbox.addWidget(self.result_button)

        # Result part
        self.statistics_monitor = StatisticsMonitor()

        self.log_monitor = QtWidgets.QTextEdit()
        self.log_monitor.setMaximumHeight(400)

        self.chart = BacktesterChart()
        self.chart.setMinimumWidth(1000)

        # Layout
        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.statistics_monitor)
        vbox.addWidget(self.log_monitor)

        hbox = QtWidgets.QHBoxLayout()
        hbox.addLayout(left_vbox)
        hbox.addLayout(vbox)
        hbox.addWidget(self.chart)
        self.setLayout(hbox)

    def register_event(self):
        """"""
        self.signal_log.connect(self.process_log_event)
        self.signal_backtesting_finished.connect(
            self.process_backtesting_finished_event)
        self.signal_optimization_finished.connect(
            self.process_optimization_finished_event)

        self.event_engine.register(EVENT_BACKTESTER_LOG, self.signal_log.emit)
        self.event_engine.register(
            EVENT_BACKTESTER_BACKTESTING_FINISHED, self.signal_backtesting_finished.emit)
        self.event_engine.register(
            EVENT_BACKTESTER_OPTIMIZATION_FINISHED, self.signal_optimization_finished.emit)

    def process_log_event(self, event: Event):
        """"""
        msg = event.data
        self.write_log(msg)

    def write_log(self, msg):
        """"""
        timestamp = datetime.now().strftime("%H:%M:%S")
        msg = f"{timestamp}\t{msg}"
        self.log_monitor.append(msg)

    def process_backtesting_finished_event(self, event: Event):
        """"""
        statistics = self.backtester_engine.get_result_statistics()
        self.statistics_monitor.set_data(statistics)

        df = self.backtester_engine.get_result_df()
        self.chart.set_data(df)

    def process_optimization_finished_event(self, event: Event):
        """"""
        self.write_log("请点击[优化结果]按钮查看")
        self.result_button.setEnabled(True)

    def start_backtesting(self):
        """"""
        class_name = self.class_combo.currentText()
        vt_symbol = self.symbol_line.text()
        interval = self.interval_combo.currentText()
        start = self.start_date_edit.date().toPyDate()
        end = self.end_date_edit.date().toPyDate()
        rate = float(self.rate_line.text())
        slippage = float(self.slippage_line.text())
        size = float(self.size_line.text())
        pricetick = float(self.pricetick_line.text())
        capital = float(self.capital_line.text())

        old_setting = self.settings[class_name]
        dialog = BacktestingSettingEditor(class_name, old_setting)
        i = dialog.exec()
        if i != dialog.Accepted:
            return

        new_setting = dialog.get_setting()
        self.settings[class_name] = new_setting

        result = self.backtester_engine.start_backtesting(
            class_name,
            vt_symbol,
            interval,
            start,
            end,
            rate,
            slippage,
            size,
            pricetick,
            capital,
            new_setting
        )

        if result:
            self.statistics_monitor.clear_data()
            self.chart.clear_data()

    def start_optimization(self):
        """"""
        class_name = self.class_combo.currentText()
        vt_symbol = self.symbol_line.text()
        interval = self.interval_combo.currentText()
        start = self.start_date_edit.date().toPyDate()
        end = self.end_date_edit.date().toPyDate()
        rate = float(self.rate_line.text())
        slippage = float(self.slippage_line.text())
        size = float(self.size_line.text())
        pricetick = float(self.pricetick_line.text())
        capital = float(self.capital_line.text())

        parameters = self.settings[class_name]
        dialog = OptimizationSettingEditor(class_name, parameters)
        i = dialog.exec()
        if i != dialog.Accepted:
            return

        optimization_setting, use_ga = dialog.get_setting()
        self.target_display = dialog.target_display

        self.backtester_engine.start_optimization(
            class_name,
            vt_symbol,
            interval,
            start,
            end,
            rate,
            slippage,
            size,
            pricetick,
            capital,
            optimization_setting,
            use_ga
        )

        self.result_button.setEnabled(False)

    def start_downloading(self):
        """"""
        vt_symbol = self.symbol_line.text()
        interval = self.interval_combo.currentText()
        start = self.start_date_edit.date().toPyDate()
        end = self.end_date_edit.date().toPyDate()

        self.backtester_engine.start_downloading(
            vt_symbol,
            interval,
            start,
            end
        )

    def show_optimization_result(self):
        """"""
        result_values = self.backtester_engine.get_result_values()

        dialog = OptimizationResultMonitor(
            result_values,
            self.target_display
        )
        dialog.exec_()

    def show(self):
        """"""
        self.showMaximized()


class StatisticsMonitor(QtWidgets.QTableWidget):
    """"""
    KEY_NAME_MAP = {
        "start_date": "首个交易日",
        "end_date": "最后交易日",

        "total_days": "总交易日",
        "profit_days": "盈利交易日",
        "loss_days": "亏损交易日",

        "capital": "起始资金",
        "end_balance": "结束资金",

        "total_return": "总收益率",
        "annual_return": "年化收益",
        "max_drawdown": "最大回撤",
        "max_ddpercent": "百分比最大回撤",

        "total_net_pnl": "总盈亏",
        "total_commission": "总手续费",
        "total_slippage": "总滑点",
        "total_turnover": "总成交额",
        "total_trade_count": "总成交笔数",

        "daily_net_pnl": "日均盈亏",
        "daily_commission": "日均手续费",
        "daily_slippage": "日均滑点",
        "daily_turnover": "日均成交额",
        "daily_trade_count": "日均成交笔数",

        "daily_return": "日均收益率",
        "return_std": "收益标准差",
        "sharpe_ratio": "夏普比率",
        "return_drawdown_ratio": "收益回撤比"
    }

    def __init__(self):
        """"""
        super().__init__()

        self.cells = {}

        self.init_ui()

    def init_ui(self):
        """"""
        self.setRowCount(len(self.KEY_NAME_MAP))
        self.setVerticalHeaderLabels(list(self.KEY_NAME_MAP.values()))

        self.setColumnCount(1)
        self.horizontalHeader().setVisible(False)
        self.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.Stretch
        )
        self.setEditTriggers(self.NoEditTriggers)

        for row, key in enumerate(self.KEY_NAME_MAP.keys()):
            cell = QtWidgets.QTableWidgetItem()
            self.setItem(row, 0, cell)
            self.cells[key] = cell

    def clear_data(self):
        """"""
        for cell in self.cells.values():
            cell.setText("")

    def set_data(self, data: dict):
        """"""
        data["capital"] = f"{data['capital']:,.2f}"
        data["end_balance"] = f"{data['end_balance']:,.2f}"
        data["total_return"] = f"{data['total_return']:,.2f}%"
        data["annual_return"] = f"{data['annual_return']:,.2f}%"
        data["max_drawdown"] = f"{data['max_drawdown']:,.2f}"
        data["max_ddpercent"] = f"{data['max_ddpercent']:,.2f}%"
        data["total_net_pnl"] = f"{data['total_net_pnl']:,.2f}"
        data["total_commission"] = f"{data['total_commission']:,.2f}"
        data["total_slippage"] = f"{data['total_slippage']:,.2f}"
        data["total_turnover"] = f"{data['total_turnover']:,.2f}"
        data["daily_net_pnl"] = f"{data['daily_net_pnl']:,.2f}"
        data["daily_commission"] = f"{data['daily_commission']:,.2f}"
        data["daily_slippage"] = f"{data['daily_slippage']:,.2f}"
        data["daily_turnover"] = f"{data['daily_turnover']:,.2f}"
        data["daily_return"] = f"{data['daily_return']:,.2f}%"
        data["return_std"] = f"{data['return_std']:,.2f}%"
        data["sharpe_ratio"] = f"{data['sharpe_ratio']:,.2f}"
        data["return_drawdown_ratio"] = f"{data['return_drawdown_ratio']:,.2f}"

        for key, cell in self.cells.items():
            value = data.get(key, "")
            cell.setText(str(value))


class BacktestingSettingEditor(QtWidgets.QDialog):
    """
    For creating new strategy and editing strategy parameters.
    """

    def __init__(
        self, class_name: str, parameters: dict
    ):
        """"""
        super(BacktestingSettingEditor, self).__init__()

        self.class_name = class_name
        self.parameters = parameters
        self.edits = {}

        self.init_ui()

    def init_ui(self):
        """"""
        form = QtWidgets.QFormLayout()

        # Add vt_symbol and name edit if add new strategy
        self.setWindowTitle(f"策略参数配置：{self.class_name}")
        button_text = "确定"
        parameters = self.parameters

        for name, value in parameters.items():
            type_ = type(value)

            edit = QtWidgets.QLineEdit(str(value))
            if type_ is int:
                validator = QtGui.QIntValidator()
                edit.setValidator(validator)
            elif type_ is float:
                validator = QtGui.QDoubleValidator()
                edit.setValidator(validator)

            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accept)
        form.addRow(button)

        self.setLayout(form)

    def get_setting(self):
        """"""
        setting = {}

        for name, tp in self.edits.items():
            edit, type_ = tp
            value_text = edit.text()

            if type_ == bool:
                if value_text == "True":
                    value = True
                else:
                    value = False
            else:
                value = type_(value_text)

            setting[name] = value

        return setting


class BacktesterChart(pg.GraphicsWindow):
    """"""

    def __init__(self):
        """"""
        super().__init__(title="Backtester Chart")

        self.dates = {}

        self.init_ui()

    def init_ui(self):
        """"""
        pg.setConfigOptions(antialias=True)

        # Create plot widgets
        self.balance_plot = self.addPlot(
            title="账户净值",
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.drawdown_plot = self.addPlot(
            title="净值回撤",
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.pnl_plot = self.addPlot(
            title="每日盈亏",
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.distribution_plot = self.addPlot(title="盈亏分布")

        # Add curves and bars on plot widgets
        self.balance_curve = self.balance_plot.plot(
            pen=pg.mkPen("#ffc107", width=3)
        )

        dd_color = "#303f9f"
        self.drawdown_curve = self.drawdown_plot.plot(
            fillLevel=-0.3, brush=dd_color, pen=dd_color
        )

        profit_color = 'r'
        loss_color = 'g'
        self.profit_pnl_bar = pg.BarGraphItem(
            x=[], height=[], width=0.3, brush=profit_color, pen=profit_color
        )
        self.loss_pnl_bar = pg.BarGraphItem(
            x=[], height=[], width=0.3, brush=loss_color, pen=loss_color
        )
        self.pnl_plot.addItem(self.profit_pnl_bar)
        self.pnl_plot.addItem(self.loss_pnl_bar)

        distribution_color = "#6d4c41"
        self.distribution_curve = self.distribution_plot.plot(
            fillLevel=-0.3, brush=distribution_color, pen=distribution_color
        )

    def clear_data(self):
        """"""
        self.balance_curve.setData([], [])
        self.drawdown_curve.setData([], [])
        self.profit_pnl_bar.setOpts(x=[], height=[])
        self.loss_pnl_bar.setOpts(x=[], height=[])
        self.distribution_curve.setData([], [])

    def set_data(self, df):
        """"""
        if df is None:
            return

        count = len(df)

        self.dates.clear()
        for n, date in enumerate(df.index):
            self.dates[n] = date

        # Set data for curve of balance and drawdown
        self.balance_curve.setData(df["balance"])
        self.drawdown_curve.setData(df["drawdown"])

        # Set data for daily pnl bar
        profit_pnl_x = []
        profit_pnl_height = []
        loss_pnl_x = []
        loss_pnl_height = []

        for count, pnl in enumerate(df["net_pnl"]):
            if pnl >= 0:
                profit_pnl_height.append(pnl)
                profit_pnl_x.append(count)
            else:
                loss_pnl_height.append(pnl)
                loss_pnl_x.append(count)

        self.profit_pnl_bar.setOpts(x=profit_pnl_x, height=profit_pnl_height)
        self.loss_pnl_bar.setOpts(x=loss_pnl_x, height=loss_pnl_height)

        # Set data for pnl distribution
        hist, x = np.histogram(df["net_pnl"], bins="auto")
        x = x[:-1]
        self.distribution_curve.setData(x, hist)


class DateAxis(pg.AxisItem):
    """Axis for showing date data"""

    def __init__(self, dates: dict, *args, **kwargs):
        """"""
        super().__init__(*args, **kwargs)
        self.dates = dates

    def tickStrings(self, values, scale, spacing):
        """"""
        strings = []
        for v in values:
            dt = self.dates.get(v, "")
            strings.append(str(dt))
        return strings


class OptimizationSettingEditor(QtWidgets.QDialog):
    """
    For setting up parameters for optimization.
    """
    DISPLAY_NAME_MAP = {
        "总收益率": "total_return",
        "夏普比率": "sharpe_ratio",
        "收益回撤比": "return_drawdown_ratio",
        "日均盈亏": "daily_net_pnl"
    }

    def __init__(
        self, class_name: str, parameters: dict
    ):
        """"""
        super().__init__()

        self.class_name = class_name
        self.parameters = parameters
        self.edits = {}

        self.optimization_setting = None
        self.use_ga = False

        self.init_ui()

    def init_ui(self):
        """"""
        QLabel = QtWidgets.QLabel

        self.target_combo = QtWidgets.QComboBox()
        self.target_combo.addItems(list(self.DISPLAY_NAME_MAP.keys()))

        grid = QtWidgets.QGridLayout()
        grid.addWidget(QLabel("目标"), 0, 0)
        grid.addWidget(self.target_combo, 0, 1, 1, 3)
        grid.addWidget(QLabel("参数"), 1, 0)
        grid.addWidget(QLabel("开始"), 1, 1)
        grid.addWidget(QLabel("步进"), 1, 2)
        grid.addWidget(QLabel("结束"), 1, 3)

        # Add vt_symbol and name edit if add new strategy
        self.setWindowTitle(f"优化参数配置：{self.class_name}")

        validator = QtGui.QDoubleValidator()
        row = 2

        for name, value in self.parameters.items():
            type_ = type(value)
            if type_ not in [int, float]:
                continue

            start_edit = QtWidgets.QLineEdit(str(value))
            step_edit = QtWidgets.QLineEdit(str(1))
            end_edit = QtWidgets.QLineEdit(str(value))

            for edit in [start_edit, step_edit, end_edit]:
                edit.setValidator(validator)

            grid.addWidget(QLabel(name), row, 0)
            grid.addWidget(start_edit, row, 1)
            grid.addWidget(step_edit, row, 2)
            grid.addWidget(end_edit, row, 3)

            self.edits[name] = {
                "type": type_,
                "start": start_edit,
                "step": step_edit,
                "end": end_edit
            }

            row += 1

        parallel_button = QtWidgets.QPushButton("多进程优化")
        parallel_button.clicked.connect(self.generate_parallel_setting)
        grid.addWidget(parallel_button, row, 0, 1, 4)

        row += 1
        ga_button = QtWidgets.QPushButton("遗传算法优化")
        ga_button.clicked.connect(self.generate_ga_setting)
        grid.addWidget(ga_button, row, 0, 1, 4)

        self.setLayout(grid)

    def generate_ga_setting(self):
        """"""
        self.use_ga = True
        self.generate_setting()

    def generate_parallel_setting(self):
        """"""
        self.use_ga = False
        self.generate_setting()

    def generate_setting(self):
        """"""
        self.optimization_setting = OptimizationSetting()

        self.target_display = self.target_combo.currentText()
        target_name = self.DISPLAY_NAME_MAP[self.target_display]
        self.optimization_setting.set_target(target_name)

        for name, d in self.edits.items():
            type_ = d["type"]
            start_value = type_(d["start"].text())
            step_value = type_(d["step"].text())
            end_value = type_(d["end"].text())

            if start_value == end_value:
                self.optimization_setting.add_parameter(name, start_value)
            else:
                self.optimization_setting.add_parameter(
                    name,
                    start_value,
                    end_value,
                    step_value
                )

        self.accept()

    def get_setting(self):
        """"""
        return self.optimization_setting, self.use_ga


class OptimizationResultMonitor(QtWidgets.QDialog):
    """
    For viewing optimization result.
    """

    def __init__(
        self, result_values: list, target_display: str
    ):
        """"""
        super().__init__()

        self.result_values = result_values
        self.target_display = target_display

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("参数优化结果")
        self.resize(1100, 500)

        table = QtWidgets.QTableWidget()

        table.setColumnCount(2)
        table.setRowCount(len(self.result_values))
        table.setHorizontalHeaderLabels(["参数", self.target_display])
        table.setEditTriggers(table.NoEditTriggers)
        table.verticalHeader().setVisible(False)

        table.horizontalHeader().setSectionResizeMode(
            0, QtWidgets.QHeaderView.ResizeToContents
        )
        table.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.Stretch
        )

        for n, tp in enumerate(self.result_values):
            setting, target_value, _ = tp
            setting_cell = QtWidgets.QTableWidgetItem(str(setting))
            target_cell = QtWidgets.QTableWidgetItem(str(target_value))

            setting_cell.setTextAlignment(QtCore.Qt.AlignCenter)
            target_cell.setTextAlignment(QtCore.Qt.AlignCenter)

            table.setItem(n, 0, setting_cell)
            table.setItem(n, 1, target_cell)

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(table)

        self.setLayout(vbox)

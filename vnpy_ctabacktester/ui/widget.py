import platform
import csv
import shutil
import subprocess
from datetime import datetime, timedelta
from copy import copy
from typing import Any, cast

import numpy as np
import pyqtgraph as pg
from pandas import DataFrame

from vnpy.trader.constant import Interval, Direction, Exchange, Offset
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import QtCore, QtWidgets, QtGui
from vnpy.trader.ui.widget import BaseMonitor, BaseCell, DirectionCell, EnumCell
from vnpy.event import Event, EventEngine
from vnpy.chart import ChartWidget, CandleItem, VolumeItem
from vnpy.trader.utility import load_json, save_json
from vnpy.trader.object import BarData, TradeData, OrderData
from vnpy.trader.database import DB_TZ
from vnpy_ctastrategy.backtesting import DailyResult

from ..locale import _
from ..engine import (
    APP_NAME,
    EVENT_BACKTESTER_LOG,
    EVENT_BACKTESTER_BACKTESTING_FINISHED,
    EVENT_BACKTESTER_DOWNLOADING_FINISHED,
    EVENT_BACKTESTER_OPTIMIZATION_FINISHED,
    OptimizationSetting,
    BacktesterEngine
)


class BacktesterManager(QtWidgets.QWidget):
    """"""

    setting_filename: str = "cta_backtester_setting.json"
    symbol_history_filename: str = "cta_backtester_symbols.json"

    signal_log: QtCore.Signal = QtCore.Signal(Event)
    signal_backtesting_finished: QtCore.Signal = QtCore.Signal(Event)
    signal_optimization_finished: QtCore.Signal = QtCore.Signal(Event)
    signal_downloading_finished: QtCore.Signal = QtCore.Signal(Event)

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine) -> None:
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine

        self.backtester_engine: BacktesterEngine = main_engine.get_engine(APP_NAME)     # type: ignore
        self.class_names: list = []
        self.settings: dict = {}

        self.target_display: str = ""
        self.symbol_history: list[str] = []
        self.symbol_history_records: list[dict] = []

        self.init_ui()
        self.register_event()
        self.backtester_engine.init_engine()
        self.init_strategy_settings()
        self.load_backtesting_setting()
        self.load_symbol_history()

    def init_strategy_settings(self) -> None:
        """"""
        self.class_names = self.backtester_engine.get_strategy_class_names()
        self.class_names.sort()

        for class_name in self.class_names:
            setting: dict = self.backtester_engine.get_default_setting(class_name)
            self.settings[class_name] = setting

        self.class_combo.addItems(self.class_names)

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(_("CTA回测"))

        # Setting Part
        self.class_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()

        self.symbol_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()
        self.symbol_combo.setEditable(True)
        self.symbol_combo.setInsertPolicy(QtWidgets.QComboBox.InsertPolicy.NoInsert)
        self.symbol_combo.setMaxVisibleItems(12)
        self.symbol_combo.setSizeAdjustPolicy(
            QtWidgets.QComboBox.SizeAdjustPolicy.AdjustToContentsOnFirstShow
        )
        self.symbol_combo.setCurrentText("IF88.CFFEX")
        self.symbol_completer: QtWidgets.QCompleter = QtWidgets.QCompleter(
            self.symbol_combo.model(), self
        )
        self.symbol_completer.setFilterMode(QtCore.Qt.MatchContains)
        self.symbol_completer.setCaseSensitivity(QtCore.Qt.CaseSensitivity.CaseInsensitive)
        self.symbol_completer.setCompletionMode(
            QtWidgets.QCompleter.CompletionMode.PopupCompletion
        )
        self.symbol_combo.setCompleter(self.symbol_completer)
        self.symbol_combo.installEventFilter(self)
        self.symbol_combo.lineEdit().installEventFilter(self)

        self.interval_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()
        for interval in Interval:
            self.interval_combo.addItem(interval.value)
        interval_view: QtWidgets.QListView = QtWidgets.QListView()
        interval_palette: QtGui.QPalette = interval_view.palette()
        interval_palette.setColor(QtGui.QPalette.ColorRole.Text, QtGui.QColor("white"))
        interval_palette.setColor(QtGui.QPalette.ColorRole.Base, QtGui.QColor("#2b2b2b"))
        interval_view.setPalette(interval_palette)
        interval_view.setTextElideMode(QtCore.Qt.TextElideMode.ElideNone)
        self.interval_combo.setView(interval_view)
        self.interval_combo.setSizeAdjustPolicy(
            QtWidgets.QComboBox.SizeAdjustPolicy.AdjustToContents
        )
        self.interval_combo.setSizePolicy(
            QtWidgets.QSizePolicy.Policy.Expanding,
            QtWidgets.QSizePolicy.Policy.Fixed
        )
        font_metrics = QtGui.QFontMetrics(self.interval_combo.font())
        max_text = max((interval.value for interval in Interval), key=len)
        min_width = font_metrics.horizontalAdvance(max_text) + 40
        self.interval_combo.setMinimumWidth(min_width)

        end_dt: datetime = datetime.now()
        start_dt: datetime = end_dt - timedelta(days=3 * 365)

        self.start_date_edit: QtWidgets.QDateEdit = QtWidgets.QDateEdit(
            QtCore.QDate(
                start_dt.year,
                start_dt.month,
                start_dt.day
            )
        )
        self.end_date_edit: QtWidgets.QDateEdit = QtWidgets.QDateEdit(
            QtCore.QDate.currentDate()
        )

        self.rate_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit("0.000025")
        self.slippage_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit("0.2")
        self.size_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit("300")
        self.pricetick_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit("0.2")
        self.capital_line: QtWidgets.QLineEdit = QtWidgets.QLineEdit("1000000")

        self.backtesting_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("开始回测"))
        self.backtesting_button.clicked.connect(self._on_backtesting_button_clicked)
        self._download_in_progress: bool = False

        optimization_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("参数优化"))
        optimization_button.clicked.connect(self.start_optimization)

        self.result_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("优化结果"))
        self.result_button.clicked.connect(self.show_optimization_result)
        self.result_button.setEnabled(False)

        self.downloading_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("下载数据"))
        self.downloading_button.clicked.connect(self.toggle_downloading)

        self.order_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("委托记录"))
        self.order_button.clicked.connect(self.show_backtesting_orders)
        self.order_button.setEnabled(False)

        self.trade_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("成交记录"))
        self.trade_button.clicked.connect(self.show_backtesting_trades)
        self.trade_button.setEnabled(False)

        self.daily_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("每日盈亏"))
        self.daily_button.clicked.connect(self.show_daily_results)
        self.daily_button.setEnabled(False)

        self.candle_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("K线图表"))
        self.candle_button.clicked.connect(self.show_candle_chart)
        self.candle_button.setEnabled(False)

        edit_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("代码编辑"))
        edit_button.clicked.connect(self.edit_strategy_code)

        reload_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("策略重载"))
        reload_button.clicked.connect(self.reload_strategy_class)

        for button in [
            self.backtesting_button,
            optimization_button,
            self.downloading_button,
            self.result_button,
            self.order_button,
            self.trade_button,
            self.daily_button,
            self.candle_button,
            edit_button,
            reload_button
        ]:
            button.setFixedHeight(button.sizeHint().height() * 2)

        form: QtWidgets.QFormLayout = QtWidgets.QFormLayout()
        form.addRow(_("交易策略"), self.class_combo)
        form.addRow(_("本地代码"), self.symbol_combo)
        form.addRow(_("K线周期"), self.interval_combo)
        form.addRow(_("开始日期"), self.start_date_edit)
        form.addRow(_("结束日期"), self.end_date_edit)
        form.addRow(_("手续费率"), self.rate_line)
        form.addRow(_("交易滑点"), self.slippage_line)
        form.addRow(_("合约乘数"), self.size_line)
        form.addRow(_("价格跳动"), self.pricetick_line)
        form.addRow(_("回测资金"), self.capital_line)

        result_grid: QtWidgets.QGridLayout = QtWidgets.QGridLayout()
        result_grid.addWidget(self.trade_button, 0, 0)
        result_grid.addWidget(self.order_button, 0, 1)
        result_grid.addWidget(self.daily_button, 1, 0)
        result_grid.addWidget(self.candle_button, 1, 1)

        left_vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        left_vbox.addLayout(form)
        left_vbox.addWidget(self.backtesting_button)
        left_vbox.addWidget(self.downloading_button)
        left_vbox.addStretch()
        left_vbox.addLayout(result_grid)
        left_vbox.addStretch()
        left_vbox.addWidget(optimization_button)
        left_vbox.addWidget(self.result_button)
        left_vbox.addStretch()
        left_vbox.addWidget(edit_button)
        left_vbox.addWidget(reload_button)

        # Result part
        self.statistics_monitor: StatisticsMonitor = StatisticsMonitor()

        self.log_monitor: QtWidgets.QTextEdit = QtWidgets.QTextEdit()

        self.chart: BacktesterChart = BacktesterChart()
        chart: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        chart.addWidget(self.chart)

        self.trade_dialog: BacktestingResultDialog = BacktestingResultDialog(
            self.main_engine,
            self.event_engine,
            _("回测成交记录"),
            BacktestingTradeMonitor
        )
        self.order_dialog: BacktestingResultDialog = BacktestingResultDialog(
            self.main_engine,
            self.event_engine,
            _("回测委托记录"),
            BacktestingOrderMonitor
        )
        self.daily_dialog: BacktestingResultDialog = BacktestingResultDialog(
            self.main_engine,
            self.event_engine,
            _("回测每日盈亏"),
            DailyResultMonitor
        )

        # Candle Chart
        self.candle_dialog: CandleChartDialog = CandleChartDialog()

        # Layout
        middle_vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        middle_vbox.addWidget(self.statistics_monitor)
        middle_vbox.addWidget(self.log_monitor)

        left_hbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        left_hbox.addLayout(left_vbox)
        left_hbox.addLayout(middle_vbox)

        left_widget: QtWidgets.QWidget = QtWidgets.QWidget()
        left_widget.setLayout(left_hbox)

        right_vbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        right_vbox.addWidget(self.chart)

        right_widget: QtWidgets.QWidget = QtWidgets.QWidget()
        right_widget.setLayout(right_vbox)

        hbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox.addWidget(left_widget)
        hbox.addWidget(right_widget)
        self.setLayout(hbox)

    def load_backtesting_setting(self) -> None:
        """"""
        setting: dict = load_json(self.setting_filename)
        if not setting:
            return

        self.class_combo.setCurrentIndex(
            self.class_combo.findText(setting["class_name"])
        )

        self.symbol_combo.setCurrentText(setting["vt_symbol"])

        self.interval_combo.setCurrentIndex(
            self.interval_combo.findText(setting["interval"])
        )

        start_str: str = setting.get("start", "")
        if start_str:
            start_dt: QtCore.QDate = QtCore.QDate.fromString(start_str, "yyyy-MM-dd")
            self.start_date_edit.setDate(start_dt)

        self.rate_line.setText(str(setting["rate"]))
        self.slippage_line.setText(str(setting["slippage"]))
        self.size_line.setText(str(setting["size"]))
        self.pricetick_line.setText(str(setting["pricetick"]))
        self.capital_line.setText(str(setting["capital"]))

    def register_event(self) -> None:
        """"""
        self.signal_log.connect(self.process_log_event)
        self.signal_backtesting_finished.connect(
            self.process_backtesting_finished_event)
        self.signal_optimization_finished.connect(
            self.process_optimization_finished_event)
        self.signal_downloading_finished.connect(self.process_downloading_finished_event)

        self.event_engine.register(EVENT_BACKTESTER_LOG, self.signal_log.emit)
        self.event_engine.register(EVENT_BACKTESTER_BACKTESTING_FINISHED, self.signal_backtesting_finished.emit)
        self.event_engine.register(EVENT_BACKTESTER_OPTIMIZATION_FINISHED, self.signal_optimization_finished.emit)
        self.event_engine.register(
            EVENT_BACKTESTER_DOWNLOADING_FINISHED,
            self.signal_downloading_finished.emit
        )

    def process_log_event(self, event: Event) -> None:
        """"""
        msg = event.data
        self.write_log(msg)

    def write_log(self, msg: str) -> None:
        """"""
        timestamp: str = datetime.now().strftime("%H:%M:%S")
        msg = f"{timestamp}\t{msg}"
        self.log_monitor.append(msg)

    def process_backtesting_finished_event(self, event: Event) -> None:
        """"""
        statistics: dict | None = self.backtester_engine.get_result_statistics()
        if statistics:
            self.statistics_monitor.set_data(statistics)

        df: DataFrame | None = self.backtester_engine.get_result_df()
        if df is not None:
            self.chart.set_data(df)

        self.trade_button.setEnabled(True)
        self.order_button.setEnabled(True)
        self.daily_button.setEnabled(True)

        # Tick data can not be displayed using candle chart
        interval: str = self.interval_combo.currentText()
        if interval != Interval.TICK.value:
            self.candle_button.setEnabled(True)

    def process_optimization_finished_event(self, event: Event) -> None:
        """"""
        self.write_log(_("请点击[优化结果]按钮查看"))
        self.result_button.setEnabled(True)

    def process_downloading_finished_event(self, event: Event) -> None:
        """"""
        self.downloading_button.setText(_("下载数据"))
        self._set_backtesting_button_state(False)

        pending: dict | None = self.backtester_engine._pop_pending_backtest()
        if pending:
            result: bool = self.backtester_engine.start_backtesting(**pending)
            if result:
                self._after_backtesting_started()

    def start_backtesting(self) -> None:
        """"""
        class_name: str = self.class_combo.currentText()
        if not class_name:
            self.write_log(_("请选择要回测的策略"))
            return

        vt_symbol: str = self.symbol_combo.currentText()
        interval: str = self.interval_combo.currentText()
        start: datetime = cast(datetime, self.start_date_edit.dateTime().toPython())
        end: datetime = cast(datetime, self.end_date_edit.dateTime().toPython())
        rate: float = float(self.rate_line.text())
        slippage: float = float(self.slippage_line.text())
        size: float = float(self.size_line.text())
        pricetick: float = float(self.pricetick_line.text())
        capital: float = float(self.capital_line.text())

        # Check validity of vt_symbol
        if "." not in vt_symbol:
            self.write_log(_("本地代码缺失交易所后缀，请检查"))
            return

        __, exchange_str = vt_symbol.split(".")
        if exchange_str not in Exchange.__members__:
            self.write_log(_("本地代码的交易所后缀不正确，请检查"))
            return

        # Save backtesting parameters
        backtesting_setting: dict = {
            "class_name": class_name,
            "vt_symbol": vt_symbol,
            "interval": interval,
            "start": start.strftime("%Y-%m-%d"),
            "rate": rate,
            "slippage": slippage,
            "size": size,
            "pricetick": pricetick,
            "capital": capital
        }
        save_json(self.setting_filename, backtesting_setting)
        self.update_symbol_history(vt_symbol)

        # Get strategy setting
        old_setting: dict = self.settings[class_name]
        dialog: BacktestingSettingEditor = BacktestingSettingEditor(class_name, old_setting)
        i: int = dialog.exec()
        if i != dialog.DialogCode.Accepted:
            return

        new_setting: dict = dialog.get_setting()
        self.settings[class_name] = new_setting

        pending: dict = {
            "class_name": class_name,
            "vt_symbol": vt_symbol,
            "interval": interval,
            "start": start,
            "end": end,
            "rate": rate,
            "slippage": slippage,
            "size": size,
            "pricetick": pricetick,
            "capital": capital,
            "setting": new_setting
        }

        if not self.backtester_engine.ensure_backtesting_data(
            vt_symbol, interval, start, end, pending
        ):
            self._set_backtesting_button_state(True)
            return

        result: bool = self.backtester_engine.start_backtesting(**pending)

        if result:
            self._after_backtesting_started()

    def _after_backtesting_started(self) -> None:
        self.statistics_monitor.clear_data()
        self.chart.clear_data()

        self.trade_button.setEnabled(False)
        self.order_button.setEnabled(False)
        self.daily_button.setEnabled(False)
        self.candle_button.setEnabled(False)

        self.trade_dialog.clear_data()
        self.order_dialog.clear_data()
        self.daily_dialog.clear_data()
        self.candle_dialog.clear_data()

    def _set_backtesting_button_state(self, downloading: bool) -> None:
        self._download_in_progress = downloading
        if downloading:
            self.backtesting_button.setText(_("停止下载"))
        else:
            self.backtesting_button.setText(_("开始回测"))

    def _on_backtesting_button_clicked(self) -> None:
        if self._download_in_progress:
            self.backtester_engine._pop_pending_backtest()
            self.backtester_engine.stop_downloading()
            self._set_backtesting_button_state(False)
            return

        self.start_backtesting()

    def start_optimization(self) -> None:
        """"""
        class_name: str = self.class_combo.currentText()
        vt_symbol: str = self.symbol_combo.currentText()
        interval: str = self.interval_combo.currentText()
        start: datetime = cast(datetime, self.start_date_edit.dateTime().toPython())
        end: datetime = cast(datetime, self.end_date_edit.dateTime().toPython())
        rate: float = float(self.rate_line.text())
        slippage: float = float(self.slippage_line.text())
        size: float = float(self.size_line.text())
        pricetick: float = float(self.pricetick_line.text())
        capital: float = float(self.capital_line.text())

        parameters: dict = self.settings[class_name]
        dialog: OptimizationSettingEditor = OptimizationSettingEditor(class_name, parameters)
        i: int = dialog.exec()
        if i != dialog.DialogCode.Accepted:
            return

        optimization_setting, use_ga, max_workers = dialog.get_setting()
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
            use_ga,
            max_workers
        )

        self.result_button.setEnabled(False)

    def start_downloading(self) -> None:
        """"""
        vt_symbol: str = self.symbol_combo.currentText()
        interval: str = self.interval_combo.currentText()
        start_date: QtCore.QDate = self.start_date_edit.date()
        end_date: QtCore.QDate = self.end_date_edit.date()

        start: datetime = datetime(
            start_date.year(),
            start_date.month(),
            start_date.day(),
        )
        start= start.replace(tzinfo=DB_TZ)

        end: datetime = datetime(
            end_date.year(),
            end_date.month(),
            end_date.day(),
            23,
            59,
            59,
        )
        end = end.replace(tzinfo=DB_TZ)

        result: bool = self.backtester_engine.start_downloading(
            vt_symbol,
            interval,
            start,
            end
        )
        if result:
            self.update_symbol_history(vt_symbol)
            self.downloading_button.setText(_("停止下载"))

    def toggle_downloading(self) -> None:
        """"""
        if self.backtester_engine.is_downloading():
            self.backtester_engine.stop_downloading()
            self.downloading_button.setText(_("下载数据"))
        else:
            self.start_downloading()

    def show_optimization_result(self) -> None:
        """"""
        result_values: list | None = self.backtester_engine.get_result_values()
        if result_values is None:
            return

        dialog: OptimizationResultMonitor = OptimizationResultMonitor(
            result_values,
            self.target_display
        )
        dialog.exec_()

    def show_backtesting_trades(self) -> None:
        """"""
        if not self.trade_dialog.is_updated():
            trades: list[TradeData] = self.backtester_engine.get_all_trades()
            self.trade_dialog.update_data(trades)

        self.trade_dialog.exec_()

    def show_backtesting_orders(self) -> None:
        """"""
        if not self.order_dialog.is_updated():
            orders: list[OrderData] = self.backtester_engine.get_all_orders()
            self.order_dialog.update_data(orders)

        self.order_dialog.exec_()

    def show_daily_results(self) -> None:
        """"""
        if not self.daily_dialog.is_updated():
            results: list[DailyResult] = self.backtester_engine.get_all_daily_results()
            self.daily_dialog.update_data(results)

        self.daily_dialog.exec_()

    def show_candle_chart(self) -> None:
        """"""
        if not self.candle_dialog.is_updated():
            history: list = self.backtester_engine.get_history_data()
            self.candle_dialog.update_history(history)

            trades: list[TradeData] = self.backtester_engine.get_all_trades()
            self.candle_dialog.update_trades(trades)
        else:
            trades = self.backtester_engine.get_all_trades()
            self.candle_dialog.update_position_cost(trades)

        self.candle_dialog.exec_()

    def edit_strategy_code(self) -> None:
        """"""
        class_name: str = self.class_combo.currentText()
        if not class_name:
            return

        file_path: str = self.backtester_engine.get_strategy_class_file(class_name)

        # 按优先级排序的常用代码编辑器命令列表
        editor_cmds: list[str] = [
            "code",         # VS Code
            "cursor",       # Cursor
            "pycharm64",    # PyCharm (Windows)
            "charm",        # PyCharm (命令行启动器)
        ]

        # 查找可用的编辑器
        editor_cmd: str = ""
        for cmd in editor_cmds:
            if shutil.which(cmd):
                editor_cmd = cmd
                break

        if editor_cmd:
            if platform.system() == "Windows":
                subprocess.run([editor_cmd, file_path], shell=True)
            else:
                subprocess.run([editor_cmd, file_path])
        else:
            QtWidgets.QMessageBox.warning(
                self,
                _("启动代码编辑器失败"),
                _("未检测到可用的代码编辑器，请安装以下任一编辑器并添加到系统PATH：\n"
                  "Cursor、VS Code、PyCharm")
            )

    def reload_strategy_class(self) -> None:
        """"""
        self.backtester_engine.reload_strategy_class()

        current_strategy_name: str = self.class_combo.currentText()

        self.class_combo.clear()
        self.init_strategy_settings()

        ix: int = self.class_combo.findText(current_strategy_name)
        self.class_combo.setCurrentIndex(ix)

    def load_symbol_history(self) -> None:
        """"""
        records: list[dict] = []
        data = load_json(self.symbol_history_filename)
        if isinstance(data, list):
            for item in data:
                if isinstance(item, dict) and "symbol" in item:
                    records.append(
                        {
                            "symbol": str(item.get("symbol", "")).strip(),
                            "last_used": str(item.get("last_used", "")),
                            "count": int(item.get("count", 0) or 0),
                        }
                    )
                elif isinstance(item, str):
                    records.append(
                        {"symbol": item.strip(), "last_used": "", "count": 1}
                    )
        self.set_symbol_history_records(records)

    def set_symbol_history_records(self, records: list[dict]) -> None:
        """"""
        filtered: list[dict] = []
        for record in records:
            symbol: str = record.get("symbol", "").strip()
            if not symbol:
                continue
            filtered.append(
                {
                    "symbol": symbol,
                    "last_used": record.get("last_used", ""),
                    "count": int(record.get("count", 0) or 0),
                }
            )

        filtered.sort(
            key=lambda r: (r["last_used"], r["count"]), reverse=True
        )
        self.symbol_history_records = filtered[:50]
        self.set_symbol_history([r["symbol"] for r in self.symbol_history_records])

    def set_symbol_history(self, symbols: list[str]) -> None:
        """"""
        self.symbol_history = symbols
        current_text: str = self.symbol_combo.currentText()
        self.symbol_combo.blockSignals(True)
        self.symbol_combo.clear()
        self.symbol_combo.addItems(symbols)
        self.symbol_combo.setCurrentText(current_text)
        self.symbol_combo.blockSignals(False)

    def update_symbol_history(self, vt_symbol: str) -> None:
        """"""
        vt_symbol = vt_symbol.strip()
        if not vt_symbol:
            return

        now: str = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
        updated: bool = False
        records: list[dict] = []
        for record in self.symbol_history_records:
            if record["symbol"] == vt_symbol:
                record["count"] = int(record.get("count", 0) or 0) + 1
                record["last_used"] = now
                updated = True
            records.append(record)

        if not updated:
            records.append(
                {"symbol": vt_symbol, "last_used": now, "count": 1}
            )

        save_json(self.symbol_history_filename, records)
        self.set_symbol_history_records(records)

    def eventFilter(self, obj: QtCore.QObject, event: QtCore.QEvent) -> bool:  # type: ignore[override]
        if obj in {self.symbol_combo, self.symbol_combo.lineEdit()}:
            if event.type() == QtCore.QEvent.Type.MouseButtonPress:
                if not self.symbol_combo.currentText().strip():
                    self.symbol_combo.showPopup()
        return super().eventFilter(obj, event)

    def show(self) -> None:
        """"""
        self.showMaximized()


class StatisticsMonitor(QtWidgets.QTableWidget):
    """"""
    KEY_NAME_MAP: dict = {
        "start_date": _("首个交易日"),
        "end_date": _("最后交易日"),

        "total_days": _("总交易日"),
        "profit_days": _("盈利交易日"),
        "loss_days": _("亏损交易日"),

        "capital": _("起始资金"),
        "end_balance": _("结束资金"),

        "total_return": _("总收益率"),
        "annual_return": _("年化收益"),
        "max_drawdown": _("最大回撤"),
        "max_ddpercent": _("百分比最大回撤"),
        "max_drawdown_duration": _("最大回撤天数"),

        "total_net_pnl": _("总盈亏"),
        "total_commission": _("总手续费"),
        "total_slippage": _("总滑点"),
        "total_turnover": _("总成交额"),
        "total_trade_count": _("总成交笔数"),

        "daily_net_pnl": _("日均盈亏"),
        "daily_commission": _("日均手续费"),
        "daily_slippage": _("日均滑点"),
        "daily_turnover": _("日均成交额"),
        "daily_trade_count": _("日均成交笔数"),

        "daily_return": _("日均收益率"),
        "return_std": _("收益标准差"),
        "sharpe_ratio": _("夏普比率"),
        "ewm_sharpe": _("EWM夏普"),
        "return_drawdown_ratio": _("收益回撤比")
    }

    def __init__(self) -> None:
        """"""
        super().__init__()

        self.cells: dict = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setRowCount(len(self.KEY_NAME_MAP))
        self.setVerticalHeaderLabels(list(self.KEY_NAME_MAP.values()))

        self.setColumnCount(1)
        self.horizontalHeader().setVisible(False)
        self.horizontalHeader().setSectionResizeMode(
            QtWidgets.QHeaderView.ResizeMode.Stretch
        )
        self.setEditTriggers(self.EditTrigger.NoEditTriggers)

        for row, key in enumerate(self.KEY_NAME_MAP.keys()):
            cell: QtWidgets.QTableWidgetItem = QtWidgets.QTableWidgetItem()
            self.setItem(row, 0, cell)
            self.cells[key] = cell

    def clear_data(self) -> None:
        """"""
        for cell in self.cells.values():
            cell.setText("")

    def set_data(self, data: dict) -> None:
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
        data["daily_trade_count"] = f"{data['daily_trade_count']:,.2f}"
        data["daily_return"] = f"{data['daily_return']:,.2f}%"
        data["return_std"] = f"{data['return_std']:,.2f}%"
        data["sharpe_ratio"] = f"{data['sharpe_ratio']:,.2f}"
        data["ewm_sharpe"] = f"{data['ewm_sharpe']:,.2f}"
        data["return_drawdown_ratio"] = f"{data['return_drawdown_ratio']:,.2f}"

        for key, cell in self.cells.items():
            value = data.get(key, "")
            cell.setText(str(value))


class EscCloseDialog(QtWidgets.QDialog):
    """"""

    def keyPressEvent(self, event: QtGui.QKeyEvent) -> None:  # type: ignore[override]
        if event.key() == QtCore.Qt.Key.Key_Escape:
            self.reject()
            return
        super().keyPressEvent(event)


class BacktestingSettingEditor(EscCloseDialog):
    """
    For creating new strategy and editing strategy parameters.
    """

    def __init__(
        self, class_name: str, parameters: dict
    ) -> None:
        """"""
        super().__init__()

        self.class_name: str = class_name
        self.parameters: dict = parameters
        self.edits: dict = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        form: QtWidgets.QFormLayout = QtWidgets.QFormLayout()

        # Add vt_symbol and name edit if add new strategy
        self.setWindowTitle(_("策略参数配置：{}").format(self.class_name))
        button_text: str = _("确定")
        parameters: dict = self.parameters

        for name, value in parameters.items():
            type_ = type(value)

            edit: QtWidgets.QLineEdit = QtWidgets.QLineEdit(str(value))
            if type_ is int:
                int_validator: QtGui.QIntValidator = QtGui.QIntValidator()
                edit.setValidator(int_validator)
            elif type_ is float:
                double_validator: QtGui.QDoubleValidator = QtGui.QDoubleValidator()
                edit.setValidator(double_validator)

            form.addRow(f"{name} {type_}", edit)

            self.edits[name] = (edit, type_)

        button: QtWidgets.QPushButton = QtWidgets.QPushButton(button_text)
        button.clicked.connect(self.accept)
        form.addRow(button)

        widget: QtWidgets.QWidget = QtWidgets.QWidget()
        widget.setLayout(form)

        scroll: QtWidgets.QScrollArea = QtWidgets.QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(widget)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(scroll)
        self.setLayout(vbox)

    def get_setting(self) -> dict:
        """"""
        setting: dict = {}

        for name, tp in self.edits.items():
            edit, type_ = tp
            value_text = edit.text()

            if type_ is bool:
                if value_text == "True":
                    value = True
                else:
                    value = False
            else:
                value = type_(value_text)

            setting[name] = value

        return setting


class BacktesterChart(pg.GraphicsLayoutWidget):
    """"""

    def __init__(self) -> None:
        """"""
        super().__init__(title="Backtester Chart")

        self.dates: dict = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        pg.setConfigOptions(antialias=True)

        # Create plot widgets
        self.balance_plot = self.addPlot(
            title=_("账户净值"),
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.drawdown_plot = self.addPlot(
            title=_("净值回撤"),
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.pnl_plot = self.addPlot(
            title=_("每日盈亏"),
            axisItems={"bottom": DateAxis(self.dates, orientation="bottom")}
        )
        self.nextRow()

        self.distribution_plot = self.addPlot(title=_("盈亏分布"))

        # Add curves and bars on plot widgets
        self.balance_curve = self.balance_plot.plot(
            pen=pg.mkPen("#ffc107", width=3)
        )

        dd_color: str = "#303f9f"
        self.drawdown_curve = self.drawdown_plot.plot(
            fillLevel=-0.3, brush=dd_color, pen=dd_color
        )

        profit_color: str = 'r'
        loss_color: str = 'g'
        self.profit_pnl_bar = pg.BarGraphItem(
            x=[], height=[], width=0.3, brush=profit_color, pen=profit_color
        )
        self.loss_pnl_bar = pg.BarGraphItem(
            x=[], height=[], width=0.3, brush=loss_color, pen=loss_color
        )
        self.pnl_plot.addItem(self.profit_pnl_bar)
        self.pnl_plot.addItem(self.loss_pnl_bar)

        distribution_color: str = "#6d4c41"
        self.distribution_curve = self.distribution_plot.plot(
            fillLevel=-0.3, brush=distribution_color, pen=distribution_color
        )

    def clear_data(self) -> None:
        """"""
        self.balance_curve.setData([], [])
        self.drawdown_curve.setData([], [])
        self.profit_pnl_bar.setOpts(x=[], height=[])
        self.loss_pnl_bar.setOpts(x=[], height=[])
        self.distribution_curve.setData([], [])

    def set_data(self, df: DataFrame) -> None:
        """"""
        if df is None:
            return

        count: int = len(df)

        self.dates.clear()
        for n, date in enumerate(df.index):
            self.dates[n] = date

        # Set data for curve of balance and drawdown
        self.balance_curve.setData(df["balance"])
        self.drawdown_curve.setData(df["drawdown"])

        balance_series = df["balance"].dropna()
        if not balance_series.empty:
            min_balance = float(balance_series.min())
            max_balance = float(balance_series.max())
            padding = (max_balance - min_balance) * 0.02
            if padding == 0:
                padding = max(1.0, max_balance * 0.001)
            self.balance_plot.setRange(
                yRange=(min_balance - padding, max_balance + padding)
            )

        # Set data for daily pnl bar
        profit_pnl_x: list = []
        profit_pnl_height: list = []
        loss_pnl_x: list = []
        loss_pnl_height: list = []

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

    def __init__(self, dates: dict, *args: Any, **kwargs: Any) -> None:
        """"""
        super().__init__(*args, **kwargs)
        self.dates: dict = dates

    def tickStrings(self, values: list, scale: float, spacing: float) -> list:
        """"""
        strings: list = []
        for v in values:
            dt = self.dates.get(v, "")
            strings.append(str(dt))
        return strings


class OptimizationSettingEditor(EscCloseDialog):
    """
    For setting up parameters for optimization.
    """
    DISPLAY_NAME_MAP: dict = {
        _("总收益率"): "total_return",
        _("夏普比率"): "sharpe_ratio",
        _("EWM夏普"): "ewm_sharpe",
        _("收益回撤比"): "return_drawdown_ratio",
        _("日均盈亏"): "daily_net_pnl"
    }

    def __init__(
        self, class_name: str, parameters: dict
    ) -> None:
        """"""
        super().__init__()

        self.class_name: str = class_name
        self.parameters: dict = parameters
        self.edits: dict = {}

        self.optimization_setting: OptimizationSetting = None
        self.use_ga: bool = False

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.target_combo: QtWidgets.QComboBox = QtWidgets.QComboBox()
        self.target_combo.addItems(list(self.DISPLAY_NAME_MAP.keys()))

        self.worker_spin: QtWidgets.QSpinBox = QtWidgets.QSpinBox()
        self.worker_spin.setRange(0, 10000)
        self.worker_spin.setValue(0)
        self.worker_spin.setToolTip(_("设为0则自动根据CPU核心数启动对应数量的进程"))

        grid: QtWidgets.QGridLayout = QtWidgets.QGridLayout()
        grid.addWidget(QtWidgets.QLabel(_("优化目标")), 0, 0)
        grid.addWidget(self.target_combo, 0, 1, 1, 3)
        grid.addWidget(QtWidgets.QLabel(_("进程上限")), 1, 0)
        grid.addWidget(self.worker_spin, 1, 1, 1, 3)
        grid.addWidget(QtWidgets.QLabel(_("参数")), 2, 0)
        grid.addWidget(QtWidgets.QLabel(_("开始")), 2, 1)
        grid.addWidget(QtWidgets.QLabel(_("步进")), 2, 2)
        grid.addWidget(QtWidgets.QLabel(_("结束")), 2, 3)

        # Add vt_symbol and name edit if add new strategy
        self.setWindowTitle(_("优化参数配置：{}").format(self.class_name))

        validator: QtGui.QDoubleValidator = QtGui.QDoubleValidator()
        row: int = 3

        for name, value in self.parameters.items():
            type_ = type(value)
            if type_ not in [int, float]:
                continue

            start_edit: QtWidgets.QLineEdit = QtWidgets.QLineEdit(str(value))
            step_edit: QtWidgets.QLineEdit = QtWidgets.QLineEdit(str(1))
            end_edit: QtWidgets.QLineEdit = QtWidgets.QLineEdit(str(value))

            for edit in [start_edit, step_edit, end_edit]:
                edit.setValidator(validator)

            grid.addWidget(QtWidgets.QLabel(name), row, 0)
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

        parallel_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("多进程优化"))
        parallel_button.clicked.connect(self.generate_parallel_setting)
        grid.addWidget(parallel_button, row, 0, 1, 4)

        row += 1
        ga_button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("遗传算法优化"))
        ga_button.clicked.connect(self.generate_ga_setting)
        grid.addWidget(ga_button, row, 0, 1, 4)

        widget: QtWidgets.QWidget = QtWidgets.QWidget()
        widget.setLayout(grid)

        scroll: QtWidgets.QScrollArea = QtWidgets.QScrollArea()
        scroll.setWidgetResizable(True)
        scroll.setWidget(widget)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(scroll)
        self.setLayout(vbox)

    def generate_ga_setting(self) -> None:
        """"""
        self.use_ga = True
        self.generate_setting()

    def generate_parallel_setting(self) -> None:
        """"""
        self.use_ga = False
        self.generate_setting()

    def generate_setting(self) -> None:
        """"""
        self.optimization_setting = OptimizationSetting()

        self.target_display: str = self.target_combo.currentText()
        target_name: str = self.DISPLAY_NAME_MAP[self.target_display]
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

    def get_setting(self) -> tuple[OptimizationSetting, bool, int]:
        """"""
        return self.optimization_setting, self.use_ga, self.worker_spin.value()


class OptimizationResultMonitor(EscCloseDialog):
    """
    For viewing optimization result.
    """

    def __init__(
        self, result_values: list, target_display: str
    ) -> None:
        """"""
        super().__init__()

        self.result_values: list = result_values
        self.target_display: str = target_display

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(_("参数优化结果"))
        self.resize(1100, 500)

        # Creat table to show result
        table: QtWidgets.QTableWidget = QtWidgets.QTableWidget()

        table.setColumnCount(2)
        table.setRowCount(len(self.result_values))
        table.setHorizontalHeaderLabels([_("参数"), self.target_display])
        table.setEditTriggers(table.EditTrigger.NoEditTriggers)
        table.verticalHeader().setVisible(False)

        table.horizontalHeader().setSectionResizeMode(
            0, QtWidgets.QHeaderView.ResizeMode.ResizeToContents
        )
        table.horizontalHeader().setSectionResizeMode(
            1, QtWidgets.QHeaderView.ResizeMode.Stretch
        )

        for n, tp in enumerate(self.result_values):
            setting, target_value, __ = tp
            setting_cell: QtWidgets.QTableWidgetItem = QtWidgets.QTableWidgetItem(str(setting))
            target_cell: QtWidgets.QTableWidgetItem = QtWidgets.QTableWidgetItem(f"{target_value:.2f}")

            setting_cell.setTextAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)
            target_cell.setTextAlignment(QtCore.Qt.AlignmentFlag.AlignCenter)

            table.setItem(n, 0, setting_cell)
            table.setItem(n, 1, target_cell)

        # Create layout
        button: QtWidgets.QPushButton = QtWidgets.QPushButton(_("保存"))
        button.clicked.connect(self.save_csv)

        hbox: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox.addStretch()
        hbox.addWidget(button)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(table)
        vbox.addLayout(hbox)

        self.setLayout(vbox)

    def save_csv(self) -> None:
        """
        Save table data into a csv file
        """
        path, __ = QtWidgets.QFileDialog.getSaveFileName(
            self, _("保存数据"), "", "CSV(*.csv)")

        if not path:
            return

        with open(path, "w") as f:
            writer = csv.writer(f, lineterminator="\n")

            writer.writerow([_("参数"), self.target_display])

            for tp in self.result_values:
                setting, target_value, __ = tp
                row_data: list = [str(setting), str(target_value)]
                writer.writerow(row_data)


class BacktestingTradeMonitor(BaseMonitor):
    """
    Monitor for backtesting trade data.
    """

    headers: dict = {
        "tradeid": {"display": _("成交号 "), "cell": BaseCell, "update": False},
        "orderid": {"display": _("委托号"), "cell": BaseCell, "update": False},
        "symbol": {"display": _("代码"), "cell": BaseCell, "update": False},
        "exchange": {"display": _("交易所"), "cell": EnumCell, "update": False},
        "direction": {"display": _("方向"), "cell": DirectionCell, "update": False},
        "offset": {"display": _("开平"), "cell": EnumCell, "update": False},
        "price": {"display": _("价格"), "cell": BaseCell, "update": False},
        "volume": {"display": _("数量"), "cell": BaseCell, "update": False},
        "datetime": {"display": _("时间"), "cell": BaseCell, "update": False},
        "gateway_name": {"display": _("接口"), "cell": BaseCell, "update": False},
    }


class BacktestingOrderMonitor(BaseMonitor):
    """
    Monitor for backtesting order data.
    """

    headers: dict = {
        "orderid": {"display": _("委托号"), "cell": BaseCell, "update": False},
        "symbol": {"display": _("代码"), "cell": BaseCell, "update": False},
        "exchange": {"display": _("交易所"), "cell": EnumCell, "update": False},
        "type": {"display": _("类型"), "cell": EnumCell, "update": False},
        "direction": {"display": _("方向"), "cell": DirectionCell, "update": False},
        "offset": {"display": _("开平"), "cell": EnumCell, "update": False},
        "price": {"display": _("价格"), "cell": BaseCell, "update": False},
        "volume": {"display": _("总数量"), "cell": BaseCell, "update": False},
        "traded": {"display": _("已成交"), "cell": BaseCell, "update": False},
        "status": {"display": _("状态"), "cell": EnumCell, "update": False},
        "datetime": {"display": _("时间"), "cell": BaseCell, "update": False},
        "gateway_name": {"display": _("接口"), "cell": BaseCell, "update": False},
    }


class FloatCell(BaseCell):
    """
    Cell used for showing pnl data.
    """

    def __init__(self, content: Any, data: Any) -> None:
        """"""
        content = f"{content:.2f}"
        super().__init__(content, data)


class DailyResultMonitor(BaseMonitor):
    """
    Monitor for backtesting daily result.
    """

    headers: dict = {
        "date": {"display": _("日期"), "cell": BaseCell, "update": False},
        "trade_count": {"display": _("成交笔数"), "cell": BaseCell, "update": False},
        "start_pos": {"display": _("开盘持仓"), "cell": BaseCell, "update": False},
        "end_pos": {"display": _("收盘持仓"), "cell": BaseCell, "update": False},
        "turnover": {"display": _("成交额"), "cell": FloatCell, "update": False},
        "commission": {"display": _("手续费"), "cell": FloatCell, "update": False},
        "slippage": {"display": _("滑点"), "cell": FloatCell, "update": False},
        "trading_pnl": {"display": _("交易盈亏"), "cell": FloatCell, "update": False},
        "holding_pnl": {"display": _("持仓盈亏"), "cell": FloatCell, "update": False},
        "total_pnl": {"display": _("总盈亏"), "cell": FloatCell, "update": False},
        "net_pnl": {"display": _("净盈亏"), "cell": FloatCell, "update": False},
    }


class BacktestingResultDialog(EscCloseDialog):
    """"""

    def __init__(
        self,
        main_engine: MainEngine,
        event_engine: EventEngine,
        title: str,
        table_class: type[BaseMonitor]
    ) -> None:
        """"""
        super().__init__()

        self.main_engine: MainEngine = main_engine
        self.event_engine: EventEngine = event_engine
        self.title: str = title
        self.table_class: type[BaseMonitor] = table_class

        self.updated: bool = False

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(self.title)
        self.resize(1100, 600)

        self.table: BaseMonitor = self.table_class(self.main_engine, self.event_engine)

        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.table)

        self.setLayout(vbox)

    def clear_data(self) -> None:
        """"""
        self.updated = False
        self.table.setRowCount(0)

    def update_data(self, data: list) -> None:
        """"""
        self.updated = True

        data.reverse()
        for obj in data:
            self.table.insert_new_row(obj)

    def is_updated(self) -> bool:
        """"""
        return self.updated


class CandleChartDialog(EscCloseDialog):
    """"""

    def __init__(self) -> None:
        """"""
        super().__init__()

        self.updated: bool = False

        self.dt_ix_map: dict = {}
        self.ix_bar_map: dict = {}

        self.high_price = 0
        self.low_price = 0
        self.price_range = 0

        self.items: list = []
        self.position_cost_map: dict[int, tuple[float, float, float]] = {}

        self.init_ui()

    def init_ui(self) -> None:
        """"""
        self.setWindowTitle(_("回测K线图表"))
        self.resize(1400, 800)

        # Create chart widget
        self.chart: ChartWidget = ChartWidget()
        self.chart.add_plot("candle", hide_x_axis=True)
        self.chart.add_plot("volume", maximum_height=200)
        self.chart.add_item(CandleItem, "candle", "candle")
        self.chart.add_item(VolumeItem, "volume", "volume")
        self.chart.add_cursor()

        # Create help widget
        text1: str = _("红色虚线 —— 盈利交易")
        label1: QtWidgets.QLabel = QtWidgets.QLabel(text1)
        label1.setStyleSheet("color:red")

        text2: str = _("绿色虚线 —— 亏损交易")
        label2: QtWidgets.QLabel = QtWidgets.QLabel(text2)
        label2.setStyleSheet("color:#00FF00")

        text3: str = _("黄色向上箭头 —— 买入开仓 Buy")
        label3: QtWidgets.QLabel = QtWidgets.QLabel(text3)
        label3.setStyleSheet("color:yellow")

        text4: str = _("黄色向下箭头 —— 卖出平仓 Sell")
        label4: QtWidgets.QLabel = QtWidgets.QLabel(text4)
        label4.setStyleSheet("color:yellow")

        text5: str = _("紫红向下箭头 —— 卖出开仓 Short")
        label5: QtWidgets.QLabel = QtWidgets.QLabel(text5)
        label5.setStyleSheet("color:magenta")

        text6: str = _("紫红向上箭头 —— 买入平仓 Cover")
        label6: QtWidgets.QLabel = QtWidgets.QLabel(text6)
        label6.setStyleSheet("color:magenta")

        hbox1: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox1.addStretch()
        hbox1.addWidget(label1)
        hbox1.addStretch()
        hbox1.addWidget(label2)
        hbox1.addStretch()

        hbox2: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox2.addStretch()
        hbox2.addWidget(label3)
        hbox2.addStretch()
        hbox2.addWidget(label4)
        hbox2.addStretch()

        hbox3: QtWidgets.QHBoxLayout = QtWidgets.QHBoxLayout()
        hbox3.addStretch()
        hbox3.addWidget(label5)
        hbox3.addStretch()
        hbox3.addWidget(label6)
        hbox3.addStretch()

        # Set layout
        vbox: QtWidgets.QVBoxLayout = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.chart)
        vbox.addLayout(hbox1)
        vbox.addLayout(hbox2)
        vbox.addLayout(hbox3)
        self.setLayout(vbox)

    def update_history(self, history: list) -> None:
        """"""
        self.updated = True
        self.chart.update_history(history)

        for ix, bar in enumerate(history):
            self.ix_bar_map[ix] = bar
            self.dt_ix_map[bar.datetime] = ix

            if not self.high_price:
                self.high_price = bar.high_price
                self.low_price = bar.low_price
            else:
                self.high_price = max(self.high_price, bar.high_price)
                self.low_price = min(self.low_price, bar.low_price)

        self.price_range = self.high_price - self.low_price

    def update_trades(self, trades: list) -> None:
        """"""
        trade_pairs: list = generate_trade_pairs(trades)

        self.update_position_cost(trades)

        candle_plot: pg.PlotItem = self.chart.get_plot("candle")

        scatter_data: list = []

        y_adjustment: float = self.price_range * 0.001

        for d in trade_pairs:
            open_ix = self.dt_ix_map[d["open_dt"]]
            close_ix = self.dt_ix_map[d["close_dt"]]
            open_price = d["open_price"]
            close_price = d["close_price"]

            # Trade Line
            x: list = [open_ix, close_ix]
            y: list = [open_price, close_price]

            if d["direction"] == Direction.LONG and close_price >= open_price:
                color: str = "r"
            elif d["direction"] == Direction.SHORT and close_price <= open_price:
                color = "r"
            else:
                color = "g"

            pen: QtGui.QPen = pg.mkPen(color, width=1.5, style=QtCore.Qt.PenStyle.DashLine)
            item: pg.PlotCurveItem = pg.PlotCurveItem(x, y, pen=pen)

            self.items.append(item)
            candle_plot.addItem(item)

            # Trade Scatter
            open_bar: BarData = self.ix_bar_map[open_ix]
            close_bar: BarData = self.ix_bar_map[close_ix]

            if d["direction"] == Direction.LONG:
                scatter_color: str = "yellow"
                open_symbol: str = "t1"
                close_symbol: str = "t"
                open_side: int = 1
                close_side: int = -1
                open_y: float = open_bar.low_price
                close_y: float = close_bar.high_price
            else:
                scatter_color = "magenta"
                open_symbol = "t"
                close_symbol = "t1"
                open_side = -1
                close_side = 1
                open_y = open_bar.high_price
                close_y = close_bar.low_price

            pen = pg.mkPen(QtGui.QColor(scatter_color))
            brush: QtGui.QBrush = pg.mkBrush(QtGui.QColor(scatter_color))
            size: int = 10

            open_scatter: dict = {
                "pos": (open_ix, open_y - open_side * y_adjustment),
                "size": size,
                "pen": pen,
                "brush": brush,
                "symbol": open_symbol
            }

            close_scatter: dict = {
                "pos": (close_ix, close_y - close_side * y_adjustment),
                "size": size,
                "pen": pen,
                "brush": brush,
                "symbol": close_symbol
            }

            scatter_data.append(open_scatter)
            scatter_data.append(close_scatter)

            # Trade text
            volume = d["volume"]
            text_color: QtGui.QColor = QtGui.QColor(scatter_color)
            open_text: pg.TextItem = pg.TextItem(f"[{volume}]", color=text_color, anchor=(0.5, 0.5))
            close_text: pg.TextItem = pg.TextItem(f"[{volume}]", color=text_color, anchor=(0.5, 0.5))

            open_text.setPos(open_ix, open_y - open_side * y_adjustment * 3)
            close_text.setPos(close_ix, close_y - close_side * y_adjustment * 3)

            self.items.append(open_text)
            self.items.append(close_text)

            candle_plot.addItem(open_text)
            candle_plot.addItem(close_text)

        trade_scatter: pg.ScatterPlotItem = pg.ScatterPlotItem(scatter_data)
        self.items.append(trade_scatter)
        candle_plot.addItem(trade_scatter)

    def clear_data(self) -> None:
        """"""
        self.updated = False

        candle_plot: pg.PlotItem = self.chart.get_plot("candle")
        for item in self.items:
            candle_plot.removeItem(item)
        self.items.clear()

        self.chart.clear_all()

        self.dt_ix_map.clear()
        self.ix_bar_map.clear()
        self.position_cost_map.clear()
        if hasattr(self.chart, "_manager"):
            self.chart._manager.extra_info_map = {}  # type: ignore[attr-defined]

    def is_updated(self) -> bool:
        """"""
        return self.updated

    def update_position_cost(self, trades: list[TradeData]) -> None:
        """"""
        self.position_cost_map.clear()
        if not self.ix_bar_map:
            return

        sorted_trades: list[TradeData] = [
            t for t in trades if t.datetime is not None
        ]
        sorted_trades.sort(key=lambda t: t.datetime)

        pos: float = 0.0
        cost: float = 0.0
        trade_ix: int = 0

        for ix, bar in self.ix_bar_map.items():
            while trade_ix < len(sorted_trades):
                trade: TradeData = sorted_trades[trade_ix]
                if trade.datetime > bar.datetime:
                    break
                pos, cost = self.apply_trade_to_position(pos, cost, trade)
                trade_ix += 1

            float_pnl: float = (bar.close_price - cost) * pos if pos else 0.0
            self.position_cost_map[ix] = (
                round(pos, 6),
                round(cost, 6),
                round(float_pnl, 6)
            )

        if hasattr(self.chart, "_manager"):
            self.chart._manager.extra_info_map = self.position_cost_map  # type: ignore[attr-defined]

    def apply_trade_to_position(
        self,
        pos: float,
        cost: float,
        trade: TradeData
    ) -> tuple[float, float]:
        """"""
        volume: float = trade.volume
        price: float = trade.price
        offset: Offset = trade.offset

        def open_long(curr_pos: float, curr_cost: float) -> tuple[float, float]:
            new_pos = curr_pos + volume
            new_cost = (curr_cost * curr_pos + price * volume) / new_pos if new_pos else 0.0
            return new_pos, new_cost

        def close_long(curr_pos: float, curr_cost: float) -> tuple[float, float]:
            new_pos = max(curr_pos - volume, 0.0)
            if new_pos == 0:
                return 0.0, 0.0
            return new_pos, curr_cost

        def open_short(curr_pos: float, curr_cost: float) -> tuple[float, float]:
            new_pos = curr_pos - volume
            abs_prev = abs(curr_pos)
            abs_new = abs(new_pos)
            new_cost = (curr_cost * abs_prev + price * volume) / abs_new if abs_new else 0.0
            return new_pos, new_cost

        def cover_short(curr_pos: float, curr_cost: float) -> tuple[float, float]:
            new_pos = min(curr_pos + volume, 0.0)
            if new_pos == 0:
                return 0.0, 0.0
            return new_pos, curr_cost

        if trade.direction == Direction.LONG:
            if offset == Offset.OPEN:
                return open_long(pos, cost)
            if offset in {Offset.CLOSE, Offset.CLOSETODAY, Offset.CLOSEYESTERDAY}:
                return cover_short(pos, cost)
            if pos < 0:
                return cover_short(pos, cost)
            return open_long(pos, cost)

        if trade.direction == Direction.SHORT:
            if offset == Offset.OPEN:
                return open_short(pos, cost)
            if offset in {Offset.CLOSE, Offset.CLOSETODAY, Offset.CLOSEYESTERDAY}:
                return close_long(pos, cost)
            if pos > 0:
                return close_long(pos, cost)
            return open_short(pos, cost)

        return pos, cost


def generate_trade_pairs(trades: list) -> list:
    """"""
    long_trades: list = []
    short_trades: list = []
    trade_pairs: list = []

    for trade in trades:
        trade = copy(trade)

        if trade.direction == Direction.LONG:
            same_direction: list = long_trades
            opposite_direction: list = short_trades
        else:
            same_direction = short_trades
            opposite_direction = long_trades

        while trade.volume and opposite_direction:
            open_trade: TradeData = opposite_direction[0]

            close_volume = min(open_trade.volume, trade.volume)
            d: dict = {
                "open_dt": open_trade.datetime,
                "open_price": open_trade.price,
                "close_dt": trade.datetime,
                "close_price": trade.price,
                "direction": open_trade.direction,
                "volume": close_volume,
            }
            trade_pairs.append(d)

            open_trade.volume -= close_volume
            if not open_trade.volume:
                opposite_direction.pop(0)

            trade.volume -= close_volume

        if trade.volume:
            same_direction.append(trade)

    return trade_pairs

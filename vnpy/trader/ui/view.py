
from PySide6.QtCore import Qt, QModelIndex, QSettings, QByteArray

from .qt import QtWidgets


class BaseView(QtWidgets.QTableView):
    """
    Base view.
    """

    tip_text = ""

    def __init__(self):
        """"""
        super().__init__()
        self.verticalHeader().hide()
        self.init_menu()
        self.load_setting()
        self.func = None

    def init_menu(self) -> None:
        """
        Create right click menu.
        """
        self.setContextMenuPolicy(Qt.ActionsContextMenu)

        resize_action = QtWidgets.QAction("调整列宽", self)
        resize_action.triggered.connect(self.resize_columns)
        self.addAction(resize_action)

        save_action = QtWidgets.QAction("保存数据", self)
        save_action.triggered.connect(self.save_csv)
        self.addAction(save_action)

    def resize_columns(self) -> None:
        """"""
        self.resizeColumnsToContents()

    def save_csv(self) -> None:
        """
        Save table data into a csv file.
        """
        self.model().save_csv(self)

    def init_double_click(self) -> None:
        """
        Connect double click event to table view.
        """
        self.setToolTip(self.tip_text)
        self.doubleClicked.connect(self.double_click_event)

    def double_click_event(self, index: QModelIndex) -> None:
        """
        Double click event.
        """
        pass

    def add_double_click_event(self, func: callable):
        """
        Add double click event to table view.
        """
        self.func = func

    def save_setting(self) -> None:
        """
        Save setting.
        """
        settings = QSettings(self.__class__.__name__, "custom")
        settings.setValue("column_state", self.horizontalHeader().saveState())

    def load_setting(self) -> None:
        """
        Load setting.
        """
        settings = QSettings(self.__class__.__name__, "custom")
        column_state = settings.value("column_state")

        if isinstance(column_state, QByteArray):
            self.horizontalHeader().restoreState(column_state)
            self.horizontalHeader().setSortIndicator(-1, Qt.AscendingOrder)


class CancelOrderView(BaseView):
    """
    Table view with double click event to cancel order.
    """

    tip_text = "双击单元格撤单"

    def __init__(self):
        """"""
        super().__init__()
        self.init_double_click()

    def double_click_event(self, index: QModelIndex) -> None:
        """
        Cancel order if row double clicked.
        """
        self.model().cancel_order(index)


class FillView(BaseView):
    """
    Table view with double click event to get trading data.
    """

    tip_text = "双击填充委托"

    def __init__(self):
        """"""
        super().__init__()
        self.init_double_click()

    def double_click_event(self, index: QModelIndex) -> None:
        """
        Double click to get the instance
        """
        order = self.model().get_data(index)
        self.func(order)

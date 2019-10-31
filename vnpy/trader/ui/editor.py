from typing import Callable, Dict
from pathlib import Path

from PyQt5 import QtWidgets, Qsci, QtGui


class CodeEditor(QtWidgets.QMainWindow):
    """"""

    def __init__(self):
        """"""
        super().__init__()

        self.editors: [str, Qsci.QsciScintilla] = {}

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("策略编辑器")

        self.init_menu()
        self.init_central()

    def init_central(self):
        """"""
        self.tab = QtWidgets.QTabWidget()
        self.path_label = QtWidgets.QLabel()

        vbox = QtWidgets.QVBoxLayout()
        vbox.addWidget(self.tab)
        vbox.addWidget(self.path_label)

        widget = QtWidgets.QWidget()
        widget.setLayout(vbox)

        self.setCentralWidget(widget)

    def init_menu(self):
        """"""
        bar = self.menuBar()

        file_bar = bar.addMenu("文件")
        self.add_menu_action(file_bar, "新建", self.new_file)
        self.add_menu_action(file_bar, "打开", self.open_file)
        self.add_menu_action(file_bar, "保存", self.save_file)
        self.add_menu_action(file_bar, "另存为", self.save_file)

        edit_bar = bar.addMenu("编辑")
        self.add_menu_action(edit_bar, "复制", self.copy)
        self.add_menu_action(edit_bar, "粘贴", self.paste)
        self.add_menu_action(edit_bar, "剪切", self.cut)
        edit_bar.addSeparator()
        self.add_menu_action(edit_bar, "查找", self.find)
        self.add_menu_action(edit_bar, "替换", self.replace)

        help_bar = bar.addMenu("帮助")
        self.add_menu_action(help_bar, "快捷键", self.show_shortcut)

    def add_menu_action(
        self,
        menu: QtWidgets.QMenu,
        action_name: str,
        func: Callable,
    ):
        """"""
        action = QtWidgets.QAction(action_name, self)
        action.triggered.connect(func)
        menu.addAction(action)

    def new_editor(self):
        """"""
        # Create editor object
        editor = Qsci.QsciScintilla()

        # Set editor font
        font = QtGui.QFont()
        font.setFamily('Consolas')
        font.setFixedPitch(True)
        font.setPointSize(10)

        editor.setFont(font)
        editor.setMarginsFont(font)

        # Set margin for line numbers
        font_metrics = QtGui.QFontMetrics(font)
        editor.setMarginWidth(0, font_metrics.width("00000") + 6)
        editor.setMarginLineNumbers(0, True)
        editor.setMarginsBackgroundColor(QtGui.QColor("#cccccc"))

        # Set brace matching
        editor.setBraceMatching(Qsci.QsciScintilla.SloppyBraceMatch)

        # Hide horizontal scroll bar
        editor.SendScintilla(Qsci.QsciScintilla.SCI_SETHSCROLLBAR, 0)

        # Set current line color
        editor.setCaretLineVisible(True)
        editor.setCaretLineBackgroundColor(QtGui.QColor("#ffe4e4"))

        # Set Python lexer
        lexer = Qsci.QsciLexerPython()
        lexer.setDefaultFont(font)
        editor.setLexer(lexer)

        # Add minimum editor size
        editor.setMinimumSize(600, 450)

        # Enable auto complete
        editor.setAutoCompletionSource(Qsci.QsciScintilla.AcsAll)
        editor.setAutoCompletionThreshold(2)
        editor.setAutoCompletionCaseSensitivity(False)
        editor.setAutoCompletionReplaceWord(False)

        # Use space indentation
        editor.setIndentationsUseTabs(False)
        editor.setTabWidth(4)
        editor.setIndentationGuides(True)

        # Enable folding
        editor.setFolding(True)

        return editor

    def open_editor(self, file_path: str):
        """"""
        if file_path in self.editors:
            editor = self.editors[file_path]
            editor.show()
            return

        editor = self.new_editor()
        self.editors[file_path] = editor

        buf = open(file_path, encoding="UTF8").read()
        editor.setText(buf)

        file_name = Path(file_path).name
        i = self.tab.addTab(editor, file_name)
        self.tab.setCurrentIndex(i)

        self.path_label.setText(file_path)

    def close_editor(self):
        """"""
        pass

    def open_file(self):
        """"""
        file_path, _ = QtWidgets.QFileDialog.getOpenFileName(
            self, "打开", "", "Python(*.py)")

        if file_path:
            self.open_editor(file_path)

    def new_file(self):
        """"""
        file_path, _ = QtWidgets.QFileDialog.getSaveFileName(
            self, "新建", "", "Python(*.py)")

        if file_path:
            open(file_path, "a").close()
            self.open_editor(file_path)

    def save_file(self):
        """"""
        pass

    def copy(self):
        """"""
        editor = self.get_active_editor()
        editor.copy()

    def paste(self):
        """"""
        editor = self.get_active_editor()
        editor.paste()

    def cut(self):
        """"""
        editor = self.get_active_editor()
        editor.cut()

    def show_shortcut(self):
        """"""
        pass

    def find(self):
        """"""
        pass

    def replace(self):
        """"""
        pass

    def get_active_editor(self):
        """"""
        for editor in self.editors.values():
            if editor.isVisible():
                return editor


if __name__ == "__main__":
    import sys
    from vnpy.trader.ui import create_qapp

    app = create_qapp()

    editor = CodeEditor()
    editor.showMaximized()
    editor.open_editor(sys.argv[0])

    app.exec_()

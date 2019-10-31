from typing import Callable, Dict
from pathlib import Path

from PyQt5 import QtWidgets, Qsci, QtGui


class CodeEditor(QtWidgets.QMainWindow):
    """"""
    NEW_FILE_NAME = "Untitled"

    def __init__(self):
        """"""
        super().__init__()

        self.new_file_count = 0
        self.editor_path_map: Dict[Qsci.QsciScintilla, str] = {}

        self.init_ui()

    def init_ui(self):
        """"""
        self.setWindowTitle("策略编辑器")

        self.init_menu()
        self.init_central()

    def init_central(self):
        """"""
        self.tab = QtWidgets.QTabWidget()
        self.tab.currentChanged.connect(self.update_path_label)

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

        file_menu = bar.addMenu("文件")
        self.add_menu_action(file_menu, "新建", self.new_file, "Ctrl+N")
        self.add_menu_action(file_menu, "打开", self.open_file, "Ctrl+O")
        self.add_menu_action(file_menu, "保存", self.save_file, "Ctrl+S")
        self.add_menu_action(
            file_menu,
            "另存为",
            self.save_file_as,
            "Ctrl+Shift+S"
        )
        file_menu.addSeparator()
        self.add_menu_action(file_menu, "退出", self.close)

        edit_menu = bar.addMenu("编辑")
        self.add_menu_action(edit_menu, "复制", self.copy, "Ctrl+C")
        self.add_menu_action(edit_menu, "粘贴", self.paste, "Ctrl+P")
        self.add_menu_action(edit_menu, "剪切", self.cut, "Ctrl+X")
        edit_menu.addSeparator()
        self.add_menu_action(edit_menu, "查找", self.find, "Ctrl+F")
        self.add_menu_action(edit_menu, "替换", self.replace, "Ctrl+H")

        help_menu = bar.addMenu("帮助")

    def add_menu_action(
        self,
        menu: QtWidgets.QMenu,
        action_name: str,
        func: Callable,
        shortcut: str = "",
    ):
        """"""
        action = QtWidgets.QAction(action_name, self)
        action.triggered.connect(func)
        menu.addAction(action)

        if shortcut:
            sequence = QtGui.QKeySequence(shortcut)
            action.setShortcut(sequence)

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

    def open_editor(self, file_path: str = ""):
        """"""
        # Show editor tab if file already opened
        if file_path:
            file_path = str(Path(file_path))

            for editor, path in self.editor_path_map.items():
                if file_path == path:
                    editor.show()
                    return

        # Otherwise create new editor
        editor = self.new_editor()

        if file_path:
            buf = open(file_path, encoding="UTF8").read()
            editor.setText(buf)
            file_name = Path(file_path).name

            self.editor_path_map[editor] = file_path
        else:
            self.new_file_count += 1
            file_name = f"{self.NEW_FILE_NAME}-{self.new_file_count}"

            self.editor_path_map[editor] = file_name

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
        self.open_editor("")

    def save_file(self):
        """"""
        editor = self.get_active_editor()
        file_path = self.editor_path_map[editor]

        if self.NEW_FILE_NAME in file_path:
            file_path, _ = QtWidgets.QFileDialog.getSaveFileName(
                self, "保存", "", "Python(*.py)")
            file_path = str(Path(file_path))

        self.save_editor_text(editor, file_path)

    def save_file_as(self):
        """"""
        editor = self.get_active_editor()

        file_path, _ = QtWidgets.QFileDialog.getSaveFileName(
            self, "保存", "", "Python(*.py)")

        self.save_editor_text(editor, file_path)

    def save_editor_text(self, editor: Qsci.QsciScintilla, file_path: str):
        """"""
        if file_path:
            self.editor_path_map[editor] = file_path

            i = self.tab.currentIndex()
            file_name = Path(file_path).name
            self.tab.setTabText(i, file_name)

            with open(file_path, "w") as f:
                f.write(editor.text())

        self.update_path_label()

    def copy(self):
        """"""
        self.get_active_editor().copy()

    def paste(self):
        """"""
        self.get_active_editor.paste()

    def cut(self):
        """"""
        self.get_active_editor.cut()

    def find(self):
        """"""
        dialog = FindDialog(
            self.get_active_editor(),
            False
        )
        dialog.exec_()

    def replace(self):
        """"""
        dialog = FindDialog(
            self.get_active_editor(),
            True
        )
        dialog.exec_()

    def get_active_editor(self):
        """"""
        return self.tab.currentWidget()

    def closeEvent(self, event):
        """"""
        for editor, path in self.editor_path_map.items():
            i = QtWidgets.QMessageBox.question(
                self,
                "退出保存",
                f"是否要保存{path}？",
                QtWidgets.QMessageBox.Save | QtWidgets.QMessageBox.No | QtWidgets.QMessageBox.Cancel,
                QtWidgets.QMessageBox.Save
            )

            if i == QtWidgets.QMessageBox.Save:
                if self.NEW_FILE_NAME in path:
                    path, _ = QtWidgets.QFileDialog.getSaveFileName(
                        self, "保存", "", "Python(*.py)")

                if path:
                    self.save_editor_text(editor, path)
            elif i == QtWidgets.QMessageBox.Cancel:
                break

        event.accept()

    def update_path_label(self):
        """"""
        editor = self.get_active_editor()
        path = self.editor_path_map[editor]
        self.path_label.setText(path)


class FindDialog(QtWidgets.QDialog):
    """"""

    def __init__(self, editor: Qsci.QsciScintilla, replace: bool = False):
        """"""
        super().__init__()

        self.editor = editor
        self.replace = replace

        self.text = ""
        self.case_sensitive = False
        self.whole_word = False
        self.selection = False

        self.init_ui()

    def init_ui(self):
        """"""
        find_label = QtWidgets.QLabel("查找")
        replace_label = QtWidgets.QLabel("替换")

        self.find_line = QtWidgets.QLineEdit()
        self.replace_line = QtWidgets.QLineEdit()

        self.case_check = QtWidgets.QCheckBox("大小写")
        self.whole_check = QtWidgets.QCheckBox("全词匹配")
        self.selection_check = QtWidgets.QCheckBox("选中区域")

        find_button = QtWidgets.QPushButton("查找")
        find_button.clicked.connect(self.find_text)

        replace_button = QtWidgets.QPushButton("替换")
        replace_button.clicked.connect(self.replace_text)

        check_hbox = QtWidgets.QHBoxLayout()
        check_hbox.addWidget(self.case_check)
        check_hbox.addStretch()
        check_hbox.addWidget(self.whole_check)
        check_hbox.addStretch()
        check_hbox.addWidget(self.selection_check)
        check_hbox.addStretch()

        button_hbox = QtWidgets.QHBoxLayout()
        button_hbox.addWidget(find_button)
        button_hbox.addWidget(replace_button)

        form = QtWidgets.QFormLayout()
        form.addRow(find_label, self.find_line)
        form.addRow(replace_label, self.replace_line)
        form.addRow(check_hbox)
        form.addRow(button_hbox)

        self.setLayout(form)

        if self.replace:
            self.setWindowTitle("替换")
        else:
            self.setWindowTitle("查找")
            replace_label.setVisible(False)
            self.replace_line.setVisible(False)
            replace_button.setVisible(False)

    def find_text(self):
        """"""
        new_text = self.find_line.text()
        new_case_sensitive = self.case_check.isChecked()
        new_whole_word = self.whole_check.isChecked()
        new_selection = self.selection_check.isChecked()

        if (
            new_text == self.text
            and new_case_sensitive == self.case_sensitive
            and new_whole_word == self.whole_word
            and new_selection == self.selection
        ):
            self.editor.findNext()
            return

        self.text = new_text
        self.case_sensitive = new_case_sensitive
        self.whole_word = new_whole_word
        self.selection = new_selection

        if not self.selection:
            self.editor.findFirst(
                self.text,
                False,
                self.case_sensitive,
                self.whole_word,
                False,
                show=True
            )
        else:
            self.editor.findFirstInSelection(
                self.text,
                False,
                self.case_sensitive,
                self.whole_word,
                False,
                show=True
            )

    def replace_text(self):
        """"""
        new_text = self.replace_line.text()

        self.editor.replace(new_text)


if __name__ == "__main__":
    import sys
    from vnpy.trader.ui import create_qapp

    app = create_qapp()

    editor = CodeEditor()
    editor.showMaximized()
    editor.open_editor(sys.argv[0])

    app.exec_()

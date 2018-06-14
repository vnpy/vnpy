# encoding: UTF-8

from vnpy.trader.uiQt import QtGui, QtWidgets, QtCore

COLOR_BID = QtGui.QColor(255,174,201)
COLOR_ASK = QtGui.QColor(160,255,160)
COLOR_STRIKE = QtGui.QColor(0,0,160)
COLOR_POS = QtGui.QColor(225,255,255)
COLOR_SYMBOL = QtGui.QColor('white')
COLOR_BLACK = QtGui.QColor('black')

CALL_SUFFIX = '_call'
PUT_SUFFIX = '_put'

STYLESHEET_START = "background-color: rgb(111,255,244); color: black"
STYLESHEET_STOP = "background-color: rgb(255,201,111); color: black"


########################################################################
class OmCell(QtWidgets.QTableWidgetItem):
    """单元格"""

    #----------------------------------------------------------------------
    def __init__(self, text=None, background=None, foreground=None, data=None):
        """Constructor"""
        super(OmCell, self).__init__()
        
        self.data = data
        self.background = None
        
        if text:
            self.setText(text)
            
        if foreground:
            self.setForeground(foreground)
            
        if background:
            self.setBackground(background)
            self.background = background
        
        self.setTextAlignment(QtCore.Qt.AlignCenter)
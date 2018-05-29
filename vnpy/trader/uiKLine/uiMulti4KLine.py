# -*- coding: utf-8 -*-
"""
多周期显示K线，
时间点同步
华富资产/李来佳
"""

import sys
import os
import ctypes
import platform
system = platform.system()

# 将repostory的目录，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..' , '..'))
sys.path.append(ROOT_PATH)


from vnpy.trader.uiKLine.uiCrosshair import Crosshair
from vnpy.trader.uiKLine.uiKLine import  *


class GridKline(QtWidgets.QWidget):

    def __init__(self, parent=None):
        self.parent = parent
        super(GridKline, self).__init__(parent)

        self.periods = ['m30', 'h1', 'h2', 'd']
        self.kline_dict = {}

        self.initUI()

    def initUI(self):
        gridLayout = QtWidgets.QGridLayout()

        for period_name in self.periods:
            canvas = KLineWidget(display_vol=False, display_sub=True)
            canvas.show()
            canvas.KLtitle.setText('{}'.format(period_name), size='18pt')
            canvas.title = '{}'.format(period_name)
            canvas.add_indicator(indicator='ma5', is_main=True)
            canvas.add_indicator(indicator='ma10', is_main=True)
            canvas.add_indicator(indicator='ma18', is_main=True)
            canvas.add_indicator(indicator='sk', is_main=False)
            canvas.add_indicator(indicator='sd', is_main=False)
            self.kline_dict[period_name] = canvas
            # 注册重定向事件
            canvas.relocate_notify_func = self.onRelocate

        gridLayout.addWidget(self.kline_dict['m30'], 0, 1)
        gridLayout.addWidget(self.kline_dict['h1'], 0, 2)
        gridLayout.addWidget(self.kline_dict['h2'], 1, 1)
        gridLayout.addWidget(self.kline_dict['d'], 1, 2)

        self.setLayout(gridLayout)

        self.show()

        self.load_multi_kline()

    # ----------------------------------------------------------------------
    def load_multi_kline(self):
        """加载多周期窗口"""

        try:
            for period_name in self.periods:
                canvas = self.kline_dict.get(period_name,None)
                if canvas is not None:
                    df = pd.read_csv('I99_{}.csv'.format(period_name))
                    df = df.set_index(pd.DatetimeIndex(df['datetime']))
                    canvas.loadData(df, main_indicators=['ma5', 'ma10', 'ma18'], sub_indicators=['sk', 'sd'])

            # 载入 回测引擎生成的成交记录
            trade_list_file = 'TradeList.csv'
            if os.path.exists(trade_list_file):
                df_trade = pd.read_csv(trade_list_file)
                self.kline_dict['h1'].add_signals(df_trade)

            # 载入策略生成的交易事务过程
            tns_file = 'tns.csv'
            if os.path.exists(tns_file):
                df_tns = pd.read_csv(tns_file)
                self.kline_dict['h2'].add_trans_df(df_tns)
                self.kline_dict['d'].add_trans_df(df_tns)


        except Exception as ex:
            traceback.print_exc()
            QtWidgets.QMessageBox.warning(self, 'Exception', u'Load data Exception',
                                          QtWidgets.QMessageBox.Cancel,
                                          QtWidgets.QMessageBox.NoButton)

            return

    def onRelocate(self,window_id, t_value, count_k):
        """
        重定位所有周期的时间
        :param window_id:
        :param t_value:
        :return:
        """
        for period_name in self.periods:
            try:
                canvas = self.kline_dict.get(period_name, None)
                if canvas is not None:
                    canvas.relocate(window_id,t_value, count_k)
            except Exception as ex:
                traceback.print_exc()
########################################################################
# 功能测试
########################################################################

from vnpy.trader.uiQt import createQApp
from vnpy.trader.vtFunction import loadIconPath


def  display_multi_grid():

    qApp = createQApp()
    qApp.setWindowIcon(QtGui.QIcon(loadIconPath('dashboard.ico')))
    w = GridKline()
    w.showMaximized()
    sys.exit(qApp.exec_())

if __name__ == '__main__':

#
    ## 界面设置
    #cfgfile = QtCore.QFile('css.qss')
    #cfgfile.open(QtCore.QFile.ReadOnly)
    #styleSheet = cfgfile.readAll()
    #styleSheet = str(styleSheet)
    #qApp.setStyleSheet(styleSheet)
#
    # K线界面
    try:
        #ui = KLineWidget(display_vol=False,display_sub=True)
        #ui.show()
        #ui.KLtitle.setText('btc(H2)',size='20pt')
        #ui.add_indicator(indicator='ma5', is_main=True)
        #ui.add_indicator(indicator='ma10', is_main=True)
        #ui.add_indicator(indicator='ma18', is_main=True)
        #ui.add_indicator(indicator='sk',is_main=False)
        #ui.add_indicator(indicator='sd', is_main=False)
        #ui.loadData(pd.DataFrame.from_csv('data/btc_h2.csv'), main_indicators=['ma5','ma10','ma18'], sub_indicators=['sk','sd'])

        #ui = MultiKline(parent=app)
        #ui.show()

        #app.exec_()
    #

        display_multi_grid()

    except Exception as ex:
        print(u'exception:{},trace:{}'.format(str(ex), traceback.format_exc()))

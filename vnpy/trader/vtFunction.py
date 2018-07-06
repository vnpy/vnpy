# encoding: UTF-8

"""
包含一些开发中常用的函数
"""

import os,sys
import decimal
import json
from datetime import datetime
import importlib

MAX_NUMBER = 10000000000000
MAX_DECIMAL = 8


def floatToStr(float_str):
    """格式化显示浮点字符串，去除后面的0"""
    if '.' in float_str:
        llen = len(float_str)
        if llen > 0:
            for i in range(llen):
                vv = llen - i - 1
                if float_str[vv] not in ['.', '0']:
                    return float_str[:vv + 1]
                elif float_str[vv] in ['.']:
                    return float_str[:vv]
        return float_str
    else:
        return float_str

# -----------------------------------------
def systemSymbolToVnSymbol(symbol):
    """
    数字交易所合约symbol转化vnpy合约symbol
	ethusdt --> eth_usdt
	etcbtc  --> etc_btc
	ethusdt.HUOBI --> eth_usdt
	etcbtc.HUOBI  --> etc_btc
	ETHUSDT--> eth_usdt
    :param symbol:
    :return:
    """
    symbol = symbol.replace('_', '')
    symbol = ((symbol.split('.'))[0]).lower()
    if 'usdt' in symbol:
        return symbol[:-4] + "_usdt"
    else:
        return symbol[:-3] + "_" + symbol[-3:]

# -------------------------------------
def VnSymbolToSystemSymbol(symbol):
    """
    vnpy合约转化至数字交易所合约
    etc_btc  --> etcbtc
	eth_usdt --> ethusdt
	btc_usdt.OKEX => btcusdt
    :param symbol:
    :return:
    """
    symbol = (symbol.split('.'))[0]
    return (''.join(symbol.split('_'))).lower()


# ----------------------------------------------------------------------
def safeUnicode(value):
    """检查接口数据潜在的错误，保证转化为的字符串正确"""
    # 检查是数字接近0时会出现的浮点数上限
    if type(value) is int or type(value) is float:
        if value > MAX_NUMBER:
            value = 0
    
    # 检查防止小数点位过多
    if type(value) is float:
        d = decimal.Decimal(str(value))
        if abs(d.as_tuple().exponent) > MAX_DECIMAL:
            value = round(float(value), ndigits=MAX_DECIMAL)

    return value

#----------------------------------------------------------------------
def loadMongoSetting():
    """载入MongoDB数据库的配置"""

    try:
        from vnpy.trader.vtGlobal import globalSetting
        host = globalSetting['mongoHost']
        port = globalSetting['mongoPort']
        logging = globalSetting['mongoLogging']
    except:
        host = 'localhost'
        port = 27017
        logging = False
        
    return host, port, logging

#----------------------------------------------------------------------
def todayDate():
    """获取当前本机电脑时间的日期"""
    return datetime.now().replace(hour=0, minute=0, second=0, microsecond=0)

# 图标路径
iconPathDict = {}

path = os.path.abspath(os.path.join(os.path.dirname(__file__),'ico'))

for root, subdirs, files in os.walk(path):
    for fileName in files:
        if '.ico' in fileName:
            iconPathDict[fileName] = os.path.join(root, fileName)

# ----------------------------------------------------------------------
def loadIconPath(iconName):
    """加载程序图标路径"""
    global iconPathDict
    return iconPathDict.get(iconName, '')

# ----------------------------------------------------------------------
def getTempPath(name):
    """获取存放临时文件的路径"""
    tempPath = os.path.join(os.getcwd(), 'temp')
    if not os.path.exists(tempPath):
        os.makedirs(tempPath)

    path = os.path.join(tempPath, name)
    return path


# JSON配置文件路径
jsonPathDict = {}

# ----------------------------------------------------------------------
def getJsonPath(name, moduleFile):
    """
    获取JSON配置文件的路径：
    1. 优先从当前工作目录查找JSON文件
    2. 若无法找到则前往模块所在目录查找
    """
    currentFolder = os.getcwd()
    currentJsonPath = os.path.join(currentFolder, name)
    if os.path.isfile(currentJsonPath):
        print(u'use work folder file:{}'.format(currentJsonPath))
        jsonPathDict[name] = currentJsonPath
        return currentJsonPath

    moduleFolder = os.path.abspath(os.path.dirname(moduleFile))
    moduleJsonPath = os.path.join(moduleFolder, '.', name)
    print(u'use module file:{}'.format(moduleJsonPath))
    jsonPathDict[name] = moduleJsonPath
    return moduleJsonPath


# ----------------------------- 扩展的功能 ---------
try:
    import openpyxl
    from openpyxl.utils.dataframe import dataframe_to_rows
    from openpyxl.drawing.image import Image
except:
    print(u'can not import openpyxl',file=sys.stderr)

def save_df_to_excel(file_name, sheet_name, df):
    """
    保存dataframe到execl
    :param file_name: 保存的excel文件名
    :param sheet_name: 保存的sheet
    :param df: dataframe
    :return: True/False
    """
    if file_name is None or sheet_name is None or df is None:
        return False

    if 'openpyxl' not in sys.modules:
        print(u'can not import openpyxl', file=sys.stderr)
        return False

    try:
        ws = None

        try:
            # 读取文件
            wb = openpyxl.load_workbook(file_name)
        except:
            # 创建一个excel workbook
            wb = openpyxl.Workbook()
            ws = wb.active
            ws.title = sheet_name
        try:
            # 定位WorkSheet
            if ws is None:
                ws = wb[sheet_name]
        except:
            # 创建一个WorkSheet
            ws = wb.create_sheet()
            ws.title = sheet_name

        rows = dataframe_to_rows(df)
        for r_idx, row in enumerate(rows, 1):
            for c_idx, value in enumerate(row, 1):
                ws.cell(row=r_idx, column=c_idx, value=value)

        # Save the workbook
        wb.save(file_name)
        wb.close()
    except Exception as ex:
        import traceback
        print(u'save_df_to_excel exception:{}'.format(str(ex)), traceback.format_exc(),file=sys.stderr)

def save_text_to_excel(file_name, sheet_name, text):
    """
    保存文本文件到excel
    :param file_name:
    :param sheet_name:
    :param text:
    :return:
    """
    if file_name is None or len(sheet_name)==0 or len(text) == 0 :
        return False

    if 'openpyxl' not in sys.modules:
        return False

    try:
        ws = None
        try:
            # 读取文件
            wb = openpyxl.load_workbook(file_name)
        except:
            # 创建一个excel workbook
            wb = openpyxl.Workbook()
            ws = wb.active
            ws.title = sheet_name
        try:
            # 定位WorkSheet
            if ws is None:
                ws = wb[sheet_name]
        except:
            # 创建一个WorkSheet
            ws = wb.create_sheet()
            ws.title = sheet_name

        # 设置宽度，自动换行方式
        ws.column_dimensions["A"].width = 120
        ws['A2'].alignment = openpyxl.styles.Alignment(wrapText=True)
        ws['A2'].value = text

        # Save the workbook
        wb.save(file_name)
        wb.close()
        return True
    except Exception as ex:
        import traceback
        print(u'save_text_to_excel exception:{}'.format(str(ex)), traceback.format_exc(),file=sys.stderr)
        return False


def save_images_to_excel(file_name, sheet_name, image_names):
    """
    # 保存图形文件到excel
    :param file_name: excel文件名
    :param sheet_name: workSheet
    :param image_names: 图像文件名列表
    :return:
    """
    if file_name is None or len(sheet_name) == 0 or len(image_names) == 0:
        return False

    if 'openpyxl' not in sys.modules:
        return False
    try:
        ws = None

        try:
            # 读取文件
            wb = openpyxl.load_workbook(file_name)
        except:
            # 创建一个excel workbook
            wb = openpyxl.Workbook()
            ws = wb.active
            ws.title = sheet_name
        try:
            # 定位WorkSheet
            if ws is None:
                ws = wb[sheet_name]
        except:
            # 创建一个WorkSheet
            ws = wb.create_sheet()
            ws.title = sheet_name

        i = 1

        for image_name in image_names:
            try:
                # 加载图形文件
                img1 = Image(image_name)

                cell_id = 'A{0}'.format(i)
                ws[cell_id].value = image_name
                cell_id = 'A{0}'.format(i + 1)

                i += 30

                # 添加至对应的WorkSheet中
                ws.add_image(img1, cell_id)
            except:
                print('exception loading image {0}'.format(image_name), file=sys.stderr)
                return False

        # Save the workbook
        wb.save(file_name)
        wb.close()
        return True
    except Exception as ex:
        import traceback
        print(u'save_images_to_excel exception:{}'.format(str(ex)), traceback.format_exc(),file=sys.stderr)
        return False
# encoding: UTF-8

print 'laoding vntrader.vtConstant'

# 默认空值
EMPTY_STRING = ''
EMPTY_UNICODE = u''
EMPTY_INT = 0
EMPTY_FLOAT = 0.0

# k线颜色
COLOR_RED = u'Red'      # 上升K线
COLOR_BLUE = u'Blue'    # 下降K线
COLOR_EQUAL = u'Equal'  # 平K线


from language import constant

# 将常量定义添加到vtConstant.py的局部字典中
d = locals()
for name in dir(constant):
    if '__' not in name:
        d[name] = constant.__getattribute__(name)

print 'finished load vntrader.vtConstant'
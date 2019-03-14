import talib._ta_lib as _ta_lib
from ._ta_lib import __TA_FUNCTION_NAMES__


for func_name in __TA_FUNCTION_NAMES__:
    globals()[func_name] = getattr(_ta_lib, "stream_%s" % func_name)

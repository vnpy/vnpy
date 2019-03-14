import talib._ta_lib as _ta_lib
from ._ta_lib import Function as _Function, __TA_FUNCTION_NAMES__, _get_defaults_and_docs

# add some backwards compat for backtrader
from ._ta_lib import TA_FUNC_FLAGS, TA_INPUT_FLAGS, TA_OUTPUT_FLAGS

_func_obj_mapping = {
    func_name: getattr(_ta_lib, func_name)
    for func_name in __TA_FUNCTION_NAMES__
}


def Function(function_name, *args, **kwargs):
    func_name = function_name.upper()
    if func_name not in _func_obj_mapping:
        raise Exception('%s not supported by TA-LIB.' % func_name)

    return _Function(
        func_name, _func_obj_mapping[func_name], *args, **kwargs
    )


for func_name in __TA_FUNCTION_NAMES__:
    globals()[func_name] = Function(func_name)


__all__ = ["Function", "_get_defaults_and_docs"] + __TA_FUNCTION_NAMES__

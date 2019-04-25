# noinspection PyUnresolvedReferences
import typing
if typing.TYPE_CHECKING:
    from typing import *
    # noinspection PyUnresolvedReferences
    from enum import Enum
    from .vnxtp import *


def set_async_callback_exception_handler(handler: Callable[[Exception, object, str], bool]):
    """
    set a customize exception handler for async callback in this module(pyd)
    \a handler should return True if it handles that exception,
    If the return value of \a handler is not True, exception will be re-thrown.
    """
    ...


class AsyncDispatchException:
    what: str
    instance: object
    function_name: str


from . import vnxtp_XTP_API as API


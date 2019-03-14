"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""


"""
This module has tools for implementing the IB low level messaging.
"""


import struct
import logging

from ibapi.common import UNSET_INTEGER, UNSET_DOUBLE

logger = logging.getLogger(__name__)


def make_msg(text) -> bytes:
    """ adds the length prefix """
    msg = struct.pack("!I%ds" % len(text), len(text), str.encode(text))
    return msg


def make_field(val) -> str:
    """ adds the NULL string terminator """

    if val is None:
        raise ValueError("Cannot send None to TWS")

    # bool type is encoded as int
    if type(val) is bool:
        val = int(val)

    field = str(val) + '\0'
    return field


def make_field_handle_empty(val) -> str:

    if val is None:
        raise ValueError("Cannot send None to TWS")

    if UNSET_INTEGER == val or UNSET_DOUBLE == val:
        val = ""

    return make_field(val)


def read_msg(buf:bytes) -> tuple:
    """ first the size prefix and then the corresponding msg payload """
    if len(buf) < 4:
        return (0, "", buf)
    size = struct.unpack("!I", buf[0:4])[0]
    logger.debug("read_msg: size: %d", size)
    if len(buf) - 4 >= size:
        text = struct.unpack("!%ds" % size, buf[4:4+size])[0]
        return (size, text, buf[4+size:])
    else:
        return (size, "", buf)


def read_fields(buf:bytes) -> tuple:

    if isinstance(buf, str):
        buf = buf.encode()

    """ msg payload is made of fields terminated/separated by NULL chars """
    fields = buf.split(b"\0")

    return tuple(fields[0:-1])   #last one is empty; this may slow dow things though, TODO




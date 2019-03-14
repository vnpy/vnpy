"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""

"""
Simple class mapping a tag to a value. Both of them are strings. 
They are used in a list to convey extra info with the requests.
"""

from ibapi.object_implem import Object


class TagValue(Object):
    def __init__(self, tag:str=None, value:str=None):
        self.tag = str(tag)
        self.value = str(value)

    def __str__(self):
        # this is not only used for Python dump but when encoding to send
        # so don't change it lightly !
        return "%s=%s;" % (self.tag, self.value)

 

"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""

class Object(object):

    def __str__(self):
        return "Object"

    def __repr__(self):
        return str(id(self)) + ": " + self.__str__()

  

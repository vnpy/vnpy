"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""


""" 
    Simple enum implementation
"""


class Enum:
    def __init__(self, *args):
        self.idx2name = {}
        for (idx, name) in enumerate(args):
            setattr(self, name, idx)
            self.idx2name[idx] = name

    def to_str(self, idx):
        return self.idx2name.get(idx, "NOTFOUND")



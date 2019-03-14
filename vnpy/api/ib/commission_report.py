"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""

from ibapi.object_implem import Object 
from ibapi import utils

class CommissionReport(Object):

    def __init__(self):
        self.execId = ""
        self.commission = 0. 
        self.currency = ""
        self.realizedPNL =  0.
        self.yield_ = 0.
        self.yieldRedemptionDate = 0  # YYYYMMDD format

    def __str__(self):
        return "ExecId: %s, Commission: %f, Currency: %s, RealizedPnL: %s, Yield: %s, YieldRedemptionDate: %d" % (self.execId, self.commission, 
            self.currency, utils.floatToStr(self.realizedPNL), utils.floatToStr(self.yield_), self.yieldRedemptionDate)

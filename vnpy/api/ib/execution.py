"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""



from ibapi.object_implem import Object

class Execution(Object):

    def __init__(self):
        self.execId = ""
        self.time =  ""
        self.acctNumber =  ""
        self.exchange =  ""
        self.side = ""
        self.shares = 0.
        self.price = 0. 
        self.permId = 0
        self.clientId = 0
        self.orderId = 0
        self.liquidation = 0
        self.cumQty = 0.
        self.avgPrice = 0.
        self.orderRef =  ""
        self.evRule =  ""
        self.evMultiplier = 0.
        self.modelCode =  ""
        self.lastLiquidity = 0

    def __str__(self):
        return "ExecId: %s, Time: %s, Account: %s, Exchange: %s, Side: %s, Shares: %f, Price: %f, PermId: %d, " \
                "ClientId: %d, OrderId: %d, Liquidation: %d, CumQty: %f, AvgPrice: %f, OrderRef: %s, EvRule: %s, " \
                "EvMultiplier: %f, ModelCode: %s, LastLiquidity: %d" % (self.execId, self.time, self.acctNumber, 
                self.exchange, self.side, self.shares, self.price, self.permId, self.clientId, self.orderId, self.liquidation,
                self.cumQty, self.avgPrice, self.orderRef, self.evRule, self.evMultiplier, self.modelCode, self.lastLiquidity)

class ExecutionFilter(Object):

    # Filter fields
    def __init__(self):
        self.clientId = 0
        self.acctCode = ""
        self.time = ""
        self.symbol = ""
        self.secType = ""
        self.exchange = "" 
        self.side = ""


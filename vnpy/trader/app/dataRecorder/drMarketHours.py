'''
market hours
'''

import json
from datetime import datetime, timedelta, time
from vnpy.trader.vtFunction import getJsonPath

class MarketOpenings(object):
    """ records market operating time """

    def __init__(self, marketName, marketTimes):
        """ Constructor
        marketName is a string,
        marketTimes is a dict in the following format:
        {
            "SymbolsIncluded": ["P1901", "y1901"],  
            "MORNING_START": "09:00:00",
            "MORNING_BREAK": "10:15:00",
            "MORNING_RESTART": "10:30:00",
            "MORNING_END": "11:30:00",
            "AFTERNOON_START": "13:30:00",
            "AFTERNOON_END": "15:00:00",
            "NIGHT_START": "21:00:00",
            "NIGHT_END": "02:30:00"
        }
        you may add as many symbols as you want, after 'SymbolsIncluded',
        it's better to define market hours based on symbols due to the different policies of exchanges,
        if you add symbols, the symbols must be the same as defined by the exchange,
        if you add symbols, you may define the exchange name arbitrarily,
        the system checks by the symbols first, and if not found, it checks by the exchange names,
        you may define or leave out any of these time points, if that makes sense,
        but you must define 'MORNING_START' for non-24-hour sessions,
        if you leave out 'MORNING_START', then the system assumes it being a 24-hour session,
        the order of these time points can be arbitrary,
        the format of the time points must be 'HH:MM:SS',
        'NIGHT_END' does not equal the end of a day bar, which is defined elsewhere,
        """

        self.market = marketName
        self.sessions = []

        self.morningStart = None
        self.morningBreak = None
        self.morningRestart = None
        self.morningEnd = None
        self.aftStart = None
        self.aftEnd = None
        self.nightStart = None
        self.nightEnd = None

        session = [0, 0]
        id = 0
        if marketTimes.has_key("MORNING_START"):
            self.morningStart = datetime.strptime(marketTimes["MORNING_START"], '%H:%M:%S').time()
            session[id] = self.morningStart
            id = 1
        else:
            session[0] = time(0, 0)
            session[1] = time(0, 0)
            self.sessions.append(session)            
            return

        if marketTimes.has_key("MORNING_BREAK"):
            self.morningBreak = datetime.strptime(marketTimes["MORNING_BREAK"], '%H:%M:%S').time()
            session[id] = self.morningBreak
            self.sessions.append(session[id])
            id = 0

        if marketTimes.has_key("MORNING_RESTART") and id == 0:
            self.morningRestart = datetime.strptime(marketTimes["MORNING_RESTART"], '%H:%M:%S').time()
            session[id] = self.morningRestart
            id = 1

        if marketTimes.has_key("MORNING_END") and id == 1:
            self.morningEnd = datetime.strptime(marketTimes["MORNING_END"], '%H:%M:%S').time()
            session[id] = self.morningEnd
            self.sessions.append(session[id])
            id = 0

        if marketTimes.has_key("AFTERNOON_START") and id == 0:
            self.aftStart = datetime.strptime(marketTimes["AFTERNOON_START"], '%H:%M:%S').time()
            session[id] = self.aftStart
            id = 1

        if marketTimes.has_key("AFTERNOON_END") and id == 1:
            self.aftEnd = datetime.strptime(marketTimes["AFTERNOON_END"], '%H:%M:%S').time()
            session[id] = self.aftEnd
            self.sessions.append(session[id])
            id = 0

        if marketTimes.has_key("NIGHT_START") and id == 0:
            self.nightStart = datetime.strptime(marketTimes["NIGHT_START"], '%H:%M:%S').time()
            session[id] = self.nightStart
            id = 1

        if marketTimes.has_key("NIGHT_END") and id == 0:
            self.nightEnd = datetime.strptime(marketTimes["NIGHT_END"], '%H:%M:%S').time()
            session[id] = self.nightEnd
            self.sessions.append(session[id])


    def isMarketOpen(self, curTime):
        """ checks if market is open """
        for session in self.sessions :
            if session[0] == session[1] :
                return True
            elif session[0] < session[1] :
                if session[0] <= curTime < session[1] :
                    return True
            else:
                if session[0] <= curTime or curTime < session[1] :
                    return True
        False                        


class MarketsOpHours(object):
    """ records market hours that is defined in file 'MarketHours.json' """

    settingFileName = 'MarketHours.json'
    settingFilePath = getJsonPath(settingFileName, __file__)  

    def __init__(self):
        """Constructor"""
        self.markettimes = {}
        self.loadSetting()
        

    def loadSetting(self):
        """ load market operating times from file """
        with open(self.settingFilePath) as f:
            markets = json.load(f)
            for ex in markets:
                mts = MarketOpenings(ex, markets[ex])
                self.markettimes[ex] = mts
                if markets[ex].has_key("SymbolsIncluded") :
                    for symbol in markets[ex]["SymbolsIncluded"] :
                        self.markettimes[symbol] = mts
                        

    def isMarketOpen(self, es, curTime) :
        """ 
        checks if market is open at 'curTime'
        'es' can be an exchange name or a symbol of a financial product
        """
        self.markettimes.has_key(es) and self.markettimes[es].isMarketOpen(curTime)
        
        
    def isMarketOpen(self, symbol, exchange, curTime) :
        """ 
        checks if market is open at 'curTime'
        """
        if self.markettimes.has_key(symbol) :
            if self.markettimes[symbol].isMarketOpen(curTime) ;
                return True
            else :
                return False
        else :
            if self.markettimes[exchange].isMarketOpen(curTime) : 
                return True

        False

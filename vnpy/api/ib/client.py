"""
Copyright (C) 2018 Interactive Brokers LLC. All rights reserved. This code is subject to the terms
and conditions of the IB API Non-Commercial License or the IB API Commercial License, as applicable.
"""
import time


"""
The main class to use from API user's point of view.
It takes care of almost everything:
- implementing the requests
- creating the answer decoder
- creating the connection to TWS/IBGW
The user just needs to override EWrapper methods to receive the answers.
"""

import logging
import queue
import socket

from ibapi import (decoder, reader, comm)
from ibapi.connection import Connection
from ibapi.message import OUT
from ibapi.common import * # @UnusedWildImport
from ibapi.contract import Contract
from ibapi.order import Order
from ibapi.execution import ExecutionFilter
from ibapi.scanner import ScannerSubscription
from ibapi.comm import (make_field, make_field_handle_empty)
from ibapi.utils import (current_fn_name, BadMessage)
from ibapi.errors import * #@UnusedWildImport
from ibapi.server_versions import * # @UnusedWildImport

#TODO: use pylint

logger = logging.getLogger(__name__)


class EClient(object):
    (DISCONNECTED, CONNECTING, CONNECTED, REDIRECT) = range(4)

    #TODO: support redirect !!

    def __init__(self, wrapper):
        self.msg_queue = queue.Queue()
        self.wrapper = wrapper
        self.decoder = None
        self.reset()


    def reset(self):
        self.done = False
        self.nKeybIntHard = 0
        self.conn = None
        self.host = None
        self.port = None
        self.extraAuth = False
        self.clientId = None
        self.serverVersion_ = None
        self.connTime = None
        self.connState = None
        self.optCapab = ""
        self.asynchronous = False
        self.reader = None
        self.decode = None
        self.setConnState(EClient.DISCONNECTED)


    def setConnState(self, connState):
        _connState = self.connState
        self.connState = connState
        logger.debug("%s connState: %s -> %s" % (id(self), _connState,
                                                 self.connState))

    def sendMsg(self, msg):
        full_msg = comm.make_msg(msg)
        logger.info("%s %s %s", "SENDING", current_fn_name(1), full_msg)
        self.conn.sendMsg(full_msg)


    def logRequest(self, fnName, fnParams):
        if logger.isEnabledFor(logging.INFO):
            if 'self' in fnParams:
                prms = dict(fnParams)
                del prms['self']
            else:
                prms = fnParams
            logger.info("REQUEST %s %s" % (fnName, prms))


    def startApi(self):
        """  Initiates the message exchange between the client application and
        the TWS/IB Gateway. """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(),
                               NOT_CONNECTED.msg())
            return

        VERSION = 2

        msg = make_field(OUT.START_API) \
           + make_field(VERSION)    \
           + make_field(self.clientId)

        if self.serverVersion() >= MIN_SERVER_VER_OPTIONAL_CAPABILITIES:
            msg += make_field(self.optCapab)

        self.sendMsg(msg)

    def connect(self, host, port, clientId):
        """This function must be called before any other. There is no
        feedback for a successful connection, but a subsequent attempt to
        connect will return the message \"Already connected.\"

        host:str - The host name or IP address of the machine where TWS is
            running. Leave blank to connect to the local host.
        port:int - Must match the port specified in TWS on the
            Configure>API>Socket Port field.
        clientId:int - A number used to identify this client connection. All
            orders placed/modified from this client will be associated with
            this client identifier.

            Note: Each client MUST connect with a unique clientId."""


        try:
            self.host = host
            self.port = port
            self.clientId = clientId
            logger.debug("Connecting to %s:%d w/ id:%d", self.host, self.port, self.clientId)

            self.conn = Connection(self.host, self.port)

            self.conn.connect()
            self.setConnState(EClient.CONNECTING)

            #TODO: support async mode

            v100prefix = "API\0"
            v100version = "v%d..%d" % (MIN_CLIENT_VER, MAX_CLIENT_VER)
            #v100version = "v%d..%d" % (MIN_CLIENT_VER, 101)
            msg = comm.make_msg(v100version)
            logger.debug("msg %s", msg)
            msg2 = str.encode(v100prefix, 'ascii') + msg
            logger.debug("REQUEST %s", msg2)
            self.conn.sendMsg(msg2)

            self.decoder = decoder.Decoder(self.wrapper, self.serverVersion())
            fields = []

            #sometimes I get news before the server version, thus the loop
            while len(fields) != 2:
                self.decoder.interpret(fields)
                buf = self.conn.recvMsg()
                logger.debug("ANSWER %s", buf)
                if len(buf) > 0:
                    (size, msg, rest) = comm.read_msg(buf)
                    logger.debug("size:%d msg:%s rest:%s|", size, msg, rest)
                    fields = comm.read_fields(msg)
                    logger.debug("fields %s", fields)
                else:
                    fields = []

            (server_version, conn_time) = fields
            server_version = int(server_version)
            logger.debug("ANSWER Version:%d time:%s", server_version, conn_time)
            self.connTime = conn_time
            self.serverVersion_ = server_version
            self.decoder.serverVersion = self.serverVersion()

            self.setConnState(EClient.CONNECTED)

            self.reader = reader.EReader(self.conn, self.msg_queue)
            self.reader.start()   # start thread
            logger.info("sent startApi")
            self.startApi()
            self.wrapper.connectAck()
        except socket.error:
            if self.wrapper:
                self.wrapper.error(NO_VALID_ID, CONNECT_FAIL.code(), CONNECT_FAIL.msg())
            logger.info("could not connect")
            self.disconnect()
            self.done = True


    def disconnect(self):
        """Call this function to terminate the connections with TWS.
        Calling this function does not cancel orders that have already been
        sent."""

        self.setConnState(EClient.DISCONNECTED)
        if self.conn is not None:
            logger.info("disconnecting")
            self.conn.disconnect()
            self.wrapper.connectionClosed()
            self.reset()


    def isConnected(self):
        """Call this function to check if there is a connection with TWS"""

        logger.debug("%s isConn: %s" % (id(self), self.connState))
        return EClient.CONNECTED == self.connState

    def keyboardInterrupt(self):
        #intended to be overloaded
        pass

    def keyboardInterruptHard(self):
        self.nKeybIntHard += 1
        if self.nKeybIntHard > 5:
            raise SystemExit()


    def run(self):
        """This is the function that has the message loop."""
        timeStart = time.time()
        timeOut = 20

        try:
            while not self.done and (self.isConnected()
                        or not self.msg_queue.empty()):
                if time.time() - timeStart > timeOut: # stop application after timeout
                    self.keyboardInterrupt()
                    self.keyboardInterruptHard()

                try:
                    try:
                        text = self.msg_queue.get(block=True, timeout=0.2)
                        if len(text) > MAX_MSG_LEN:
                            self.wrapper.error(NO_VALID_ID, BAD_LENGTH.code(),
                                "%s:%d:%s" % (BAD_LENGTH.msg(), len(text), text))
                            self.disconnect()
                            break
                    except queue.Empty:
                        logger.debug("queue.get: empty")
                    else:
                        fields = comm.read_fields(text)
                        logger.debug("fields %s", fields)
                        self.decoder.interpret(fields)
                except (KeyboardInterrupt, SystemExit):
                    logger.info("detected KeyboardInterrupt, SystemExit")
                    self.keyboardInterrupt()
                    self.keyboardInterruptHard()
                except BadMessage:
                    logger.info("BadMessage")
                    self.conn.disconnect()

                logger.debug("conn:%d queue.sz:%d",
                             self.isConnected(),
                             self.msg_queue.qsize())
        finally:
            self.disconnect()


    def reqCurrentTime(self):
        """Asks the current system time on the server side."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(),
                               NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_CURRENT_TIME) \
           + make_field(VERSION)

        self.sendMsg(msg)


    def serverVersion(self):
        """Returns the version of the TWS instance to which the API
        application is connected."""

        return self.serverVersion_


    def setServerLogLevel(self, logLevel:int):
        """The default detail level is ERROR. For more details, see API
        Logging."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(),
                               NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.SET_SERVER_LOGLEVEL) \
            + make_field(VERSION) \
            + make_field(logLevel)

        self.sendMsg(msg)


    def twsConnectionTime(self):
        """Returns the time the API application made a connection to TWS."""

        return self.connTime





    ##########################################################################
    ################## Market Data
    ##########################################################################


    def reqMktData(self, reqId:TickerId, contract:Contract,
                    genericTickList:str, snapshot:bool, regulatorySnapshot: bool,
                    mktDataOptions:TagValueList):
        """Call this function to request market data. The market data
        will be returned by the tickPrice and tickSize events.

        reqId: TickerId - The ticker id. Must be a unique value. When the
            market data returns, it will be identified by this tag. This is
            also used when canceling the market data.
        contract:Contract - This structure contains a description of the
            Contractt for which market data is being requested.
        genericTickList:str - A commma delimited list of generic tick types.
            Tick types can be found in the Generic Tick Types page.
            Prefixing w/ 'mdoff' indicates that top mkt data shouldn't tick.
            You can specify the news source by postfixing w/ ':<source>.
            Example: "mdoff,292:FLY+BRF"
        snapshot:bool - Check to return a single snapshot of Market data and
            have the market data subscription cancel. Do not enter any
            genericTicklist values if you use snapshots.
        regulatorySnapshot: bool - With the US Value Snapshot Bundle for stocks,
            regulatory snapshots are available for 0.01 USD each.
        mktDataOptions:TagValueList - For internal use only.
            Use default value XYZ. """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(),
                               NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_DELTA_NEUTRAL:
            if contract.deltaNeutralContract:
                self.wrapper.error(reqId, UPDATE_TWS.code(),
                    UPDATE_TWS.msg() + "  It does not support delta-neutral orders.")
                return

        if self.serverVersion() < MIN_SERVER_VER_REQ_MKT_DATA_CONID:
            if contract.conId > 0:
                self.wrapper.error(reqId, UPDATE_TWS.code(),
                    UPDATE_TWS.msg() + "  It does not support conId parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(),
                    UPDATE_TWS.msg() + "  It does not support tradingClass parameter in reqMktData.")
                return

        VERSION = 11

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_MKT_DATA),
            make_field(VERSION),
            make_field(reqId)]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_REQ_MKT_DATA_CONID:
            flds += [make_field(contract.conId),]

        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier), # srv v15 and above
            make_field(contract.exchange),
            make_field(contract.primaryExchange), # srv v14 and above
            make_field(contract.currency),
            make_field(contract.localSymbol) ] # srv v2 and above

        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]

        # Send combo legs for BAG requests (srv v8 and above)
        if contract.secType == "BAG":
            comboLegsCount = len(contract.comboLegs) if contract.comboLegs else 0
            flds += [make_field(comboLegsCount),]
            for comboLeg in contract.comboLegs:
                    flds += [make_field(comboLeg.conId),
                        make_field( comboLeg.ratio),
                        make_field( comboLeg.action),
                        make_field( comboLeg.exchange)]

        if self.serverVersion() >= MIN_SERVER_VER_DELTA_NEUTRAL:
            if contract.deltaNeutralContract:
                flds += [make_field(True),
                    make_field(contract.deltaNeutralContract.conId),
                    make_field(contract.deltaNeutralContract.delta),
                    make_field(contract.deltaNeutralContract.price)]
            else:
                flds += [make_field(False),]

        flds += [make_field(genericTickList), # srv v31 and above
            make_field(snapshot)] # srv v35 and above

        if self.serverVersion() >= MIN_SERVER_VER_REQ_SMART_COMPONENTS:
            flds += [make_field(regulatorySnapshot),]

        # send mktDataOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            #current doc says this part if for "internal use only" -> won't support it
            if mktDataOptions:
                raise NotImplementedError("not supported")
            mktDataOptionsStr = ""
            flds += [make_field(mktDataOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)


    def cancelMktData(self, reqId:TickerId):
        """After calling this function, market data for the specified id
        will stop flowing.

        reqId: TickerId - The ID that was specified in the call to
            reqMktData(). """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 2

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.CANCEL_MKT_DATA),
            make_field(VERSION),
            make_field(reqId)]

        msg = "".join(flds)
        self.sendMsg(msg)


    def reqMarketDataType(self, marketDataType:int):
        """The API can receive frozen market data from Trader
        Workstation. Frozen market data is the last data recorded in our system.
        During normal trading hours, the API receives real-time market data. If
        you use this function, you are telling TWS to automatically switch to
        frozen market data after the close. Then, before the opening of the next
        trading day, market data will automatically switch back to real-time
        market data.

        marketDataType:int - 1 for real-time streaming market data or 2 for
            frozen market data"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_MARKET_DATA_TYPE:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(),
                UPDATE_TWS.msg() + "  It does not support market data type requests.")
            return

        VERSION = 1

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_MARKET_DATA_TYPE),
            make_field(VERSION),
            make_field(marketDataType)]

        msg = "".join(flds)
        self.sendMsg(msg)

    def reqSmartComponents(self, reqId: int, bboExchange: str):
        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return


        if self.serverVersion() < MIN_SERVER_VER_REQ_SMART_COMPONENTS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                "  It does not support smart components request.")
            return

        msg = make_field(OUT.REQ_SMART_COMPONENTS) \
            + make_field(reqId) \
            + make_field(bboExchange)

        self.sendMsg(msg)

    def reqMarketRule(self, marketRuleId: int):
        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_MARKET_RULES:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               " It does not support market rule requests.")
            return

        msg = make_field(OUT.REQ_MARKET_RULE) \
            + make_field(marketRuleId)

        self.sendMsg(msg)

    def reqTickByTickData(self, reqId: int, contract: Contract, tickType: str,
                          numberOfTicks: int, ignoreSize: bool):
        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_TICK_BY_TICK:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               " It does not support tick-by-tick data requests.")
            return

        if self.serverVersion() < MIN_SERVER_VER_TICK_BY_TICK_IGNORE_SIZE:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               " It does not support ignoreSize and numberOfTicks parameters "
                               "in tick-by-tick data requests.")
            return

        msg = make_field(OUT.REQ_TICK_BY_TICK_DATA)\
            + make_field(reqId) \
            + make_field(contract.conId) \
            + make_field(contract.symbol) \
            + make_field(contract.secType) \
            + make_field(contract.lastTradeDateOrContractMonth) \
            + make_field(contract.strike) \
            + make_field(contract.right) \
            + make_field(contract.multiplier) \
            + make_field(contract.exchange) \
            + make_field(contract.primaryExchange) \
            + make_field(contract.currency) \
            + make_field(contract.localSymbol) \
            + make_field(contract.tradingClass) \
            + make_field(tickType)

        if self.serverVersion() >= MIN_SERVER_VER_TICK_BY_TICK_IGNORE_SIZE:
            msg += make_field(numberOfTicks) \
                + make_field(ignoreSize)

        self.sendMsg(msg)

    def cancelTickByTickData(self, reqId: int):
        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_TICK_BY_TICK:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               " It does not support tick-by-tick data requests.")
            return

        msg = make_field(OUT.CANCEL_TICK_BY_TICK_DATA) \
            + make_field(reqId)

        self.sendMsg(msg)

    ##########################################################################
    ################## Options
    ##########################################################################

    def calculateImpliedVolatility(self, reqId:TickerId, contract:Contract,
                                   optionPrice:float, underPrice:float,
                                   implVolOptions:TagValueList):
        """Call this function to calculate volatility for a supplied
        option price and underlying price. Result will be delivered
        via EWrapper.tickOptionComputation()

        reqId:TickerId -  The request id.
        contract:Contract -  Describes the contract.
        optionPrice:double - The price of the option.
        underPrice:double - Price of the underlying."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_CALC_IMPLIED_VOLAT:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support calculateImpliedVolatility req.")
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support tradingClass parameter in calculateImpliedVolatility.")
                return

        VERSION = 3

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_CALC_IMPLIED_VOLAT),
            make_field(VERSION),
            make_field(reqId),
            # send contract fields
            make_field(contract.conId),
            make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]
        flds += [ make_field( optionPrice),
            make_field( underPrice)]

        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            implVolOptStr = ""
            tagValuesCount = len(implVolOptions) if implVolOptions else 0
            if implVolOptions:
                for implVolOpt in implVolOptions:
                    implVolOptStr += str(implVolOpt)
            flds += [make_field(tagValuesCount),
                make_field(implVolOptStr)]

        msg = "".join(flds)
        self.sendMsg(msg)



    def cancelCalculateImpliedVolatility(self, reqId:TickerId):
        """Call this function to cancel a request to calculate
        volatility for a supplied option price and underlying price.

        reqId:TickerId - The request ID.  """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_CALC_IMPLIED_VOLAT:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support calculateImpliedVolatility req.")
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_CALC_IMPLIED_VOLAT) \
            + make_field(VERSION) \
            + make_field(reqId)

        self.sendMsg(msg)


    def calculateOptionPrice(self, reqId:TickerId, contract:Contract,
                             volatility:float, underPrice:float,
                             optPrcOptions:TagValueList):
        """Call this function to calculate option price and greek values
        for a supplied volatility and underlying price.

        reqId:TickerId -    The ticker ID.
        contract:Contract - Describes the contract.
        volatility:double - The volatility.
        underPrice:double - Price of the underlying."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_CALC_IMPLIED_VOLAT:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support calculateImpliedVolatility req.")
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support tradingClass parameter in calculateImpliedVolatility.")
                return

        VERSION = 3

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_CALC_OPTION_PRICE),
            make_field(VERSION),
            make_field(reqId),
            # send contract fields
            make_field(contract.conId),
            make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]
        flds += [ make_field(volatility),
            make_field(underPrice)]

        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            optPrcOptStr = ""
            tagValuesCount = len(optPrcOptions) if optPrcOptions else 0
            if optPrcOptions:
                for implVolOpt in optPrcOptions:
                    optPrcOptStr += str(implVolOpt)
            flds += [make_field(tagValuesCount),
                make_field(optPrcOptStr)]

        msg = "".join(flds)
        self.sendMsg(msg)



    def cancelCalculateOptionPrice(self, reqId:TickerId):
        """Call this function to cancel a request to calculate the option
        price and greek values for a supplied volatility and underlying price.

        reqId:TickerId - The request ID.  """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_CALC_IMPLIED_VOLAT:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support calculateImpliedVolatility req.")
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_CALC_OPTION_PRICE) \
            + make_field(VERSION) \
            + make_field(reqId)

        self.sendMsg(msg)


    def exerciseOptions(self, reqId:TickerId, contract:Contract,
                        exerciseAction:int, exerciseQuantity:int,
                        account:str, override:int):
        """reqId:TickerId - The ticker id. multipleust be a unique value.
        contract:Contract - This structure contains a description of the
            contract to be exercised
        exerciseAction:int - Specifies whether you want the option to lapse
            or be exercised.
            Values are 1 = exercise, 2 = lapse.
        exerciseQuantity:int - The quantity you want to exercise.
        account:str - destination account
        override:int - Specifies whether your setting will override the system's
            natural action. For example, if your action is "exercise" and the
            option is not in-the-money, by natural action the option would not
            exercise. If you have override set to "yes" the natural action would
             be overridden and the out-of-the money option would be exercised.
            Values are: 0 = no, 1 = yes."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support conId, multiplier, tradingClass parameter in exerciseOptions.")
                return

        VERSION = 2

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.EXERCISE_OPTIONS),
            make_field(VERSION),
            make_field(reqId)]
        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.conId),]
        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]
        flds += [make_field(exerciseAction),
            make_field(exerciseQuantity),
            make_field(account),
            make_field(override)]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Orders
    ########################################################################

    def placeOrder(self, orderId:OrderId , contract:Contract, order:Order):
        """Call this function to place an order. The order status will
        be returned by the orderStatus event.

        orderId:OrderId - The order id. You must specify a unique value. When the
            order START_APItus returns, it will be identified by this tag.
            This tag is also used when canceling the order.
        contract:Contract - This structure contains a description of the
            contract which is being traded.
        order:Order - This structure contains the details of tradedhe order.
            Note: Each client MUST connect with a unique clientId."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(orderId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_DELTA_NEUTRAL:
            if contract.deltaNeutralContract:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support delta-neutral orders.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SCALE_ORDERS2:
            if order.scaleSubsLevelSize != UNSET_INTEGER:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support Subsequent Level Size for Scale orders.")
                return

        if self.serverVersion() < MIN_SERVER_VER_ALGO_ORDERS:
            if order.algoStrategy:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support algo orders.")
                return

        if self.serverVersion() < MIN_SERVER_VER_NOT_HELD:
            if order.notHeld:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support notHeld parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SEC_ID_TYPE:
            if contract.secIdType or contract.secId:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support secIdType and secId parameters.")
                return

        if self.serverVersion() < MIN_SERVER_VER_PLACE_ORDER_CONID:
            if contract.conId and contract.conId > 0:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support conId parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SSHORTX:
            if order.exemptCode != -1:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support exemptCode parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SSHORTX:
            if contract.comboLegs:
                for comboLeg in contract.comboLegs:
                    if comboLeg.exemptCode != -1:
                        self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                            "  It does not support exemptCode parameter.")
                        return

        if self.serverVersion() < MIN_SERVER_VER_HEDGE_ORDERS:
            if order.hedgeType:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support hedge orders.")
                return

        if self.serverVersion() < MIN_SERVER_VER_OPT_OUT_SMART_ROUTING:
            if order.optOutSmartRouting:
                self.wrapper.error( orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support optOutSmartRouting parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_DELTA_NEUTRAL_CONID:
            if order.deltaNeutralConId > 0 \
                    or order.deltaNeutralSettlingFirm  \
                    or order.deltaNeutralClearingAccount  \
                    or order.deltaNeutralClearingIntent:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support deltaNeutral parameters: ConId, SettlingFirm, ClearingAccount, ClearingIntent.")
                return

        if self.serverVersion() < MIN_SERVER_VER_DELTA_NEUTRAL_OPEN_CLOSE:
            if order.deltaNeutralOpenClose \
                    or order.deltaNeutralShortSale \
                    or order.deltaNeutralShortSaleSlot > 0  \
                    or order.deltaNeutralDesignatedLocation:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support deltaNeutral parameters: OpenClose, ShortSale, ShortSaleSlot, DesignatedLocation.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SCALE_ORDERS3:
            if order.scalePriceIncrement > 0 and order.scalePriceIncrement != UNSET_DOUBLE:
                if order.scalePriceAdjustValue != UNSET_DOUBLE \
                        or order.scalePriceAdjustInterval != UNSET_INTEGER \
                        or order.scaleProfitOffset != UNSET_DOUBLE \
                        or order.scaleAutoReset  \
                        or order.scaleInitPosition != UNSET_INTEGER \
                        or order.scaleInitFillQty != UNSET_INTEGER \
                        or order.scaleRandomPercent:
                    self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                            "  It does not support Scale order parameters: PriceAdjustValue, PriceAdjustInterval, " +
                            "ProfitOffset, AutoReset, InitPosition, InitFillQty and RandomPercent")
                    return

        if self.serverVersion() < MIN_SERVER_VER_ORDER_COMBO_LEGS_PRICE and contract.secType == "BAG":
            if order.orderComboLegs:
                for orderComboLeg in order.orderComboLegs:
                    if orderComboLeg.price != UNSET_DOUBLE:
                        self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                                "  It does not support per-leg prices for order combo legs.")
                        return

        if self.serverVersion() < MIN_SERVER_VER_TRAILING_PERCENT:
            if order.trailingPercent != UNSET_DOUBLE:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support trailing percent parameter")
                return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support tradingClass parameter in placeOrder.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SCALE_TABLE:
            if order.scaleTable or order.activeStartTime or order.activeStopTime:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support scaleTable, activeStartTime and activeStopTime parameters")
                return

        if self.serverVersion() < MIN_SERVER_VER_ALGO_ID:
            if order.algoId:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support algoId parameter")
                return

        if self.serverVersion() < MIN_SERVER_VER_ORDER_SOLICITED:
            if order.solicited:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support order solicited parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_MODELS_SUPPORT:
            if order.modelCode:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support model code parameter.")
                return

        if self.serverVersion() < MIN_SERVER_VER_EXT_OPERATOR:
            if order.extOperator:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support ext operator parameter")
                return

        if self.serverVersion() < MIN_SERVER_VER_SOFT_DOLLAR_TIER:
            if order.softDollarTier.name or order.softDollarTier.val:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support soft dollar tier")
                return

        if self.serverVersion() < MIN_SERVER_VER_CASH_QTY:
            if order.cashQty:
                self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support cash quantity parameter")
                return

        if self.serverVersion() < MIN_SERVER_VER_DECISION_MAKER and (order.mifid2DecisionMaker != "" or order.mifid2DecisionAlgo != ""):
            self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support MIFID II decision maker parameters")
            return

        if self.serverVersion() < MIN_SERVER_VER_MIFID_EXECUTION and (order.mifid2ExecutionTrader != "" or order.mifid2ExecutionAlgo != ""):
            self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support MIFID II execution parameters")
            return

        if self.serverVersion() < MIN_SERVER_VER_AUTO_PRICE_FOR_HEDGE and order.dontUseAutoPriceForHedge:
            self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support dontUseAutoPriceForHedge parameter")
            return

        if self.serverVersion() < MIN_SERVER_VER_ORDER_CONTAINER and order.isOmsContainer:
            self.wrapper.error(orderId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        " It does not support oms container parameter")
            return

        VERSION = 27 if (self.serverVersion() < MIN_SERVER_VER_NOT_HELD) else 45

        # send place order msg
        flds = []
        flds += [make_field(OUT.PLACE_ORDER)]

        if self.serverVersion() < MIN_SERVER_VER_ORDER_CONTAINER:
            flds += [make_field(VERSION)]

        flds += [make_field(orderId)]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_PLACE_ORDER_CONID:
            flds.append(make_field( contract.conId))
        flds += [make_field( contract.symbol),
            make_field( contract.secType),
            make_field( contract.lastTradeDateOrContractMonth),
            make_field( contract.strike),
            make_field( contract.right),
            make_field( contract.multiplier), # srv v15 and above
            make_field( contract.exchange),
            make_field( contract.primaryExchange), # srv v14 and above
            make_field( contract.currency),
            make_field( contract.localSymbol)] # srv v2 and above
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds.append(make_field( contract.tradingClass))

        if self.serverVersion() >= MIN_SERVER_VER_SEC_ID_TYPE:
            flds += [make_field( contract.secIdType),
                make_field( contract.secId)]

        # send main order fields
        flds.append(make_field( order.action))

        if self.serverVersion() >= MIN_SERVER_VER_FRACTIONAL_POSITIONS:
            flds.append(make_field(order.totalQuantity))
        else:
            flds.append(make_field(int(order.totalQuantity)))

        flds.append(make_field(order.orderType))
        if self.serverVersion() < MIN_SERVER_VER_ORDER_COMBO_LEGS_PRICE:
            flds.append(make_field(
                order.lmtPrice if order.lmtPrice != UNSET_DOUBLE else 0))
        else:
            flds.append(make_field_handle_empty( order.lmtPrice))
        if self.serverVersion() < MIN_SERVER_VER_TRAILING_PERCENT:
            flds.append(make_field(
                order.auxPrice if order.auxPrice != UNSET_DOUBLE else 0))
        else:
            flds.append(make_field_handle_empty( order.auxPrice))

        # send extended order fields
            flds += [make_field( order.tif),
            make_field( order.ocaGroup),
            make_field( order.account),
            make_field( order.openClose),
            make_field( order.origin),
            make_field( order.orderRef),
            make_field( order.transmit),
            make_field( order.parentId),      # srv v4 and above
            make_field( order.blockOrder),    # srv v5 and above
            make_field( order.sweepToFill),   # srv v5 and above
            make_field( order.displaySize),   # srv v5 and above
            make_field( order.triggerMethod), # srv v5 and above
            make_field( order.outsideRth),    # srv v5 and above
            make_field( order.hidden)]        # srv v7 and above

        # Send combo legs for BAG requests (srv v8 and above)
        if contract.secType == "BAG":
            comboLegsCount = len(contract.comboLegs) if contract.comboLegs else 0
            flds.append(make_field(comboLegsCount))
            if comboLegsCount > 0:
                for comboLeg in contract.comboLegs:
                    assert comboLeg
                    flds += [make_field(comboLeg.conId),
                        make_field( comboLeg.ratio),
                        make_field( comboLeg.action),
                        make_field( comboLeg.exchange),
                        make_field( comboLeg.openClose),
                        make_field( comboLeg.shortSaleSlot),      #srv v35 and above
                        make_field( comboLeg.designatedLocation)] # srv v35 and above
                    if self.serverVersion() >= MIN_SERVER_VER_SSHORTX_OLD:
                        flds.append(make_field(comboLeg.exemptCode))

        # Send order combo legs for BAG requests
        if self.serverVersion() >= MIN_SERVER_VER_ORDER_COMBO_LEGS_PRICE and contract.secType == "BAG":
            orderComboLegsCount = len(order.orderComboLegs) if order.orderComboLegs else 0
            flds.append(make_field( orderComboLegsCount))
            if orderComboLegsCount:
                for orderComboLeg in order.orderComboLegs:
                    assert orderComboLeg
                    flds.append(make_field_handle_empty( orderComboLeg.price))

        if self.serverVersion() >= MIN_SERVER_VER_SMART_COMBO_ROUTING_PARAMS and contract.secType == "BAG":
                smartComboRoutingParamsCount = len(order.smartComboRoutingParams) if order.smartComboRoutingParams else 0
                flds.append(make_field( smartComboRoutingParamsCount))
                if smartComboRoutingParamsCount > 0:
                    for tagValue in order.smartComboRoutingParams:
                        flds += [make_field(tagValue.tag),
                            make_field(tagValue.value)]

        ######################################################################
        # Send the shares allocation.
        #
        # This specifies the number of order shares allocated to each Financial
        # Advisor managed account. The format of the allocation string is as
        # follows:
        #                      <account_code1>/<number_shares1>,<account_code2>/<number_shares2>,...N
        # E.g.
        #              To allocate 20 shares of a 100 share order to account 'U101' and the
        #      residual 80 to account 'U203' enter the following share allocation string:
        #          U101/20,U203/80
        #####################################################################
        # send deprecated sharesAllocation field
        flds += [make_field( ""),            # srv v9 and above

            make_field( order.discretionaryAmt), # srv v10 and above
            make_field( order.goodAfterTime), # srv v11 and above
            make_field( order.goodTillDate), # srv v12 and above

            make_field( order.faGroup),      # srv v13 and above
            make_field( order.faMethod),     # srv v13 and above
            make_field( order.faPercentage), # srv v13 and above
            make_field( order.faProfile)]    # srv v13 and above

        if self.serverVersion() >= MIN_SERVER_VER_MODELS_SUPPORT:
            flds.append(make_field( order.modelCode))

        # institutional short saleslot data (srv v18 and above)
        flds += [make_field( order.shortSaleSlot),   # 0 for retail, 1 or 2 for institutions
            make_field( order.designatedLocation)]   # populate only when shortSaleSlot = 2.
        if self.serverVersion() >= MIN_SERVER_VER_SSHORTX_OLD:
            flds.append(make_field( order.exemptCode))

        # not needed anymore
        #bool isVolOrder = (order.orderType.CompareNoCase("VOL") == 0)

        # srv v19 and above fields
        flds.append(make_field( order.ocaType))
        #if( self.serverVersion() < 38) {
        # will never happen
        #      send( /* order.rthOnly */ false);
        #}
        flds += [make_field( order.rule80A),
            make_field( order.settlingFirm),
            make_field( order.allOrNone),
            make_field_handle_empty( order.minQty),
            make_field_handle_empty( order.percentOffset),
            make_field( order.eTradeOnly),
            make_field( order.firmQuoteOnly),
            make_field_handle_empty( order.nbboPriceCap),
            make_field( order.auctionStrategy), # AUCTION_MATCH, AUCTION_IMPROVEMENT, AUCTION_TRANSPARENT
            make_field_handle_empty( order.startingPrice),
            make_field_handle_empty( order.stockRefPrice),
            make_field_handle_empty( order.delta),
            make_field_handle_empty( order.stockRangeLower),
            make_field_handle_empty( order.stockRangeUpper),

            make_field( order.overridePercentageConstraints),    #srv v22 and above

            # Volatility orders (srv v26 and above)
            make_field_handle_empty( order.volatility),
            make_field_handle_empty( order.volatilityType),
            make_field( order.deltaNeutralOrderType),             # srv v28 and above
            make_field_handle_empty( order.deltaNeutralAuxPrice)] # srv v28 and above

        if self.serverVersion() >= MIN_SERVER_VER_DELTA_NEUTRAL_CONID and order.deltaNeutralOrderType:
            flds += [make_field( order.deltaNeutralConId),
                make_field( order.deltaNeutralSettlingFirm),
                make_field( order.deltaNeutralClearingAccount),
                make_field( order.deltaNeutralClearingIntent)]

        if self.serverVersion() >= MIN_SERVER_VER_DELTA_NEUTRAL_OPEN_CLOSE and order.deltaNeutralOrderType:
            flds += [make_field( order.deltaNeutralOpenClose),
                make_field( order.deltaNeutralShortSale),
                make_field( order.deltaNeutralShortSaleSlot),
                make_field( order.deltaNeutralDesignatedLocation)]

        flds += [make_field( order.continuousUpdate),
            make_field_handle_empty( order.referencePriceType),
            make_field_handle_empty( order.trailStopPrice)] # srv v30 and above

        if self.serverVersion() >= MIN_SERVER_VER_TRAILING_PERCENT:
            flds.append(make_field_handle_empty( order.trailingPercent))

        # SCALE orders
        if self.serverVersion() >= MIN_SERVER_VER_SCALE_ORDERS2:
            flds += [make_field_handle_empty( order.scaleInitLevelSize),
                make_field_handle_empty( order.scaleSubsLevelSize)]
        else:
                # srv v35 and above)
            flds += [make_field( ""), # for not supported scaleNumComponents
                make_field_handle_empty(order.scaleInitLevelSize)] # for scaleComponentSize

        flds.append(make_field_handle_empty( order.scalePriceIncrement))

        if self.serverVersion() >= MIN_SERVER_VER_SCALE_ORDERS3 \
            and order.scalePriceIncrement != UNSET_DOUBLE \
            and order.scalePriceIncrement > 0.0:

            flds += [make_field_handle_empty( order.scalePriceAdjustValue),
                make_field_handle_empty( order.scalePriceAdjustInterval),
                make_field_handle_empty( order.scaleProfitOffset),
                make_field( order.scaleAutoReset),
                make_field_handle_empty( order.scaleInitPosition),
                make_field_handle_empty( order.scaleInitFillQty),
                make_field( order.scaleRandomPercent)]

        if self.serverVersion() >= MIN_SERVER_VER_SCALE_TABLE:
            flds += [make_field( order.scaleTable),
                make_field( order.activeStartTime),
                make_field( order.activeStopTime)]

        # HEDGE orders
        if self.serverVersion() >= MIN_SERVER_VER_HEDGE_ORDERS:
            flds.append(make_field( order.hedgeType))
            if order.hedgeType:
                flds.append(make_field( order.hedgeParam))

        if self.serverVersion() >= MIN_SERVER_VER_OPT_OUT_SMART_ROUTING:
            flds.append(make_field( order.optOutSmartRouting))

        if self.serverVersion() >= MIN_SERVER_VER_PTA_ORDERS:
            flds += [make_field( order.clearingAccount),
                make_field( order.clearingIntent)]

        if self.serverVersion() >= MIN_SERVER_VER_NOT_HELD:
            flds.append(make_field( order.notHeld))

        if self.serverVersion() >= MIN_SERVER_VER_DELTA_NEUTRAL:
            if contract.deltaNeutralContract:
                flds += [make_field(True),
                    make_field(contract.deltaNeutralContract.conId),
                    make_field(contract.deltaNeutralContract.delta),
                    make_field(contract.deltaNeutralContract.price)]
            else:
                flds.append(make_field(False))

        if self.serverVersion() >= MIN_SERVER_VER_ALGO_ORDERS:
            flds.append(make_field( order.algoStrategy))
            if order.algoStrategy:
                algoParamsCount = len(order.algoParams) if order.algoParams else 0
                flds.append(make_field(algoParamsCount))
                if algoParamsCount > 0:
                    for algoParam in order.algoParams:
                        flds += [make_field(algoParam.tag),
                            make_field(algoParam.value)]

        if self.serverVersion() >= MIN_SERVER_VER_ALGO_ID:
            flds.append(make_field( order.algoId))

        flds.append(make_field( order.whatIf)) # srv v36 and above

        # send miscOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            miscOptionsStr = ""
            if order.orderMiscOptions:
                for tagValue in order.orderMiscOptions:
                    miscOptionsStr += str(tagValue)
            flds.append(make_field( miscOptionsStr))

        if self.serverVersion() >= MIN_SERVER_VER_ORDER_SOLICITED:
            flds.append(make_field(order.solicited))

        if self.serverVersion() >= MIN_SERVER_VER_RANDOMIZE_SIZE_AND_PRICE:
            flds += [make_field(order.randomizeSize),
                make_field(order.randomizePrice)]

        if self.serverVersion() >= MIN_SERVER_VER_PEGGED_TO_BENCHMARK:
            if order.orderType == "PEG BENCH":
                flds += [make_field(order.referenceContractId),
                    make_field(order.isPeggedChangeAmountDecrease),
                    make_field(order.peggedChangeAmount),
                    make_field(order.referenceChangeAmount),
                    make_field(order.referenceExchangeId)]

            flds.append(make_field(len(order.conditions)))

            if len(order.conditions) > 0:
                for cond in order.conditions:
                    flds.append(make_field(cond.type()))
                    flds += cond.make_fields()

                flds += [make_field(order.conditionsIgnoreRth),
                    make_field(order.conditionsCancelOrder)]

            flds += [make_field(order.adjustedOrderType),
                make_field(order.triggerPrice),
                make_field(order.lmtPriceOffset),
                make_field(order.adjustedStopPrice),
                make_field(order.adjustedStopLimitPrice),
                make_field(order.adjustedTrailingAmount),
                make_field(order.adjustableTrailingUnit)]

        if self.serverVersion() >= MIN_SERVER_VER_EXT_OPERATOR:
            flds.append(make_field( order.extOperator))

        if self.serverVersion() >= MIN_SERVER_VER_SOFT_DOLLAR_TIER:
            flds += [make_field(order.softDollarTier.name),
                make_field(order.softDollarTier.val)]

        if self.serverVersion() >= MIN_SERVER_VER_CASH_QTY:
            flds.append(make_field( order.cashQty))

        if self.serverVersion() >= MIN_SERVER_VER_DECISION_MAKER:
            flds.append(make_field( order.mifid2DecisionMaker))
            flds.append(make_field( order.mifid2DecisionAlgo))

        if self.serverVersion() >= MIN_SERVER_VER_MIFID_EXECUTION:
            flds.append(make_field( order.mifid2ExecutionTrader))
            flds.append(make_field( order.mifid2ExecutionAlgo))

        if self.serverVersion() >= MIN_SERVER_VER_AUTO_PRICE_FOR_HEDGE:
            flds.append(make_field(order.dontUseAutoPriceForHedge))

        if self.serverVersion() >= MIN_SERVER_VER_ORDER_CONTAINER:
            flds.append(make_field(order.isOmsContainer))

        if self.serverVersion() >= MIN_SERVER_VER_D_PEG_ORDERS:
            flds.append(make_field(order.discretionaryUpToLimitPrice))

        msg = "".join(flds)
        self.sendMsg(msg)


    def cancelOrder(self, orderId:OrderId):
        """Call this function to cancel an order.

        orderId:OrderId - The order ID that was specified previously in the call
            to placeOrder()"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_ORDER) \
            + make_field(VERSION) \
            + make_field(orderId)

        self.sendMsg(msg)


    def reqOpenOrders(self):
        """Call this function to request the open orders that were
        placed from this client. Each open order will be fed back through the
        openOrder() and orderStatus() functions on the EWrapper.

        Note:  The client with a clientId of 0 will also receive the TWS-owned
        open orders. These orders will be associated with the client and a new
        orderId will be generated. This association will persist over multiple
        API and TWS sessions.  """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_OPEN_ORDERS) \
            + make_field(VERSION)

        self.sendMsg(msg)


    def reqAutoOpenOrders(self, bAutoBind:bool):
        """Call this function to request that newly created TWS orders
        be implicitly associated with the client. When a new TWS order is
        created, the order will be associated with the client, and fed back
        through the openOrder() and orderStatus() functions on the EWrapper.

        Note:  This request can only be made from a client with clientId of 0.

        bAutoBind: If set to TRUE, newly created TWS orders will be implicitly
        associated with the client. If set to FALSE, no association will be
        made."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_AUTO_OPEN_ORDERS) \
            + make_field(VERSION) \
            + make_field(bAutoBind)

        self.sendMsg(msg)


    def reqAllOpenOrders(self):
        """Call this function to request the open orders placed from all
        clients and also from TWS. Each open order will be fed back through the
        openOrder() and orderStatus() functions on the EWrapper.

        Note:  No association is made between the returned orders and the
        requesting client."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_ALL_OPEN_ORDERS) \
            + make_field(VERSION)

        self.sendMsg(msg)


    def reqGlobalCancel(self):
        """Use this function to cancel all open orders globally. It
        cancels both API and TWS open orders.

        If the order was created in TWS, it also gets canceled. If the order
        was initiated in the API, it also gets canceled."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_GLOBAL_CANCEL) \
           + make_field(VERSION)

        self.sendMsg(msg)


    def reqIds(self, numIds:int):
        """Call this function to request from TWS the next valid ID that
        can be used when placing an order.  After calling this function, the
        nextValidId() event will be triggered, and the id returned is that next
        valid ID. That ID will reflect any autobinding that has occurred (which
        generates new IDs and increments the next valid ID therein).

        numIds:int - deprecated"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_IDS) \
           + make_field(VERSION)   \
           + make_field(numIds)

        self.sendMsg(msg)



    #########################################################################
    ################## Account and Portfolio
    ########################################################################

    def reqAccountUpdates(self, subscribe:bool, acctCode:str):
        """Call this function to start getting account values, portfolio,
        and last update time information via EWrapper.updateAccountValue(),
        EWrapperi.updatePortfolio() and Wrapper.updateAccountTime().

        subscribe:bool - If set to TRUE, the client will start receiving account
            and Portfoliolio updates. If set to FALSE, the client will stop
            receiving this information.
        acctCode:str -The account code for which to receive account and
            portfolio updates."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 2

        flds = []
        flds += [make_field(OUT.REQ_ACCT_DATA),
           make_field(VERSION),
           make_field(subscribe),  # TRUE = subscribe, FALSE = unsubscribe.
           make_field(acctCode)]   # srv v9 and above, the account code. This will only be used for FA clients

        msg = "".join(flds)
        self.sendMsg(msg)


    def reqAccountSummary(self, reqId:int, groupName:str, tags:str):
        """Call this method to request and keep up to date the data that appears
        on the TWS Account Window Summary tab. The data is returned by
        accountSummary().

        Note:   This request is designed for an FA managed account but can be
        used for any multi-account structure.

        reqId:int - The ID of the data request. Ensures that responses are matched
            to requests If several requests are in process.
        groupName:str - Set to All to returnrn account summary data for all
            accounts, or set to a specific Advisor Account Group name that has
            already been created in TWS Global Configuration.
        tags:str - A comma-separated list of account tags.  Available tags are:
            accountountType
            NetLiquidation,
            TotalCashValue - Total cash including futures pnl
            SettledCash - For cash accounts, this is the same as
            TotalCashValue
            AccruedCash - Net accrued interest
            BuyingPower - The maximum amount of marginable US stocks the
                account can buy
            EquityWithLoanValue - Cash + stocks + bonds + mutual funds
            PreviousDayEquityWithLoanValue,
            GrossPositionValue - The sum of the absolute value of all stock
                and equity option positions
            RegTEquity,
            RegTMargin,
            SMA - Special Memorandum Account
            InitMarginReq,
            MaintMarginReq,
            AvailableFunds,
            ExcessLiquidity,
            Cushion - Excess liquidity as a percentage of net liquidation value
            FullInitMarginReq,
            FullMaintMarginReq,
            FullAvailableFunds,
            FullExcessLiquidity,
            LookAheadNextChange - Time when look-ahead values take effect
            LookAheadInitMarginReq,
            LookAheadMaintMarginReq,
            LookAheadAvailableFunds,
            LookAheadExcessLiquidity,
            HighestSeverity - A measure of how close the account is to liquidation
            DayTradesRemaining - The Number of Open/Close trades a user
                could put on before Pattern Day Trading is detected. A value of "-1"
                means that the user can put on unlimited day trades.
            Leverage - GrossPositionValue / NetLiquidation
            $LEDGER - Single flag to relay all cash balance tags*, only in base
                currency.
            $LEDGER:CURRENCY - Single flag to relay all cash balance tags*, only in
                the specified currency.
            $LEDGER:ALL - Single flag to relay all cash balance tags* in all
            currencies."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_ACCOUNT_SUMMARY) \
           + make_field(VERSION)   \
           + make_field(reqId)     \
           + make_field(groupName) \
           + make_field(tags)

        self.sendMsg(msg)


    def cancelAccountSummary(self, reqId:int):
        """Cancels the request for Account Window Summary tab data.

        reqId:int - The ID of the data request being canceled."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_ACCOUNT_SUMMARY) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)


    def reqPositions(self):
        """Requests real-time position data for all accounts."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_POSITIONS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support positions request.")
            return

        VERSION = 1

        msg = make_field(OUT.REQ_POSITIONS) \
           + make_field(VERSION)

        self.sendMsg(msg)


    def cancelPositions(self):
        """Cancels real-time position updates."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_POSITIONS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support positions request.")
            return


        VERSION = 1

        msg = make_field(OUT.CANCEL_POSITIONS) \
           + make_field(VERSION)

        self.sendMsg(msg)


    def reqPositionsMulti(self, reqId:int, account:str, modelCode:str):
        """Requests positions for account and/or model.
        Results are delivered via EWrapper.positionMulti() and
        EWrapper.positionMultiEnd() """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_MODELS_SUPPORT:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support positions multi request.")
            return

        VERSION = 1

        msg = make_field(OUT.REQ_POSITIONS_MULTI) \
           + make_field(VERSION)   \
           + make_field(reqId)     \
           + make_field(account) \
           + make_field(modelCode)

        self.sendMsg(msg)


    def cancelPositionsMulti(self, reqId:int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_MODELS_SUPPORT:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support cancel positions multi request.")
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_POSITIONS_MULTI) \
           + make_field(VERSION)   \
           + make_field(reqId)     \

        self.sendMsg(msg)


    def reqAccountUpdatesMulti(self, reqId: int, account:str, modelCode:str,
                                ledgerAndNLV:bool):
        """Requests account updates for account and/or model."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_MODELS_SUPPORT:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support account updates multi request.")
            return

        VERSION = 1

        msg = make_field(OUT.REQ_ACCOUNT_UPDATES_MULTI) \
           + make_field(VERSION)   \
           + make_field(reqId)     \
           + make_field(account) \
           + make_field(modelCode) \
           + make_field(ledgerAndNLV)

        self.sendMsg(msg)


    def cancelAccountUpdatesMulti(self, reqId:int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_MODELS_SUPPORT:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support cancel account updates multi request.")
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_ACCOUNT_UPDATES_MULTI) \
           + make_field(VERSION)   \
           + make_field(reqId)     \

        self.sendMsg(msg)

    #########################################################################
    ################## Daily PnL
    #########################################################################


    def reqPnL(self, reqId: int, account: str, modelCode: str):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_PNL:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support PnL request.")
            return

        msg = make_field(OUT.REQ_PNL) \
            + make_field(reqId) \
            + make_field(account) \
            + make_field(modelCode)

        self.sendMsg(msg)

    def cancelPnL(self, reqId: int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_PNL:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support PnL request.")
            return

        msg = make_field(OUT.CANCEL_PNL) \
            + make_field(reqId)

        self.sendMsg(msg)

    def reqPnLSingle(self, reqId: int, account: str, modelCode: str, conid: int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_PNL:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               "  It does not support PnL request.")
            return

        msg = make_field(OUT.REQ_PNL_SINGLE) \
            + make_field(reqId) \
            + make_field(account) \
            + make_field(modelCode) \
            + make_field(conid)

        self.sendMsg(msg)

    def cancelPnLSingle(self, reqId: int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_PNL:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               "  It does not support PnL request.")
            return

        msg = make_field(OUT.CANCEL_PNL_SINGLE) \
            + make_field(reqId)

        self.sendMsg(msg)

    #########################################################################
    ################## Executions
    #########################################################################


    def reqExecutions(self, reqId:int, execFilter:ExecutionFilter):
        """When this function is called, the execution reports that meet the
        filter criteria are downloaded to the client via the execDetails()
        function. To view executions beyond the past 24 hours, open the
        Trade Log in TWS and, while the Trade Log is displayed, request
        the executions again from the API.

        reqId:int - The ID of the data request. Ensures that responses are
            matched to requests if several requests are in process.
        execFilter:ExecutionFilter - This object contains attributes that
            describe the filter criteria used to determine which execution
            reports are returned.

        NOTE: Time format must be 'yyyymmdd-hh:mm:ss' Eg: '20030702-14:55'"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 3

        # send req open orders msg
        flds = []
        flds += [make_field(OUT.REQ_EXECUTIONS),
            make_field(VERSION)]

        if self.serverVersion() >= MIN_SERVER_VER_EXECUTION_DATA_CHAIN:
            flds += [make_field( reqId),]

        # Send the execution rpt filter data (srv v9 and above)
        flds += [make_field( execFilter.clientId),
            make_field(execFilter.acctCode),
            make_field(execFilter.time),
            make_field(execFilter.symbol),
            make_field(execFilter.secType),
            make_field(execFilter.exchange),
            make_field(execFilter.side)]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Contract Details
    #########################################################################


    def reqContractDetails(self, reqId:int , contract:Contract):
        """Call this function to download all details for a particular
        underlying. The contract details will be received via the contractDetails()
        function on the EWrapper.

        reqId:int - The ID of the data request. Ensures that responses are
            make_fieldatched to requests if several requests are in process.
        contract:Contract - The summary description of the contract being looked
            up."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_SEC_ID_TYPE:
            if contract.secIdType or contract.secId:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support secIdType and secId parameters.")
                return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support tradingClass parameter in reqContractDetails.")
                return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            if contract.primaryExchange:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                        "  It does not support primaryExchange parameter in reqContractDetails.")
                return

        VERSION = 8

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_CONTRACT_DATA),
            make_field( VERSION)]

        if self.serverVersion() >= MIN_SERVER_VER_CONTRACT_DATA_CHAIN:
            flds += [make_field( reqId),]

        # send contract fields
        flds += [make_field(contract.conId), # srv v37 and above
            make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier)] # srv v15 and above

        if self.serverVersion() >= MIN_SERVER_VER_PRIMARYEXCH:
            flds += [make_field(contract.exchange),
                make_field(contract.primaryExchange)]
        elif self.serverVersion() >= MIN_SERVER_VER_LINKING:
            if (contract.primaryExchange and
                (contract.exchange == "BEST" or contract.exchange == "SMART")):
                flds += [make_field(contract.exchange + ":" + contract.primaryExchange),]
            else:
                flds += [make_field(contract.exchange),]

        flds += [make_field( contract.currency),
            make_field( contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass), ]
        flds += [make_field(contract.includeExpired),] # srv v31 and above

        if self.serverVersion() >= MIN_SERVER_VER_SEC_ID_TYPE:
            flds += [make_field( contract.secIdType),
                make_field( contract.secId)]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Market Depth
    #########################################################################

    def reqMktDepthExchanges(self):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_MKT_DEPTH_EXCHANGES:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               "  It does not support market depth exchanges request.")
            return

        msg = make_field(OUT.REQ_MKT_DEPTH_EXCHANGES)

        self.sendMsg(msg)

    def reqMktDepth(self, reqId:TickerId, contract:Contract,
                    numRows:int, isSmartDepth:bool, mktDepthOptions:TagValueList):
        """Call this function to request market depth for a specific
        contract. The market depth will be returned by the updateMktDepth() and
        updateMktDepthL2() events.

        Requests the contract's market depth (order book). Note this request must be
        direct-routed to an exchange and not smart-routed. The number of simultaneous
        market depth requests allowed in an account is calculated based on a formula
        that looks at an accounts equity, commissions, and quote booster packs.

        reqId:TickerId - The ticker id. Must be a unique value. When the market
            depth data returns, it will be identified by this tag. This is
            also used when canceling the market depth
        contract:Contact - This structure contains a description of the contract
            for which market depth data is being requested.
        numRows:int - Specifies the numRowsumber of market depth rows to display.
        isSmartDepth:bool - specifies SMART depth request
        mktDepthOptions:TagValueList - For internal use only. Use default value
            XYZ."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return


        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass or contract.conId > 0:
                self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support conId and tradingClass parameters in reqMktDepth.")
                return

        if self.serverVersion() < MIN_SERVER_VER_SMART_DEPTH and isSmartDepth:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                " It does not support SMART depth request.")
            return

        VERSION = 5

        # send req mkt depth msg
        flds = []
        flds += [make_field(OUT.REQ_MKT_DEPTH),
            make_field(VERSION),
            make_field(reqId)]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.conId),]
        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier), # srv v15 and above
            make_field(contract.exchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]

        flds += [make_field(numRows),] # srv v19 and above

        if self.serverVersion() >= MIN_SERVER_VER_SMART_DEPTH:
            flds += [make_field(isSmartDepth),]

        # send mktDepthOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            #current doc says this part if for "internal use only" -> won't support it
            if mktDepthOptions:
                raise NotImplementedError("not supported")
            mktDataOptionsStr = ""
            flds += [make_field(mktDataOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)


    def cancelMktDepth(self, reqId:TickerId, isSmartDepth:bool):
        """After calling this function, market depth data for the specified id
        will stop flowing.

        reqId:TickerId - The ID that was specified in the call to
            reqMktDepth().
        isSmartDepth:bool - specifies SMART depth request"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_SMART_DEPTH and isSmartDepth:
            self.wrapper.error( reqId, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                " It does not support SMART depth cancel.")
            return

        VERSION = 1

        # send cancel mkt depth msg
        flds = []
        flds += [make_field(OUT.CANCEL_MKT_DEPTH),
            make_field(VERSION),
            make_field(reqId)]

        if self.serverVersion() >= MIN_SERVER_VER_SMART_DEPTH:
            flds += [make_field(isSmartDepth)]

        msg = "".join(flds)

        self.sendMsg(msg)


    #########################################################################
    ################## News Bulletins
    #########################################################################

    def reqNewsBulletins(self, allMsgs:bool):
        """Call this function to start receiving news bulletins. Each bulletin
        will be returned by the updateNewsBulletin() event.

        allMsgs:bool - If set to TRUE, returns all the existing bulletins for
        the currencyent day and any new ones. If set to FALSE, will only
        return new bulletins. """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_NEWS_BULLETINS) \
            + make_field(VERSION) \
            + make_field(allMsgs)

        self.sendMsg(msg)


    def cancelNewsBulletins(self):
        """Call this function to stop receiving news bulletins."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_NEWS_BULLETINS) \
            + make_field(VERSION)

        self.sendMsg(msg)


    #########################################################################
    ################## Financial Advisors
    #########################################################################

    def reqManagedAccts(self):
        """Call this function to request the list of managed accounts. The list
        will be returned by the managedAccounts() function on the EWrapper.

        Note:  This request can only be made when connected to a FA managed account."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_MANAGED_ACCTS) \
           + make_field(VERSION)

        return self.sendMsg(msg)


    def requestFA(self, faData:FaDataType):
        """Call this function to request FA configuration information from TWS.
        The data returns in an XML string via a "receiveFA" ActiveX event.

        faData:FaDataType - Specifies the type of Financial Advisor
            configuration data beingingg requested. Valid values include:
            1 = GROUPS
            2 = PROFILE
            3 = ACCOUNT ALIASES"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_FA) \
           + make_field(VERSION) \
           + make_field(int(faData))

        return self.sendMsg(msg)


    def replaceFA(self, faData:FaDataType , cxml:str):
        """Call this function to modify FA configuration information from the
        API. Note that this can also be done manually in TWS itself.

        faData:FaDataType - Specifies the type of Financial Advisor
            configuration data beingingg requested. Valid values include:
            1 = GROUPS
            2 = PROFILE
            3 = ACCOUNT ALIASES
        cxml: str - The XML string containing the new FA configuration
            information.  """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REPLACE_FA) \
           + make_field(VERSION) \
           + make_field(int(faData)) \
           + make_field(cxml) \

        return self.sendMsg(msg)


    #########################################################################
    ################## Historical Data
    #########################################################################

    def reqHistoricalData(self, reqId:TickerId , contract:Contract, endDateTime:str,
                          durationStr:str, barSizeSetting:str, whatToShow:str,
                          useRTH:int, formatDate:int, keepUpToDate:bool, chartOptions:TagValueList):
        """Requests contracts' historical data. When requesting historical data, a
        finishing time and date is required along with a duration string. The
        resulting bars will be returned in EWrapper.historicalData()

        reqId:TickerId - The id of the request. Must be a unique value. When the
            market data returns, it whatToShowill be identified by this tag. This is also
            used when canceling the market data.
        contract:Contract - This object contains a description of the contract for which
            market data is being requested.
        endDateTime:str - Defines a query end date and time at any point during the past 6 mos.
            Valid values include any date/time within the past six months in the format:
            yyyymmdd HH:mm:ss ttt

            where "ttt" is the optional time zone.
        durationStr:str - Set the query duration up to one week, using a time unit
            of seconds, days or weeks. Valid values include any integer followed by a space
            and then S (seconds), D (days) or W (week). If no unit is specified, seconds is used.
        barSizeSetting:str - Specifies the size of the bars that will be returned (within IB/TWS listimits).
            Valid values include:
            1 sec
            5 secs
            15 secs
            30 secs
            1 min
            2 mins
            3 mins
            5 mins
            15 mins
            30 mins
            1 hour
            1 day
        whatToShow:str - Determines the nature of data beinging extracted. Valid values include:

            TRADES
            MIDPOINT
            BID
            ASK
            BID_ASK
            HISTORICAL_VOLATILITY
            OPTION_IMPLIED_VOLATILITY
        useRTH:int - Determines whether to return all data available during the requested time span,
            or only data that falls within regular trading hours. Valid values include:

            0 - all data is returned even where the market in question was outside of its
            regular trading hours.
            1 - only data within the regular trading hours is returned, even if the
            requested time span falls partially or completely outside of the RTH.
        formatDate: int - Determines the date format applied to returned bars. validd values include:

            1 - dates applying to bars returned in the format: yyyymmdd{space}{space}hh:mm:dd
            2 - dates are returned as a long integer specifying the number of seconds since
                1/1/1970 GMT.
        chartOptions:TagValueList - For internal use only. Use default value XYZ. """


        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(),
                               NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass or contract.conId > 0:
                self.wrapper.error(reqId, UPDATE_TWS.code(),
                    UPDATE_TWS.msg() + "  It does not support conId and tradingClass parameters in reqHistoricalData.")
                return

        VERSION = 6

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.REQ_HISTORICAL_DATA),]

        if self.serverVersion() < MIN_SERVER_VER_SYNT_REALTIME_BARS:
            flds += [make_field(VERSION),]

        flds += [make_field(reqId),]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.conId),]
        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field( contract.tradingClass),]
        flds += [make_field(contract.includeExpired), # srv v31 and above
            make_field(endDateTime), # srv v20 and above
            make_field(barSizeSetting), # srv v20 and above
            make_field(durationStr),
            make_field(useRTH),
            make_field(whatToShow),
            make_field(formatDate)] # srv v16 and above

        # Send combo legs for BAG requests
        if contract.secType == "BAG":
            flds += [make_field(len(contract.comboLegs)),]
            for comboLeg in contract.comboLegs:
                flds += [make_field( comboLeg.conId),
                    make_field( comboLeg.ratio),
                    make_field( comboLeg.action),
                    make_field( comboLeg.exchange)]

        if self.serverVersion() >= MIN_SERVER_VER_SYNT_REALTIME_BARS:
            flds += [make_field(keepUpToDate), ]

        # send chartOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            chartOptionsStr = ""
            if chartOptions:
                for tagValue in chartOptions:
                    chartOptionsStr += str(tagValue)
            flds += [make_field( chartOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)

    def cancelHistoricalData(self, reqId:TickerId):
        """Used if an internet disconnect has occurred or the results of a query
        are otherwise delayed and the application is no longer interested in receiving
        the data.

        reqId:TickerId - The ticker ID. Must be a unique value."""


        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_HISTORICAL_DATA) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)

    # Note that formatData parameter affects intraday bars only
    # 1-day bars always return with date in YYYYMMDD format

    def reqHeadTimeStamp(self, reqId:TickerId, contract:Contract,
                                                 whatToShow: str, useRTH: int, formatDate: int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_HEAD_TIMESTAMP:
            self.wrapper.error(reqId, UPDATE_TWS.code(),
                UPDATE_TWS.msg() + "  It does not support head time stamp requests.")
            return

        flds = []
        flds += [make_field(OUT.REQ_HEAD_TIMESTAMP),
            make_field(reqId),
            make_field(contract.conId),
            make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol),
            make_field(contract.tradingClass),
            make_field(contract.includeExpired),
            make_field(useRTH),
            make_field(whatToShow),
            make_field(formatDate) ]

        msg = "".join(flds)
        self.sendMsg(msg)

    def cancelHeadTimeStamp(self, reqId: TickerId):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_CANCEL_HEADTIMESTAMP:
            self.wrapper.error(reqId, UPDATE_TWS.code(),
                               UPDATE_TWS.msg() + "  It does not support head time stamp requests.")
            return

        flds = []
        flds += [make_field(OUT.CANCEL_HEAD_TIMESTAMP),
                 make_field(reqId) ]

        msg = "".join(flds)
        self.sendMsg(msg)

    def reqHistogramData(self, tickerId: int, contract: Contract,
                     useRTH: bool, timePeriod: str):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_HISTOGRAM:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                       "  It does not support histogram requests..")
            return

        flds = []
        flds += [make_field(OUT.REQ_HISTOGRAM_DATA),
            make_field(tickerId),
            make_field(contract.conId),
            make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol),
            make_field(contract.tradingClass),
            make_field(contract.includeExpired),
            make_field(useRTH),
            make_field(timePeriod)]

        msg = "".join(flds)
        self.sendMsg(msg)

    def cancelHistogramData(self, tickerId: int):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_HISTOGRAM:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                            "  It does not support histogram requests..")
            return

        msg = make_field(OUT.CANCEL_HISTOGRAM_DATA) + make_field(tickerId)

        self.sendMsg(msg)

    def reqHistoricalTicks(self, reqId: int, contract: Contract, startDateTime: str,
                           endDateTime: str, numberOfTicks: int, whatToShow: str, useRth: int,
                           ignoreSize: bool, miscOptions: TagValueList):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_HISTORICAL_TICKS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               "  It does not support historical ticks requests..")
            return

        flds = []
        flds += [make_field(OUT.REQ_HISTORICAL_TICKS),
                 make_field(reqId),
                 make_field(contract.conId),
                 make_field(contract.symbol),
                 make_field(contract.secType),
                 make_field(contract.lastTradeDateOrContractMonth),
                 make_field(contract.strike),
                 make_field(contract.right),
                 make_field(contract.multiplier),
                 make_field(contract.exchange),
                 make_field(contract.primaryExchange),
                 make_field(contract.currency),
                 make_field(contract.localSymbol),
                 make_field(contract.tradingClass),
                 make_field(contract.includeExpired),
                 make_field(startDateTime),
                 make_field(endDateTime),
                 make_field(numberOfTicks),
                 make_field(whatToShow),
                 make_field(useRth),
                 make_field(ignoreSize)]

        miscOptionsString = ""
        if miscOptions:
            for tagValue in miscOptions:
                miscOptionsString += str(tagValue)
        flds += [make_field(miscOptionsString),]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Market Scanners
    #########################################################################


    def reqScannerParameters(self):
        """Requests an XML string that describes all possible scanner queries."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.REQ_SCANNER_PARAMETERS) \
           + make_field(VERSION)

        self.sendMsg(msg)



    def reqScannerSubscription(self, reqId:int,
                               subscription:ScannerSubscription,
                               scannerSubscriptionOptions:TagValueList,
                               scannerSubscriptionFilterOptions:TagValueList):
        """reqId:int - The ticker ID. Must be a unique value.
        scannerSubscription:ScannerSubscription - This structure contains
            possible parameters used to filter results.
        scannerSubscriptionOptions:TagValueList - For internal use only.
            Use default value XYZ."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_SCANNER_GENERIC_OPTS and scannerSubscriptionFilterOptions is not None:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                               " It does not support API scanner subscription generic filter options")
            return

        VERSION = 4

        flds = []
        flds += [make_field(OUT.REQ_SCANNER_SUBSCRIPTION)]

        if self.serverVersion() < MIN_SERVER_VER_SCANNER_GENERIC_OPTS:
            flds += [make_field(VERSION)]

        flds +=[make_field(reqId),
            make_field_handle_empty(subscription.numberOfRows),
            make_field(subscription.instrument),
            make_field(subscription.locationCode),
            make_field(subscription.scanCode),
            make_field_handle_empty(subscription.abovePrice),
            make_field_handle_empty(subscription.belowPrice),
            make_field_handle_empty(subscription.aboveVolume),
            make_field_handle_empty(subscription.marketCapAbove),
            make_field_handle_empty(subscription.marketCapBelow),
            make_field(subscription.moodyRatingAbove),
            make_field(subscription.moodyRatingBelow),
            make_field(subscription.spRatingAbove),
            make_field(subscription.spRatingBelow),
            make_field(subscription.maturityDateAbove),
            make_field(subscription.maturityDateBelow),
            make_field_handle_empty(subscription.couponRateAbove),
            make_field_handle_empty(subscription.couponRateBelow),
            make_field(subscription.excludeConvertible),
            make_field_handle_empty(subscription.averageOptionVolumeAbove), # srv v25 and above
            make_field(subscription.scannerSettingPairs), # srv v25 and above
            make_field(subscription.stockTypeFilter)] # srv v27 and above

        # send scannerSubscriptionFilterOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_SCANNER_GENERIC_OPTS:
            scannerSubscriptionFilterOptionsStr = ""
            if scannerSubscriptionFilterOptions:
                for tagValueOpt in scannerSubscriptionFilterOptions:
                    scannerSubscriptionFilterOptionsStr += str(tagValueOpt)
            flds += [make_field(scannerSubscriptionFilterOptionsStr)]

        # send scannerSubscriptionOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            scannerSubscriptionOptionsStr = ""
            if scannerSubscriptionOptions:
                for tagValueOpt in scannerSubscriptionOptions:
                    scannerSubscriptionOptionsStr += str(tagValueOpt)
            flds += [make_field(scannerSubscriptionOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)



    def cancelScannerSubscription(self, reqId:int):
        """reqId:int - The ticker ID. Must be a unique value."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_SCANNER_SUBSCRIPTION) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)


    #########################################################################
    ################## Real Time Bars
    #########################################################################


    def reqRealTimeBars(self, reqId:TickerId, contract:Contract, barSize:int,
                        whatToShow:str, useRTH:bool,
                        realTimeBarsOptions:TagValueList):
        """Call the reqRealTimeBars() function to start receiving real time bar
        results through the realtimeBar() EWrapper function.

        reqId:TickerId - The Id for the request. Must be a unique value. When the
            data is received, it will be identified by this Id. This is also
            used when canceling the request.
        contract:Contract - This object contains a description of the contract
            for which real time bars are being requested
        barSize:int - Currently only 5 second bars are supported, if any other
            value is used, an exception will be thrown.
        whatToShow:str - Determines the nature of the data extracted. Valid
            values include:
            TRADES
            BID
            ASK
            MIDPOINT
        useRTH:bool - Regular Trading Hours only. Valid values include:
            0 = all data available during the time span requested is returned,
                including time intervals when the market in question was
                outside of regular trading hours.
            1 = only data within the regular trading hours for the product
                requested is returned, even if the time time span falls
                partially or completely outside.
        realTimeBarOptions:TagValueList - For internal use only. Use default value XYZ."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            if contract.tradingClass:
                self.wrapper.error( reqId, UPDATE_TWS.code(),
                    UPDATE_TWS.msg() + "  It does not support conId and tradingClass parameter in reqRealTimeBars.")
                return

        VERSION = 3

        flds = []
        flds += [make_field(OUT.REQ_REAL_TIME_BARS),
            make_field(VERSION),
            make_field(reqId)]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.conId),]
        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.lastTradeDateOrContractMonth),
            make_field(contract.strike),
            make_field(contract.right),
            make_field(contract.multiplier),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol)]
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field(contract.tradingClass),]
        flds += [make_field(barSize),
            make_field(whatToShow),
            make_field(useRTH)]

        # send realTimeBarsOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            realTimeBarsOptionsStr = ""
            if realTimeBarsOptions:
                for tagValueOpt in realTimeBarsOptions:
                    realTimeBarsOptionsStr += str(tagValueOpt)
            flds += [make_field(realTimeBarsOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)


    def cancelRealTimeBars(self, reqId:TickerId):
        """Call the cancelRealTimeBars() function to stop receiving real time bar results.

        reqId:TickerId - The Id that was specified in the call to reqRealTimeBars(). """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(reqId, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 1

        # send req mkt data msg
        flds = []
        flds += [make_field(OUT.CANCEL_REAL_TIME_BARS),
            make_field(VERSION),
            make_field(reqId)]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Fundamental Data
    #########################################################################


    def reqFundamentalData(self, reqId:TickerId , contract:Contract,
                           reportType:str, fundamentalDataOptions:TagValueList):
        """Call this function to receive fundamental data for
        stocks. The appropriate market data subscription must be set up in
        Account Management before you can receive this data.
        Fundamental data will be returned at EWrapper.fundamentalData().

        reqFundamentalData() can handle conid specified in the Contract object,
        but not tradingClass or multiplier. This is because reqFundamentalData()
        is used only for stocks and stocks do not have a multiplier and
        trading class.

        reqId:tickerId - The ID of the data request. Ensures that responses are
             matched to requests if several requests are in process.
        contract:Contract - This structure contains a description of the
            contract for which fundamental data is being requested.
        reportType:str - One of the following XML reports:
            ReportSnapshot (company overview)
            ReportsFinSummary (financial summary)
            ReportRatios (financial ratios)
            ReportsFinStatements (financial statements)
            RESC (analyst estimates)
            CalendarReport (company calendar) """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        VERSION = 2

        if self.serverVersion() < MIN_SERVER_VER_FUNDAMENTAL_DATA:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                "  It does not support fundamental data request.")
            return

        if self.serverVersion() < MIN_SERVER_VER_TRADING_CLASS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                "  It does not support conId parameter in reqFundamentalData.")
            return

        flds = []
        flds += [make_field(OUT.REQ_FUNDAMENTAL_DATA),
            make_field(VERSION),
            make_field(reqId)]

        # send contract fields
        if self.serverVersion() >= MIN_SERVER_VER_TRADING_CLASS:
            flds += [make_field( contract.conId),]
        flds += [make_field(contract.symbol),
            make_field(contract.secType),
            make_field(contract.exchange),
            make_field(contract.primaryExchange),
            make_field(contract.currency),
            make_field(contract.localSymbol),
            make_field(reportType)]

        if self.serverVersion() >= MIN_SERVER_VER_LINKING:
            fundDataOptStr = ""
            tagValuesCount = len(fundamentalDataOptions) if fundamentalDataOptions else 0
            if fundamentalDataOptions:
                for fundDataOption in fundamentalDataOptions:
                    fundDataOptStr += str(fundDataOption)
            flds += [make_field(tagValuesCount),
                make_field(fundDataOptStr)]

        msg = "".join(flds)
        self.sendMsg(msg)


    def cancelFundamentalData(self, reqId:TickerId ):
        """Call this function to stop receiving fundamental data.

        reqId:TickerId - The ID of the data request."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_FUNDAMENTAL_DATA:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support fundamental data request.")
            return

        VERSION = 1

        msg = make_field(OUT.CANCEL_FUNDAMENTAL_DATA) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)


    ########################################################################
    ################## News
    #########################################################################

    def reqNewsProviders(self):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return


        if self.serverVersion() < MIN_SERVER_VER_REQ_NEWS_PROVIDERS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                       "  It does not support news providers request.")
            return

        msg = make_field(OUT.REQ_NEWS_PROVIDERS)

        self.sendMsg(msg)


    def reqNewsArticle(self, reqId: int, providerCode: str, articleId: str, newsArticleOptions: TagValueList):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_NEWS_ARTICLE:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                       "  It does not support news article request.")
            return

        flds = []

        flds += [make_field(OUT.REQ_NEWS_ARTICLE),
                 make_field(reqId),
                 make_field(providerCode),
                 make_field(articleId)]

        # send newsArticleOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_NEWS_QUERY_ORIGINS:
            newsArticleOptionsStr = ""
            if newsArticleOptions:
                for tagValue in newsArticleOptions:
                    newsArticleOptionsStr += str(tagValue)
            flds += [make_field(newsArticleOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)


    def reqHistoricalNews(self, reqId: int, conId: int, providerCodes: str,
                      startDateTime: str, endDateTime: str, totalResults: int, historicalNewsOptions: TagValueList):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_HISTORICAL_NEWS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                       "  It does not support historical news request.")
            return

        flds = []

        flds += [make_field(OUT.REQ_HISTORICAL_NEWS),
                 make_field(reqId),
                 make_field(conId),
                 make_field(providerCodes),
                 make_field(startDateTime),
                 make_field(endDateTime),
                 make_field(totalResults)]

        # send historicalNewsOptions parameter
        if self.serverVersion() >= MIN_SERVER_VER_NEWS_QUERY_ORIGINS:
            historicalNewsOptionsStr = ""
            if historicalNewsOptions:
                for tagValue in historicalNewsOptionsStr:
                    historicalNewsOptionsStr += str(tagValue)
            flds += [make_field(historicalNewsOptionsStr),]

        msg = "".join(flds)
        self.sendMsg(msg)


    #########################################################################
    ################## Display Groups
    #########################################################################


    def queryDisplayGroups(self, reqId: int):
        """API requests used to integrate with TWS color-grouped windows (display groups).
        TWS color-grouped windows are identified by an integer number. Currently that number ranges from 1 to 7 and are mapped to specific colors, as indicated in TWS.

        reqId:int - The unique number that will be associated with the
            response """

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support queryDisplayGroups request.")
            return

        VERSION = 1

        msg = make_field(OUT.QUERY_DISPLAY_GROUPS) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)


    def subscribeToGroupEvents(self, reqId:int, groupId:int):
        """reqId:int - The unique number associated with the notification.
        groupId:int - The ID of the group, currently it is a number from 1 to 7.
            This is the display group subscription request sent by the API to TWS."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support subscribeToGroupEvents request.")
            return

        VERSION = 1

        msg = make_field(OUT.SUBSCRIBE_TO_GROUP_EVENTS) \
           + make_field(VERSION)   \
           + make_field(reqId) \
           + make_field(groupId)

        self.sendMsg(msg)


    def updateDisplayGroup(self, reqId:int, contractInfo:str):
        """reqId:int - The requestId specified in subscribeToGroupEvents().
        contractInfo:str - The encoded value that uniquely represents the
            contract in IB. Possible values include:

            none = empty selection
            contractID@exchange - any non-combination contract.
                Examples: 8314@SMART for IBM SMART; 8314@ARCA for IBM @ARCA.
            combo = if any combo is selected."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support updateDisplayGroup request.")
            return

        VERSION = 1

        msg = make_field(OUT.UPDATE_DISPLAY_GROUP) \
           + make_field(VERSION)   \
           + make_field(reqId) \
           + make_field(contractInfo)

        self.sendMsg(msg)


    def unsubscribeFromGroupEvents(self, reqId:int):
        """reqId:int - The requestId specified in subscribeToGroupEvents()."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support unsubscribeFromGroupEvents request.")
            return

        VERSION = 1

        msg = make_field(OUT.UNSUBSCRIBE_FROM_GROUP_EVENTS) \
           + make_field(VERSION)   \
           + make_field(reqId)

        self.sendMsg(msg)


    def verifyRequest(self, apiName:str, apiVersion:str):
        """For IB's internal purpose. Allows to provide means of verification
        between the TWS and third party programs."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support verification request.")
            return

        if not self.extraAuth:
            self.wrapper.error(NO_VALID_ID, BAD_MESSAGE.code(), BAD_MESSAGE.msg() +
                    "  Intent to authenticate needs to be expressed during initial connect request.")
            return

        VERSION = 1

        msg = make_field(OUT.VERIFY_REQUEST) \
           + make_field(VERSION)   \
           + make_field(apiName)   \
           + make_field(apiVersion)

        self.sendMsg(msg)


    def verifyMessage(self, apiData:str):
        """For IB's internal purpose. Allows to provide means of verification
        between the TWS and third party programs."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support verification request.")
            return

        VERSION = 1

        msg = make_field(OUT.VERIFY_MESSAGE) \
           + make_field(VERSION)   \
           + make_field(apiData)

        self.sendMsg(msg)


    def verifyAndAuthRequest(self, apiName:str, apiVersion:str,
                             opaqueIsvKey:str):
        """For IB's internal purpose. Allows to provide means of verification
        between the TWS and third party programs."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support verification request.")
            return

        if not self.extraAuth:
            self.wrapper.error(NO_VALID_ID, BAD_MESSAGE.code(), BAD_MESSAGE.msg() +
                    "  Intent to authenticate needs to be expressed during initial connect request.")
            return

        VERSION = 1

        msg = make_field(OUT.VERIFY_AND_AUTH_REQUEST) \
           + make_field(VERSION)   \
           + make_field(apiName)   \
           + make_field(apiVersion) \
           + make_field(opaqueIsvKey)

        self.sendMsg(msg)


    def verifyAndAuthMessage(self, apiData:str, xyzResponse:str):
        """For IB's internal purpose. Allows to provide means of verification
        between the TWS and third party programs."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_LINKING:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support verification request.")
            return

        VERSION = 1

        msg = make_field(OUT.VERIFY_AND_AUTH_MESSAGE) \
           + make_field(VERSION)   \
           + make_field(apiData)   \
           + make_field(xyzResponse)

        self.sendMsg(msg)


    def reqSecDefOptParams(self, reqId:int, underlyingSymbol:str,
                            futFopExchange:str, underlyingSecType:str,
                            underlyingConId:int):
        """Requests security definition option parameters for viewing a
        contract's option chain reqId the ID chosen for the request
        underlyingSymbol futFopExchange The exchange on which the returned
        options are trading. Can be set to the empty string "" for all
        exchanges. underlyingSecType The type of the underlying security,
        i.e. STK underlyingConId the contract ID of the underlying security.
        Response comes via EWrapper.securityDefinitionOptionParameter()"""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_SEC_DEF_OPT_PARAMS_REQ:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support security definition option request.")
            return

        flds = []
        flds += [make_field(OUT.REQ_SEC_DEF_OPT_PARAMS),
            make_field(reqId),
            make_field(underlyingSymbol),
            make_field(futFopExchange),
            make_field(underlyingSecType),
            make_field(underlyingConId)]

        msg = "".join(flds)
        self.sendMsg(msg)


    def reqSoftDollarTiers(self, reqId:int):
        """Requests pre-defined Soft Dollar Tiers. This is only supported for
        registered professional advisors and hedge and mutual funds who have
        configured Soft Dollar Tiers in Account Management."""

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        msg = make_field(OUT.REQ_SOFT_DOLLAR_TIERS) \
           + make_field(reqId)

        self.sendMsg(msg)


    def reqFamilyCodes(self):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_FAMILY_CODES:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support family codes request.")
            return

        msg = make_field(OUT.REQ_FAMILY_CODES)

        self.sendMsg(msg)


    def reqMatchingSymbols(self, reqId:int, pattern:str):

        self.logRequest(current_fn_name(), vars())

        if not self.isConnected():
            self.wrapper.error(NO_VALID_ID, NOT_CONNECTED.code(), NOT_CONNECTED.msg())
            return

        if self.serverVersion() < MIN_SERVER_VER_REQ_MATCHING_SYMBOLS:
            self.wrapper.error(NO_VALID_ID, UPDATE_TWS.code(), UPDATE_TWS.msg() +
                    "  It does not support matching symbols request.")
            return

        msg = make_field(OUT.REQ_MATCHING_SYMBOLS) \
           + make_field(reqId)   \
           + make_field(pattern)

        self.sendMsg(msg)



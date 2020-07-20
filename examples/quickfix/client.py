import sys
import time
# import thread
import argparse
from datetime import datetime
import quickfix as fix
from tools.echo import echo

ECHO_DEBUG=True
if ECHO_DEBUG:
    from tools.echo import echo
else:
    def echo(f):
        def decorated(*args, **kwargs):
            f(*args, **kwargs)
        return decorated

class Application(fix.Application):
    orderID = 0
    execID = 0
    def gen_ord_id(self):
        global orderID
        orderID+=1
        return orderID

    @echo
    def onCreate(self, sessionID):
            return
    @echo
    def onLogon(self, sessionID):
            self.sessionID = sessionID
            print ("Successful Logon to session '%s'." % sessionID.toString())
            return
    @echo
    def onLogout(self, sessionID): return
    @echo
    def toAdmin(self, sessionID, message):
        return
    @echo
    def fromAdmin(self, sessionID, message):
        return

    @echo
    def toApp(self, sessionID, message):
        print(f"Recieved the following message: {message}")
        return
    @echo
    def fromApp(self, message, sessionID):
        return
    @echo
    def genOrderID(self):
    	self.orderID = self.orderID+1
    	return self.orderID
    @echo
    def genExecID(self):
    	self.execID = self.execID+1
    	return self.execID
    def put_order(self):
        print("Creating the following order: ")
        trade = fix.Message()
        trade.getHeader().setField(fix.BeginString(fix.BeginString_FIX42)) #
        trade.getHeader().setField(fix.MsgType(fix.MsgType_NewOrderSingle)) #39=D
        trade.setField(fix.ClOrdID(self.genExecID())) #11=Unique order

        trade.setField(fix.HandlInst(fix.HandlInst_MANUAL_ORDER_BEST_EXECUTION)) #21=3 (Manual order, best executiona)
        trade.setField(fix.Symbol('SMBL')) #55=SMBL ?
        trade.setField(fix.Side(fix.Side_BUY)) #43=1 Buy
        trade.setField(fix.OrdType(fix.OrdType_LIMIT)) #40=2 Limit order
        trade.setField(fix.OrderQty(100)) #38=100
        trade.setField(fix.Price(10))
        trade.setField(fix.TransactTime(int(datetime.utcnow().strftime("%s"))))
        print(trade.toString())
        fix.Session.sendToTarget(trade, self.sessionID)

def main(config_file):
    try:
        settings = fix.SessionSettings( config_file )
        application = Application()
        storeFactory = fix.FileStoreFactory( settings )
        logFactory = fix.FileLogFactory( settings )
        initiator = fix.SocketInitiator( application, storeFactory, settings, logFactory )
        initiator.start()

        while 1:
                input = raw_input()
                if input == '1':
                    print("Putin Order")
                    application.put_order()
                if input == '2':
                    sys.exit(0)
                if input == 'd':
                    import pdb
                    pdb.set_trace()
                else:
                    print("Valid input is 1 for order, 2 for exit")
                    continue
    except (fix.ConfigError, fix.RuntimeError):
        print(e)

if __name__=='__main__':
    parser = argparse.ArgumentParser(description='FIX Client')
    parser.add_argument('file_name', type=str, help='Name of configuration file')
    args = parser.parse_args()
    main(args.file_name)

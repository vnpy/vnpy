import sys
import datetime
import time
import quickfix as fix

from vnpy.trader.utility import get_file_path, get_folder_path


class FixClient(fix.Application):

    orderID = 0
    execID = 0

    def gen_ord_id(self):
        global orderID
        orderID += 1
        return orderID

    def onCreate(self,sessionID):
        print("1--onCreate, sessionID=", sessionID)
        return

    def onLogon(self, sessionID):
        print("3--onLogon, sessionID=", sessionID)
        self.sessionID = sessionID
        # print ("Successful Logon to session '%s'." % sessionID.toString())
        return

    def onLogout(self, sessionID):
        print("onLogout")
        return

    def toAdmin(self, message, sessionID):
        username = fix.Username("username")
        mypass = fix.Password("password")
        mycompid = fix.TargetSubID("targetsubid")
        message.setField(username)
        message.setField(mypass)
        message.setField(mycompid)

    def fromAdmin(self, message, sessionID):
        print("2-fromAdmin, message=", message, ",sessionID=", sessionID)
        TradeID = fix.TradingSessionID
        # message.getField(TradeID)
        return

    def toApp(self, sessionID, message):
        print("Sent the following message: %s" % message.toString())
        return

    def fromApp(self, message, sessionID):
        print("Received the following message: %s" % message.toString())
        return

    def genOrderID(self):
        self.orderID = self.orderID + 1
        return self.orderID

    def genExecID(self):
        self.execID = self.execID + 1
        return self.execID

    def put_order(self, sessionID, myinstrument, myquantity):
        self.myinstrument = myinstrument
        self.myquantity = myquantity
        print("Creating the following order: ")
        today = datetime.datetime.now()
        nextID = today.strftime("%m%d%Y%H%M%S%f")
        trade = fix.Message()
        trade.getHeader().setField(fix.StringField(8, "FIX.4.4"))
        trade.getHeader().setField(fix.MsgType(fix.MsgType_NewOrderSingle))
        trade.setField(fix.ClOrdID(nextID)) #11=Unique order
        trade.getHeader().setField(fix.Account("account"))
        trade.getHeader().setField(fix.TargetSubID("targetsubid"))
        trade.setField(fix.Symbol(myinstrument)) #55=SMBL ?
        trade.setField(fix.TransactTime())
        trade.setField(fix.CharField(54, fix.Side_BUY))
        trade.setField(fix.OrdType(fix.OrdType_MARKET))  # 40=2 Limit order
        trade.setField(fix.OrderQty(myquantity))  # 38=100
        print(trade.toString())
        fix.Session.sendToTarget(trade, self.sessionID)


class GenusClient:
    setting = None
    fix_client = None

    def start_client():
        settings = fix.SessionSettings("genus.cfg")
        fix_client = FixClient()
        store_factory = fix.FileStoreFactory(settings)
        log_factory = fix.ScreenLogFactory(settings)
        initiator = fix.SocketInitiator(
            fix_client, store_factory, settings, log_factory
        )
        initiator.start()


if __name__=='__main__':
    g = GenusClient()
    g.start_client()

    # try:
    #     settings = fix.SessionSettings("genus.cfg")
    #     application = Application()
    #     store_factory = fix.FileStoreFactory(settings)
    #     log_factory = fix.ScreenLogFactory(settings)
    #     initiator = fix.SocketInitiator(
    #         application, store_factory, settings, log_factory
    #     )
    #     initiator.start()

    #     while 1:
    #         time.sleep(2)

    #         if input == '1':
    #             print("Putin Order")
    #             application.put_order(fix.Application)
    #         if input == '2':
    #             sys.exit(0)
    #         if input == 'd':
    #             import pdb
    #             pdb.set_trace()
    #         else:
    #             print("输入1 -> 委托， 输入2 -> 退出")

    # except (fix.ConfigError, fix.RuntimeError) as e:
    #     print(e)
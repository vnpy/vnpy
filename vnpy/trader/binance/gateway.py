from binance.spot import Spot

from crypto_go.live_trading.core import BinanceListener
from vnpy.vnpy.event import EventEngine, Event
from vnpy.vnpy.trader.gateway import BaseGateway
from vnpy.vnpy.trader.object import Exchange, OrderRequest, OrderData


class BinanceSpotGateway(BaseGateway):
    """
    Binance Gateway for Spot Trading.
    """

    default_name = "BINANCE_SPOT"

    exchanges: Exchange = [Exchange.BINANCE]

    def __init__(self, event_engine: EventEngine, gateway_name: str = "BINANCE_SPOT",
                 gateway_setting: dict = None) -> None:
        """Constructor"""
        super().__init__(event_engine, gateway_name)

        self.default_setting.update(gateway_setting)

        self.spot_client = Spot(
            api_key=self.default_setting["api_key"],
            api_secret=self.default_setting["api_secret"]
        )
        self.listener_client = BinanceListener(listen_key="", event_engine=self.event_engine)

    async def init_gateway(self):
        self.register_event()
        await self.connect()

    def close(self):
        """"""
        self.spot_client.close_listen_key(listenKey=self.listener_client.listen_key)

    def register_event(self):
        self.event_engine.register(EVENT_LISTEN_KEY_EXPIRED, self.on_listen)
        self.event_engine.register(EVENT_TICKS_QUERY, self.query_ticks)
        self.event_engine.register(EVENT_ACCOUNT_QUERY, self.query_account)

    async def connect(self, setting: dict = None):
        """"""

        listen_key = self.spot_client.new_listen_key()['listenKey']

        self.listener_client.listen_key = listen_key
        await self.listener_client.subscribe_to_user_stream()

    def on_listen(self, event: Event):
        data = event.data
        self.spot_client.renew_listen_key(listenKey=data['listenKey'])

    def send_order(self, req: OrderRequest) -> str:
        """"""
        order_data: OrderData = req.create_order_data(gateway_name=self.gateway_name, orderid=None)

        order_params = self.convert2otoco_order(order_data)

        order_id = self.spot_client.new_otoco_order(**order_params)

        return order_id

    def convert2otoco_order(self, order_data: OrderData) -> dict:
        """"""
        workingClientOrderId = order_data.orderid
        listClientOrderId = f"otoco_{workingClientOrderId}"
        workingType = order_data.type.value
        workingSide = order_data.direction.value
        workingPrice = order_data.price
        workingQuantity = order_data.volume

        if workingSide == "BUY":
            pendingSide = "SELL"
            pendingAbovePrice = order_data.take_profit_price
            pendingBelowPrice = order_data.stop_loss_price
            pendingAboveClientOrderId = f"tp_{workingClientOrderId}"
            pendingBelowClientOrderId = f"sl_{workingClientOrderId}"
        else:
            pendingSide = "BUY"
            pendingAbovePrice = order_data.stop_loss_price
            pendingBelowPrice = order_data.take_profit_price
            pendingAboveClientOrderId = f"sl_{workingClientOrderId}"
            pendingBelowClientOrderId = f"tp_{workingClientOrderId}"

        pendingAboveType = "STOP_LOSS"
        pendingBelowType = "STOP_LOSS"
        pendingQuantity = workingQuantity

        return {
            "symbol": order_data.symbol,
            "workingClientOrderId": workingClientOrderId,
            "listClientOrderId": listClientOrderId,
            "workingType": workingType,
            "workingSide": workingSide,
            "workingPrice": workingPrice,
            "workingQuantity": workingQuantity,
            "pendingSide": pendingSide,
            "pendingAbovePrice": pendingAbovePrice,
            "pendingBelowPrice": pendingBelowPrice,
            "pendingAboveClientOrderId": pendingAboveClientOrderId,
            "pendingBelowClientOrderId": pendingBelowClientOrderId,
            "pendingAboveType": pendingAboveType,
            "pendingBelowType": pendingBelowType,
            "pendingQuantity": pendingQuantity
        }
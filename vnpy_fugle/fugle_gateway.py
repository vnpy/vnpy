"""
台湾富果 (Fugle) 行情与交易接口
"""

from datetime import datetime
from typing import List, Optional

from vnpy.event import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import TickData, SubscribeRequest, HistoryRequest, BarData
from vnpy.trader.constant import Exchange, Interval

from fugle_marketdata import RestClient 


class FugleGateway(BaseGateway):
    """
    VeighNa Gateway for Fugle Market Data API.
    """

    default_name: str = "FUGLE"
    exchanges: List[Exchange] = [Exchange.TSE, Exchange.OTC]

    default_setting: dict = {
        "API Key": ""
    }

    def __init__(self, event_engine: EventEngine, gateway_name: str = "FUGLE") -> None:
        """构造函数"""
        super().__init__(event_engine, gateway_name)
        
        self.client: Optional[RestClient] = None

    def connect(self, setting: dict) -> None:
        """连接Fugle API"""
        api_key = setting.get("API Key", "")
        if not api_key:
            self.write_log("连接失败：请输入API Key")
            return

        self.write_log("开始连接Fugle API")
        
        try:
            self.client = RestClient(api_key=api_key)
            self.write_log("Fugle API连接成功")
        except Exception as e:
            self.write_log(f"Fugle API连接异常：{str(e)}")

    def close(self) -> None:
        """关闭连接"""
        self.client = None
        self.write_log("Fugle API连接已断开")

    def subscribe(self, req: SubscribeRequest) -> None:
        """订阅行情（REST查询单次快照）"""
        if not self.client:
            self.write_log("订阅行情失败：Fugle API未连接")
            return

        symbol = req.symbol
        try:
            stock = self.client.stock
            data = stock.intraday.quote(symbol=symbol)

            tick = TickData(
                gateway_name=self.gateway_name,
                symbol=symbol,
                exchange=req.exchange,
                datetime=datetime.now(),
                name=data.get('name', symbol),
                volume=data.get('total', {}).get('tradeVolume', 0),
                last_price=data.get('closePrice', 0),
                open_price=data.get('openPrice', 0),
                high_price=data.get('highPrice', 0),
                low_price=data.get('lowPrice', 0),
                pre_close=data.get('previousClose', 0),
            )

            if 'bids' in data and data['bids']:
                tick.bid_price_1 = data['bids'][0]['price']
                tick.bid_volume_1 = data['bids'][0]['size']
            if 'asks' in data and data['asks']:
                tick.ask_price_1 = data['asks'][0]['price']
                tick.ask_volume_1 = data['asks'][0]['size']

            self.on_tick(tick)
            
        except Exception as e:
            self.write_log(f"获取{symbol}行情报错：{str(e)}")

    def query_history(self, req: HistoryRequest) -> Optional[List[BarData]]:
        
        if not self.client:
            self.write_log("查询历史数据失败：Fugle API未连接")
            return None

        history_bars: List[BarData] = []
        
        try:
            # 转换为Fugle API要求的YYYY-MM-DD格式
            start_str = req.start.strftime("%Y-%m-%d")
            end_str = req.end.strftime("%Y-%m-%d")
            timeframe = 'D' if req.interval == Interval.DAILY else '1'

            kwargs = {
                "symbol": req.symbol,
                "from": start_str,
                "to": end_str,
                "timeframe": timeframe
            }
            data = self.client.stock.historical.candles(**kwargs)

            if 'data' in data:
                for bar_data in data['data']:
                    dt = datetime.strptime(bar_data['date'], "%Y-%m-%d")
                    bar = BarData(
                        gateway_name=self.gateway_name,
                        symbol=req.symbol,
                        exchange=req.exchange,
                        datetime=dt,
                        interval=req.interval,
                        volume=bar_data.get('volume', 0),
                        open_price=bar_data.get('open', 0),
                        high_price=bar_data.get('high', 0),
                        low_price=bar_data.get('low', 0),
                        close_price=bar_data.get('close', 0)
                    )
                    history_bars.append(bar)

            # Fugle返回数据为降序，需转换为VeighNa要求的升序（时间由旧到新）
            history_bars.sort(key=lambda x: x.datetime)
            
            self.write_log(f"获取{req.symbol}历史数据成功，共{len(history_bars)}根")
            return history_bars

        except Exception as e:
            self.write_log(f"获取{req.symbol}历史数据报错：{str(e)}")
            return None

    def send_order(self, req):
        pass

    def cancel_order(self, req):
        pass

    def query_account(self):
        pass

    def query_position(self):
        pass
from typing import Dict, Set, Optional
from dataclasses import dataclass, field
import logging
from datetime import datetime

from vnpy.trader.object import OrderData, TradeData, OrderRequest
from vnpy.trader.constant import Status

logger = logging.getLogger(__name__)

@dataclass
class OrderManager:
    """Manages order tracking and updates"""
    
    strategy_name: str
    
    # Order tracking
    active_orders: Dict[str, OrderData] = field(default_factory=dict)
    orders: Dict[str, OrderData] = field(default_factory=dict)
    trades: Dict[str, TradeData] = field(default_factory=dict)
    
    # Active order IDs for quick lookup
    active_orderids: Set[str] = field(default_factory=set)
    
    # Statistics 
    order_count: int = 0
    trade_count: int = 0
    total_turnover: float = 0.0
    
    def on_order(self, order: OrderData) -> None:
        """Process order update"""
        if order.vt_orderid in self.active_orders:
            if not order.is_active():
                self.active_orders.pop(order.vt_orderid)
                self.active_orderids.remove(order.vt_orderid)
        
        self.orders[order.vt_orderid] = order
        self.order_count = len(self.orders)
        
        logger.debug(f"Order update - {order.vt_orderid} {order.status}")

    def on_trade(self, trade: TradeData) -> None:
        """Process trade update"""
        self.trades[trade.vt_tradeid] = trade
        self.trade_count = len(self.trades)
        self.total_turnover += trade.volume * trade.price
        
        logger.debug(f"Trade update - {trade.vt_tradeid} {trade.direction} {trade.volume}@{trade.price}")

    def get_order(self, vt_orderid: str) -> Optional[OrderData]:
        """Get order by ID"""
        return self.orders.get(vt_orderid)

    def add_active_order(self, vt_orderid: str, order: OrderData) -> None:
        """Track new active order"""
        self.active_orders[vt_orderid] = order
        self.active_orderids.add(vt_orderid)
        self.orders[vt_orderid] = order

    def get_all_active_orders(self) -> Dict[str, OrderData]:
        """Get all active orders"""
        return self.active_orders

    def cancel_all_active_orders(self) -> Set[str]:
        """Get all active orderids for cancellation"""
        return self.active_orderids.copy()

    def get_pos_direction(self, vt_symbol: str) -> int:
        """Calculate position direction from trades"""
        pos = 0
        for trade in self.trades.values():
            if trade.vt_symbol == vt_symbol:
                pos += (trade.volume if trade.direction == "long" else -trade.volume)
        return pos

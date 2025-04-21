from typing import List
from dataclasses import dataclass
import logging

from vnpy.trader.object import CancelRequest, OrderRequest, OrderData
from vnpy.trader.engine import MainEngine

logger = logging.getLogger(__name__)


# todo vnpy algo trading
class ExecutionAgent:
    """Handles order execution for portfolio strategies"""

    main_engine: MainEngine
    gateway_name: str

    def send_order(
            self,
            req: OrderRequest,
            lock: bool = False,
            net: bool = False
    ) -> List[str]:
        """Send order via main engine"""
        # Validate request
        if req.volume <= 0:
            logger.warning(f"Invalid order volume: {req.volume}")
            return []

        # Send order via main engine
        vt_orderids = []
        req_list = self.main_engine.convert_order_request(
            req, self.gateway_name, lock, net
        )

        for order_req in req_list:
            vt_orderid = self.main_engine.send_order(
                order_req, self.gateway_name
            )
            if vt_orderid:
                vt_orderids.append(vt_orderid)

        return vt_orderids

    def cancel_order(self, cancel_req: CancelRequest) -> None:
        """Cancel an order"""
        self.main_engine.cancel_order(cancel_req, self.gateway_name)

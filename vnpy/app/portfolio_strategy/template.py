from abc import ABC, abstractmethod
from typing import TYPE_CHECKING, List, Optional
from collections import defaultdict

import pandas as pd

from vnpy.trader.constant import Interval, Direction, Offset, Exchange, OrderType
from vnpy.trader.object import BarData, CancelRequest, OrderData, FactorData, OrderRequest, TradeData
from vnpy.trader.utility import convert_dict_to_dataframe

from vnpy.app.portfolio_strategy.base import EngineType
from vnpy.app.portfolio_strategy.config.models.config import ModelConfig
from vnpy.app.portfolio_strategy.config.trading.config import TradingConfig
from vnpy.app.portfolio_strategy.portfolio.portfolio_tracker import PortfolioTracker
from vnpy.app.portfolio_strategy.portfolio.order_manager import OrderManager

if TYPE_CHECKING:
    from vnpy.app.portfolio_strategy.engine import StrategyEngine


class StrategyTemplate(ABC):
    """Portfolio Strategy Template focused on factor processing"""

    # Class Properties
    author: str = ""
    required_factors: list[str] = []
    exchange: Exchange = Exchange.BINANCE
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "StrategyEngine",
            strategy_name: str,
            vt_symbols: list[str],
            state: dict
    ) -> None:
        """Constructor"""
        self.strategy_engine: "StrategyEngine" = strategy_engine
        self.strategy_name: str = strategy_name
        self.vt_symbols: list[str] = vt_symbols

        self.get_tick = self.strategy_engine.get_tick
        self.get_bar = self.strategy_engine.get_bar

        # Initialize configurations
        self.model_config = ModelConfig()
        self.trading_config = TradingConfig()

        # Control variables
        self.inited: bool = False
        self.trading: bool = False

        # Initialize managers
        self.portfolio_tracker = PortfolioTracker()
        self.order_manager = OrderManager(strategy_name=strategy_name)

        # Market data cache
        self.bars: dict[str, BarData] = defaultdict(BarData)
        self.latest_factor_data: Optional[pd.DataFrame] = None

        # Update settings
        self.restore_state(state=state)

    # --------------------------------
    # Strategy Core Methods (Abstract)
    # --------------------------------
    @abstractmethod
    def calculate(self, df: pd.DataFrame) -> pd.Series:
        """Calculate trading signals from factor data"""
        pass

    @abstractmethod
    def project_signals_to_positions(self, signals: pd.Series) -> pd.Series:
        """Convert raw signals to target positions"""
        pass

    # --------------------------------
    # Event Processing Methods
    # --------------------------------
    def on_factor(self, factor_dict: dict[tuple[str, str], FactorData]) -> List[OrderRequest]:
        """Process incoming factor data"""
        if not self.trading:
            return

        # Convert and filter factor data
        df = convert_dict_to_dataframe(factor_dict, is_polars=False)
        if not df.empty:
            df = df.loc[df.index.isin(self.vt_symbols)]
            if self.required_factors:
                df = df[self.required_factors]

            if not df.empty:
                self.latest_factor_data = df

                # Calculate target weights from signals
                signals = self.calculate(df)
                target_weights = self.project_signals_to_positions(signals)

                # Update portfolio targets
                self.portfolio_tracker.set_target_weights(target_weights)

                order_reqs = self.rebalance_portfolio()

                return order_reqs

    def on_order(self, order: OrderData) -> None:
        """Process order update"""
        self.order_manager.on_order(order)

    def on_trade(self, trade: TradeData) -> None:
        """Process trade update and update positions"""
        self.order_manager.on_trade(trade)

        # Update portfolio position
        if trade.direction == Direction.LONG:
            self.portfolio_tracker.set_position(
                trade.vt_symbol,
                self.portfolio_tracker.get_position(trade.vt_symbol) + trade.volume
            )
        else:
            self.portfolio_tracker.set_position(
                trade.vt_symbol,
                self.portfolio_tracker.get_position(trade.vt_symbol) - trade.volume
            )

    # --------------------------------
    # Portfolio Management Methods
    # --------------------------------
    def rebalance_portfolio(self) -> List[OrderRequest]:
        """Generate order requests for rebalancing"""
        self.cancel_all()

        # Get all required position changes
        position_changes = self.portfolio_tracker.get_position_changes()
        order_reqs = []

        # Process each required change
        for vt_symbol, change in position_changes.items():
            if abs(change) < 1e-9:  # Skip tiny changes
                continue

            price = self.portfolio_tracker.get_price(vt_symbol)

            if change > 0:  # Need to buy
                order_reqs.append(
                    self._create_order_request(
                        vt_symbol, Direction.LONG, OrderType.LIMIT, price, change
                    )
                )
            else:  # Need to sell
                order_reqs.append(
                    self._create_order_request(
                        vt_symbol, Direction.SHORT, OrderType.LIMIT, price, abs(change)
                    )
                )

        return order_reqs

    def close_all_positions(self) -> List[OrderRequest]:
        """Close all positions"""
        order_reqs = []
        for vt_symbol in self.vt_symbols:
            pos = self.portfolio_tracker.get_position(vt_symbol)
            if pos > 0:
                order_req = self._create_order_request(
                    vt_symbol, Direction.SHORT, OrderType.MARKET, 0, pos
                )
                order_reqs.append(order_req)
                self.write_log(f"Closed position for {vt_symbol}: {pos}")
        return order_reqs

    # --------------------------------
    # Order Management Methods
    # --------------------------------
    def _create_order_request(
        self,
        vt_symbol: str,
        direction: Direction,
        type: OrderType,
        price: float,
        volume: float
    ) -> OrderRequest:
        """Create order request"""
        return OrderRequest(
            symbol=vt_symbol,
            exchange=self.exchange,
            direction=direction,
            offset=Offset.NONE,
            type=type,
            price=price,
            volume=volume,
            reference=self.strategy_name
        )

    def cancel_order(self, order: OrderData) -> CancelRequest:
        """Cancel order"""
        if self.trading:
            cancel_req = order.create_cancel_request()
            return cancel_req

    def cancel_all_active_orders(self) -> List[CancelRequest]:
        """Cancel all active orders"""
        cancel_reqs = []
        for vt_orderid in self.order_manager.cancel_all_active_orders():
            order = self.order_manager.get_order(vt_orderid)
            cancel_reqs.append(self.cancel_order(order))
        return cancel_reqs

    # --------------------------------
    # State Management Methods
    # --------------------------------
    def get_settings(self) -> dict:
        """Get strategy settings for persistence"""
        settings = {
            "required_factors": self.required_factors,
            "model_config": self.model_config.__dict__,
            "trading_config": self.trading_config.__dict__,
            "vt_symbols": self.vt_symbols,
        }
        return settings

    def get_data(self) -> dict:
        """Get strategy runtime data"""
        portfolio_data = self.portfolio_tracker.get_state()
        
        data = {
            "inited": self.inited,
            "trading": self.trading,
            "portfolio": portfolio_data,
            "trades": {k: v.__dict__ for k, v in self.order_manager.trades.items()},
            "orders": {k: v.__dict__ for k, v in self.order_manager.orders.items()},
            "metrics": self.order_manager.get_metrics()
        }
        return data

    def get_state(self) -> dict:
        """Get complete strategy state"""
        state = {
            "settings": self.get_settings(),
            "data": self.get_data()
        }
        return state

    def restore_settings(self, settings: dict) -> None:
        """Restore strategy settings"""
        if "required_factors" in settings:
            self.required_factors = settings["required_factors"]

        if "model_config" in settings:
            self.model_config = ModelConfig(**settings["model_config"])

        if "trading_config" in settings:
            self.trading_config = TradingConfig(**settings["trading_config"])
            self.trading_config.validate()

        if "vt_symbols" in settings:
            self.vt_symbols = settings["vt_symbols"]

    def restore_data(self, data: dict) -> None:
        """Restore strategy runtime data"""
        if "portfolio" in data:
            self.portfolio_tracker.restore_state(data["portfolio"])

        if "trades" in data:
            for trade_dict in data["trades"].values():
                self.order_manager.trades[trade_dict["vt_tradeid"]] = TradeData(**trade_dict)

        if "orders" in data:
            for order_dict in data["orders"].values():
                self.order_manager.orders[order_dict["vt_orderid"]] = OrderData(**order_dict)
                
        if "metrics" in data:
            self.order_manager.order_metrics.update(data["metrics"])

        # Set status after restore
        if "inited" in data:
            self.inited = data["inited"]
        if "trading" in data:
            self.trading = data["trading"]

    def restore_state(self, state: dict) -> None:
        """Restore complete strategy state"""
        if "settings" in state:
            self.restore_settings(state["settings"])
        
        if "data" in state:
            self.restore_data(state["data"])
            
        # Set status after restore
        if "inited" in state.get("data", {}):
            self.inited = state["data"]["inited"]
        if "trading" in state.get("data", {}):
            self.trading = state["data"]["trading"]

    # --------------------------------
    # Utility Methods
    # --------------------------------
    def write_log(self, msg: str) -> None:
        """Log a message"""
        self.strategy_engine.write_log(msg, self)

    def put_event(self) -> None:
        """Push strategy data update event"""
        if self.inited:
            self.strategy_engine.put_strategy_event(self)

    def send_email(self, msg: str) -> None:
        """Send an email notification"""
        if self.inited:
            self.strategy_engine.send_email(msg, self)

    def sync_data(self) -> None:
        """Sync strategy state data to a file"""
        if self.trading:
            self.strategy_engine.sync_strategy_data(self)

    def get_engine_type(self) -> EngineType:
        """Get the engine type"""
        return self.strategy_engine.get_engine_type()
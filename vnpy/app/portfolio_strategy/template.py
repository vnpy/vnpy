from abc import ABC, abstractmethod
from typing import TYPE_CHECKING, List, Optional
from collections import defaultdict

import pandas as pd

from vnpy.trader.constant import Interval, Direction, Offset, Exchange, OrderType
from vnpy.trader.object import BarData, OrderData, FactorData, OrderRequest, TradeData
from vnpy.trader.utility import convert_dict_to_dataframe

from vnpy.app.portfolio_strategy.base import EngineType
from vnpy.app.portfolio_strategy.config.models.config import ModelConfig
from vnpy.app.portfolio_strategy.config.trading.config import TradingConfig
from vnpy.app.portfolio_strategy.utils.position_manager import PositionManager
from vnpy.app.portfolio_strategy.utils.order_manager import OrderManager

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
        self.position_manager = PositionManager()
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
    def on_factor(self, factor_dict: dict[tuple[str, str], FactorData]) -> None:
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
                # Calculate signals and convert to positions
                signals = self.calculate(df)
                positions = self.project_signals_to_positions(signals)

                # Update prices in position manager
                for vt_symbol in self.vt_symbols:
                    bar = self.bars.get(vt_symbol)
                    if bar:
                        self.position_manager.update_price(vt_symbol, bar)

                # Update target positions
                self.position_manager.set_targets(positions)

                # Execute rebalancing
                return self.rebalance_portfolio(self.bars)

    def on_order(self, order: OrderData) -> None:
        """Process order update"""
        self.order_manager.on_order(order)

    def on_trade(self, trade: TradeData) -> None:
        """Process trade update and update positions"""
        self.order_manager.on_trade(trade)

        # Update position
        if trade.direction == Direction.LONG:
            self.position_manager.set_position(
                trade.vt_symbol,
                self.position_manager.get_position(trade.vt_symbol) + trade.volume
            )
        else:
            self.position_manager.set_position(
                trade.vt_symbol,
                self.position_manager.get_position(trade.vt_symbol) - trade.volume
            )

    # --------------------------------
    # Portfolio Management Methods
    # --------------------------------
    def rebalance_portfolio(self) -> List[OrderRequest]:
        """Generate order requests for rebalancing"""
        self.cancel_all()

        # Get all required position changes
        position_changes = self.position_manager.get_position_changes()
        order_reqs = []

        # Process each required change
        for vt_symbol, change in position_changes.items():
            if abs(change) < 1e-9:  # Skip tiny changes
                continue

            price = self.position_manager.get_price(vt_symbol)

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

    def close_all_positions(self) -> None:
        """Close all positions"""
        for vt_symbol in self.vt_symbols:
            pos = self.position_manager.get_position(vt_symbol)
            if pos > 0:
                order_req = self._create_order_request(
                    vt_symbol, Direction.SHORT, OrderType.MARKET, 0, pos
                )
                self.strategy_engine.send_order(order_req, self)
                self.position_manager.set_position(vt_symbol, 0)
                self.write_log(f"Closed position for {vt_symbol}: {pos}")

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

    def cancel_order(self, order: OrderData) -> None:
        """Cancel order"""
        if self.trading:
            self.strategy_engine.cancel_order(self, order)

    def cancel_all_active_orders(self) -> None:
        """Cancel all active orders"""
        for vt_orderid in self.order_manager.cancel_all_active_orders():
            order = self.order_manager.get_order(vt_orderid)
            self.cancel_order(order)

    # --------------------------------
    # State Management Methods
    # --------------------------------
    def get_state(self, save_data=True) -> dict:
        """Get strategy state for persistence"""
        state = {
            "required_factors": self.required_factors,
            "model_config": self.model_config.__dict__,
            "trading_config": self.trading_config.__dict__
        }

        if save_data:
            state["positions"] = self.position_manager.position_df.to_dict()

        return state

    def restore_state(self, state: dict) -> None:
        """Restore strategy state from saved data"""

        if "required_factors" in state:
            self.required_factors = state["required_factors"]

        if "positions" in state:
            self.position_manager.position_df = pd.DataFrame.from_dict(
                state["positions"]
            )

        if "model_config" in state:
            self.model_config = ModelConfig(**state["model_config"])

        if "trading_config" in state:
            self.trading_config = TradingConfig(**state["trading_config"])
            self.trading_config.validate()

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
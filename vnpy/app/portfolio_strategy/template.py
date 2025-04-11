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

    author: str = ""
    required_factors: list[str] = []
    exchange: Exchange = Exchange.BINANCE
    interval: Interval = Interval.MINUTE

    def __init__(
            self,
            strategy_engine: "StrategyEngine",
            strategy_name: str,
            vt_symbols: list[str],
            setting: dict
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
        self.update_setting(setting)

    def update_setting(self, setting: dict) -> None:
        """Update model and trading configurations"""
        if "model_params" in setting:
            self.model_config = ModelConfig(**setting["model_params"])
            
        if "trading_params" in setting:
            self.trading_config = TradingConfig(**setting["trading_params"])
            self.trading_config.validate()

    @abstractmethod
    def project_signals_to_positions(self, signals: pd.Series) -> pd.Series:
        """
        Convert raw signals to target positions using trading parameters.
        Can be overridden by child classes for custom position sizing.
        
        Parameters
        ----------
        signals : pd.Series
            Raw signals per symbol from calculate()
            
        Returns
        -------
        pd.Series
            Target position sizes per symbol
        """
        # Apply position sizing parameters
        pass

    @abstractmethod 
    def calculate(self, df: pd.DataFrame) -> pd.Series:
        """
        Calculate trading signals from factor data.
        Must be implemented by child classes.
        
        Parameters
        ----------
        df : pd.DataFrame
            Factor data with:
            - Index: vt_symbols 
            - Columns: Factor values
            
        Returns
        -------
        pd.Series
            Raw signals per symbol, will be converted to positions
        """
        pass

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
                        vt_symbol, Direction.LONG, Offset.OPEN, price, change
                        )
                )
            else:  # Need to sell
                order_reqs.append(
                    self._create_order_request(
                        vt_symbol, Direction.SHORT, Offset.CLOSE, price, abs(change)
                        )
                )
        
        return order_reqs

    def _create_order_request(
        self, 
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: float
    ) -> OrderRequest:
        """Create order request"""
        return OrderRequest(
            symbol=vt_symbol,
            exchange=self.exchange,
            direction=direction,
            offset=offset,
            type=OrderType.LIMIT,
            price=price,
            volume=volume,
            reference=self.strategy_name
        )

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

    def cancel_order(self, order: OrderData) -> None:
        """Cancel order"""
        if self.trading:
            self.strategy_engine.cancel_order(self, order)

    def cancel_all(self) -> None:
        """Cancel all active orders"""
        for vt_orderid in self.order_manager.cancel_all_active_orders():
            order = self.order_manager.get_order(vt_orderid)
            self.cancel_order(order)

    def write_log(self, msg: str) -> None:
        """Log a message"""
        self.strategy_engine.write_log(msg, self)

    def get_engine_type(self) -> EngineType:
        """Get the engine type"""
        return self.strategy_engine.get_engine_type()

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
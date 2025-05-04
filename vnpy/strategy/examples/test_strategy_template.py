from vnpy.strategy.template import StrategyTemplate

from typing import Dict,Any, List,Optional

from vnpy.trader.object import OrderRequest, Exchange, Direction, OrderType
import pandas as pd
class TestStrategyTemplate(StrategyTemplate):

    strategy_name = 'test_template'


    def calculate(self, df):
        print(df)
        return pd.Series(
            {'BTCUSDT': 0.02}
        )
    
    def project_signals_to_weights(self, signals):
        print(signals)
        return pd.Series(
            {'BTCUSDT': 1}
        )
    
    def generate_orders_from_targets(self, target_positions_quote) -> List[OrderRequest]:
        print(target_positions_quote)
        return [
            OrderRequest(
                symbol="BTCUSDT",
                exchange=Exchange.BINANCE,
                direction=Direction.Long,
                type=OrderType.LIMIT,
                volume=0.001,
                price=95000,
                reference=self.strategy_name
            )
        ]
        #return super().generate_orders_from_targets(target_positions_quote)
    
    """def on_factor(self, factor_data: Dict[str, Any]) -> Optional[List[OrderRequest]]:
        factor_data=pd.DataFrame.from_dict(factor_data)
        res=self.calculate(factor_data)
        print(res)
        return None"""

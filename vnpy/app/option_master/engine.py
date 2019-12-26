""""""

from typing import Dict, List

from vnpy.trader.object import (
    LogData, ContractData, TickData,
    OrderData, TradeData,
    SubscribeRequest
)
from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TRADE, EVENT_TICK, EVENT_CONTRACT,
    EVENT_TIMER, EVENT_ORDER, EVENT_POSITION
)
from vnpy.trader.constant import Product
from vnpy.trader.converter import OffsetConverter
from vnpy.trader.utility import save_json, load_json

from .base import (
    APP_NAME, CHAIN_UNDERLYING_MAP,
    EVENT_OPTION_LOG, EVENT_OPTION_NEW_PORTFOLIO,
    InstrumentData, PortfolioData
)
from .pricing import (
    black_76, binomial_tree, black_scholes
)


PRICING_MODELS = {
    "Black-76 欧式期货期权": black_76,
    "Black-Scholes 欧式股票期权": black_scholes,
    "二叉树 美式期货期权": binomial_tree
}


class OptionEngine(BaseEngine):
    """"""

    setting_filename = "option_master_setting.json"

    def __init__(self, main_engine: MainEngine, event_engine: EventEngine):
        """"""
        super().__init__(main_engine, event_engine, APP_NAME)

        self.portfolios: Dict[str, PortfolioData] = {}
        self.instruments: Dict[str, InstrumentData] = {}
        self.active_portfolios: Dict[str, PortfolioData] = {}

        self.timer_count: int = 0
        self.timer_trigger: int = 60

        self.offset_converter: OffsetConverter = OffsetConverter(main_engine)
        self.get_position_holding = self.offset_converter.get_position_holding

        self.setting: Dict = {}

        self.load_setting()
        self.register_event()

    def close(self):
        """"""
        self.save_setting()

    def load_setting(self):
        """"""
        self.setting = load_json(self.setting_filename)

    def save_setting(self):
        """"""
        # Save underlying adjustment
        adjustment_settings = {}

        for portfolio in self.active_portfolios.values():
            adjustment_setting = {}
            for chain in portfolio.chains.values():
                adjustment_setting[chain.chain_symbol] = chain.underlying_adjustment

            adjustment_settings[portfolio.name] = adjustment_setting

        self.setting["underlying_adjustments"] = adjustment_settings

        save_json(self.setting_filename, self.setting)

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_TICK, self.process_tick_event)
        self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_POSITION, self.process_position_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data

        instrument = self.instruments.get(tick.vt_symbol, None)
        if not instrument:
            return

        portfolio = instrument.portfolio
        if not portfolio:
            return

        portfolio.update_tick(tick)

    def process_order_event(self, event: Event) -> None:
        """"""
        order: OrderData = event.data
        self.offset_converter.update_order(order)

    def process_trade_event(self, event: Event) -> None:
        """"""
        trade: TradeData = event.data
        self.offset_converter.update_trade(trade)

        instrument = self.instruments.get(trade.vt_symbol, None)
        if not instrument:
            return

        portfolio = instrument.portfolio
        if not portfolio:
            return

        portfolio.update_trade(trade)

    def process_contract_event(self, event: Event) -> None:
        """"""
        contract: ContractData = event.data

        if contract.product == Product.OPTION:
            exchange_name = contract.exchange.value
            portfolio_name = f"{contract.option_portfolio}.{exchange_name}"
            if portfolio_name not in CHAIN_UNDERLYING_MAP:
                return

            portfolio = self.get_portfolio(portfolio_name)
            portfolio.add_option(contract)

    def process_position_event(self, event: Event) -> None:
        """"""
        position = event.data
        self.offset_converter.update_position(position)

    def process_timer_event(self, event: Event) -> None:
        """"""
        self.timer_count += 1
        if self.timer_count < self.timer_trigger:
            return
        self.timer_count = 0

        for portfolio in self.active_portfolios.values():
            portfolio.calculate_atm_price()

    def get_portfolio(self, portfolio_name: str) -> PortfolioData:
        """"""
        portfolio = self.portfolios.get(portfolio_name, None)
        if not portfolio:
            portfolio = PortfolioData(portfolio_name)
            self.portfolios[portfolio_name] = portfolio

            event = Event(EVENT_OPTION_NEW_PORTFOLIO, portfolio_name)
            self.event_engine.put(event)

        return portfolio

    def write_log(self, msg: str) -> None:
        """"""
        log = LogData(msg=msg, gateway_name=APP_NAME)
        event = Event(EVENT_OPTION_LOG, log)
        self.event_engine.put(event)

    def subscribe_data(self, vt_symbol: str) -> None:
        """"""
        contract = self.main_engine.get_contract(vt_symbol)
        req = SubscribeRequest(contract.symbol, contract.exchange)
        self.main_engine.subscribe(req, contract.gateway_name)

    def update_portfolio_setting(
        self,
        portfolio_name: str,
        model_name: str,
        interest_rate: float,
        chain_underlying_map: Dict[str, str],
    ) -> None:
        """"""
        portfolio = self.get_portfolio(portfolio_name)

        for chain_symbol, underlying_symbol in chain_underlying_map.items():
            contract = self.main_engine.get_contract(underlying_symbol)
            portfolio.set_chain_underlying(chain_symbol, contract)

        portfolio.set_interest_rate(interest_rate)

        pricing_model = PRICING_MODELS[model_name]
        portfolio.set_pricing_model(pricing_model)

        portfolio_settings = self.setting.setdefault("portfolio_settings", {})
        portfolio_settings[portfolio_name] = {
            "model_name": model_name,
            "interest_rate": interest_rate,
            "chain_underlying_map": chain_underlying_map
        }
        self.save_setting()

    def get_portfolio_setting(self, portfolio_name: str) -> Dict:
        """"""
        portfolio_settings = self.setting.setdefault("portfolio_settings", {})
        return portfolio_settings.get(portfolio_name, {})

    def init_portfolio(self, portfolio_name: str) -> bool:
        """"""
        # Add to active dict
        if portfolio_name in self.active_portfolios:
            return False
        portfolio = self.get_portfolio(portfolio_name)
        self.active_portfolios[portfolio_name] = portfolio

        # Subscribe market data
        for underlying in portfolio.underlyings.values():
            self.instruments[underlying.vt_symbol] = underlying
            self.subscribe_data(underlying.vt_symbol)

        for option in portfolio.options.values():
            # Ignore options with no underlying set
            if not option.underlying:
                continue

            self.instruments[option.vt_symbol] = option
            self.subscribe_data(option.vt_symbol)

        # Update position volume
        for instrument in self.instruments.values():
            holding = self.offset_converter.get_position_holding(
                instrument.vt_symbol
            )
            if holding:
                instrument.update_holding(holding)

        portfolio.calculate_pos_greeks()

        # Load underlying adjustment from setting
        adjustment_settings = self.setting.get("underlying_adjustments", {})
        adjustment_setting = adjustment_settings.get(portfolio_name)

        if adjustment_setting:
            for chain in portfolio.chains.values():
                chain.underlying_adjustment = adjustment_setting.get(
                    chain.chain_symbol, 0
                )

        return True

    def get_portfolio_names(self) -> List[str]:
        """"""
        return list(self.portfolios.keys())

    def get_underlying_symbols(self, portfolio_name: str) -> List[str]:
        """"""
        underlying_prefix = CHAIN_UNDERLYING_MAP[portfolio_name]
        underlying_symbols = []

        contracts = self.main_engine.get_all_contracts()
        for contract in contracts:
            if contract.product == Product.OPTION:
                continue

            if contract.symbol.startswith(underlying_prefix):
                underlying_symbols.append(contract.vt_symbol)

        underlying_symbols.sort()

        return underlying_symbols

    def get_instrument(self, vt_symbol: str) -> InstrumentData:
        """"""
        instrument = self.instruments[vt_symbol]
        return instrument

    def set_timer_trigger(self, timer_trigger: int):
        """"""
        self.timer_trigger = timer_trigger

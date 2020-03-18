""""""

from typing import Dict, List, Set
from copy import copy
from collections import defaultdict

from vnpy.trader.object import (
    LogData, ContractData, TickData,
    OrderData, TradeData,
    SubscribeRequest, OrderRequest
)
from vnpy.event import Event, EventEngine
from vnpy.trader.engine import BaseEngine, MainEngine
from vnpy.trader.event import (
    EVENT_TRADE, EVENT_TICK, EVENT_CONTRACT,
    EVENT_TIMER, EVENT_ORDER, EVENT_POSITION
)
from vnpy.trader.constant import (
    Product, Offset, Direction, OrderType
)
from vnpy.trader.converter import OffsetConverter
from vnpy.trader.utility import round_to, save_json, load_json

from .base import (
    APP_NAME, CHAIN_UNDERLYING_MAP,
    EVENT_OPTION_NEW_PORTFOLIO,
    EVENT_OPTION_ALGO_PRICING, EVENT_OPTION_ALGO_TRADING,
    EVENT_OPTION_ALGO_STATUS, EVENT_OPTION_ALGO_LOG,
    InstrumentData, PortfolioData
)
try:
    from .pricing import black_76_cython as black_76
    from .pricing import binomial_tree_cython as binomial_tree
    from .pricing import black_scholes_cython as black_scholes
except ImportError:
    from .pricing import (
        black_76, binomial_tree, black_scholes
    )
    print("Faile to import cython option pricing model, please rebuild with cython in cmd.")
from .algo import ElectronicEyeAlgo


PRICING_MODELS = {
    "Black-76 欧式期货期权": black_76,
    "Black-Scholes 欧式股票期权": black_scholes,
    "二叉树 美式期货期权": binomial_tree
}


class OptionEngine(BaseEngine):
    """"""

    setting_filename = "option_master_setting.json"
    data_filename = "option_master_data.json"

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

        self.hedge_engine: OptionHedgeEngine = OptionHedgeEngine(self)
        self.algo_engine: OptionAlgoEngine = OptionAlgoEngine(self)

        self.setting: Dict = {}

        self.load_setting()
        self.register_event()

    def close(self) -> None:
        """"""
        self.save_setting()
        self.save_data()

    def load_setting(self) -> None:
        """"""
        self.setting = load_json(self.setting_filename)

    def save_setting(self) -> None:
        """
        Save underlying adjustment.
        """
        save_json(self.setting_filename, self.setting)

    def load_data(self) -> None:
        """"""
        data = load_json(self.data_filename)

        for portfolio in self.active_portfolios.values():
            portfolio_name = portfolio.name

            # Load underlying adjustment from setting
            chain_adjustments = data.get("chain_adjustments", {})
            chain_adjustment_data = chain_adjustments.get(portfolio_name, {})

            if chain_adjustment_data:
                for chain in portfolio.chains.values():
                    chain.underlying_adjustment = chain_adjustment_data.get(
                        chain.chain_symbol, 0
                    )

            # Load pricing impv from setting
            pricing_impvs = data.get("pricing_impvs", {})
            pricing_impv_data = pricing_impvs.get(portfolio_name, {})

            if pricing_impv_data:
                for chain in portfolio.chains.values():
                    for index in chain.indexes:
                        key = f"{chain.chain_symbol}_{index}"
                        pricing_impv = pricing_impv_data.get(key, 0)

                        if pricing_impv:
                            call = chain.calls[index]
                            call.pricing_impv = pricing_impv

                            put = chain.puts[index]
                            put.pricing_impv = pricing_impv

    def save_data(self) -> None:
        """"""
        chain_adjustments = {}
        pricing_impvs = {}

        for portfolio in self.active_portfolios.values():
            chain_adjustment_data = {}
            pricing_impv_data = {}
            for chain in portfolio.chains.values():
                chain_adjustment_data[chain.chain_symbol] = chain.underlying_adjustment

                for call in chain.calls.values():
                    key = f"{chain.chain_symbol}_{call.chain_index}"
                    pricing_impv_data[key] = call.pricing_impv

            chain_adjustments[portfolio.name] = chain_adjustment_data
            pricing_impvs[portfolio.name] = pricing_impv_data

        data = {
            "chain_adjustments": chain_adjustments,
            "pricing_impvs": pricing_impvs
        }

        save_json(self.data_filename, data)

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

        # Load chain adjustment and pricing impv data
        self.load_data()

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

    def set_timer_trigger(self, timer_trigger: int) -> None:
        """"""
        self.timer_trigger = timer_trigger


class OptionHedgeEngine:
    """"""

    def __init__(self, option_engine: OptionEngine):
        """"""
        self.option_engine: OptionEngine = option_engine
        self.main_engine: MainEngine = option_engine.main_engine
        self.event_engine: EventEngine = option_engine.event_engine

        # Hedging parameters
        self.portfolio_name: str = ""
        self.vt_symbol: str = ""
        self.timer_trigger = 5
        self.delta_target = 0
        self.delta_range = 0
        self.hedge_payup = 1

        self.active: bool = False
        self.active_orderids: Set[str] = set()
        self.timer_count = 0

        self.register_event()

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_order_event(self, event: Event) -> None:
        """"""
        order: OrderData = event.data

        if order.vt_orderid not in self.active_orderids:
            return

        if not order.is_active():
            self.active_orderids.remove(order.vt_orderid)

    def process_timer_event(self, event: Event) -> None:
        """"""
        if not self.active:
            return

        self.timer_count += 1
        if self.timer_count < self.timer_trigger:
            return
        self.timer_count = 0

        self.run()

    def start(
        self,
        portfolio_name: str,
        vt_symbol: str,
        timer_trigger: int,
        delta_target: int,
        delta_range: int,
        hedge_payup: int
    ) -> None:
        """"""
        if self.active:
            return

        self.portfolio_name = portfolio_name
        self.vt_symbol = vt_symbol
        self.timer_trigger = timer_trigger
        self.delta_target = delta_target
        self.delta_range = delta_range
        self.hedge_payup = hedge_payup

        self.active = True

    def stop(self) -> None:
        """"""
        if not self.active:
            return

        self.active = False
        self.timer_count = 0

    def run(self) -> None:
        """"""
        if not self.check_order_finished():
            self.cancel_all()
            return

        delta_max = self.delta_target + self.delta_range
        delta_min = self.delta_target - self.delta_range

        # Do nothing if portfolio delta is in the allowed range
        portfolio = self.option_engine.get_portfolio(self.portfolio_name)
        if delta_min <= portfolio.pos_delta <= delta_max:
            return

        # Calculate volume of contract to hedge
        delta_to_hedge = self.delta_target - portfolio.pos_delta
        instrument = self.option_engine.get_instrument(self.vt_symbol)
        hedge_volume = delta_to_hedge / instrument.theo_delta

        # Send hedge orders
        tick = self.main_engine.get_tick(self.vt_symbol)
        contract = self.main_engine.get_contract(self.vt_symbol)
        holding = self.option_engine.get_position_holding(self.vt_symbol)

        if hedge_volume > 0:
            price = tick.ask_price_1 + contract.pricetick * self.hedge_payup
            direction = Direction.LONG

            if holding:
                available = holding.short_pos - holding.short_pos_frozen
            else:
                available = 0
        else:
            price = tick.bid_price_1 - contract.pricetick * self.hedge_payup
            direction = Direction.SHORT

            if holding:
                available = holding.long_pos - holding.long_pos_frozen
            else:
                available = 0

        order_volume = abs(hedge_volume)

        req = OrderRequest(
            symbol=contract.symbol,
            exchange=contract.exchange,
            direction=direction,
            type=OrderType.LIMIT,
            volume=order_volume,
            price=round_to(price, contract.pricetick),
        )

        # Close positon if opposite available is enough
        if available > order_volume:
            req.offset = Offset.CLOSE
            vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
            self.active_orderids.add(vt_orderid)
        # Open position if no oppsite available
        elif not available:
            req.offset = Offset.OPEN
            vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
            self.active_orderids.add(vt_orderid)
        # Else close all opposite available and open left volume
        else:
            close_req = copy(req)
            close_req.offset = Offset.CLOSE
            close_req.volume = available
            close_orderid = self.main_engine.send_order(close_req, contract.gateway_name)
            self.active_orderids.add(close_orderid)

            open_req = copy(req)
            open_req.offset = Offset.OPEN
            open_req.volume = order_volume - available
            open_orderid = self.main_engine.send_order(open_req, contract.gateway_name)
            self.active_orderids.add(open_orderid)

    def check_order_finished(self) -> None:
        """"""
        if self.active_orderids:
            return False
        else:
            return True

    def cancel_all(self) -> None:
        """"""
        for vt_orderid in self.active_orderids:
            order: OrderData = self.main_engine.get_order(vt_orderid)
            req = order.create_cancel_request()
            self.main_engine.cancel_order(req, order.gateway_name)


class OptionAlgoEngine:

    def __init__(self, option_engine: OptionEngine):
        """"""
        self.option_engine = option_engine
        self.main_engine = option_engine.main_engine
        self.event_engine = option_engine.event_engine

        self.algos: Dict[str, ElectronicEyeAlgo] = {}
        self.active_algos: Dict[str, ElectronicEyeAlgo] = {}

        self.underlying_algo_map: Dict[str, ElectronicEyeAlgo] = defaultdict(list)
        self.order_algo_map: Dict[str, ElectronicEyeAlgo] = {}

        self.register_event()

    def init_engine(self, portfolio_name: str) -> None:
        """"""
        if self.algos:
            return

        portfolio = self.option_engine.get_portfolio(portfolio_name)

        for option in portfolio.options.values():
            algo = ElectronicEyeAlgo(self, option)
            self.algos[option.vt_symbol] = algo

    def register_event(self) -> None:
        """"""
        self.event_engine.register(EVENT_ORDER, self.process_order_event)
        self.event_engine.register(EVENT_TRADE, self.process_trade_event)
        self.event_engine.register(EVENT_TIMER, self.process_timer_event)

    def process_underlying_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data

        for algo in self.underlying_algo_map[tick.vt_symbol]:
            algo.on_underlying_tick(algo)

    def process_option_tick_event(self, event: Event) -> None:
        """"""
        tick: TickData = event.data

        algo = self.algos[tick.vt_symbol]
        algo.on_option_tick(algo)

    def process_order_event(self, event: Event) -> None:
        """"""
        order: OrderData = event.data
        algo = self.order_algo_map.get(order.vt_orderid, None)

        if algo:
            algo.on_order(order)

    def process_trade_event(self, event: Event) -> None:
        """"""
        trade: TradeData = event.data
        algo = self.order_algo_map.get(trade.vt_orderid, None)

        if algo:
            algo.on_trade(trade)

    def process_timer_event(self, event: Event) -> None:
        """"""
        for algo in self.active_algos.values():
            algo.on_timer()

    def start_algo_pricing(self, vt_symbol: str, params: dict) -> None:
        """"""
        algo = self.algos[vt_symbol]

        result = algo.start_pricing(params)
        if not result:
            return

        self.underlying_algo_map[algo.underlying.vt_symbol].append(algo)

        self.event_engine.register(
            EVENT_TICK + algo.option.vt_symbol,
            self.process_option_tick_event
        )
        self.event_engine.register(
            EVENT_TICK + algo.underlying.vt_symbol,
            self.process_underlying_tick_event
        )

    def stop_algo_pricing(self, vt_symbol: str) -> None:
        """"""
        algo = self.algos[vt_symbol]

        result = algo.stop_pricing()
        if not result:
            return

        self.event_engine.unregister(
            EVENT_TICK + vt_symbol,
            self.process_option_tick_event
        )

        buf = self.underlying_algo_map[algo.underlying.vt_symbol]
        buf.remove(algo)

        if not buf:
            self.event_engine.unregister(
                EVENT_TICK + algo.underlying.vt_symbol,
                self.process_underlying_tick_event
            )

    def start_algo_trading(self, vt_symbol: str, params: dict) -> None:
        """"""
        algo = self.algos[vt_symbol]
        algo.start_trading(params)

    def stop_algo_trading(self, vt_symbol: str) -> None:
        """"""
        algo = self.algos[vt_symbol]
        algo.stop_trading()

    def send_order(
        self,
        algo: ElectronicEyeAlgo,
        vt_symbol: str,
        direction: Direction,
        offset: Offset,
        price: float,
        volume: int
    ) -> str:
        """"""
        contract = self.main_engine.get_contract(vt_symbol)

        req = OrderRequest(
            contract.symbol,
            contract.exchange,
            direction,
            OrderType.LIMIT,
            volume,
            price,
            offset
        )

        vt_orderid = self.main_engine.send_order(req, contract.gateway_name)
        self.order_algo_map[vt_orderid] = algo

        return vt_orderid

    def cancel_order(self, vt_orderid: str) -> None:
        """"""
        order = self.main_engine.get_order(vt_orderid)
        req = order.create_cancel_request()
        self.main_engine.cancel_order(req, order.gateway_name)

    def write_algo_log(self, algo: ElectronicEyeAlgo, msg: str) -> None:
        """"""
        msg = f"[{algo.vt_symbol}] {msg}"
        log = LogData(APP_NAME, msg)
        event = Event(EVENT_OPTION_ALGO_LOG, log)
        self.event_engine.put(event)

    def put_algo_pricing_event(self, algo: ElectronicEyeAlgo) -> None:
        """"""
        event = Event(EVENT_OPTION_ALGO_PRICING, algo)
        self.event_engine.put(event)

    def put_algo_trading_event(self, algo: ElectronicEyeAlgo) -> None:
        """"""
        event = Event(EVENT_OPTION_ALGO_TRADING, algo)
        self.event_engine.put(event)

    def put_algo_status_event(self, algo: ElectronicEyeAlgo) -> None:
        """"""
        event = Event(EVENT_OPTION_ALGO_STATUS, algo)
        self.event_engine.put(event)

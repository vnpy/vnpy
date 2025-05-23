import time
import random
import threading
from datetime import datetime, timedelta
from typing import Dict, Set

from vnpy.event.engine import EventEngine
from vnpy.trader.gateway import BaseGateway
from vnpy.trader.object import BarData, SubscribeRequest, ContractData
from vnpy.trader.event import EVENT_CONTRACT
from vnpy.trader.constant import Exchange, Interval, Product

# Default gateway name
GATEWAY_NAME = "MIMIC"

class MimicGateway(BaseGateway):
    """
    VN Trader Gateway for simulating market data.
    Primarily focuses on generating BarData.
    """

    default_setting = {
        "symbols": ["MOCK_AAPL.NASDAQ", "MOCK_BTC.BINANCE"], # Example: symbol.exchange
        "simulation_interval_seconds": 1.0,
        "open_price_range_min": 90,
        "open_price_range_max": 110,
        "price_change_range_min": -2,
        "price_change_range_max": 2,
        "volume_range_min": 100,
        "volume_range_max": 1000
    }

    exchanges = [Exchange.BINANCE] # Add more as needed

    def __init__(self, event_engine: EventEngine, gateway_name: str = GATEWAY_NAME):
        """Constructor"""
        super().__init__(event_engine, gateway_name)

        self.active_simulations: Dict[str, threading.Thread] = {} # vt_symbol -> thread
        self.subscribed_symbols: Set[str] = set() # Store vt_symbols of subscribed contracts
        self.simulation_active: bool = False
        self.settings: Dict = self.default_setting.copy() # Allow modification later if needed
        self._last_bars: Dict[str, BarData] = {} # vt_symbol -> Last generated BarData

    def connect(self, setting: dict) -> None:
        """
        Start the gateway connection.
        For MimicGateway, this means preparing for data simulation.
        The actual simulation for a symbol starts upon subscription.
        """
        self.settings.update(setting) # Update with user-provided settings
        self.simulation_active = True
        self.write_log("MimicGateway connected and simulation prepared.")
        
        # Optionally, pre-populate some ContractData if symbols are in settings
        for symbol_exchange_str in self.settings.get("symbols", []):
            try:
                symbol, exchange_str = symbol_exchange_str.split(".")
                exchange = Exchange(exchange_str.upper()) # Ensure exchange is valid
                
                contract = ContractData(
                    symbol=symbol,
                    exchange=exchange,
                    name=f"{symbol} Mock Contract",
                    product=Product.SPOT, # Or make this configurable
                    size=1,
                    pricetick=0.01,
                    gateway_name=self.gateway_name
                )
                self.on_contract(contract)
            except ValueError as e:
                self.write_log(f"Error parsing symbol/exchange string '{symbol_exchange_str}': {e}")


    def subscribe(self, req: SubscribeRequest) -> None:
        """
        Subscribe to market data.
        For MimicGateway, this starts the bar data simulation for the given symbol.
        """
        if not self.simulation_active:
            self.write_log("MimicGateway is not active. Cannot subscribe.")
            return

        vt_symbol = req.vt_symbol
        if vt_symbol in self.active_simulations:
            self.write_log(f"Already subscribed to {vt_symbol}. Ignoring.")
            return

        self.subscribed_symbols.add(vt_symbol)
        
        # Create and send a contract object if not already sent via connect
        # This ensures strategies know about the contract
        contract = ContractData(
            symbol=req.symbol,
            exchange=req.exchange,
            name=f"{req.symbol} Mock Contract",
            product=Product.SPOT, # Or make this configurable
            size=1,
            pricetick=0.01,
            gateway_name=self.gateway_name
        )
        self.on_contract(contract) # Inform upstream about the contract

        self.write_log(f"Subscribed to {vt_symbol} and started bar simulation.")
        thread = threading.Thread(target=self._run_bar_simulation, args=(req.symbol, req.exchange, req.interval if req.interval else Interval.MINUTE))
        self.active_simulations[vt_symbol] = thread
        thread.start()

    def _run_bar_simulation(self, symbol: str, exchange: Exchange, interval: Interval):
        """
        Continuously generates and publishes BarData events for a given symbol.
        """
        vt_symbol = f"{symbol}.{exchange.value}"
        
        open_price_range = (self.settings["open_price_range_min"], self.settings["open_price_range_max"])
        price_change_range = (self.settings["price_change_range_min"], self.settings["price_change_range_max"])
        volume_range = (self.settings["volume_range_min"], self.settings["volume_range_max"])
        simulation_interval_seconds = float(self.settings["simulation_interval_seconds"])

        last_bar = self._last_bars.get(vt_symbol)

        while self.simulation_active and vt_symbol in self.subscribed_symbols:
            bar = self._generate_bar_data(
                symbol, exchange, interval, last_bar,
                open_price_range=open_price_range,
                price_change_range=price_change_range,
                volume_range=volume_range
            )
            self.on_bar(bar) # Use BaseGateway's on_bar method to push data
            self._last_bars[vt_symbol] = bar
            last_bar = bar
            
            time.sleep(simulation_interval_seconds)
        
        self.write_log(f"Bar simulation stopped for {vt_symbol}.")
        if vt_symbol in self.active_simulations:
            del self.active_simulations[vt_symbol]


    def _generate_bar_data(
        self, 
        symbol: str, 
        exchange: Exchange, 
        interval: Interval, 
        last_bar: BarData = None,
        open_price_range: tuple = (90, 110),
        price_change_range: tuple = (-2, 2),
        volume_range: tuple = (100, 1000)
    ) -> BarData:
        """
        Generates a new BarData object.
        """
        dt = datetime.now()
        
        if last_bar:
            open_price = last_bar.close_price
            dt = last_bar.datetime + self._get_timedelta(interval)
        else:
            # For the first bar, use the configured open_price_range
            open_price = round(random.uniform(open_price_range[0], open_price_range[1]), 2)

        price_change = random.uniform(price_change_range[0], price_change_range[1])
        close_price = round(open_price + price_change, 2)
        
        high_addition = random.uniform(0, abs(price_change * 0.5) + 0.1 * open_price * 0.01) # Add a small percentage of open
        low_subtraction = random.uniform(0, abs(price_change * 0.5) + 0.1 * open_price * 0.01)

        high_price = max(open_price, close_price) + high_addition
        low_price = min(open_price, close_price) - low_subtraction
        
        open_price = max(0.01, open_price) # Ensure prices are positive
        high_price = max(0.01, high_price)
        low_price = max(0.01, low_price)
        close_price = max(0.01, close_price)
        
        actual_high = max(open_price, close_price, high_price)
        actual_low = min(open_price, close_price, low_price)
        high_price = actual_high
        low_price = actual_low

        volume = random.uniform(volume_range[0], volume_range[1])

        print(f"Generated BarData: {symbol}, Open: {open_price}, High: {high_price}, Low: {low_price}, Close: {close_price}, Volume: {volume}")

        bar = BarData(
            gateway_name=self.gateway_name,
            symbol=symbol,
            exchange=exchange,
            datetime=dt,
            interval=interval,
            volume=volume,
            open_price=open_price,
            high_price=high_price,
            low_price=low_price,
            close_price=close_price
        )
        return bar

    def _get_timedelta(self, interval: Interval) -> timedelta:
        if interval == Interval.MINUTE:
            return timedelta(minutes=1)
        elif interval == Interval.HOUR:
            return timedelta(hours=1)
        elif interval == Interval.DAILY:
            return timedelta(days=1)
        else: # Default or unknown interval
            self.write_log(f"Unsupported interval {interval}, defaulting to 1 minute timedelta.")
            return timedelta(minutes=1)

    def close(self) -> None:
        """
        Stop the gateway connection.
        """
        self.simulation_active = False
        self.subscribed_symbols.clear() # Clear subscriptions
        
        # Wait for all simulation threads to finish
        for vt_symbol, thread in list(self.active_simulations.items()): # Iterate over a copy
            if thread.is_alive():
                thread.join(timeout=2.0) # Wait for thread to die
            if vt_symbol in self.active_simulations :
                 del self.active_simulations[vt_symbol]


        self.write_log("MimicGateway closed.")

    def send_order(self, req):  # OrderRequest
        """MimicGateway does not handle orders yet."""
        self.write_log(f"Order request received for {req.vt_symbol}, but MimicGateway does not handle orders yet. Request: {req}")
        # In the future, this could randomly accept/reject or simulate fills.
        return "" # Gateways usually return a vt_orderid string

    def cancel_order(self, req): # CancelRequest
        """MimicGateway does not handle orders yet."""
        self.write_log(f"Cancel order request received for {req.vt_orderid}, but MimicGateway does not handle orders yet.")
        return False # Usually returns True if cancellation sent

    def query_account(self):
        """MimicGateway does not simulate account info yet."""
        pass

    def query_position(self):
        """MimicGateway does not simulate position info yet."""
        pass

import time
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.object import BarData, SubscribeRequest, ContractData
from vnpy.trader.event import EVENT_BAR, EVENT_CONTRACT
from vnpy.trader.constant import Exchange, Interval, Product

# Import the MimicGateway
from vnpy.gateway.mimicgateway import MimicGateway 
# Or, if __init__.py in vnpy.gateway is set up: from vnpy.gateway import MimicGateway

# --- Configuration ---
GATEWAY_ID = "MIMIC"
SYMBOLS_TO_SUBSCRIBE = [
    {"symbol": "MIMICA", "exchange": Exchange.BINANCE, "interval": Interval.MINUTE},
    {"symbol": "MIMICB", "exchange": Exchange.NASDAQ, "interval": Interval.MINUTE},
    # Add a third symbol with a slightly different configuration for variety
    {"symbol": "MIMICC", "exchange": Exchange.SSE, "interval": Interval.MINUTE} 
]
SIMULATION_DURATION_SECONDS = 20 # Increased duration for multi-symbol demo

# --- Event Handlers ---
def bar_event_handler(event):
    bar: BarData = event.data
    print(f"Received Bar: {bar.vt_symbol} - Time: {bar.datetime} O:{bar.open_price} H:{bar.high_price} L:{bar.low_price} C:{bar.close_price} V:{bar.volume}")

def contract_event_handler(event):
    contract: ContractData = event.data # Corrected type hint
    print(f"Received Contract: {contract.vt_symbol} - Name: {contract.name} - Gateway: {contract.gateway_name}")

def main():
    print("Starting MimicGateway Multi-Symbol Example...")

    # 1. Initialize EventEngine
    event_engine = EventEngine()
    print("EventEngine initialized.")

    # 2. Initialize MainEngine (which also starts EventEngine)
    main_engine = MainEngine(event_engine)
    print(f"MainEngine initialized. Available gateways: {main_engine.get_all_gateway_names()}")

    # Prepare symbols for gateway settings
    gateway_setting_symbols = [f"{s['symbol']}.{s['exchange'].value}" for s in SYMBOLS_TO_SUBSCRIBE]

    gateway_settings = {
        "symbols": gateway_setting_symbols,
        "simulation_interval_seconds": 1.0, # Bars every second for each symbol
        "open_price_range_min": 100,
        "open_price_range_max": 105,
        "price_change_range_min": -1,
        "price_change_range_max": 1,
        "volume_range_min": 50,
        "volume_range_max": 200
    }
    main_engine.connect(GATEWAY_ID, gateway_settings)
    print(f"Connection to {GATEWAY_ID} requested with symbols: {gateway_setting_symbols}")

    print("Waiting a moment for gateway connection and initial contract events...")
    time.sleep(2) 

    event_engine.register(EVENT_CONTRACT, contract_event_handler)
    print(f"Registered contract_event_handler for {EVENT_CONTRACT}")

    for sub_info in SYMBOLS_TO_SUBSCRIBE:
        vt_symbol_to_subscribe = f"{sub_info['symbol']}.{sub_info['exchange'].value}"
        bar_event_type = EVENT_BAR + vt_symbol_to_subscribe
        
        # Register specific bar handler for this vt_symbol
        event_engine.register(bar_event_type, bar_event_handler)
        print(f"Registered bar_event_handler for event type: {bar_event_type}")

        req = SubscribeRequest(
            symbol=sub_info['symbol'],
            exchange=sub_info['exchange'],
            interval=sub_info['interval']
        )
        print(f"Subscribing to {vt_symbol_to_subscribe} via MainEngine...")
        main_engine.subscribe(req, GATEWAY_ID)
    
    print(f"Running multi-symbol simulation for {SIMULATION_DURATION_SECONDS} seconds...")
    start_time = time.time()
    while time.time() - start_time < SIMULATION_DURATION_SECONDS:
        time.sleep(0.1)

    print("Simulation finished. Cleaning up...")
    main_engine.close_gateway(GATEWAY_ID)
    print(f"Closed gateway {GATEWAY_ID}")
    
    main_engine.close()
    print("MainEngine closed. Example finished.")

if __name__ == "__main__":
    main()

"""
High-Performance Trading Example with Disruptor Engine.
This script demonstrates how to configure the environment for ultra-low latency
using the Rust-backed Disruptor engine and CPU core pinning.
"""

import sys
from time import sleep
from vnpy.event import create_engine
from vnpy.trader.engine import MainEngine
from vnpy.trader.setting import SETTINGS
from vnpy.trader.logger import INFO

# 1. Configure Disruptor Engine for HFT
# Using busy_spin for zero-latency polling
SETTINGS["event.use_disruptor"] = True
SETTINGS["event.buffer_size"] = 131072  # Increased for burst handling
SETTINGS["event.wait_strategy"] = "busy_spin"
SETTINGS["event.core_id"] = 1  # Pin managed worker to Core 1 (ensure isolated core)

def run_hft():
    """Run the HFT engine configuration."""
    print("Initializing Institutional HFT Stack...")
    
    # 2. Create Engine (Factory will return DisruptorEventEngine based on SETTINGS)
    event_engine = create_engine()
    
    # Verify implementation
    from vnpy.event.disruptor_engine import DisruptorEventEngine
    if isinstance(event_engine, DisruptorEventEngine):
        print(f"Engine Type: DISRUPTOR")
        print(f"Strategy:    {SETTINGS['event.wait_strategy']}")
        print(f"Buffer Size: {SETTINGS['event.buffer_size']}")
    else:
        print("CRITICAL: Failed to initialize Disruptor Engine. Falling back to Standard Queue.")
        sys.exit(1)

    # 3. Initialize Main Engine
    main_engine = MainEngine(event_engine)
    print("MainEngine started successfully.")

    # 4. Stress Test: Simulate high-frequency event burst
    print("Simulating event burst (100k events)...")
    from vnpy.event import Event
    
    def on_event(event):
        pass # Handle events

    event_engine.register("hft_event", on_event)
    
    import time
    start = time.perf_counter()
    for i in range(100_000):
        event_engine.put(Event("hft_event", i))
    
    end = time.perf_counter()
    print(f"Published 100k events in {end - start:.4f}s")
    
    # Keep alive for a moment to let worker finish
    sleep(1)
    
    print("Stopping HFT Engine...")
    main_engine.close()
    print("Done.")

if __name__ == "__main__":
    run_hft()

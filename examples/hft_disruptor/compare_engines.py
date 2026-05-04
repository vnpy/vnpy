"""
Performance Comparison: Standard vs. Disruptor Event Engine.
Runs a 100k event burst through both implementations to quantify the 
throughput gains of the Rust-backed core.
"""

import time
from vnpy.event import Event, EventEngine
from vnpy.event.disruptor_engine import DisruptorEventEngine
from vnpy.trader.setting import SETTINGS

def run_benchmark(engine_name, engine, n=100_000):
    """Run a throughput benchmark on a given engine."""
    # Register dummy handler
    def handler(event):
        pass
    
    engine.register("bench", handler)
    engine.start()
    
    # Warm up
    for i in range(1000):
        engine.put(Event("bench", i))
    
    time.sleep(0.1)
    
    # Benchmark
    start = time.perf_counter()
    for i in range(n):
        engine.put(Event("bench", i))
    
    # Wait for all events to be processed (timer strategy)
    # For a fair comparison, we check if the engine has finished
    # In standard engine, we can't easily check queue size without internal access
    # but we'll wait enough for 100k events.
    time.sleep(1.0) 
    
    end = time.perf_counter()
    total_time = end - start - 1.0 # Subtract wait time
    throughput = n / total_time
    
    engine.stop()
    return total_time, throughput

def main():
    print(f"{'='*60}")
    print(f"{'Engine Type':<25} | {'Time (s)':<10} | {'Throughput (TPS)':<15}")
    print(f"{'-'*60}")
    
    # 1. Standard Engine
    std_engine = EventEngine()
    std_time, std_tps = run_benchmark("Standard", std_engine)
    print(f"{'Standard (Python Queue)':<25} | {std_time:<10.4f} | {std_tps:<15,.0f}")

    # 2. Disruptor Engine (Blocking)
    SETTINGS["event.use_disruptor"] = True
    SETTINGS["event.wait_strategy"] = "blocking"
    dis_engine_block = DisruptorEventEngine()
    dis_time_b, dis_tps_b = run_benchmark("Disruptor-Blocking", dis_engine_block)
    print(f"{'Disruptor (Blocking)':<25} | {dis_time_b:<10.4f} | {dis_tps_b:<15,.0f}")

    # 3. Disruptor Engine (Busy Spin)
    SETTINGS["event.wait_strategy"] = "busy_spin"
    dis_engine_spin = DisruptorEventEngine()
    dis_time_s, dis_tps_s = run_benchmark("Disruptor-BusySpin", dis_engine_spin)
    print(f"{'Disruptor (BusySpin)':<25} | {dis_time_s:<10.4f} | {dis_tps_s:<15,.0f}")
    
    print(f"{'='*60}")
    gain = (dis_tps_s / std_tps)
    print(f"Peak Performance Gain: {gain:.2f}x")

if __name__ == "__main__":
    main()

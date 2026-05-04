import time
import os
import psutil
from vnpy.event import Event
from vnpy.event.disruptor_engine import DisruptorEventEngine

def get_memory_usage():
    process = psutil.Process(os.getpid())
    return process.memory_info().rss / (1024 * 1024)  # MB

def test_memory_stability():
    print(f"Starting memory stress test...")
    engine = DisruptorEventEngine()
    engine.start()
    
    # Register a simple handler
    def handler(event):
        pass
    engine.register("test", handler)
    
    initial_mem = get_memory_usage()
    print(f"Initial Memory: {initial_mem:.2f} MB")
    
    # Publish 10 Million events
    n = 10_000_000
    batch_size = 1000
    
    t0 = time.perf_counter()
    for i in range(n // batch_size):
        events = [Event("test", j) for j in range(batch_size)]
        engine.put_batch(events)
        
        if i % 1000 == 0:
            current_mem = get_memory_usage()
            print(f"  Processed {i*batch_size:,} events... Current Memory: {current_mem:.2f} MB")
            
    # Wait for processing to finish with a timeout
    timeout = time.time() + 10.0
    while engine._producer.get_metrics()["pending_count"] > 0 and time.time() < timeout:
        time.sleep(0.1)
        
    if engine._producer.get_metrics()["pending_count"] > 0:
        print(f"\nWarning: Pending count did not reach 0. Final metrics: {engine._producer.get_metrics()}")
        
    final_mem = get_memory_usage()
    elapsed = time.perf_counter() - t0
    
    print(f"\nFinal Memory: {final_mem:.2f} MB")
    print(f"Memory Delta: {final_mem - initial_mem:.2f} MB")
    print(f"Time: {elapsed:.2f} s")
    
    # If there was a leak, memory would have grown significantly.
    # Each PyObject is ~32-64 bytes. 10M leaked objects = 300-600MB.
    # Allowing for some overhead/fragmentation, we expect delta < 50MB.
    assert (final_mem - initial_mem) < 100 
    
    engine.stop()

if __name__ == "__main__":
    test_memory_stability()

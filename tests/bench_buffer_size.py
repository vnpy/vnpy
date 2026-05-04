import time
import threading
from vnpy_disruptor import DisruptorProducer

def measure_e2e(buffer_size, n=100_000):
    """End-to-end throughput and latency for a raw producer."""
    p = DisruptorProducer(buffer_size, "busy_spin")
    
    received = [0]
    done = threading.Event()
    lats = []
    
    def handler(batch):
        # We don't measure individual latency here to keep throughput high
        received[0] += len(batch)
        if received[0] >= n:
            done.set()
            
    p.start_worker(handler)
    
    # Warm up
    p.publish({"test": 0})
    time.sleep(0.1)
    
    payload = {"price": 42.0}
    t0 = time.perf_counter()
    for _ in range(n):
        p.publish(payload)
        
    if not done.wait(timeout=5.0):
        p.stop()
        return 0, 0
        
    elapsed = time.perf_counter() - t0
    tput = n / elapsed
    
    # Now measure latency separately with low load
    lats = []
    signal = threading.Event()
    t_send = [0.0]
    
    def lat_handler(batch):
        lats.append((time.perf_counter() - t_send[0]) * 1_000_000)
        signal.set()
        
    p.stop()
    p = DisruptorProducer(buffer_size, "busy_spin")
    p.start_worker(lat_handler)
    
    for _ in range(100):
        signal.clear()
        t_send[0] = time.perf_counter()
        p.publish(payload)
        if not signal.wait(timeout=1.0):
            break
            
    avg_lat = sum(lats) / len(lats) if lats else 0
    p.stop()
    return tput, avg_lat

def main():
    sizes = [4096, 16384, 65536, 262144]
    print(f"{'Buffer Size':<12} | {'Latency (µs)':<12} | {'Throughput (TPS)':<18}")
    print("-" * 50)
    
    for size in sizes:
        tput, lat = measure_e2e(size)
        print(f"{size:<12,} | {lat:<12.1f} | {tput:18,.0f}")

if __name__ == "__main__":
    main()

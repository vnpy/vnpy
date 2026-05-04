# Disruptor Event Engine Configuration Guide

The Disruptor Event Engine can be configured globally via the standard VeighNa setting system, allowing for seamless transition from the legacy queue-based engine to the high-performance Rust core.

## 1. Global Configuration (`vt_setting.json`)

The most common way to enable the Disruptor engine is by adding the following keys to your `vt_setting.json` file:

```json
{
    "event.use_disruptor": true,
    "event.buffer_size": 65536,
    "event.wait_strategy": "blocking"
}
```

### Parameter Reference

| Key | Type | Default | Description |
| :--- | :--- | :--- | :--- |
| `event.use_disruptor` | bool | `false` | Enable/Disable the high-performance Rust engine. |
| `event.buffer_size` | int | `65536` | Ring buffer size. **MUST** be a power of 2. |
| `event.wait_strategy` | str | `blocking` | Wait strategy for the worker thread (`blocking`, `yielding`, `busy_spin`, `sleeping`). |
| `event.core_id` | int | `null` | Optional CPU core ID to pin the managed worker thread (HFT optimization). |

## 2. Wait Strategy Selection

- **`blocking` (Institutional Default)**: Uses adaptive parking. Near-zero idle CPU usage while maintaining low latency (~16µs). Recommended for most production environments.
- **`yielding`**: Spins for a short period before yielding. Slightly lower latency but higher CPU consumption.
- **`busy_spin`**: Zero-latency polling. Consumes 100% of one CPU core. Recommended only for ultra-low latency requirements with dedicated core pinning.
- **`sleeping`**: Uses `thread::sleep`. Lowest CPU usage but highest latency. Only for low-throughput data recording tasks.

## 3. Programmatic Usage

You can also explicitly instantiate or configure the engine in your scripts:

```python
from vnpy.event import create_engine
from vnpy.trader.setting import SETTINGS

# Method A: Update SETTINGS before creating the engine
SETTINGS["event.use_disruptor"] = True
SETTINGS["event.buffer_size"] = 131072
event_engine = create_engine()

# Method B: Direct instantiation (Advanced)
from vnpy.event.disruptor_engine import DisruptorEventEngine
event_engine = DisruptorEventEngine(buffer_size=65536, wait_strategy="busy_spin")
```

## 4. Verification

To verify that your application is running on the Disruptor engine, you can check the instance type:

```python
from vnpy.event.disruptor_engine import DisruptorEventEngine
if isinstance(event_engine, DisruptorEventEngine):
    print("Running on High-Performance Disruptor Engine")
```

# Event Engine Queue Pattern Audit (2026-05-04)

## 1. Objective
Audit the standard VeighNa event engine to identify required queue patterns (SPSC, MPSC, SPMC, MPMC) and ensure the Disruptor implementation satisfies these requirements with maximum efficiency.

## 2. Producer-Consumer Analysis

### 2.1 Producers (Writers)
- **Gateways**: Multiple active gateways (e.g., CTP, Binance, IB) each run in dedicated network or API threads. They publish market data (Ticks), order updates, and account status simultaneously.
- **MainEngine**: Publishes system logs and operational events from the main thread.
- **Functional Engines (Apps)**: Engines like `CtaStrategy` or `PortfolioManager` may publish internal events (e.g., strategy status) from their respective logic threads.
- **Internal Timer**: The `EventEngine` background timer thread publishes `EVENT_TIMER` periodically.

**Requirement**: **Multi-Producer (MP)** is mandatory.

### 2.2 Consumers (Readers)
- **EventEngine Worker**: The standard implementation uses a **single background thread** to consume events from the queue and dispatch them to registered handlers sequentially.
- **Sequential Constraint**: VeighNa handlers typically assume sequential execution of events for a given strategy to avoid race conditions in portfolio state.

**Requirement**: **Single-Consumer (SC)** is the current operational standard.

## 3. Queue Pattern Mapping

| Pattern | Required? | Justification |
| :--- | :---: | :--- |
| **SPSC** | No | Multiple producers exist. |
| **MPSC** | **Yes** | **Primary pattern.** Multiple gateways/timer producing to a single dispatcher. |
| **SPMC** | No | Not used in standard VeighNa architecture. |
| **MPMC** | No* | Technically not required but implemented by Disruptor for future-proofing and robustness under multi-thread stress. |

## 4. Disruptor-Rs Alignment
The current `DisruptorEventEngine` implementation (backed by `disruptor-rs` v4.1) is configured as:
- **Producer**: `MultiProducer` (Lock-free ring buffer access for multiple threads).
- **Consumer**: Single Managed Worker thread (Acquires GIL and dispatches events).

### Optimization Path
While the engine is technically **MPMC-capable**, it operates in **MPSC mode** to maintain full compatibility with the legacy sequential handler model. 

### Future Considerations (MPMC)
If VeighNa were to evolve into a multi-consumer model (e.g., one worker thread per Asset Class or per Strategy Group), the existing Disruptor architecture is already **MPMC-ready**. This would allow for:
1. **Parallel Dispatching**: Distributing events across multiple cores.
2. **Priority Lanes**: Separate consumer groups for high-priority Ticks vs. low-priority Logs.

## 5. Conclusion
The **MPSC** pattern is the critical requirement. The current Disruptor implementation perfectly satisfies this with high-performance, lock-free publication and managed sequential consumption.

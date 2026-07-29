# C++ Price-Time Priority Matching Engine Demo

这是一个面向学习和面试交流的单品种撮合引擎。它刻意保持依赖少、规则明确、结果可复现，用来展示订单簿设计、价格时间优先、订单生命周期、正确性验证和延迟测量。

它不是交易所生产系统，也不宣称是 HFT 基础设施。

## 已实现的范围

- C++20，除标准库外无第三方依赖
- 单品种、单线程、同步、确定性撮合
- 限价单、市价单和撤单
- 买卖多档订单簿
- 价格优先、同价时间优先（FIFO）
- 部分成交和跨价位成交
- 成交价取 maker（簿上订单）价格
- 限价单未成交余量继续挂簿，相当于 GTC
- 市价单未成交余量立即撤销，相当于 IOC
- Accepted、Trade、Canceled、Rejected 等顺序事件
- 订单簿快照和内部不变量检查
- 命令文件确定性重放
- 无测试框架依赖的单元测试和随机状态测试
- 输出 P50/P99/P999 的简单混合负载基准

明确没有实现：改单、FOK、冰山单、STP（自成交保护）、账户和风控、持久化日志、故障恢复、多线程、多品种分片、生产级增量行情发布。

## 撮合语义

1. 合法新订单先产生 `OrderAccepted`。
2. 买单从最低卖价开始成交，卖单从最高买价开始成交。
3. 同一个价位按照 `arrival_sequence` 的先后顺序成交。
4. 成交价格使用 maker 的挂单价格，而不是 taker 的限价。
5. 每次成交产生一个 `Trade`，其中包含 maker/taker ID、taker方向、成交量以及双方剩余量。
6. 限价订单的剩余量加入自己的订单簿；市价订单的剩余量产生 `OrderCanceled`。
7. 已被接受的订单 ID 在一次引擎生命周期内不能复用，即使订单已经成交或撤销。
8. 协议校验失败的订单没有被接受，因此修正后允许复用相同 ID。
9. 每条输出事件和每笔成交在单个引擎生命周期内都有全局递增序号，便于审计与确定性重放；`clear()`会开启新的生命周期并重置序号和ID集合。

API约定限价单价格必须大于0，市价单价格必须等于0。对于已经接受过的ID，重复ID拒绝优先于重试请求中其他字段的校验错误。

消费者可以根据 `Trade.maker_remaining` 和 `Trade.taker_remaining` 推导 `PARTTRADED` 或 `ALLTRADED`，Demo没有额外发送 Filled 事件。

## 数据结构

```text
BidBook: map<Price, PriceLevel, greater<Price>>
AskBook: map<Price, PriceLevel, less<Price>>

PriceLevel:
    total_quantity
    list<RestingOrder>       # 同价FIFO

active_orders:
    unordered_map<OrderId, {side, price, list_iterator}>

seen_order_ids:
    unordered_set<OrderId>   # 当前引擎生命周期内的已接受ID
```

选择这些结构是为了让规则和复杂度容易验证：

| 操作 | 复杂度 | 原因 |
|---|---:|---|
| 查询最优买卖价 | `O(1)` | 有序映射的 `begin()` |
| 新增挂单 | `O(log P)` | 查找或创建价位，价位内尾插为 `O(1)` |
| 撤单 | 平均 `O(log P)` | ID索引平均 `O(1)`，随后按价格查价位 `O(log P)` |
| 撮合 | `O(F + L)` | `F`为触达订单数，`L`为清空价位数 |
| 残量挂簿 | 额外 `O(log P)` | 查找己方价位 |
| 全量快照 | `O(P + N)` | 遍历价位和所有挂单 |

`std::map`和`std::list`会产生节点分配，适合清晰的面试 Demo，但不是最低延迟实现。为拒绝终态订单ID复用，`seen_order_ids`在生命周期内只增不减，这也是长时间运行时需要用会话化ID或持久化去重机制解决的Demo取舍。生产版本还可以讨论预分配对象池、intrusive list、稠密价格数组、缓存局部性和按品种分片。

## 构建和运行

在本目录执行：

```bash
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Debug
cmake --build build
ctest --test-dir build --output-on-failure
```

运行内置场景：

```bash
./build/matching_engine_demo
```

内置场景会依次展示：

1. 两笔同价卖单进入FIFO队列；
2. 一笔限价买单先吃掉队首，再部分成交第二笔；
3. 一笔市价买单跨两档扫单；
4. 市价单无法成交的余量自动撤销；
5. 普通挂单撤单和不变量检查。

交互模式：

```bash
./build/matching_engine_demo --interactive
```

支持的指令如下，价格均使用整数 tick：

```text
LIMIT  <id> <BUY|SELL> <price> <qty>
MARKET <id> <BUY|SELL> <qty>
CANCEL <id>
BOOK [depth]
CHECK
QUIT
```

重放示例命令：

```bash
./build/matching_engine_demo --file examples/demo_commands.txt
```

## 正确性验证

测试覆盖以下关键规则：

- 买卖方向对称
- maker价格成交
- 更优价格优先
- 同价FIFO
- 部分成交和价位汇总量更新
- 跨档扫单
- 限价余量挂簿
- 市价余量撤销
- 撤销价位中的头部、中间和最后一笔订单
- 活动、已成交和已撤销订单ID去重
- 非法ID、数量和价格
- 价位总量整数溢出保护
- 事件与成交序号递增
- 相同命令重放得到完全一致的事件和快照
- 5,000步确定性随机命令过程中持续检查内部不变量

引擎的核心不变量包括：

- 不存在空价位；
- 所有挂单剩余量大于0；
- 价位汇总量等于该价位所有订单剩余量之和；
- 同价订单的到达序号严格递增；
- 订单簿与订单ID索引一一对应；
- 每个活动订单都属于已接受ID集合；
- 一条命令处理结束后，最优买价严格低于最优卖价。

Sanitizer验证：

```bash
cmake -S . -B build-asan -G Ninja \
  -DCMAKE_BUILD_TYPE=Debug \
  -DMATCHING_ENGINE_ENABLE_SANITIZERS=ON
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

## 基准测试

使用 Release 构建，不要用 Debug 数字讨论性能：

```bash
cmake -S . -B build-release -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build-release
./build-release/matching_engine_bench --operations 1000000 --seed 42
```

混合负载为55%非交叉限价挂单、35%撤单、10%市价单。基准复用事件缓冲区，单次延迟只包围 `submit/cancel` 调用；吞吐量则包含随机负载生成、候选订单维护以及逐操作计时。因此二者口径不同，需要分别解释。

程序会分别报告限价挂单、撤单和市价单的延迟分布，并输出整体吞吐量：

```text
throughput_ops_per_second
limit_latency_p50/p99/p999_ns
cancel_latency_p50/p99/p999_ns
market_latency_p50/p99/p999_ns
active_orders_initial/final
events_generated
trades_final
```

这些数字是本机进程内微基准，不包含网络、序列化、风控、持久化、CPU绑核、NUMA和真实行情突发，也没有消除操作系统调度噪声。每笔延迟还包含两次 `steady_clock::now()` 的计时开销；订单簿和 `seen_order_ids` 会随当前混合负载增长，因此它不是严格的稳态测试。不要把一次运行的结果包装成生产性能结论；面试中应报告编译模式、硬件、负载、订单簿深度、轮数以及分位数。

## 与 vn.py 的关系

vn.py在实盘中负责策略、订单路由、OMS和交易接口适配；真正撮合通常发生在交易所。当前版本尚未接入vn.py，下面是把这个Demo作为本地仿真交易所的下一步适配设计：

```text
vn.py Strategy/App
      |
      | OrderRequest
      v
Custom MatchingGateway
      |
      | NewOrder / Cancel
      v
C++ MatchingEngine
      |
      | Accepted / Trade / Canceled / Rejected
      v
Gateway.on_order / Gateway.on_trade
      |
      v
vn.py EventEngine + OmsEngine
```

适配层需要完成：

- 将 `vt_symbol` 路由到对应品种的引擎实例；
- 将价格除以最小跳动转换为整数 tick；
- 把 vn.py 的订单方向、类型和数量转换成引擎命令；
- 根据事件中的剩余量生成 `OrderData` 状态；
- 把 `Trade`转换为 `TradeData`并调用 Gateway 回调；
- 保证订单和成交ID在重启、重放时一致。

当前快照函数只是调试查询接口，并不是生产级增量行情发布器。

公共C++ API假设调用方传入类型合法的枚举值；交互CLI会校验方向、订单类型和完整数值文本。跨语言或网络接入时，适配层仍需进行协议级枚举校验。

## 面试时怎么讲

### 60秒版本

> 我实现了一个单品种、单线程、确定性的C++订单撮合引擎。买卖盘使用按价格排序的map，价位内部使用list维护FIFO，再用unordered_map保存订单ID到链表节点的索引。它支持限价、市价、撤单、部分成交和跨档成交，成交价取maker价格。每个命令会生成带单调序号的领域事件，并通过单元测试、随机状态测试和内部不变量验证正确性。我还写了Release微基准，报告吞吐量和P50/P99/P999，同时明确区分进程内Demo和生产低延迟系统的差距。

### 常见追问

**为什么价格不用 `double`？**

交易价格只能落在最小变动单位上。把价格转换为整数 tick 可以避免浮点比较和哈希的不确定性，例如 `0.1 + 0.2` 无法精确表示的问题。

**为什么是 `map + list + unordered_map`？**

`map`维护价格优先级，`list`稳定地维护同价FIFO，ID索引让撤单无需扫描订单簿。代价是节点分配多、缓存局部性一般，所以它强调正确性和可解释性，而不是声称最低延迟。

**为什么成交价使用 maker 价格？**

taker表示愿意以不差于其限价成交，真正簿上已经存在的报价是maker价格。比如买价105打到卖价100，应当在100成交。

**为什么使用单线程？**

同一个订单簿需要严格确定的全序。单写者模型避免锁竞争，也使事件顺序和重放结果稳定。多核扩展通常优先按品种分片，而不是让多个线程同时修改同一本订单簿。

**撤单是 `O(1)` 吗？**

当前实现不是。ID索引平均 `O(1)` 找到订单，但还要用价格在 `map`中查找价位，所以整体是平均 `O(log P)`。若要进一步优化，可以在handle中保存稳定的价位节点或容器迭代器。

**如何保证正确性？**

除了场景测试，我把订单簿规则写成可执行不变量，并在随机命令序列中周期性检查。相同命令在两个引擎实例中还必须产生完全相同的事件和最终快照。

**如何恢复崩溃？**

当前版本不做持久化。生产化方案会把输入命令或输出事件追加到WAL，周期性生成带序号快照；恢复时加载快照并从最后序号继续重放，同时需要校验和、幂等ID和主备切换协议。

**下一步怎么降低延迟？**

先建立稳定基准，再依次考虑预分配订单池、intrusive list、减少variant/vector分配、稠密价格数组、缓存行布局、CPU绑核和按品种分片。任何优化都必须继续通过相同的不变量和重放测试。

## 五分钟演示顺序

1. 运行 `ctest`，说明先证明规则正确。
2. 运行内置场景，指着FIFO队列解释价格时间优先。
3. 展示 `Trade`中的maker、taker和双方剩余量。
4. 运行一次Release基准，说明测试口径和局限。
5. 最后说明如何通过自定义Gateway接入vn.py，以及生产化还缺哪些组件。

## 目录结构

```text
include/matching_engine/matching_engine.hpp  公共类型和引擎API
src/matching_engine.cpp                      订单簿和撮合实现
src/main.cpp                                 内置场景、交互CLI和命令重放
tests/test_matching_engine.cpp               单元与随机状态测试
benchmarks/benchmark.cpp                     混合负载微基准
examples/demo_commands.txt                   可重放命令示例
```

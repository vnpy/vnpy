# 脚本策略

ScriptTrader模块的作用：


## Jupyter模式

### 加载启动

### 连接接口

### 查询数据

use_df可选参数的作用（返回pandas.DataFrame，在Jupyter中分析更方便）

### 发出指令


## 脚本策略模式

### 加载启动

### 脚本策略

### 运行控制

while循环的退出控制变量：engine.strategy_active

## 函数功能说明

### 单条查询

* get_tick

### 多条查询

* get_ticks

### 全量查询

* get_all_contracts

### 交易委托

* buy
* cancel_order

### 信息输出

* write_log
* send_email
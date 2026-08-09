# RiskManager - 事前风控管理模块

## 功能简介

RiskManager是用于**事前风控管理**的功能模块，采用插件式架构设计，提供标准化的风控规则开发模板（RuleTemplate）。用户可以通过其UI界面便捷完成风控规则的启停、参数修改和状态监控，也可以自行编写符合业务需求的自定义风控规则。

内置5条风控规则，覆盖中国期货程序化交易系统监管要求中的核心检测项：

- **活动委托检查**：限制同时处于活动状态的委托数量上限
- **每日上限检查**：限制日内累计委托/撤单/成交笔数（支持全汇总和单合约两个维度）
- **重复报单检查**：防止短时间内重复发送完全相同的委托
- **委托规模检查**：限制单笔委托的数量和名义价值
- **委托指令检查**：验证委托价格、数量是否符合合约规范（合约存在性、最小变动价位、数量上下限等）

## 加载启动

### VeighNa Station加载

启动登录VeighNa Station后，点击【交易】按钮，在配置对话框中的【应用模块】栏勾选【RiskManager】。

### 脚本加载

在启动脚本中添加如下代码：

```python3
# 写在顶部
from vnpy_riskmanager import RiskManagerApp

# 写在创建main_engine对象后
main_engine.add_app(RiskManagerApp)
```

## 启动模块

在菜单栏中点击【功能】-> 【交易风控】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/1-1.png)

即可进入事前风控模块的UI界面。界面采用左侧规则列表 + 右侧规则详情（参数/变量）的布局，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/22.png)

左侧列表显示所有已加载的风控规则名称，点击后右侧显示该规则的当前参数和实时变量。每条规则都包含`active`参数，可在【修改风控参数】对话框中单独启用或停用。

当任何一条规则拦截委托时，系统会：
- 在VeighNa Trader主界面的【日志】栏输出拦截原因
- 通过Windows系统托盘弹出气泡通知（停留30秒）
- 播放系统提示音（当前仅支持Windows）


## 内置风控规则

### 活动委托检查（ActiveOrderRule）

限制同时处于活动状态（提交中 / 未成交 / 部分成交）的委托数量。

| 参数 | 名称 | 默认值 | 说明 |
|------|------|:---:|------|
| active_order_limit | 活动委托上限 | 50 | 活动委托数量达到此值后不再发单 |

| 变量 | 名称 | 说明 |
|------|------|------|
| active_order_count | 活动委托数量 | 当前处于活动状态的委托笔数 |

当一笔委托状态变为非活动（全部成交 / 已撤销 / 拒单）时，计数器自动释放。

### 每日上限检查（DailyLimitRule）

限制日内累计的委托、撤单和成交笔数，支持全汇总（所有合约合计）和单合约两个维度的独立上限。

| 参数 | 名称 | 默认值 | 说明 |
|------|------|:---:|------|
| total_order_limit | 汇总委托上限 | 20000 | 所有合约合计的委托笔数上限 |
| total_cancel_limit | 汇总撤单上限 | 10000 | 所有合约合计的撤单笔数上限 |
| total_trade_limit | 汇总成交上限 | 10000 | 所有合约合计的成交笔数上限 |
| contract_order_limit | 合约委托上限 | 2000 | 单个合约的委托笔数上限 |
| contract_cancel_limit | 合约撤单上限 | 1000 | 单个合约的撤单笔数上限 |
| contract_trade_limit | 合约成交上限 | 1000 | 单个合约的成交笔数上限 |

| 变量 | 名称 | 说明 |
|------|------|------|
| total_order_count | 汇总委托笔数 | 当天所有合约累计委托笔数 |
| total_cancel_count | 汇总撤单笔数 | 当天所有合约累计撤单笔数 |
| total_trade_count | 汇总成交笔数 | 当天所有合约累计成交笔数 |
| contract_order_count | 合约委托笔数 | 各合约分别统计（dict，key为vt_symbol） |
| contract_cancel_count | 合约撤单笔数 | 各合约分别统计 |
| contract_trade_count | 合约成交笔数 | 各合约分别统计 |

六项上限中有任意一项达到即拦截后续委托。计数器每日重置。

### 重复报单检查（DuplicateOrderRule）

防止策略因逻辑错误在短时间内反复发送完全相同的委托请求。

规则将每笔委托请求格式化为字符串（合约代码 + 委托类型 + 方向 + 开平 + 数量 @ 价格），统计相同请求的重复次数。

| 参数 | 名称 | 默认值 | 说明 |
|------|------|:---:|------|
| duplicate_order_limit | 重复报单上限 | 10 | 相同委托请求的允许最大次数 |

| 变量 | 名称 | 说明 |
|------|------|------|
| duplicate_order_count | 重复报单笔数 | 当前累计的重复报单统计（dict） |

委托一旦被拦截，计数器不再增加（避免无限增长），用户需手动排查策略逻辑。

### 委托规模检查（OrderSizeRule）

限制单笔委托的数量和名义价值，防止因参数错误导致异常大单。

| 参数 | 名称 | 默认值 | 说明 |
|------|------|:---:|------|
| order_volume_limit | 委托数量上限 | 500 | 单笔委托允许的最大手数 |
| order_value_limit | 委托价值上限 | 1000000 | 单笔委托允许的最大名义价值 |

委托名义价值的计算公式为：`数量 × 价格 × 合约乘数`。由于合约乘数需要从CTP等接口推送的合约信息中获取，仅当合约信息已缓存且为限价单时才会执行价值检查。

### 委托指令检查（OrderValidityRule）

验证委托本身的合法性，确保发送到交易所的委托不会被拒单。检测项包括：

1. **合约存在性**：委托的目标合约代码是否在系统中可查到
2. **价格精度**：委托价格是否为合约最小变动价位（pricetick）的整数倍
3. **数量范围**：委托数量是否在合约允许的[min_volume, max_volume]区间内

该规则除公共的`active`参数外，**无其他用户可配置参数**。默认启用，建议始终保持开启，避免低级的委托格式错误。

## 自定义风控规则

用户可以像编写CTA策略一样编写自己的风控规则。RiskManager提供了标准化的风控规则开发模板（RuleTemplate），只需继承基类并实现必要的方法即可添加新的风控逻辑。

### 规则模板

所有风控规则继承`RuleTemplate`基类，其结构与`CtaTemplate`高度一致：

```python
from vnpy_riskmanager.template import RuleTemplate
from vnpy.trader.object import OrderRequest, OrderData, TradeData, TickData


class MyCustomRule(RuleTemplate):
    """自定义风控规则"""

    # 规则名称（UI显示名，同时作为配置主键，需全局唯一）
    name: str = "我的自定义规则"

    # 参数字段 → UI显示名
    parameters: dict[str, str] = {
        "my_limit": "自定义上限",
    }

    # 变量字段 → UI显示名
    variables: dict[str, str] = {
        "my_count": "自定义计数",
    }

    def on_init(self) -> None:
        """初始化（构造函数中自动调用）"""
        self.my_limit: int = 100
        self.my_count: int = 0

    def check_allowed(self, req: OrderRequest, gateway_name: str) -> bool:
        """
        检查是否允许此笔委托。
        返回 True = 放行，返回 False = 拦截并输出日志。
        """
        if self.my_count >= self.my_limit:
            self.write_log(f"自定义计数{self.my_count}达到上限")
            return False
        return True

    def on_order(self, order: OrderData) -> None:
        """收到委托回报时触发"""
        self.my_count += 1
        self.put_event()

    def on_trade(self, trade: TradeData) -> None:
        """收到成交回报时触发"""
        pass

    def on_tick(self, tick: TickData) -> None:
        """收到行情Tick时触发"""
        pass

    def on_timer(self) -> None:
        """每秒定时触发"""
        pass
```

### RuleTemplate方法速查

| 方法 | 触发时机 | 说明 |
|------|------|------|
| `check_allowed(req, gateway)` | 每次发单前 | **核心方法**，返回True/False决定是否放行 |
| `on_init()` | 规则实例化时 | 初始化参数和变量 |
| `on_order(order)` | 收到委托回报 | 更新活动委托、计数器等 |
| `on_trade(trade)` | 收到成交回报 | 更新成交计数等 |
| `on_tick(tick)` | 收到行情Tick | 如需要基于行情数据做风控 |
| `on_timer()` | 每秒 | 如需要基于时间窗口做统计 |
| `write_log(msg)` | 主动调用 | 输出拦截日志到主界面 |
| `put_event()` | 主动调用 | 推送变量更新到UI界面 |
| `get_contract(vt_symbol)` | 主动调用 | 查询合约信息（乘数、最小变动价位等） |

注意：只有实际**重写**了`on_order` / `on_trade` / `on_tick` / `on_timer`的规则才会收到对应的事件推送。RiskEngine会通过`needs_callback()`方法自动检测，避免不必要的事件分发开销。

### 放置自定义规则

对于用户自行开发的风控规则，需要放到VeighNa Trader运行时目录下的**rules**目录中，才能被识别加载。具体的运行时目录路径，可以在VeighNa Trader主界面顶部的标题栏查看。该目录通常与`.vntrader`文件夹平级，若不存在`rules`目录，需自行创建。

对于在Windows上默认安装的用户来说，放置规则的rules目录路径通常为：

```
C:\Users\Administrator\rules
```

其中Administrator为当前登录Windows的系统用户名。

请注意：

- 显示在UI左侧的是规则类的`name`属性，而不是规则文件名；
- 规则**类名**必须以`Rule`结尾（例如`MyCustomRule`），否则不会被加载。

RiskEngine启动时会自动扫描并加载该目录下符合条件的规则类，同时也会加载`vnpy_riskmanager.rules`包内的内置规则。两个来源的规则会合并显示在UI左侧的规则列表中。

如规则文件发生修改，**重新启动VeighNa Trader**即可加载新版本。

### Cython加速

对于性能敏感的场景（如高频交易中大量事件回调），可以将`.py`编译为`.pyd`（Windows）或`.so`（Linux）。`vnpy_riskmanager.rules`目录下已经提供了每条内置规则的Cython版本（`.pyx`文件），用户自定义规则也可以同样处理。

RiskEngine在扫描规则时会同时匹配`*.py`、`*.pyd`、`*.so`后缀的文件，无需额外配置。若同一规则类同时存在纯Python与编译版本，后加载的版本会覆盖先加载的版本（扫描顺序为`py` → `pyd` → `so`）。

## 参数配置

### 修改参数

在UI界面左侧列表中选择需要修改的规则，点击右下角的【修改风控参数】按钮：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/33.png)

弹出参数编辑对话框，各参数根据类型自动匹配输入控件：
- **bool类型**：下拉框（True / False），如`active`开关
- **int类型**：整数微调框
- **float类型**：浮点数微调框（6位小数精度）

修改后点击【确定】保存并立即生效。参数会自动持久化到运行时目录下`.vntrader`文件夹中的`risk_manager_setting.json`文件，下次启动自动恢复。

### 启停规则

每条规则都有`active`参数（默认True）。设为False后该规则不再参与委托拦截检查。可在【修改风控参数】对话框中，将`active`对应的下拉框改为False后保存。

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/risk_manager/44.png)

建议日常保持全部规则启用。如需临时关闭某条规则以排查问题，关闭后应立即恢复。

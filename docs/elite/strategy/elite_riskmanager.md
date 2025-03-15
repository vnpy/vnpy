# 事前交易风控

RiskManager模块是用于**事前交易风控**的功能模块，用户可以通过其配置json文件操作来便捷完成风控任务。


## 主要优势

RiskManager模块提供包括标准化的风控规则开发模板，支持用户按需开发各种自定义风控规则。

内置常用风控规则包括：

* BlackListRule: 黑名单规则
* WhiteListRule: 白名单规则
* OrderLimitRule: 委托数量和金额限制规则
* SelfTradeRule: 自成交限制规则
* RiskLevelRule: 账户风险度限制规则
* OrderFlowRule: 委托流量限制规则
* PriceRangeRule: 价格偏离度规则
* PosLimitRule: 持仓上限规则
* TradeValueRule: 日内开仓限制规则


## 启动模块

RiskManager模块需要启动之前通过【策略应用】标签页加载。

启动登录VeighNa Elite Trader后，启动模块之前，请先连接交易接口。看到VeighNa Elite Trader主界面【日志】栏输出“合约信息查询成功”之后再启动模块。

请注意，IB接口因为登录时无法自动获取所有的合约信息，只有在用户手动订阅行情时才能获取。因此需要在主界面上先行手动订阅合约行情，再启动模块。

成功连接交易接口后，在菜单栏中点击【功能】-> 【风控引擎】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/riskmanager/1.png)

即可进入风控引擎模块的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/riskmanager/2.png)


## 配置风控

事前风控模块负责在委托通过交易API接口发出前，检查其状态是否符合各种风控规则。

用户可通过编辑.vntrader文件夹下的risk_engine_setting.json配置风控规则，如下图所示（仅示例）：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/riskmanager/3.png)

**请注意，风控规则配置的时候，对应规则的“active”要设置为true才会启用规则，设置为false是不会启用的。**

成功配置风控规则之后，启动VeighNa Elite Trader并加载风控引擎模块即可在发出委托之前检查每一笔发出的委托是否符合风控要求。若委托被风控引擎拦截，VeighNa Elite Trader主界面的【日志】栏会输出相应日志，风控引擎的UI界面也会输出日志，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/elite/riskmanager/4.png)


## 风控规则介绍

### BlackListRule: 黑名单规则

 - black_list[list[str]] 黑名单

 启用之后，在黑名单列表内的vt_symbol委托会被拦截。

### WhiteListRule: 白名单规则

 - white_list[list[str]] 白名单

 启用之后，不在白名单列表内的vt_symbol委托会被拦截。

### OrderLimitRule: 委托数量和金额限制规则

 - order_cancel_limit[int] 日内撤单次数上限
 - order_volume_limit[int] 单笔委托数量上限
 - order_value_limit[float] 单笔委托金额上限

 启用之后，找不到对应vt_symbol合约信息的委托会被拦截，日内撤单次数超过配置上限，单笔委托数量超过配置上限以及单笔委托金额超过配置上限的委托都会被拦截。

### SelfTradeRule: 自成交限制规则

 启用之后，委托方向与未成交委托相反且委托价格超过未成交委托价格的委托（以多头为例，新委托方向为多，未成交方向为空，且新委托价格大于等于未成交空方向委托价格）会被拦截。

### RiskLevelRule: 账户风险度限制规则

 - risk_level_limit[float] 保证金风险度上限（只支持单账户）

 启用之后，接口获取不到账户当前资金时发出的委托会被拦截，账户冻结资金/账户余额小于配置的保证金风险度上限时发出的委托也会被拦截。

### PriceRangeRule: 价格偏离度规则

 - price_range_limit[float] 价格偏离度

 启用之后，没有获取到对应vt_symbol实时行情的委托会被拦截，委托价格超过合约涨跌停价或者委托价格超过价格上下限的委托都会被拦截。

 请注意，价格上下限是基于合约最新价 * (1 +/- price_range_limit)然后取min/max再基于合约价格跳动进行调整的。

### PosLimitRule: 持仓上限规则

 - contract_setting[dict]
  - vt_symbol(key)
  - setting(value)
   - long_pos_limit[int] 多头仓位限制
   - short_pos_limit[int] 空头仓位限制
   - net_pos_limit[int] 净仓位限制
   - total_pos_limit[int] 总仓位限制
   - oi_percent_limit[float] 日内成交净额限制

 启用之后，没有获取到对应vt_symbol实时行情的委托会被拦截，委托合约多仓总数量、空仓总数量、净仓总数量、总仓总数量以及持仓集中度超限的委托会被拦截。

 请注意，持仓集中度超限认定是委托合约的总仓位超过了委托合约的持仓量（tick.open_interest）与配置的该合约日内成交净额限制的乘积。

### TradeValueRule: 日内开仓限制规则

 - contract_setting[dict]
  - vt_symbol(key)
  - setting(value)
   - trade_value_limit[int] 日内成交敞口变化上限

 启用之后，发出委托与缓存的该合约日内成交敞口累加超过配置的变化上限就会被拦截。

 请注意，缓存配置合约的每一笔委托成交敞口都是基于委托价格、委托数量以及合约乘数的乘积计算的。

### OrderFlowRule: 委托流量限制规则

 - order_flow_interval[int] 委托流控时间窗口
 - order_flow_limit[int] 委托流控给定时间窗口内最多允许发出的委托笔数
 - total_order_limit[int] 日内总委托笔数上限

 启用之后，发出委托笔数在配置的流控时间窗口内超过配置的最多允许委托笔数就会被拦截，发出委托笔数超过配置的当日总委托笔数上限也会被拦截。

 请注意，日内总委托笔数取决于主引擎查到的所有委托的长度。

# 算法交易
算法交易可以用于把巨型单子拆分成一个个小单，能够有效降低交易成本，冲击成本等（冰山算法、狙击手算法)；也可以在设定的阈值内进行高抛低吸操作(网格算法、套利算法）。

&nbsp;

## 模块构成

算法交易模块主要由4部分构成，如下图：

- engine：定义了算法引擎，其中包括：引擎初始化、保存/移除/加载算法配置、启动算法、停止算法、订阅行情、挂撤单等。
- template：定义了交易算法模板，具体的算法示例，如冰山算法，都需要继承于该模板。
- algos：具体的交易算法示例。用户基于算法模板和官方提供的算法示例，可以自己搭建新的算法。
- ui：基于PyQt5的GUI图形应用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/algo_trader_document.png)

&nbsp;

## 基本操作

在VN Trader的菜单栏中点击“功能”—>“算法交易”即可打开如图算法交易模块窗口，如下图。

算法交易模块有2部分构成：
- 委托交易，用于启动算法交易；
- 数据监控，用于监控算法交易执行情况，并且能够手动停止算法。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/algo_trader_all_section.png)

&nbsp;

### 委托交易

下面以时间加权平均算法为例，具体介绍如下图委托交易功能选项。
- 算法：目前提供了5种交易算法：时间加权平均算法、冰山算法、狙击手算法、条件委托、最优限价；
- 本地代码：vt_symbol格式，如AAPL.SMART, 用于算法交易组建订阅行情和委托交易；
- 方向：做多或者做空；
- 价格：委托下单的价格；
- 数量：委托的总数量，需要拆分成小单进行交易；
- 执行时间：运行改算法交易的总时间，以秒为单位；
- 每轮间隔：每隔一段时间（秒）进行委托下单操作；
- 启动算法：设置好算法配置后，用于立刻执行算法交易。

所以，该算法执行的任务如下：通过时间加权平均算法，买入10000股AAPL（美股），执行价格为180美金，执行时间为600秒，间隔为6秒；即每隔6秒钟，当买一价少于等于180时，以180的价格买入100股AAPL，买入操作分割成100次。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/trading_section.png)

交易配置可以保存在json文件，这样每次打开算法交易模块就不用重复输入配置。其操作是在“算法名称”选项输入该算法设置命名，然后点击下方"保存设置”按钮。保存的json文件在C:\Users\Administrator\\.vntrader文件夹的algo_trading_setting.json中，如图。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/setting.png)

委托交易界面最下方的“全部停止”按钮用于一键停止所有执行中的算法交易。

&nbsp;

### 数据监控

数据监控由4个部分构成。

- 活动组件：显示正在运行的算法交易，包括：算法名称、参数、状态。最左边的“停止”按钮用于手动停止执行中的算法。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/action.png)

&nbsp;

- 历史委托组件：显示已完成的算法交易，同样包括：算法名称、参数、状态。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/final.png)

&nbsp;

- 日志组件：显示启动、停止、完成算法的相关日志信息。在打开算法交易模块后，会进行初始化，故日志上会首先显示“算法交易引擎启动”和“算法配置载入成功”。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/log_section.png)

&nbsp;

- 配置组件：用于载入algo_trading_setting.json的配置信息，并且以图形化界面显示出来。
用户可以点击“使用”按钮立刻读取配置信息，并显示在委托交易界面上，点击“启动算法”即可开始进行交易；
用户也可以点击“移除”按钮来移除该算法配置，同步更新到json文件内。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/algo_trader/setting_section.png)

&nbsp;

## 算法示例


### 直接委托算法

直接发出新的委托（限价单、停止单、市价单）

```
    def on_tick(self, tick: TickData):
        """"""
        if not self.vt_orderid:
            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
                
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    self.volume,
                    self.order_type,
                    self.offset
                )
        self.put_variables_event()
```

&nbsp;

### 时间加权平均算法

- 将委托数量平均分布在某个时间区域内；
- 每隔一段时间用指定的价格挂出买单（或者卖单）。
- 买入情况：买一价低于目标价格时，发出委托，委托数量在剩余委托量与委托分割量中取最小值。
- 卖出情况：卖一价高于目标价格时，发出委托，委托数量在剩余委托量与委托分割量中取最小值。

```
    def on_timer(self):
        """"""
        self.timer_count += 1
        self.total_count += 1
        self.put_variables_event()

        if self.total_count >= self.time:
            self.write_log("执行时间已结束，停止算法")
            self.stop()
            return

        if self.timer_count < self.interval:
            return
        self.timer_count = 0

        if not self.last_tick:
            return
        tick = self.last_tick
        self.last_tick = None

        self.cancel_all()

        left_volume = self.volume - self.traded
        order_volume = min(self.order_volume, left_volume)

        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                self.buy(self.vt_symbol, self.price,
                         order_volume, offset=self.offset)
        else:
            if tick.bid_price_1 >= self.price:
                self.sell(self.vt_symbol, self.price,
                          order_volume, offset=self.offset)
```

&nbsp;

### 冰山算法

- 在某个价位挂单，但是只挂一部分，直到全部成交。
- 买入情况：先检查撤单：最新Tick卖一价低于目标价格，执行撤单；若无活动委托，发出委托：委托数量在剩余委托量与挂出委托量中取最小值。
- 卖出情况：先检查撤单：最新Tick买一价高于目标价格，执行撤单；若无活动委托，发出委托：委托数量在剩余委托量与挂出委托量中取最小值。

```
    def on_timer(self):
        """"""
        self.timer_count += 1

        if self.timer_count < self.interval:
            self.put_variables_event()
            return

        self.timer_count = 0

        contract = self.get_contract(self.vt_symbol)
        if not contract:
            return

        # If order already finished, just send new order
        if not self.vt_orderid:
            order_volume = self.volume - self.traded
            order_volume = min(order_volume, self.display_volume)

            if self.direction == Direction.LONG:
                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
            else:
                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        # Otherwise check for cancel
        else:
            if self.direction == Direction.LONG:
                if self.last_tick.ask_price_1 <= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick卖一价，低于买入委托价格，之前委托可能丢失，强制撤单")
            else:
                if self.last_tick.bid_price_1 >= self.price:
                    self.cancel_order(self.vt_orderid)
                    self.vt_orderid = ""
                    self.write_log(u"最新Tick买一价，高于卖出委托价格，之前委托可能丢失，强制撤单")

        self.put_variables_event()
```

&nbsp;

### 狙击手算法

- 监控最新tick推送的行情，发现好的价格立刻报价成交。
- 买入情况：最新Tick卖一价低于目标价格时，发出委托，委托数量在剩余委托量与卖一量中取最小值。
- 卖出情况：最新Tick买一价高于目标价格时，发出委托，委托数量在剩余委托量与买一量中取最小值。

```
    def on_tick(self, tick: TickData):
        """"""
        if self.vt_orderid:
            self.cancel_all()
            return

        if self.direction == Direction.LONG:
            if tick.ask_price_1 <= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.ask_volume_1)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )
        else:
            if tick.bid_price_1 >= self.price:
                order_volume = self.volume - self.traded
                order_volume = min(order_volume, tick.bid_volume_1)

                self.vt_orderid = self.sell(
                    self.vt_symbol,
                    self.price,
                    order_volume,
                    offset=self.offset
                )

        self.put_variables_event()
```

&nbsp;

### 条件委托算法

- 监控最新tick推送的行情，发现行情突破立刻报价成交。
- 买入情况：Tick最新价高于目标价格时，发出委托，委托价为目标价格加上超价。
- 卖出情况：Tick最新价低于目标价格时，发出委托，委托价为目标价格减去超价。

```
    def on_tick(self, tick: TickData):
        """"""
        if self.vt_orderid:
            return

        if self.direction == Direction.LONG:
            if tick.last_price >= self.stop_price:
                price = self.stop_price + self.price_add

                if tick.limit_up:
                    price = min(price, tick.limit_up)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    price,
                    self.volume,
                    offset=self.offset
                )
                self.write_log(f"停止单已触发，代码：{self.vt_symbol}，方向：{self.direction}, 价格：{self.stop_price}，数量：{self.volume}，开平：{self.offset}")                   

        else:
            if tick.last_price <= self.stop_price:
                price = self.stop_price - self.price_add
                
                if tick.limit_down:
                    price = max(price, tick.limit_down)

                self.vt_orderid = self.buy(
                    self.vt_symbol,
                    price,
                    self.volume,
                    offset=self.offset
                )
                self.write_log(f"停止单已触发，代码：{self.vt_symbol}，方向：{self.direction}, 价格：{self.stop_price}，数量：{self.volume}，开平：{self.offset}") 

        self.put_variables_event()
```

&nbsp;

### 最优限价算法

- 监控最新tick推送的行情，发现好的价格立刻报价成交。
- 买入情况：先检查撤单：最新Tick买一价不等于目标价格时，执行撤单；若无活动委托，发出委托：委托价格为最新Tick买一价，委托数量为剩余委托量与随机量之间取最小值。
- 卖出情况：先检查撤单：最新Tick卖一价不等于目标价格时，执行撤单；若无活动委托，发出委托：委托价格为最新Tick卖一价，委托数量为剩余委托量与随机量之间取最小值。

```
    def on_tick(self, tick: TickData):
        """"""
        self.last_tick = tick

        if self.direction == Direction.LONG:
            if not self.vt_orderid:
                self.buy_best_limit()
            elif self.order_price != self.last_tick.bid_price_1:
                self.cancel_all()
        else:
            if not self.vt_orderid:
                self.sell_best_limit()
            elif self.order_price != self.last_tick.ask_price_1:
                self.cancel_all()

        self.put_variables_event()

    def buy_best_limit(self):
        """"""
        volume_left = self.volume - self.traded

        rand_volume = self.generate_rand_volume()
        order_volume = min(rand_volume, volume_left)

        self.order_price = self.last_tick.bid_price_1
        self.vt_orderid = self.buy(
            self.vt_symbol,
            self.order_price,
            order_volume,
            offset=self.offset
        )        

    def sell_best_limit(self):
        """"""
        volume_left = self.volume - self.traded

        rand_volume = self.generate_rand_volume()
        order_volume = min(rand_volume, volume_left)

        self.order_price = self.last_tick.ask_price_1
        self.vt_orderid = self.sell(
            self.vt_symbol,
            self.order_price,
            order_volume,
            offset=self.offset
        ) 
```

&nbsp;

### 网格算法

- 每隔一段时间检查委托情况，若有委托则先清空。
- 基于用户设置的价格步进（即网格）计算目标距离，目标距离=（目标价格- 当前价格）/价格步进，故当前价格低于目标价格，目标距离为正，方向为买入；当前价格高于目标价格，目标距离为负，方向为卖出。（高抛低吸概念）
- 计算目标仓位，目标仓位= 取整后的目标距离 * 委托数量步进。注意卖卖方向取整的方式是不同的：买入方向要向下取整math.floor()，如目标距离为1.6，取1；卖出方向要向上取整，如目标距离为-1.6，取-1。
- 计算具体委托仓位：若目标买入仓位大于当前仓位，执行买入操作；若目标卖出仓位低于当前仓位，执行卖出操作。
- 为了能够快速成交，买入情况是基于ask price计算，卖出情况是基于bid price计算。


```
    def on_timer(self):
        """"""
        if not self.last_tick:
            return

        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return        
        self.timer_count = 0
        
        if self.vt_orderid:
            self.cancel_all()        

        # Calculate target volume to buy
        target_buy_distance = (self.price - self.last_tick.ask_price_1) / self.step_price
        target_buy_position = math.floor(target_buy_distance) * self.step_volume
        target_buy_volume = target_buy_position - self.pos

        # Buy when price dropping
        if target_buy_volume > 0:
            self.vt_orderid = self.buy(
                self.vt_symbol,
                self.last_tick.ask_price_1,
                min(target_buy_volume, self.last_tick.ask_volume_1)
            )
        
        # Calculate target volume to sell
        target_sell_distance = (self.price - self.last_tick.bid_price_1) / self.step_price
        target_sell_position = math.ceil(target_sell_distance) * self.step_volume
        target_sell_volume = self.pos - target_sell_position

        # Sell when price rising
        if target_sell_volume > 0:
            self.vt_orderid = self.sell(
                self.vt_symbol,
                self.last_tick.bid_price_1,
                min(target_sell_volume, self.last_tick.bid_volume_1)
            )
```

&nbsp;

### 套利算法

- 每隔一段时间检查委托情况，若有委托则先清空；若主动腿还持有净持仓，通过被动腿成交来对冲。
- 计算价差spread_bid_price 和 spread_ask_price, 以及对应的委托数量
- 卖出情况：主动腿价格相对被动腿上涨，其价差spread_bid_price大于spread_up时，触发买入信号
- 买入情况：主动腿价格相对被动腿下跌，其价差spread_ask_price小于 - spread_down(spread_down默认设置为正数)时，触发卖出信号
- 在买卖信号判断加入最大持仓的限制，其作用是避免持仓过多导致保证金不足或者直接被交易所惩罚性强平；而且随着价差持续波动，主动腿持仓可以从0 -> 10 -> 0 -> -10 -> 0,从而实现平仓获利离场。


```
    def on_timer(self):
        """"""
        self.timer_count += 1
        if self.timer_count < self.interval:
            self.put_variables_event()
            return
        self.timer_count = 0

        # Cancel all active orders before moving on
        if self.active_vt_orderid or self.passive_vt_orderid:
            self.write_log("有未成交委托，执行撤单")
            self.cancel_all()
            return
        
        # Make sure that active leg is fully hedged by passive leg
        if (self.active_pos + self.passive_pos) != 0:
            self.write_log("主动腿和被动腿数量不一致，执行对冲")
            self.hedge()
            return
      
        # Make sure  that tick data of both leg are available
        active_tick = self.get_tick(self.active_vt_symbol)
        passive_tick = self.get_tick(self.passive_vt_symbol)
        if not active_tick or not passive_tick:
            self.write_log("获取某条套利腿的行情失败，无法交易")
            return

        # Calculate spread
        spread_bid_price = active_tick.bid_price_1 - passive_tick.ask_price_1
        spread_ask_price = active_tick.ask_price_1 - passive_tick.bid_price_1

        spread_bid_volume = min(active_tick.bid_volume_1, passive_tick.ask_volume_1)
        spread_ask_volume = min(active_tick.ask_volume_1, passive_tick.bid_volume_1)

        msg = f"价差盘口，买：{spred_bid_price} ({spred_bid_volume}), 卖：{spred_ask_price} ({spred_ask_volume})"
        self.write_log(msg)

        # Sell condition
        if spread_bid_price > self.spread_up:
            self.write_log("套利价差超过上限，满足做空条件")

            if self.active_pos > -self.max_pos:
                self.write_log("当前持仓小于最大持仓限制，执行卖出操作")

                volume = min(spread_bid_volume,
                             self.active_pos + self.max_pos)

                self.active_vt_orderid = self.sell(
                    self.active_vt_symbol,
                    active_tick.bid_price_1,
                    volume
                )

        # Buy condition
        elif spread_ask_price < -self.spread_down:
            self.write_log("套利价差超过下限，满足做多条件")

            if self.active_pos < self.max_pos:
                self.write_log("当前持仓小于最大持仓限制，执行买入操作")

                volume = min(spread_ask_volume,
                             self.max_pos - self.active_pos)

                self.active_vt_orderid = self.buy(
                    self.active_vt_symbol,
                    active_tick.ask_price_1,
                    volume
                )

        # Update GUI
        self.put_variables_event()
    
    def hedge(self):
        """"""
        tick = self.get_tick(self.passive_vt_symbol)
        volume = -self.active_pos - self.passive_pos

        if volume > 0:
            self.passive_vt_orderid = self.buy(
                self.passive_vt_symbol,
                tick.ask_price_1,
                volume
            )
        elif volume < 0:
            self.passive_vt_orderid = self.sell(
                self.passive_vt_symbol,
                tick.bid_price_1,
                abs(volume)
            )

    def on_trade(self, trade: TradeData):
        """"""
        # Update pos
        if trade.direction == Direction.LONG:
            if trade.vt_symbol == self.active_vt_symbol:
                self.active_pos += trade.volume
            else:
                self.passive_pos += trade.volume
        else:
            if trade.vt_symbol == self.active_vt_symbol:
                self.active_pos -= trade.volume
            else:
                self.passive_pos -= trade.volume

        # Hedge if active symbol traded
        if trade.vt_symbol == self.active_vt_symbol:
            self.write_log("收到主动腿成交回报，执行对冲")
            self.hedge()

        self.put_variables_event()

```
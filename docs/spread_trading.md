# 价差交易模块

价差交易与CTA有比较大的不同：

- CTA主要是针对单标的品种，盈利主要靠肥尾部分，特点是低胜率高盈亏比。

- 价差交易针对的是关联程度高的品种，实现方式可以是期现套利、跨期套利、跨市套利、跨品种套利。从另一个角度来看，价差交易的标的物是价差，价差的统计特征是均值回归，即围绕某个数值上下波动。因此出现黑天鹅的概率要远远少于单标的品种，其盈利主要靠尖峰部分。

&nbsp;

根据品种相关程度不同，价差交易所适用的领域也有所不同：

- 相关程度100%，也就是说交易的是同一样商品，区别仅仅是所处的市场不同。举个例子：比特币在火币的价格是8500美元，在币安是8495美元，这样完全可以从币安以8495美元买入，并且在火币以8500美元卖出，赚取5美元的无风险利润。因此类似这种无风险套利，拼的是低延时，属于高频交易领域。需要投入大量精力在托管机房、海底光缆、网卡设计等方面。

- 相关程度高的品种，如期货的近期合约和远期合约，可以做日内交易。简单的可以设置固定阈值，如价差<买入阈值，买入价差（买入主动腿，并且卖出被动退完成对冲）；价差>卖出阈值，卖出价差（卖出主动腿，并且买入被动腿完成对冲）。若价差并不严格的遵守均值回归；或者在大周期上价差发生较大的偏离，但是在小周期上围绕着均值上下波动；这两类可以使用布林带通道实现套利，如价差>布林带通道上轨，卖出价差；价差<布林带下轨，买入价差。

- 相关程度价高品种，如产业链相关的期货品种，可以做基本面套利。基本面套利更要求投资者主动挖掘有用信息，如参与实地调研，或者使用无人机加上图形识别技术监控品种的实际库存状况；通过对基本面信息的分析与处理，然后在单个方向去交易价差，即在高位卖出价差，在均值位平仓离场。由于价差基本面套利的持仓周期可以从几周到几个月，所以对执行的要求不高，更偏重于基本面信息的挖掘和处理。

&nbsp;

## 模块构成

价差交易模块主要由6部分构成，如下图：

- base：定义了价差交易模块中用到的一些基础设置，如主动腿/被动腿合约数据结构，以及由主动腿和被动腿合成的价差数据结构。

- template：包含了价差算法模板和价差交易策略模板。

- strategies: 官方提供的价差交易策略示例，如basic_spread_strategy实现了只要设置好固定的阈值（buy、sell、short、cover），即可实现自动化交易。

- algo: 定义了主动对价成交算法：为了规避交易所设置挂撤单次数的上限，通用做法是牺牲点差来保证成交率。并且价差交易也要求在主动腿完成交易后，被动腿要立刻跟上完成对冲。

- engine：定义了父类价差引擎，并且继承于父类的价差数据引擎、价差算法引擎、价差策略引擎。

- ui：基于PyQt5的GUI图形应用。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/seis_elementos.png)


&nbsp;

## 基本操作

### 打开价差交易界面

打开VN Trader，先连接上交易接口，如BITMEX；然后在菜单栏中点击【功能】->【价差交易】进入价差交易界面。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/inicio.png)

&nbsp;

总体来说，价差交易界面可分成2部分：

- 交易部分：在创建好价差合约后，可以调用价差策略实现自动交易，也可以手动交易来调整仓位。
- 监控部分：可以查看实时价差合约行情信息，价差策略和价差算法执行情况，日志组件也会输出相关信息。

&nbsp;

### 创建价差合约

1） 寻找可组成价差的合约：

- 回到VN Trader，在菜单栏中点击【帮助】-> 【查询合约】按钮，弹出合约查询界面;
- 在界面中找到我们用于价差交易的合约;
- 在BITMEX的示例中，我们主要通过比特币期货的跨期套利来展示，即交易XBTUSD（比特币期货永续合约）和XBTZ19（比特币期货19年12月到期合约）。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/future_contracto.png)

&nbsp;

2） 构建价差合约

- 点击【价差创建】按钮，会弹出创建价差界面；
- 在界面中，【价差名称】指的是用户定义的价差合约名称；
- 【主动腿代码】是在下面的【腿】选项中，通过【本地代码】来找到的主动腿。一般来说，价差交易原则上是主动腿完成交易后，立刻用被动腿进行对冲，故主动腿一般选择较为不活跃的合约，价格乘数和交易乘数均为正；被动腿一般选择较为活跃的合约，价格乘数和交易乘数均为负；
- 【腿】包含构建价差合约的主动腿与被动腿，它们由【本地代码】，【价格乘数】，【交易乘数】组成；
- 在BITMEX的比特币期货跨期套利示例中，其价格乘数和交易乘数均为1：1，即价差= XBTZ19 - XBTUSD；买入1手价差等于买入1手XBTZ19，同时卖出1手XBTUSD完成对冲。
- 设置好价差合约的参数后，点击下方的【创建价差】按钮。


注意：在多条腿并且期货合约规模不等时，构建价差会相对困难一些，如构建虚拟钢厂套利所用到的价差合约：

- 螺纹钢生产技艺是16吨铁矿石加上5吨焦炭练成10吨螺纹钢。
- 基于价格乘数的价差spread = 1* RB - 1.6\*I  - 0.5\*O。
- 但是由于螺纹是10吨/手，铁矿石和焦炭都是100吨/手，所以他们交易乘数是1：10：10；
- 故基于最大公约数规则，其实际交易手数关系是每买入100手螺纹钢（1000吨），需要卖出16手铁矿石（1600吨）和5手焦炭（500吨）完成对冲。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/contruction_spread_contracto.png)

&nbsp;

3）监控价差合约

- 创建好xbt价差后，【日志】组件会输出相关信息；
- 【价差】组件也实时价差合约的行情信息，价差合约由base.py的SpreadData类来负责；
- 在xbt价差的示例中，【买价】= 1\*XBTZ19买一价 - 1\*XBTUSD卖一价
- 【买量】= min（XBTZ19买一量，XBTUSD卖一量），取最小值用于保证各合约能均能成交；
- 【卖价】= 1\*XBTZ19卖一价 - 1\*XBTUSD买一价；
- 【卖量】= min（XBTZ19卖一量，XBTUSD买一量）；

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/resultado_contruction_spread_contracto.png)

&nbsp;

### 手动交易

假设当前xbt价差合约，买价为330和卖价为340；并且在大周期上，价差围绕0上下波动。

价差交易的盈利在于高抛低吸，即在低位，如-500买入xbt价差合约，在高位，如+500卖出xbt价差合约，平仓获利离场。由于不能立刻成交，所以其默认执行算法SpreadTaker（主动对价成交算法）会每隔一段时间进行委托操作：一般是以超价的限价单的形式发出委托。

下面通过2个例子，分别是发出委托立即成交和发出委托等待成交来具体介绍手动交易的操作情况：

1）发出委托立即成交

- 目标价差合约价格的350；
- 我们以超价5美金的形式，及355的价位发出买入限价单；
- 由于限价单（355）价位高于当前卖价（340），所以委托立刻成交。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano.png)

&nbsp;

2）成交委托监控

- 【日志】组件显示发出买入xbt价差合约的顺序是：发出XBTZ19多头委托 -> XBTZ19委托成交 -> 发出XBTUSD空头委托 -> XBTUSD委托成交。价差交易必须遵循的逻辑是主动腿成交后，才去用被动腿来对冲头寸，并且对冲必须尽可能及时。这也为什么一般被动腿选择较为活跃合约的原因。

- 【价差】组件显示买入1手xbt价差合约成交后，【净仓】从0变成1；实际上，VN Trader【持仓】组件显示，XBTZ19合约多头持仓1手，XBTUSD合约空头持仓1手。

- 【算法】组件显示本次委托SpreadTaker算法执行情况：成交数量1手，委托状态是完全成交。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/resultado_buy_en_mano.png)

&nbsp;

3）发出委托等待成交

- 以-500的价位发出限价买入指令，由于当前买价卖价分别位于330和340，所以委托状态是“未成交”。仅当卖价低于-500时，才出发该限价单，已超价5美金，即-495去主动成交。
- 【日志】组件显示本次算法即SpreadTaker_000004已经启动，但由于价格没有触发到目标价位，算法在循环读秒中处于等待状态；
- 【算法】组件显示其委托状态为"未成交"，要结束算法只需鼠标双击【SpreadTaker_000004】单元格即可。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano_no_trade.png)

&nbsp;

4）撤销委托

鼠标双击完【SpreadTaker_000004】单元格后，在【日志】组件可以看到算法已经停止，【算法】组件显示委托状态由“未成交”变成”已撤单“。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/buy_en_mano_cancel.png)

&nbsp;

### 自动交易

目前，vnpy官方只提供一个价差策略BasicSpreadStrategy，策略逻辑相对简单，即设置4个目标价位：

- 在价差合约的价格低位买入开仓（BUY），然后在接近均值时候卖出平仓（SELL）；
- 在合约价格高位卖出开仓（SHORT），然后在价格走低接近均值买入平仓（COVER）。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/dibujo_spread.png)

&nbsp;

BasicSpreadStrategy策略继承于SpreadStrategyTemplate，其策略逻辑主要在on_spread_data()函数上。执行逻辑是先检测仓位：

- 若无仓位，分别发出买入开仓和卖出开仓委托，然后检测若存在平仓委托，调用stop_algo()函数撤销；
- 若持有多头仓位，先发出卖出平仓委托，然后检测若存在买入开仓委托，撤单处理；
- 若持有空头仓位，先发出买入平仓委托，然后检测若存在卖出开仓委托，撤单处理。

```
    def on_spread_data(self):
        """
        Callback when spread price is updated.
        """
        self.spread_pos = self.get_spread_pos()

        # No position
        if not self.spread_pos:
            # Start open algos
            if not self.buy_algoid:
                self.buy_algoid = self.start_long_algo(
                    self.buy_price, self.max_pos, self.payup, self.interval
                )

            if not self.short_algoid:
                self.short_algoid = self.start_short_algo(
                    self.short_price, self.max_pos, self.payup, self.interval
                )

            # Stop close algos
            if self.sell_algoid:
                self.stop_algo(self.sell_algoid)

            if self.cover_algoid:
                self.stop_algo(self.cover_algoid)

        # Long position
        elif self.spread_pos > 0:
            # Start sell close algo
            if not self.sell_algoid:
                self.sell_algoid = self.start_short_algo(
                    self.sell_price, self.spread_pos, self.payup, self.interval
                )

            # Stop buy open algo
            if self.buy_algoid:
                self.stop_algo(self.buy_algoid)

        # Short position
        elif self.spread_pos < 0:
            # Start cover close algo
            if not self.cover_algoid:
                self.cover_algoid = self.start_long_algo(
                    self.cover_price, abs(
                        self.spread_pos), self.payup, self.interval
                )

            # Stop short open algo
            if self.short_algoid:
                self.stop_algo(self.short_algoid)

        self.put_event()
```

由此可见，BasicSpreadStrategy策略逻辑是基于预先设置好的阈值来发出委托，只能处理相对简单的均值回归情况，若价差均值并不是围绕某个固定数值波动，或者它能够持续走出趋势，就需要更加复杂的策略，如价差的布林带策略等等。这些更加个性化的策略，用户可以基于SpreadStrategyTemplate策略模板自己实现。

现在展示价差交易模块，如何基于现有策略去创建策略实例来实现自动交易。由于其用法与CTA策略模块一样，故用户迁移成交较低。

1）添加策略实例

- 先选择使用的策略：BasicSpreadStrategy；
- 点击【添加策略】按钮，在弹出的界面中写入相关参数；
- 【strategy_name】为用户自定义的策略实例名称，这里是xbt_arb；
- 【spread_name】为用于交易的价差合约，这里是xbt；
- 【buy_price】为买入开仓阈值，这里是-500，即当价格跌破-500时，执行委托；
- 【sell_price】为卖出平仓阈值，这里是-200，即当价格回升到-200时，执行委托；
- 【short_price】为卖出开仓阈值，这里是500，即当价格上涨到500时，执行委托；
- 【cover_price】为买入平仓阈值，这里是200，即当价格下跌到200时，执行委托；
- 【max_pos】为主动腿委托数量；
- 【payup】为超价的数值;
- 【interval】为时间间隔，即每隔一段时间，会发出委托；
- 最后，点击【添加】按钮完成策略实例的创建。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/add_strategy.png)

&nbsp;

2）启动策略

- 创建好策略实例后，在【策略】组件会显示该策略；
- 依次点击【初始化】和【启动】按钮后，在【日志】组件中可以看到相关信息的输出；
- 【算法】组件显示，xbt_arb策略调用SpreadTaker算法，分别在-500和500的位子上挂上买入和卖出委托；
- 由于实际价格没有达到这2个阈值，故委托一直挂着，其委托状态为"未成交"。

![](https://vnpy-community.oss-cn-shanghai.aliyuncs.com/forum_experience/yazhang/spread_trading/start_strategy.png)

&nbsp;

最后，若要停止策略，点击【停止】按钮即可；【编辑】按钮用于修改策略参数；【移除】按钮用于移除该策略。

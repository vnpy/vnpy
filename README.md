# By Traders, For Traders.

vn.py网站  http://www.vnpy.cn/
vn.py LOGO
![vn.py-logo](http://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png)
![vn.py-site]( https://pic2.zhimg.com/80/v2-c6e03a3dbbc163c07dd8876378b1d951_hd.jpg)

### vn.py python框架简介

vn.py (http://www.vnpy.cn) 是基于Python的开源量化交易系统开发框架，起源于中国国内私募基金的自主交易系统。2015年1月项目正式在Github发布，在开源社区数年持续不断的贡献下，已经从早期的交易API接口封装，一步步成长为一套多市场多接口的量化交易平台。随着量化交易行业业内关注度的上升，用户群体也日渐多样化，包括：高校研究机构、专业个人投资者、私募基金、期货资管、证券自营和资管等等。
vn.py由于属于纯Python架构不适合搭建多账户系统，因为Python适合数据处理，但不适合多账户的并发。如需要多账户，消除原始VN.PY性能架构缺陷，建议采用资管系统来实现。
期货资管系统推荐酷操盘手系列 http://www.kucps.com/  虽然是商业化产品，但是是可以获得免费使用的。

### 对vn.py和量化交易新手的建议：
1.Python 适合用于快速开发，解释性语言导致了运行效率比较低，但是开发速度相对于其他语言却很高。当然Python做数据分析的效率比较高，但是做底层会下降一个数量级的原因，所以尽可能建议用成熟的资管系统去实现多账户。目前虚拟币市场比较混乱，厂商的API水平参差不齐，而A股禁止使用资管系统，外盘相对而言波动小是一个更成熟的市场，国内的期货的API是最成熟和完善的，那么期货的资管也很丰富，包括了信管家、融航、酷操盘手等。

2.因为搭建整个量化平台需要涉及很多，包括数据处理，策略开发，底层搭建，而这些工作在私募基金是由一个团队去完成的，如果是一个爱好者自己做怎么的也得3-5年吧。所以给出的建议是，尽可能的将精力放在策略开发上，对底层和框架可以拿来主义。

3.对一些人工智能库该怎么用，对大多数程序员来说也只是学会调用，能做到调参的已经是比较高的水平了。若想真正做到精通人工智能算法，对程序员也不是一个简单的工作，更不要说一般爱好者了，人工智能算法需要的是优秀的算法工程师 ， 要熟练的掌握高等数学、线性代数、离散数学、组合数学、矩阵论、概率统计等数学课程，数据结构 （树、链表、矩阵、图）等各种典型的数据结构以及常用的查找和排序算法（比如冒泡排序、快速排序、二分查找、希尔排序等，熟悉各自算法的时间复杂度）。对于通用型的算法思想，比如递推、分治、贪心、递归、动态规划等算法策略要熟记于心并能灵活运用。要做好人工智能算法这一些都离不开深厚的数学功底。。
所以所以对一般量化交易爱好者而言，一上来不要追求人工智能去开发策略。

4.vn.py python框架也在不断进化，vn.py目前最大的问题是性能问题，相信未来还有更好的框架出现，建议爱好者将精力方在策略开发上，策略相比平台则是更保值的东西。


---

### vn.py python框架项目内容

1. 全功能量化交易平台vn.py（vnpy.trader），整合了多种交易接口，并针对具体策略算法和功能开发提供了简洁易用的API，用于快速构建交易员所需的量化交易应用。

    * 覆盖国内外所有交易品种（期货、股票、外汇、期权、外盘、数字货币、CFD）等交易接口API：

        * 国内市场

            * CTP(ctpGateway)
            * 飞马(femasGateway)
            * 金仕达黄金(ksgoldGateway)
            * 金仕达期权(ksotpGateway)
	    * 中信证券期权(cshshlpGateway)
            * 飞鼠(sgitGateway)
            * 中泰证券XTP(xtpGateway)
            * Wind行情(windGateway)
            * 飞创(xspeedGateway)
            * 飞创证券(secGateway)
            * QDP(qdpGateway)
	    
        * 海外市场

            * 富途证券(futuGateway)
            * 上海直达期货(shzdGateway)
            * Interactive Brokers(ibGateway)
            * 福汇(fxcmGateway)


        * 数字货币
            * 币安(binanceGateway)
	    * FCoin (fcoinGateway)
            * BigOne (bigoneGateway)
	    * OKEX(okexGateway)
            * OKEX合约(okexfGateway)
            * 火币(huobiGateway)
            * BitMEX (bitmexGateway)
            * Bitfinex (bitfinexGateway)
            * Coinbase Pro (coinbaseGateway)
            * LBank(lbankGateway)
            * CCXT (ccxtGateway)


	    
### 其他量化交易网站，和支持VN.PY扩展功能
 
    
[酷操盘手资管软件、酷操盘手跟单软件系列]  http://www.kucps.com/
         
[行情数据免费下载]  http://www.mdshare.cn/

[量化资源导航]  http://www.pythonpai.cn

[量化交易社区]  http://www.pythonpai.com
    
[A股交易工具] http://www.quicklib.net

    * 经过开源社区大量用户实盘检验，做到开箱即用的各类量化策略交易应用（包括逻辑层和界面层）：
    
        * CtaStrategy：CTA策略引擎模块，在保持易用性的同时，允许用户针对CTA类策略运行过程中委托的报撤行为进行细粒度控制（降低交易滑点、实现高频策略）

        * SpreadTrading：价差交易模块，根据用户的配置自动实现价差组合的深度行情以及持仓变化计算，同时内置的交易算法SniperAlgo可以满足大部分到价成交策略的需求，用户也可以基于AlgoTemplate开发更复杂的价差算法

        * OptionMaster：期权交易模块，强大的期权投资组合管理功能，结合基于Cython开发的高效期权定价模型，支持毫秒级别的整体希腊值持仓风险计算，用户可以基于期权交易引擎OmEngine快速开发各类复杂期权交易应用

        * AlgoTrading：算法交易模块，提供多种常用的智能交易算法：TWAP、Sniper、BestLimit、Iceberg、Arbitrage等等，支持数据库配置保存、CSV文件加载启动以及RPC跨进程算法交易服务

        * TradeCopy：复制交易模块，用户可以通过发布者Provider进程来对外提供交易策略信号（手动、策略均可），订阅者Subscriber进程根据收到的信号自动执行同步交易，简洁快速得实现一拖多账户交易功能

        * RiskManager：事前风控模块，负责在交易系统将任何交易请求发出到柜台前的一系列标准检查操作，支持用户自定义风控规则的扩展
	
	* RpcService：RPC跨进程调用服务，基于MainEngineProxy组件，用户可以如同开发单一进程应用搬开发多进程架构的复杂交易应用

        * RtdService：EXCEL RTD服务组件，通过pyxll模块提供EXCEL表格系统对VN Trader系统内所有数据的访问

        * DataRecorder：实盘行情记录，支持Tick和K线数据的落地，用于策略开发回测以及实盘运行初始化



2. Python交易API接口封装（vnpy.api），提供上述交易接口的底层对接实现

3. 简洁易用的事件驱动引擎（vnpy.event），作为事件驱动型交易程序的核心

4. 支持服务器端数据推送的RPC框架（vnpy.rpc），用于实现多进程分布式架构的交易系统

5. 数据相关的API接口（vnpy.data），用于构建和更新历史行情数据库，目前包括：

    * 上海中期历史行情服务（shcifco）

6. 关于vn.py项目的应用演示（examples），对于新手而言可以从这里开始学习vn.py项目的使用方式

7. vn.py项目的Docker镜像（docker）：

    * web docker，在Docker中启动基于Web交易的交易服务器WebTrader，在浏览器中实现CTA策略的运维操作

    * vnc docker，内嵌了完整的vn.py图形化运行环境（Linux），并通过VNC Server对外提供虚拟桌面访问

9. [社区论坛] http://www.vnpy.cn ，内容包括vn.py项目的开发教程和Python在量化交易领域的应用研究等内容

10. 官方交流QQ群262656087，管理严格（定期清除长期潜水的成员），入群费将捐赠给vn.py社区基金

---
### 环境准备

**Windows**

推荐使用Windows环境一键安装脚本init.bat，打开cmd后运行即可自动完成以下环境和vn.py框架的下载安装工作。若由于网络不稳定的原因，导致某些步骤安装耗时过长而失败，可以配置好VPN后，手动在cmd中执行失败的命令继续完成安装。

1. 支持的操作系统：Windows 7/8/10/Server 2008
2. 安装[MongoDB](https://www.mongodb.org/downloads#production)，并[将MongoDB配置为系统服务](https://docs.mongodb.com/manual/tutorial/install-mongodb-on-windows/#configure-a-windows-service-for-mongodb-community-edition)
3. 安装[Anaconda 5.2.0](http://www.continuum.io/downloads)，**注意必须是Python 2.7 32位版本**
4. 安装[Visual C++ Redistributable Packages for VS2013 x86版本](https://support.microsoft.com/en-us/help/3138367/update-for-visual-c-2013-and-visual-c-redistributable-package)

**Ubuntu**

请参考项目wiki中的[教程] https://github.com/wdgwz/vnpy/wiki/Ubuntu%E7%8E%AF%E5%A2%83%E5%AE%89%E8%A3%85

---
### vn.py python框架项目安装

在[这里]  https://github.com/wdgwz/vnpy/releases 下载最新版本，解压后:
* Ubuntu：在Terminal中运行bash install.sh自动安装
* Windows：双击运行install.bat自动安装


**关于TA-Lib安装**

Ubuntu上安装到talib时若遭遇'Permission denied'错误，请在install.sh运行完成后，在Terminal中输入以下命令安装：

```
sudo /home/vnpy/anaconda2/bin/conda install -c quantopian ta-lib=0.4.9
```

其中"/home/vnpy/anaconda2/"是你的Anaconda安装路径。


---
### Quick Start 


1. 在[SimNow](http://simnow.com.cn/)注册CTP仿真账号，记下你的**账号、密码、经纪商编号**，然后下载快期查询你的**交易和行情服务器地址**

2. 找到vn.py应用示例目录examples，打开examples\VN Trader\CTP_connect.json，修改账号、密码、服务器等为上一步注册完成后你的信息（注意使用专门的编程编辑器，如Sublime Text等，防止json编码出错）

3. 找到VN Trader的启动入口run.py，并双击运行（若无法双击，则在当前目录按住Shift点鼠标右键，打开cmd输入python run.py运行），run.py内容如下：

```
# encoding: UTF-8

import sys
reload(sys)

# vn.trader模块
from vnpy.trader.uiQt import createQApp
from vnpy.trader.uiMainWindow import MainWindow
from vnpy.event import EventEngine
from vnpy.trader.vtEngine import MainEngine


# 加载底层接口
from vnpy.trader.gateway import ctpGateway, ibGateway

# 加载上层应用
from vnpy.trader.app import (riskManager, ctaStrategy, 
                             spreadTrading, algoTrading)


#----------------------------------------------------------------------
def main():
    """主程序入口"""
    # 创建Qt应用对象
    qApp = createQApp()

    # 创建事件引擎
    ee = EventEngine()

    # 创建主引擎
    me = MainEngine(ee)

    # 添加交易接口
    me.addGateway(ctpGateway)
    me.addGateway(ibGateway)

    # 添加上层应用
    me.addApp(riskManager)
    me.addApp(ctaStrategy)
    me.addApp(spreadTrading)
    me.addApp(algoTrading)

    # 创建主窗口
    mw = MainWindow(me, ee)
    mw.showMaximized()

    # 在主线程中启动Qt事件循环
    sys.exit(qApp.exec_())


if __name__ == '__main__':
    main()

```

更多使用方法方法请参考examples下的其他目录。

---

### vn.py  用户文档

项目的最新文档请查看[Github Wiki]()，知乎专栏和官网文档已经落后于项目开发版本，建议只作为额外的参考资料。

https://github.com/wdgwz/vnpy/wiki

### 开发工具推荐
* [Visual Studio 2013](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)：这个就不多说了（作者编译API封装用的是2013版本）

* [WingIDE](http://wingware.com/)：非常好用的Python集成开发环境（好用度超过Pycharm）

* [Visual Studio Code](https://code.visualstudio.com/)：针对编程的文本编辑器，方便阅读项目中的Python、C++、Markdown文件



---
### 贡献代码

vn.py使用github托管其源代码，如果希望贡献代码请使用github的PR(Pull Request)的流程:

1. [创建 Issue]   https://github.com/wdgwz/vnpy/issues/new - 对于较大的改动(如新功能，大型重构等)最好先开issue讨论一下，较小的improvement(如文档改进，bugfix等)直接发PR即可

2. Fork [vn.py] https://github.com/wdgwz/vnpy - 点击右上角**Fork**按钮

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	* 如果你的fork已经过时，需要手动sync：[https://help.github.com/articles/syncing-a-fork/](https://help.github.com/articles/syncing-a-fork/)

4. 从**dev**创建你自己的feature branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改并将修改push到你的fork上

6. 创建从你的fork的$my_feature_branch分支到主项目的**dev**分支的[Pull Request] -  
[在此]https://github.com/wdgwz/vnpy/compare?expand=1点击**compare across forks**，选择需要的fork和branch创建PR

7. 等待review, 需要继续改进，或者被Merge!
 
 

先强调一下：**vn.py是开源项目，可以永久免费使用 ！！！**

 
VNPY原始作者：用Python的程序员
还有其他为VNPY做出贡献的其他作者

---
### License
MIT
该协议规定：只要你标记原始作者姓名，可以用于任何场合而没有任何限制

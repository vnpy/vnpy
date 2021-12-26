# By Traders, For Traders.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png"/>
</p>

💬 Want to read this in **english** ? Go [**here**](README_ENG.md)

<p align="center">
    <img src ="https://img.shields.io/badge/version-3.0.0.b-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux|macos-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.7-blue.svg" />
    <img src ="https://img.shields.io/github/workflow/status/vnpy/vnpy/Python%20application/master"/>
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

vn.py是一套基于Python的开源量化交易系统开发框架，在开源社区7年持续不断的贡献下一步步成长为全功能量化交易平台，自2015年正式发布以来已经积累了众多来自金融机构或相关领域的用户，包括私募基金、证券公司、期货公司等。

全新的《vn.py全实战进阶》系列在线课程，已经在官方微信公众号[**vnpy-community**]上线，覆盖CTA策略（已完成）、期权波动率交易（更新中）等内容。购买请扫描下方二维码关注后，点击菜单栏的【进阶课程】按钮即可：

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy_qr.jpg"/>
</p>

在使用vn.py进行二次开发（策略、模块等）的过程中有任何疑问，请查看[**vn.py项目文档**](https://www.vnpy.com/docs/cn/index.html)，如果无法解决请前往[**官方社区论坛**](https://www.vnpy.com/forum/)的【提问求助】板块寻求帮助，也欢迎在【经验分享】板块分享你的使用心得！

针对vn.py的金融机构用户，创建了一个专门的【vn.py机构用户群】（QQ群号：676499931），主要分享机构应用方面相关的问题，如：银行间市场接入、资管O32系统、分布式部署等内容。请注意本群只对金融机构用户开放，加群时请注明：姓名-机构-部门。

## 功能特点

1. 全功能量化交易平台（vnpy.trader），整合了多种交易接口，并针对具体策略算法和功能开发提供了简洁易用的API，用于快速构建交易员所需的量化交易应用。

2. 覆盖国内外所有交易品种的交易接口（vnpy.gateway）：

    * 国内市场

        * CTP（[ctp](https://www.github.com/vnpy/vnpy_ctp)）：国内期货、期权

        * CTP Mini（[mini](https://www.github.com/vnpy/vnpy_mini)）：国内期货、期权

        * CTP证券（[sopt](https://www.github.com/vnpy/vnpy_sopt)）：ETF期权

        * 飞马（[femas](https://www.github.com/vnpy/vnpy_femas)）：国内期货

        * 恒生UFT（[uft](https://www.github.com/vnpy/vnpy_uft)）：国内期货、ETF期权

        * 易盛（[esunny](https://www.github.com/vnpy/vnpy_esunny)）：国内期货、黄金TD

        * 顶点飞创（[sec](https://www.github.com/vnpy/vnpy_sec)）：ETF期权

        * 顶点HTS（[hts](https://www.github.com/vnpy/vnpy_hts)）：ETF期权

        * 南华NHTD（[nhtd](https://www.github.com/vnpy/vnpy_nhtd)）：国内期货、ETF期权

        * 中泰XTP（[xtp](https://www.github.com/vnpy/vnpy_xtp)）：国内证券（A股）、ETF期权

        * 华鑫奇点（[tora](https://www.github.com/vnpy/vnpy_tora)）：国内证券（A股）、ETF期权

        * 国泰君安（[hft](https://www.github.com/vnpy/vnpy_hft)）：国内证券（A股、两融）

        * 飞鼠（[sgit](https://www.github.com/vnpy/vnpy_sgit)）：黄金TD、国内期货

        * 金仕达黄金（[ksgold](https://www.github.com/vnpy/vnpy_ksgold)）：黄金TD

        * 融航（[rohon](https://www.github.com/vnpy/vnpy_rohon)）：期货资管

        * 中汇亿达（[comstar](https://www.github.com/vnpy/vnpy_comstar)）：银行间市场

        * TTS（[tts](https://www.github.com/vnpy/vnpy_tts)）：国内期货（仿真）

    * 海外市场

        * Interactive Brokers（[ib](https://www.github.com/vnpy/vnpy_ib)）：全球证券、期货、期权、贵金属等

        * 易盛9.0外盘（[tap](https://www.github.com/vnpy/vnpy_tap)）：全球期货

        * 直达期货（[da](https://www.github.com/vnpy/vnpy_da)）：全球期货

    * 特殊应用

        * RPC服务（[rpc](https://www.github.com/vnpy/vnpy_rpcservice)）：跨进程通讯接口，用于分布式架构

3. 开箱即用的各类量化策略交易应用（vnpy.app）：

    * [cta_strategy](https://www.github.com/vnpy/vnpy_ctastrategy)：CTA策略引擎模块，在保持易用性的同时，允许用户针对CTA类策略运行过程中委托的报撤行为进行细粒度控制（降低交易滑点、实现高频策略）

    * [cta_backtester](https://www.github.com/vnpy/vnpy_ctabacktester)：CTA策略回测模块，无需使用Jupyter Notebook，直接使用图形界面直接进行策略回测分析、参数优化等相关工作

    * [spread_trading](https://www.github.com/vnpy/vnpy_spreadtrading)：价差交易模块，支持自定义价差，实时计算价差行情和持仓，支持半自动价差算法交易以及全自动价差策略交易两种模式

    * [option_master](https://www.github.com/vnpy/vnpy_optionmaster)：期权交易模块，针对国内期权市场设计，支持多种期权定价模型、隐含波动率曲面计算、希腊值风险跟踪等功能

    * [portfolio_strategy](https://www.github.com/vnpy/vnpy_portfoliostrategy)：组合策略模块，面向同时交易多合约的量化策略（Alpha、期权套利等），提供历史数据回测和实盘自动交易功能

    * [algo_trading](https://www.github.com/vnpy/vnpy_algotrading)：算法交易模块，提供多种常用的智能交易算法：TWAP、Sniper、Iceberg、BestLimit等

    * [script_trader](https://www.github.com/vnpy/vnpy_scripttrader)：脚本策略模块，针对多标的组合类交易策略设计，同时也可以直接在命令行中实现REPL指令形式的交易，不支持回测功能

    * [paper_account](https://www.github.com/vnpy/vnpy_paperaccount)：本地仿真模块，纯本地化实现的仿真模拟交易功能，基于交易接口获取的实时行情进行委托撮合，提供委托成交推送以及持仓记录

    * [chart_wizard](https://www.github.com/vnpy/vnpy_chartwizard)：K线图表模块，基于RQData数据服务（期货）或者交易接口获取历史数据，并结合Tick推送显示实时行情变化

    * [portfolio_manager](https://www.github.com/vnpy/vnpy_portfoliomanager)：交易组合管理模块，以独立的策略交易组合（子账户）为基础，提供委托成交记录管理、交易仓位自动跟踪以及每日盈亏实时统计功能

    * [rpc_service](https://www.github.com/vnpy/vnpy_rpcservice)：RPC服务模块，允许将某一vn.py进程启动为服务端，作为统一的行情和交易路由通道，允许多客户端同时连接，实现多进程分布式系统

    * [data_manager](https://www.github.com/vnpy/vnpy_datamanager)：历史数据管理模块，通过树形目录查看数据库中已有的数据概况，选择任意时间段数据查看字段细节，支持CSV文件的数据导入和导出

    * [data_recorder](https://www.github.com/vnpy/vnpy_datarecorder)：行情记录模块，基于图形界面进行配置，根据需求实时录制Tick或者K线行情到数据库中，用于策略回测或者实盘初始化

    * [excel_rtd](https://www.github.com/vnpy/vnpy_excelrtd)：Excel RTD（Real Time Data）实时数据服务，基于pyxll模块实现在Excel中获取各类数据（行情、合约、持仓等）的实时推送更新

    * [risk_manager](https://www.github.com/vnpy/vnpy_riskmanager)：风险管理模块，提供包括交易流控、下单数量、活动委托、撤单总数等规则的统计和限制，有效实现前端风控功能

    * [web_trader](https://www.github.com/vnpy/vnpy_webtrader)：Web服务模块，针对B-S架构需求设计，实现了提供主动函数调用（REST）和被动数据推送（Websocket）的Web服务器

4. Python交易API接口封装（vnpy.api），提供上述交易接口的底层对接实现。

    * REST Client（[rest](https://www.github.com/vnpy/vnpy_rest)）：基于协程异步IO的高性能REST API客户端，采用事件消息循环的编程模型，支持高并发实时交易请求发送

    * Websocket Client（[websocket](https://www.github.com/vnpy/vnpy_websocket)）：基于协程异步IO的高性能Websocket API客户端，支持和REST Client共用事件循环并发运行，避免GIL带来的多线程性能损耗

5. 简洁易用的事件驱动引擎（vnpy.event），作为事件驱动型交易程序的核心。

6. 对接各类数据库的适配器接口：

    * SQL类

        * SQLite（[sqlite](https://www.github.com/vnpy/vnpy_sqlite)）：轻量级单文件数据库，无需安装和配置数据服务程序，vn.py的默认选项，适合入门新手用户

        * MySQL（[mysql](https://www.github.com/vnpy/vnpy_mysql)）：世界最流行的开源关系型数据库，文档资料极为丰富，且可替换其他高NewSQL兼容实现（如TiDB）

        * PostgreSQL（[postgresql](https://www.github.com/vnpy/vnpy_postgresql)）：特性更为丰富的开源关系型数据库，支持通过扩展插件来新增功能，只推荐熟手使用

    * NoSQL类

        * DolphinDB（[dolphindb](https://www.github.com/vnpy/vnpy_dolphindb)）：由浙江智臾科技有限公司研发的一款高性能分布式时序数据库，特别适用于对速度要求极高的低延时或实时性任务

        * Arctic（[arctic](https://www.github.com/vnpy/vnpy_arctic)）：由量化对冲基金Man AHL基于MongoDB开发的高性能金融时序数据库，采用了分块化储存、LZ4压缩等性能优化方案，实现比MongoDB更高的读写效率

        * MongoDB（[mongodb](https://www.github.com/vnpy/vnpy_mongodb)）：基于分布式文件储存（bson格式）的文档式数据库，内置的热数据内存缓存提供更快读写速度

        * InfluxDB（[influxdb](https://www.github.com/vnpy/vnpy_influxdb)）：针对TimeSeries Data专门设计的时序数据库，列式数据储存提供极高的读写效率和外围分析应用

        * LevelDB（[leveldb](https://www.github.com/vnpy/vnpy_leveldb)）：由Google推出的高性能Key/Value数据库，基于LSM算法实现进程内存储引擎，支持数十亿级别的海量数据

7. 对接各类数据服务的适配器接口：

    * 米筐RQData（[rqdata](https://www.github.com/vnpy/vnpy_rqdata)）：股票、期货、期权、基金、债券、黄金TD

    * 恒生UData（[udata](https://www.github.com/vnpy/vnpy_udata)）：股票、期货、期权

    * TuShare（[tushare](https://www.github.com/vnpy/vnpy_tushare)）：股票、期货、期权、基金

    * 万得Wind（[wind](https://www.github.com/vnpy/vnpy_wind)）：股票、期货、基金、债券

    * 天软Tinysoft（[tinysoft](https://www.github.com/vnpy/vnpy_tinysoft)）：股票、期货、基金、债券

    * 同花顺iFinD（[ifind](https://www.github.com/vnpy/vnpy_ifind)）：股票、期货、基金、债券

    * 天勤TQSDK（[tqsdk](https://www.github.com/vnpy/vnpy_tqsdk)）：期货

8. 跨进程通讯标准组件（vnpy.rpc），用于实现分布式部署的复杂交易系统。

9. Python高性能K线图表（vnpy.chart），支持大数据量图表显示以及实时数据更新功能。

10. [社区论坛](http://www.vnpy.com)和[知乎专栏](http://zhuanlan.zhihu.com/vn-py)，内容包括vn.py项目的开发教程和Python在量化交易领域的应用研究等内容。

11. 官方交流群262656087（QQ），管理严格（定期清除长期潜水的成员），入群费将捐赠给vn.py社区基金。

## 环境准备

* 推荐使用vn.py团队为量化交易专门打造的Python发行版[Veighna Studio-2.9.0](https://download.vnpy.com/vnstudio-2.9.0.exe)，内置了最新版的vn.py框架以及Veighna Station量化管理平台，无需手动安装
* 支持的系统版本：Windows 10以上/Windows Server 2016以上/Ubuntu 20.04 LTS以上
* 支持的Python版本：Python 3.7 64位（**注意必须是Python 3.7 64位版本**）

## 安装步骤

在[这里](https://github.com/vnpy/vnpy/releases)下载最新版本，解压后运行以下命令安装：

**Windows**

```
install.bat
```

**Ubuntu**

```
. install.sh
```

**Macos**

```
bash install_osx.sh
```

## 使用指南

1. 在[SimNow](http://www.simnow.com.cn/)注册CTP仿真账号，并在[该页面](http://www.simnow.com.cn/product.action)获取经纪商代码以及交易行情服务器地址。

2. 在[vn.py社区论坛](https://www.vnpy.com/forum/)注册获得Veighna Station账号密码（论坛账号密码即是）

3. 启动Veighna Station（安装Veighna Studio后会在桌面自动创建快捷方式），输入上一步的账号密码登录

4. 点击底部的**Veighna Trader**按钮，开始你的交易！！！

注意：

* 在Veighna Trader的运行过程中请勿关闭Veighna Station（会自动退出）

## 脚本运行

除了基于Veighna Station的图形化启动方式外，也可以在任意目录下创建run.py，写入以下示例代码：

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_backtester import CtaBacktesterApp

def main():
    """Start Veighna Trader"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    
    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()

if __name__ == "__main__":
    main()
```

在该目录下打开CMD（按住Shift->点击鼠标右键->在此处打开命令窗口/PowerShell）后运行下列命令启动Veighna Trader：

    python run.py

## 贡献代码

vn.py使用Github托管其源代码，如果希望贡献代码请使用github的PR（Pull Request）的流程:

1. [创建 Issue](https://github.com/vnpy/vnpy/issues/new) - 对于较大的改动（如新功能，大型重构等）最好先开issue讨论一下，较小的improvement（如文档改进，bufix等）直接发PR即可

2. Fork [vn.py](https://github.com/vnpy/vnpy) - 点击右上角**Fork**按钮

3. Clone你自己的fork: ```git clone https://github.com/$userid/vnpy.git```
	* 如果你的fork已经过时，需要手动sync：[同步方法](https://help.github.com/articles/syncing-a-fork/)

4. 从**dev**创建你自己的feature branch: ```git checkout -b $my_feature_branch dev```

5. 在$my_feature_branch上修改并将修改push到你的fork上

6. 创建从你的fork的$my_feature_branch分支到主项目的**dev**分支的[Pull Request] -  [在此](https://github.com/vnpy/vnpy/compare?expand=1)点击**compare across forks**，选择需要的fork和branch创建PR

7. 等待review, 需要继续改进，或者被Merge!

在提交代码的时候，请遵守以下规则，以提高代码质量：

  * 使用[flake8](https://pypi.org/project/flake8/)检查你的代码，确保没有error和warning。在项目根目录下运行```flake8```即可。

## 其他内容

* [获取帮助](https://github.com/vnpy/vnpy/blob/dev/.github/SUPPORT.md)
* [社区行为准则](https://github.com/vnpy/vnpy/blob/dev/.github/CODE_OF_CONDUCT.md)
* [Issue模板](https://github.com/vnpy/vnpy/blob/dev/.github/ISSUE_TEMPLATE.md)
* [PR模板](https://github.com/vnpy/vnpy/blob/dev/.github/PULL_REQUEST_TEMPLATE.md)

## 版权说明

MIT

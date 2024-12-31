# By Traders, For Traders.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-3.9.3-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux|macos-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.10|3.11|3.12-blue.svg" />
    <img src ="https://img.shields.io/github/actions/workflow/status/vnpy/vnpy/pythonapp.yml?branch=master"/>
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

VeighNa is a Python-based open source quantitative trading system development framework, officially released in January 2015, has grown step by step into a full-featured quantitative trading platform with 6 years of continuous contributions from the open source community, and currently has many users from domestic and international financial institutions, including: hedge funds, investment banks, futures brokers, university research institutions, proprietary trading companies, etc.

The new "VeighNa Full Practical Advance" online course series has been launched on the official WeChat account [**VeighNa开源量化**], covering CTA strategies (completed), options volatility trading (being updated) and more. To purchase, please scan the QR code below and click the [Advanced Course] button in the menu bar to.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy_qr.jpg"/>
</p>

If you have any questions about using VeighNa for secondary development (strategies, modules, etc.), please check the [**VeighNa Project Documentation**](https://www.vnpy.com/docs/cn/index.html). If you can't solve it, please go to the [Questions and Help] section of the [**Official Community Forum**](https://www.vnpy.com/forum/) forum for help, or share your experience in the [Experience Sharing] section!

For financial institution users of VeighNa, a special [VeighNa Institutional Users Group] (QQ group number: 676499931) has been created to share issues related to institutional applications, such as: interbank market access, asset management O32 system, distributed deployment, etc. Please note that this group is only open to financial institution users, please specify: Name - Institution - Department when joining the group.

## Functional Features

1. Full-featured quantitative trading platform (vnpy.trader) that integrates a variety of trading interfaces and provides simple and easy-to-use APIs for specific strategy algorithm and function development, for quickly building quantitative trading applications required by traders.

2. Trading interfaces (vnpy.gateway) covering all domestic and international trading varieties.

    * Domestic market

        * CTP ([ctp](https://www.github.com/vnpy/vnpy_ctp)): Domestic futures and options

        * CTP Mini ([mini](https://www.github.com/vnpy/vnpy_mini)): domestic futures, options

        * CTP Securities ([sopt](https://www.github.com/vnpy/vnpy_sopt)): ETF options

        * FEMAS ([femas](https://www.github.com/vnpy/vnpy_femas)): domestic futures

        * UFT ([uft](https://www.github.com/vnpy/vnpy_uft)): domestic futures, ETF options
        
        * Esunny ([esunny](https://www.github.com/vnpy/vnpy_esunny)): domestic futures, Gold TD

        * APEX XSpeed ([sec](https://www.github.com/vnpy/vnpy_sec)): ETF options

        * APEX HTS ([hts](https://www.github.com/vnpy/vnpy_hts)): ETF options

        * XTP ([xtp](https://www.github.com/vnpy/vnpy_xtp)): domestic securities (A shares), ETF options

        * TORA ([tora](https://www.github.com/vnpy/vnpy_tora)): domestic securities (A shares), ETF options

        * Guotai Junan ([hft](https://www.github.com/vnpy/vnpy_hft)): domestic securities (A shares)
        
        * SGIT ([sgit](https://www.github.com/vnpy/vnpy_sgit)): spot precious metal, domestic futures

        * KsGold ([ksgold](https://www.github.com/vnpy/vnpy_ksgold)): spot precious metal

        * Rohon ([rohon](https://www.github.com/vnpy/vnpy_rohon)): futures management

        * Jees ([jees](https://www.github.com/vnpy/vnpy_jees)): futures management

        * ComStar ([comstar](https://www.github.com/vnpy/vnpy_comstar)): interbank fixed-income market
        
        * TTS ([tts](https://www.github.com/vnpy/vnpy_tts)): domestic futures (simulation)

    * Overseas market

        * Interactive Brokers ([ib](https://www.github.com/vnpy/vnpy_ib)): global securities, futures, options, foreign exchange, etc.

        * Esunny 9.0 ([tap](https://www.github.com/vnpy/vnpy_tap)): global futures

        * Direct Futures ([da](https://www.github.com/vnpy/vnpy_da)): global futures

    * Special Applications

        * RPC service ([rpc](https://www.github.com/vnpy/vnpy_rpcservice)): inter-process communication interface for distributed architecture

3. Out-of-the-box trading applications for various quantitative strategies (vnpy.app).

    * [cta_strategy](https://www.github.com/vnpy/vnpy_ctastrategy): CTA strategy engine module, which allows users to perform fine-grained control over the withdrawal behavior of delegates during the operation of CTA-type strategies while maintaining ease of use (reducing trading slippage, implementing high-frequency strategies)

    * [cta_backtester](https://www.github.com/vnpy/vnpy_ctabacktester): CTA strategy backtester module, no need to use Jupyter Notebook, directly use the graphical interface to directly carry out strategy backtester analysis, parameter optimization and other related work

    * [spread_trading](https://www.github.com/vnpy/vnpy_spreadtrading): spread trading module, support custom spreads, real-time calculation of spread quotes and positions, support semi-automatic spread algorithm trading and fully automatic spread strategy trading two modes

    * [option_master](https://www.github.com/vnpy/vnpy_optionmaster): option trading module, designed for the domestic options market, supports a variety of option pricing models, implied volatility surface calculation, Greek value risk tracking and other functions

    * [portfolio_strategy](https://www.github.com/vnpy/vnpy_portfoliostrategy): portfolio strategy module, designed for trading multi-contract quantitative strategies (Alpha, option arbitrage, etc.) at the same time, providing historical data backtesting and live automatic trading functions

    * [algo_trading](https://www.github.com/vnpy/vnpy_algotrading): algorithm trading module, providing a variety of commonly used intelligent trading algorithms: TWAP, Sniper, Iceberg, BestLimit, etc.

    * [script_trader](https://www.github.com/vnpy/vnpy_scripttrader): script strategy module, designed for multi-standard portfolio trading strategies, also can be directly in the command line to achieve REPL instructions in the form of trading, does not support the backtest function

    * [paper_account](https://www.github.com/vnpy/vnpy_paperaccount): Simulation trading module, pure localization of simulation trading functions, based on the real-time quotes obtained from the trading interface for commission aggregation, providing commission transaction push and position records

    * [chart_wizard](https://www.github.com/vnpy/vnpy_chartwizard): K-line chart module, based on RQData data service (futures) or trading interface (digital currency) to obtain historical data, and combined with Tick push to display real-time market changes

    * [portfolio_manager](https://www.github.com/vnpy/vnpy_portfoliomanager): portfolio module, for all kinds of fundamental trading strategies, based on separate strategy sub-accounts, providing automatic tracking of trading positions and real-time profit and loss statistics

    * [rpc_service](https://www.github.com/vnpy/vnpy_rpcservice): RPC service module, allowing a VeighNa Trader process to be started as a server, serving as a unified routing channel for quotes and trades, allowing multiple clients to connect at the same time, realizing a multi-process distributed system

    * [data_manager](https://www.github.com/vnpy/vnpy_datamanager): Historical data management module, view the existing data in the database through the tree directory, select any time period data to view the field details, support CSV file data import and export

    * [data_recorder](https://www.github.com/vnpy/vnpy_datarecorder): Quotes recording module, based on the graphical interface for configuration, according to the demand for real-time recording Tick or K-line quotes to the database, for strategy backtesting or live initialization

    * [excel_rtd](https://www.github.com/vnpy/vnpy_excelrtd): Excel RTD (Real Time Data) real-time data service, based on pyxll module to achieve real-time push updates of various data (quotes, contracts, positions, etc.) in Excel

    * [risk_manager](https://www.github.com/vnpy/vnpy_riskmanager): risk management module, providing statistics and restrictions on rules including trade flow control, number of orders placed, active orders, total number of cancelled orders, etc., effectively realizing front-end risk control functions
    
    * [web_trader](https://www.github.com/vnpy/vnpy_webtrader): The web service module is designed according to the requirements of B-S architecture, and implements a web server that provides active function call (REST) and passive data push (WebSocket)


4. Python trading API interface package (vnpy.api), providing the underlying docking implementation of the above trading interface.
    
    * REST Client ([rest](https://www.github.com/vnpy/vnpy_rest)): The high-performance rest API client based on coroutine process asynchronous IO which adopts the programming model of event message cycle to support the sending of high concurrent real-time transaction requests
    
    * Websocket Client ([websocket](https://www.github.com/vnpy/vnpy_websocket)): The high-performance websocket API client based on coroutine process asynchronous IO supports which sharing event loops with REST Client to avoid multi-threaded performance loss caused by GIL


5. simple and easy-to-use event-driven engine (vnpy.event), which is the core of event-driven trading program

6. standardized management client (vnpy.database) interfacing with various databases.

    * SQL class

        * SQLite ([sqlite](https://www.github.com/vnpy/vnpy_sqlite)): lightweight single file database, no need to install and configure data service programs, default option of vnpy.py, suitable for novice users

        * MySQL ([mysql](https://www.github.com/vnpy/vnpy_mysql)): the world's most popular open source relational database, extremely rich documentation, and can replace other high NewSQL compatible implementations (such as TiDB)

        * PostgreSQL ([postgresql](https://www.github.com/vnpy/vnpy_postgresql)): more feature-rich open source relational database, support for new features through extension plug-ins, only recommended for skilled users

    * NoSQL classes

        * DolphinDB ([dolphindb](https://www.github.com/vnpy/vnpy_dolphindb)): A high-performance distributed temporal database developed by Zhejiang Zhiyu Technology Co., Ltd. is especially suitable for low latency or real-time tasks with high speed requirements
        
        * Arctic ([arctic](https://www.github.com/vnpy/vnpy_arctic)): The high-performance financial temporal database developed by quantitative hedge fund Man AHL based on mongodb which adopts performance optimization schemes such as partitioned storage and lz4 compression to achieve higher reading and writing efficiency than mongodb

        * MongoDB ([mongodb](https://www.github.com/vnpy/vnpy_mongodb)): non-relational database based on distributed file storage (bson format), built-in memory cache of hot data provides faster read and write speeds
        
        * InfluxDB ([influxdb](https://www.github.com/vnpy/vnpy_influxdb)): non-relational database specially designed for time-series data, columnar data storage provides high read/write efficiency and peripheral analysis applications
        
        * LevelDB ([leveldb](https://www.github.com/vnpy/vnpy_leveldb)): The high-performance key/value database launched by Google which realizes the process memory storage engine based on LSM algorithm, and supports billions of levels of massive data

7. Adapter interfaces for various data services:

    * RQData ([rqdata](https://www.github.com/vnpy/vnpy_rqdata)): stocks, futures, options, funds, bonds, gold spot
    
    * UData ([udata](https://www.github.com/vnpy/vnpy_udata)): stock, futures, options
    
    * TuShare ([tushare](https://www.github.com/vnpy/vnpy_tushare)): stocks, futures, options, funds
    
    * Wind ([wind](https://www.github.com/vnpy/vnpy_wind)): stocks, futures, options, funds, bonds
    
    * Tinysoft ([tinysoft](https://www.github.com/vnpy/vnpy_tinysoft)): stocks, futures, options, funds, bonds
    
    * iFinD ([ifind](https://www.github.com/vnpy/vnpy_ifind)): stocks, futures, options, funds, bonds
    
    * TQSDK ([tqsdk](https://www.github.com/vnpy/vnpy_tqsdk)): futures


8. Standard component for inter-process communication (vnpy.rpc) for implementing complex trading systems in distributed deployments

9. Python high-performance K-line charts (vnpy.chart), supporting large data volume chart display and real-time data update functions

10.  [Community Forum](http://www.vnpy.com) and [Zhihu Blog](http://zhuanlan.zhihu.com/vn-py), which include the development tutorial of VeighNa project and the research on the application of Python in the field of quantitative trading, etc.

11. The official communication group 262656087 (QQ), with strict management (regular purging of long-term diving members), and the membership fee will be donated to the VeighNa community fund.

## Environment preparation

* We recommend using the Python distribution [VeighNa Studio-2.9.0](https://download.vnpy.com/veighna-studio-2.9.0.exe), which is built with the latest version of VeighNa framework and VeighNa Station quantitative management platform, specifically created by the VeighNa team for quantitative trading. Manual installation
* Supported system versions: Windows 10 or above/Windows Server 2019 or above/Ubuntu 22.04 LTS
* Supported Python version: Python 3.10 64-bit or above

## Installation steps

Download the latest version from [here](https://github.com/vnpy/vnpy/releases), unzip it and run the following command to install it.

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

## User's Guide

1. Register a CTP Demo account at [SimNow](http://www.simnow.com.cn/) and get the broker code and the trading quotes server address at [this page](http://www.simnow.com.cn/product.action).

2. Register at [VeighNa community forum](https://www.vnpy.com/forum/) to get the VeighNa Station account password (the forum account password is)

3. Launch VeighNa Station (a shortcut will be created automatically on your desktop after installing VeighNa Studio), enter the account password from the previous step and login

4. Click on the **VeighNa Trader** button at the bottom and start your trading!

Attention.

* Please do not close VeighNa Station during the running of VeighNa Trader (it will exit automatically)
* For flexible configuration of quantitative trading application components, please use **VeighNa Trader**

## Script Run

In addition to the graphical start-up method based on VeighNa Station, you can also create run.py in any directory and write the following sample code.

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy_ctp import CtpGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp

def main():
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    
    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()

if __name__ == "__main__"。
    main()
```

Open CMD in that directory (hold Shift->click right mouse button->open command window/PowerShell here) and then run the following command to start VeighNa Trader.

    python run.py
    
## Contributing code

VeighNa uses Github to host its source code, if you wish to contribute code please use the PR (Pull Request) process of github:

1. [create Issue](https://github.com/vnpy/vnpy/issues/new) - For the larger changes (such as new features, large refactoring, etc.) it is best to first open an issue to discuss, and smaller improvements (such as document improvements, bugfixes, etc.) can be sent directly to PR

2. Fork [VeighNa](https://github.com/vnpy/vnpy) - Click the **Fork** button in the upper right corner

3. CloneYour own fork: ```git clone https://github.com/$userid/vnpy.git```

	* If your fork is out of date, you need to manually sync: [Synchronization method](https://help.github.com/articles/syncing-a-fork/)

4. Create your own feature branch from **dev**: ```git checkout -b $my_feature_branch dev```

5. Make changes on $my_feature_branch and push the changes to your fork

6. Create a [Pull Request] from your fork's $my_feature_branch branch to the main project's **dev** branch - [here](https://github.com/vnpy/vnpy/compare?expand=1) Click on **compare across forks** and select the required fork and branch to create the PR

7. Waiting for review, need to continue to improve, or be Merge!

When submitting code, please observe the following rules to improve the quality of the code:

  * Check your code with [flake8](https://pypi.org/project/flake8/) to make sure there are no errors and warnings. Just run ``flake8`` in the project root directory.


## Other content

* [Getting Help](https://github.com/vnpy/vnpy/blob/dev/.github/SUPPORT.md)
* [Community Conduct side](https://github.com/vnpy/vnpy/blob/dev/.github/CODE_OF_CONDUCT.md)
* [Issue templates](https://github.com/vnpy/vnpy/blob/dev/.github/ISSUE_TEMPLATE.md)
* [PR templates](https://github.com/vnpy/vnpy/blob/dev/.github/PULL_REQUEST_TEMPLATE.md)



## Copyright statement

MIT
  




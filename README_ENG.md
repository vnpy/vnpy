# By Traders, For Traders.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy-logo.png"/>
</p>

<p align="center">
    <img src ="https://img.shields.io/badge/version-2.0.7-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux|macos-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.7-blue.svg" />
    <img src ="https://img.shields.io/circleci/build/github/vnpy/vnpy?token=4d11df68295c8cc02a2bede46094991364190bbc"/>
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

vn.py is a Python-based open source quantitative trading system development framework, officially released in January 2015, has grown step by step into a full-featured quantitative trading platform with 6 years of continuous contributions from the open source community, and currently has more than 600 users from domestic and international financial institutions, including: private equity funds, securities proprietary and capital management, futures capital management and subsidiaries, university research institutions, proprietary trading companies, exchanges, Token Funds, etc.

The new 《vn.py Full Practical Advance》 online course series has been launched on the official WeChat public number [**vnpy-community**], covering CTA strategies (completed), options volatility trading (being updated) and more. To purchase, please scan the QR code below and click the 【Advanced Course】 button in the menu bar to.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy_qr.jpg"/>
</p>

If you have any questions about using vn.py for secondary development (strategies, modules, etc.), please check the [**vn.pyProject Documentation**](https://www.vnpy.com/docs/cn/index.html). If you can't solve it, please go to the 【Questions and Help】 section of the [**Official Community Forum**](https://www.vnpy.com/forum/) forum for help, or share your experience in the 【Experience Sharing】 section!

For financial institution users of vn.py, a special 【vn.py Institutional Users Group】 (QQ group number: 676499931) has been created to share issues related to institutional applications, such as: interbank market access, asset management O32 system, distributed deployment, etc. Please note that this group is for financial institution users only. Please note that this group is only open to financial institution users, please specify: Name - Institution - Department when adding the group.

## Functional Features

1. Full-featured quantitative trading platform (vnpy.trader) that integrates a variety of trading interfaces and provides simple and easy-to-use APIs for specific strategy algorithm and function development, for quickly building quantitative trading applications required by traders.

2. Trading interfaces (vnpy.gateway) covering all domestic and international trading varieties.

    * Domestic market

        * CTP (ctp): Domestic futures and options

        * CTP Mini (mini): domestic futures, options

        * CTP Securities (sopt): ETF options

        * Pegasus (femas): domestic futures

        * Hang Seng UFT (uft): domestic futures, ETF options

        * Feitron Securities (sec): ETF options

        * South China NHTD (nhtd): domestic futures, ETF options

        * Kuan Rui (oes): domestic securities (A shares), ETF options

        * Zhongtai XTP (xtp): Domestic securities (A shares), ETF options

        * Guotai Junan (gtja): Domestic securities (A shares)

        * Hang Seng Options (hsoption): ETF options

        * Huaxin Singularity (tora): Domestic securities (A shares), ETF options

        * Flying Rat (sgit): Gold TD, domestic futures

        * Jinshida Gold (ksgold): Gold TD

        * Rong Hang (rohon): futures management

        * Zhong Hui Yi Da (comstar): Interbank market

    * Overseas market

        * Futu Securities (futu): Hong Kong stocks, U.S. stocks

        * Interactive Brokers (ib): global securities, futures, options, foreign exchange, etc.

        * EaseUS 9.0 Foreign Exchange (tap): Global futures

        * Direct Futures (da): Global Futures

        * MetaTrader 5 (mt5): Forex, CFDs, Futures, Stocks

        * Alpaca (alpaca): US stocks (zero commission)

        * kasia investment (kasia): Hong Kong stocks

    * Digital currencies

        * BitMEX (bitmex): digital currency futures, options, perpetual contracts

        * Bybit (bybit): digital currency perpetual contracts

        * Binance (binance): digital currency spot

        * binance (binances): digital currency perpetual contracts

        * OKEX (okex): digital currency spot, futures, perpetual, options (V5 unified account)

        * Firecoin (huobi): digital currency spot

        * Firecoin Futures (huobif): digital currency futures

        * Firecoin perpetual (huobis): digital currency perpetual

        * Firecoin Options (huobio): digital currency options
        
        * Gate.io perpetual (gateios): digital currency perpetual contracts

        * Deribit (deribit), digital currency options, perpetual contracts        

        * Bitfinex (bitfinex): digital currency spot

        * Coinbase (coinbase): digital currency spot

        * Bitstamp (bitstamp): digital currency spot

        * 1Token (onetoken): digital currency brokerage (spot, futures)

    * Special Applications

        * RPC service (rpc): cross-process communication interface for distributed architecture

3. Out-of-the-box trading applications for various quantitative strategies (vnpy.app).

    * cta_strategy: CTA strategy engine module, which allows users to perform fine-grained control over the withdrawal behavior of delegates during the operation of CTA-type strategies while maintaining ease of use (reducing trading slippage, implementing high-frequency strategies)

    * cta_backtester: CTA strategy backtester module, no need to use Jupyter Notebook, directly use the graphical interface to directly carry out strategy backtester analysis, parameter optimization and other related work

    * spread_trading: spread trading module, support custom spreads, real-time calculation of spread quotes and positions, support semi-automatic spread algorithm trading and fully automatic spread strategy trading two modes

    * option_master: option trading module, designed for the domestic options market, supports a variety of option pricing models, implied volatility surface calculation, Greek value risk tracking and other functions

    * portfolio_strategy: portfolio strategy module, designed for trading multi-contract quantitative strategies (Alpha, option arbitrage, etc.) at the same time, providing historical data backtesting and live automatic trading functions

    * algo_trading: algorithm trading module, providing a variety of commonly used intelligent trading algorithms: TWAP, Sniper, Iceberg, BestLimit, etc., supporting the docking of external intelligent algorithm trading services (such as Jinnah algorithm)

    * script_trader: script strategy module, designed for multi-standard portfolio trading strategies, also can be directly in the command line to achieve REPL instructions in the form of trading, does not support the backtest function

    * market_radar: market radar module, allowing users to calculate any combination of contract data in real time based on a custom formula, which supports standard Python syntax and built-in functions

    * paper_account: Simulation trading module, pure localization of simulation trading functions, based on the real-time quotes obtained from the trading interface for commission aggregation, providing commission transaction push and position records

    * chart_wizard: K-line chart module, based on RQData data service (futures) or trading interface (digital currency) to obtain historical data, and combined with Tick push to display real-time market changes

    * portfolio_manager: portfolio module, for all kinds of fundamental trading strategies, based on separate strategy sub-accounts, providing automatic tracking of trading positions and real-time profit and loss statistics

    * rpc_service: RPC service module, allowing a VN Trader process to be started as a server, serving as a unified routing channel for quotes and trades, allowing multiple clients to connect at the same time, realizing a multi-process distributed system

    * data_manager: Historical data management module, view the existing data in the database through the tree directory, select any time period data to view the field details, support CSV file data import and export

    * data_recorder: Quotes recording module, based on the graphical interface for configuration, according to the demand for real-time recording Tick or K-line quotes to the database, for strategy backtesting or live initialization

    * excel_rtd: Excel RTD (Real Time Data) real-time data service, based on pyxll module to achieve real-time push updates of various data (quotes, contracts, positions, etc.) in Excel

    * risk_manager: risk management module, providing statistics and restrictions on rules including trade flow control, number of orders placed, active orders, total number of cancelled orders, etc., effectively realizing front-end risk control functions

4. Python trading API interface package (vnpy.api), providing the underlying docking implementation of the above trading interface.

5. simple and easy-to-use event-driven engine (vnpy.event), which is the core of event-driven trading program

6. standardized management client (vnpy.database) interfacing with various databases.

    * SQL class

        * SQLite (sqlite): lightweight single file database, no need to install and configure data service programs, default option of vnpy.py, suitable for novice users

        * MySQL (mysql): the world's most popular open source relational database, extremely rich documentation, and can replace other high NewSQL compatible implementations (such as TiDB)

        * PostgreSQL (postgresql): more feature-rich open source relational database, support for new features through extension plug-ins, only recommended for skilled users

    * NoSQL classes

        * MongoDB (mongodb): non-relational database based on distributed file storage (bson format), built-in memory cache of hot data provides faster read and write speeds

        * InfluxDB (influxdb): non-relational database specially designed for time-series data, columnar data storage provides high read/write efficiency and peripheral analysis applications

6. standard component for cross-process communication (vnpy.rpc) for implementing complex trading systems in distributed deployments

7. Python high-performance K-line charts (vnpy.chart), supporting large data volume chart display and real-time data update functions

8. [Community Forum](http://www.vnpy.com) and [Zhihu Column](http://zhuanlan.zhihu.com/vn-py), which include the development tutorial of vn.py project and the research on the application of Python in the field of quantitative trading, etc.

9. The official communication group 262656087 (QQ), with strict management (regular purging of long-term diving members), and the membership fee will be donated to the vn.py community fund.

## Environment preparation

* We recommend using the Python distribution [VNStudio-2.3.0](https://download.vnpy.com/vnstudio-2.3.0.exe), which is built with the latest version of vn.py framework and VN Station quantitative management platform, specifically created by the vn.py team for quantitative trading. Manual installation
* Supported system versions: Windows 7 or above/Windows Server 2008 or above/Ubuntu 18.04 LTS
* Supported Python version: Python 3.7 64-bit (**Note that it must be Python 3.7 64-bit version**)

## Installation steps

Download the latest version from [here](https://github.com/vnpy/vnpy/releases), unzip it and run the following command to install it.

**Windows**

    install.bat

**Ubuntu**

    bash install.sh

## User's Guide

1. Register a CTP Demo account at [SimNow](http://www.simnow.com.cn/) and get the broker code and the trading quotes server address at [this page](http://www.simnow.com.cn/product.action).

2. Register at [vn.py community forum](https://www.vnpy.com/forum/) to get the VN Station account password (the forum account password is)

3. Launch VN Station (a shortcut will be created automatically on your desktop after installing VN Studio), enter the account password from the previous step and login

4. Click on the **VN Trader Lite** button at the bottom and start your trading!

Attention.

* Please do not close VN Station during the running of VN Trader (it will exit automatically)
* For flexible configuration of quantitative trading application components, please use **VN Trader Pro**

## Script Run

In addition to the graphical start-up method based on VN Station, you can also create run.py in any directory and write the following sample code.

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_backtester import CtaBacktesterApp

def main():
    ""启动VN交易"""
    qapp = create_qapp()

    event_engine = EventEngine()
    main_engine = MainEngine(event_engine)
    
    main_engine.add_gateway(CtpGateway)
    main_engine.add_app(CtaStrategyApp)
    main_engine.add_app(CtaBacktesterApp)

    main_window = MainWindow(main_engine, event_engine)
    main_window.showMaximized()

    qapp.exec()

如果 __name__ == "__main__"。
    main()
```

Open CMD in that directory (hold Shift->click right mouse button->open command window/PowerShell here) and then run the following command to start VN Trader.

    python run.py
    
## Contributing code

vn.py uses Github to host its source code, if you wish to contribute code please use the PR (Pull Request) process of github:

1. [create Issue](https://github.com/vnpy/vnpy/issues/new) - For the larger changes (such as new features, large refactoring, etc.) it is best to first open an issue to discuss, and smaller improvements (such as document improvements, bugfixes, etc.) can be sent directly to PR

2. Fork [vn.py](https://github.com/vnpy/vnpy) - Click the **Fork** button in the upper right corner

3. CloneYour own fork: ```git clone https://github.com/$userid/vnpy.git```

	* If your fork is out of date, you need to manually sync: [Synchronization method](https://help.github.com/articles/syncing-a-fork/)

4. Create your own feature branch from **dev**: ```git checkout -b $my_feature_branch dev```

5. Make changes on $my_feature_branch and push the changes to your fork

6. Create a [Pull Request] from your fork's $my_feature_branch branch to the main project's **dev** branch - [here](https://github.com/vnpy/vnpy/compare?expand=1) Click on **compare across forks** and select the required fork and branch to create the PR

7. Waiting for review, need to continue to improve, or be Merge!

When submitting code, please observe the following rules to improve the quality of the code:

  * Use [autopep8](https://github.com/hhatto/autopep8) to format your code. Run ```autopep8 --in-place --recursive . ``` Just do it.
  * Check your code with [flake8](https://pypi.org/project/flake8/) to make sure there are no errors and warnings. Just run ``flake8`` in the project root directory.



## Project Donation

We have received many donations from the community over the past 6 years and would like to thank them all! All donations are put into the vn.py Community Fund, which supports the operation of the vn.py project.

Just to be clear: **vn.py is an open source project and can be used for free forever, there is no mandatory donation requirement!**

Donation method: 支付宝3216630132@qq.com *Xiao Excellent）

Long-term maintenance of the donation list, please indicate in the message that it is a project donation and the name of the donor.


## Other content

* [Getting Help](https://github.com/vnpy/vnpy/blob/dev/docs/SUPPORT.md)
* [Community Conduct side](https://github.com/vnpy/vnpy/blob/dev/docs/CODE_OF_CONDUCT.md)
* [Issue templates](https://github.com/vnpy/vnpy/blob/dev/docs/ISSUE_TEMPLATE.md)
* [PR templates](https://github.com/vnpy/vnpy/blob/dev/docs/PULL_REQUEST_TEMPLATE.md)



## Copyright statement

MIT
  




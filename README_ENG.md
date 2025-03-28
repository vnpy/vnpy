# VeighNa - By Traders, For Traders, AI-Powered.

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/veighna-logo.png"/>
</p>

💬 Want to read this in **chinese** ? Go [**here**](README.md)

<p align="center">
    <img src ="https://img.shields.io/badge/version-4.0.0-blueviolet.svg"/>
    <img src ="https://img.shields.io/badge/platform-windows|linux|macos-yellow.svg"/>
    <img src ="https://img.shields.io/badge/python-3.10|3.11|3.12|3.13-blue.svg" />
    <img src ="https://img.shields.io/github/actions/workflow/status/vnpy/vnpy/pythonapp.yml?branch=master"/>
    <img src ="https://img.shields.io/github/license/vnpy/vnpy.svg?color=orange"/>
</p>

VeighNa is a Python-based open source quantitative trading system development framework that has grown step by step into a fully-featured quantitative trading platform with continuous contributions from the open source community. It currently has many users from domestic and international financial institutions, including hedge funds, investment banks, futures brokers, university research institutions, proprietary trading companies, etc.

:rocket: :rocket: :rocket: **The VeighNa Elite Quantitative Terminal for professional traders has been officially released, providing comprehensive support for professional traders' needs in areas such as massive strategy concurrency, intelligent position rolling, algorithmic order execution, multi-account trading support, and more. For more detailed information, please scan the QR code below and follow the account, then click on the menu bar's [Community Exchange -> Elite Member Services]**:

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/vnpy_qr.jpg"/>
</p>

If you have any questions about using VeighNa for secondary development (strategies, modules, etc.), please check the [**VeighNa Project Documentation**](https://www.vnpy.com/docs/cn/index.html). If you can't solve it, please go to the [Questions and Help] section of the [**Official Community Forum**](https://www.vnpy.com/forum/) for help, or share your experience in the [Experience Sharing] section!

**Want to get more information about VeighNa?** Please scan the QR code below to add the assistant and join the [VeighNa Community Exchange WeChat Group]:

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/github_wx.png"/, width=250>
</p>


## AI-Powered

On the tenth anniversary of VeighNa's release, version 4.0 officially introduces the [vnpy.alpha](./vnpy/alpha) module targeting AI quantitative strategies, providing professional quantitative traders with **an all-in-one multi-factor machine learning (ML) strategy development, research, and live trading solution**:

<p align="center">
  <img src ="https://vnpy.oss-cn-shanghai.aliyuncs.com/alpha_demo.jpg"/, width=700>
</p>

* :bar_chart: **[dataset](./vnpy/alpha/dataset)**: Factor Feature Engineering

    * Designed specifically for ML algorithm training optimization, supporting efficient batch feature calculation and processing
    * Built-in rich factor feature expression calculation engine, enabling rapid one-click generation of training data
    * [Alpha 158](./vnpy/alpha/dataset/datasets/alpha_158.py): A collection of stock market features from Microsoft's Qlib project, covering multiple dimensions of quantitative factors including K-line patterns, price trends, and time-series volatility

* :bulb: **[model](./vnpy/alpha/model)**: Prediction Model Training

    * Provides standardized ML model development templates, greatly simplifying model building and training processes
    * Unified API interface design, supporting seamless switching between different algorithms for performance comparison testing
    * Integrates multiple mainstream machine learning algorithms:
        * [Lasso](./vnpy/alpha/model/models/lasso_model.py): Classic Lasso regression model, implementing feature selection through L1 regularization
        * [LightGBM](./vnpy/alpha/model/models/lgb_model.py): Efficient gradient boosting decision tree with a training engine optimized for large-scale datasets
        * [MLP](./vnpy/alpha/model/models/mlp_model.py): Multi-layer perceptron neural network, suitable for modeling complex non-linear relationships

* :robot: **[strategy](./vnpy/alpha/strategy)**: Strategy Research and Development

    * Quickly build quantitative trading strategies based on ML signal prediction models
    * Support for both cross-sectional multi-asset and time-series single-asset strategy types

* :microscope: **[lab](./vnpy/alpha/lab.py)**: Research Process Management

    * Integrates complete workflow including data management, model training, signal generation, and strategy backtesting
    * Simple API design with built-in visualization analysis tools for intuitive evaluation of strategy performance and model effectiveness

* :book: **[notebook](./examples/alpha_research)**: Quantitative Research Demo

    * [download_data_rq](./examples/alpha_research/download_data_rq.ipynb): Download A-share index constituent stock data based on RQData, including index constituent tracking and historical market data retrieval
    * [research_workflow_lasso](./examples/alpha_research/research_workflow_lasso.ipynb): Quantitative research workflow based on Lasso regression model, demonstrating feature selection and prediction capability of linear models
    * [research_workflow_lgb](./examples/alpha_research/research_workflow_lgb.ipynb): Quantitative research workflow based on LightGBM gradient boosting tree, utilizing efficient ensemble learning methods for prediction
    * [research_workflow_mlp](./examples/alpha_research/research_workflow_mlp.ipynb): Quantitative research workflow based on multilayer perceptron neural network, demonstrating the application of deep learning in quantitative trading

The design concept of the vnpy.alpha module was inspired by the [Qlib](https://github.com/microsoft/qlib) project, providing powerful AI quantitative capabilities while maintaining ease of use. We would like to express our sincere gratitude to the Qlib development team!


## Functional Features

Modules marked with :arrow_up: have completed the upgrade compatibility testing for version 4.0. Additionally, the 4.0 core framework uses an upgrade approach that prioritizes compatibility, so most modules can also be used directly (interfaces involving C++ API encapsulation must be upgraded before use).

1. :arrow_up: Multi-functional quantitative trading platform (vnpy.trader) that integrates various trading interfaces and provides simple and easy-to-use APIs for specific strategy algorithm and function development, for quickly building quantitative trading applications required by traders.

2. Trading interfaces (vnpy.gateway) covering all domestic and international trading varieties:

    * Domestic market

        * :arrow_up: CTP ([ctp](https://www.github.com/vnpy/vnpy_ctp)): Domestic futures and options

        * CTP Mini ([mini](https://www.github.com/vnpy/vnpy_mini)): Domestic futures, options

        * CTP Securities ([sopt](https://www.github.com/vnpy/vnpy_sopt)): ETF options

        * FEMAS ([femas](https://www.github.com/vnpy/vnpy_femas)): Domestic futures

        * UFT ([uft](https://www.github.com/vnpy/vnpy_uft)): Domestic futures, ETF options
        
        * Esunny ([esunny](https://www.github.com/vnpy/vnpy_esunny)): Domestic futures, Gold TD

        * APEX XSpeed ([sec](https://www.github.com/vnpy/vnpy_sec)): ETF options

        * APEX HTS ([hts](https://www.github.com/vnpy/vnpy_hts)): ETF options

        * XTP ([xtp](https://www.github.com/vnpy/vnpy_xtp)): Domestic securities (A shares), ETF options

        * TORA ([tora](https://www.github.com/vnpy/vnpy_tora)): Domestic securities (A shares), ETF options

        * Guotai Junan ([hft](https://www.github.com/vnpy/vnpy_hft)): Domestic securities (A shares, margin trading)
        
        * OST ([ost](https://www.github.com/vnpy/vnpy_ost)): Domestic securities (A shares)
        
        * EMT ([emt](https://www.github.com/vnpy/vnpy_emt)): Domestic securities (A shares)
        
        * SGIT ([sgit](https://www.github.com/vnpy/vnpy_sgit)): Gold TD, domestic futures

        * KsGold ([ksgold](https://www.github.com/vnpy/vnpy_ksgold)): Gold TD

        * LStar ([lstar](https://www.github.com/vnpy/vnpy_lstar)): Futures asset management

        * Rohon ([rohon](https://www.github.com/vnpy/vnpy_rohon)): Futures asset management

        * Jees ([jees](https://www.github.com/vnpy/vnpy_jees)): Futures asset management

        * ComStar ([comstar](https://www.github.com/vnpy/vnpy_comstar)): Interbank market
        
        * GoldMiner ([gm](https://www.github.com/vnpy/vnpy_gm)): Domestic securities (simulation)
        
        * UF Cloud ([uf](https://www.github.com/vnpy/vnpy_uf)): Domestic securities (simulation)
        
        * TTS ([tts](https://www.github.com/vnpy/vnpy_tts)): Domestic futures (simulation)

    * Overseas market

        * Interactive Brokers ([ib](https://www.github.com/vnpy/vnpy_ib)): Global securities, futures, options, forex, etc.

        * Esunny 9.0 ([tap](https://www.github.com/vnpy/vnpy_tap)): Global futures

        * Direct Futures ([da](https://www.github.com/vnpy/vnpy_da)): Global futures

    * Special Applications

        * :arrow_up: RQData Market Data ([rqdata](https://www.github.com/vnpy/vnpy_rqdata)): Cross-market (stocks, indices, ETFs, futures) real-time market data

        * XtQuant Market Data ([xt](https://www.github.com/vnpy/vnpy_xt)): Cross-market (stocks, indices, convertible bonds, ETFs, futures, options) real-time market data

        * RPC service ([rpc](https://www.github.com/vnpy/vnpy_rpcservice)): Inter-process communication interface for distributed architecture

3. Out-of-the-box trading applications for various quantitative strategies (vnpy.app):

    * :arrow_up: [cta_strategy](https://www.github.com/vnpy/vnpy_ctastrategy): CTA strategy engine module, which allows users to perform fine-grained control over the order management during the operation of CTA-type strategies while maintaining ease of use (reducing trading slippage, implementing high-frequency strategies)

    * [cta_backtester](https://www.github.com/vnpy/vnpy_ctabacktester): CTA strategy backtester module, no need to use Jupyter Notebook, directly use the graphical interface to carry out strategy backtesting analysis, parameter optimization and other related work

    * [spread_trading](https://www.github.com/vnpy/vnpy_spreadtrading): Spread trading module, supports custom spreads, real-time calculation of spread quotes and positions, supports semi-automatic spread algorithm trading and fully automatic spread strategy trading modes

    * [option_master](https://www.github.com/vnpy/vnpy_optionmaster): Option trading module, designed for the domestic options market, supports various option pricing models, implied volatility surface calculation, Greek value risk tracking and other functions

    * [portfolio_strategy](https://www.github.com/vnpy/vnpy_portfoliostrategy): Portfolio strategy module, designed for trading multi-contract quantitative strategies (Alpha, option arbitrage, etc.) simultaneously, providing historical data backtesting and live automatic trading functions

    * [algo_trading](https://www.github.com/vnpy/vnpy_algotrading): Algorithm trading module, providing various commonly used intelligent trading algorithms: TWAP, Sniper, Iceberg, BestLimit, etc.

    * [script_trader](https://www.github.com/vnpy/vnpy_scripttrader): Script strategy module, designed for multi-asset portfolio trading strategies and computational tasks, also can directly achieve REPL instruction trading in the command line, does not support backtesting functions

    * [paper_account](https://www.github.com/vnpy/vnpy_paperaccount): Simulation trading module, pure localized implementation of simulation trading functions, based on real-time quotes obtained from the trading interface for order matching, providing order execution pushing and position records

    * [chart_wizard](https://www.github.com/vnpy/vnpy_chartwizard): K-line chart module, based on RQData data service (futures) or trading interface to obtain historical data, and combined with Tick push to display real-time market changes

    * [portfolio_manager](https://www.github.com/vnpy/vnpy_portfoliomanager): Portfolio module, for various fundamental trading strategies, based on separate strategy sub-accounts, providing automatic tracking of trading positions and real-time profit and loss statistics

    * [rpc_service](https://www.github.com/vnpy/vnpy_rpcservice): RPC service module, allowing a VeighNa Trader process to be started as a server, serving as a unified routing channel for quotes and trades, allowing multiple clients to connect simultaneously, realizing a multi-process distributed system

    * [data_manager](https://www.github.com/vnpy/vnpy_datamanager): Historical data management module, view existing data in the database through a tree directory, select any time period data to view field details, supports CSV file data import and export

    * [data_recorder](https://www.github.com/vnpy/vnpy_datarecorder): Market data recording module, based on the graphical interface for configuration, records Tick or K-line data to the database in real-time according to demand, for strategy backtesting or live initialization

    * [excel_rtd](https://www.github.com/vnpy/vnpy_excelrtd): Excel RTD (Real Time Data) real-time data service, based on pyxll module to achieve real-time push updates of various data (quotes, contracts, positions, etc.) in Excel

    * [risk_manager](https://www.github.com/vnpy/vnpy_riskmanager): Risk management module, providing statistics and restrictions on rules including trade flow control, number of orders placed, active orders, total number of cancelled orders, etc., effectively implementing front-end risk control functions
    
    * [web_trader](https://www.github.com/vnpy/vnpy_webtrader): Web service module, designed according to the requirements of B-S architecture, implementing a web server that provides active function calls (REST) and passive data push (WebSocket)


4. Python trading API interface package (vnpy.api), providing the underlying implementation of the above trading interfaces:
    
    * REST Client ([rest](https://www.github.com/vnpy/vnpy_rest)): High-performance REST API client based on coroutine process asynchronous IO which adopts the programming model of event message cycle to support sending high concurrent real-time transaction requests
    
    * Websocket Client ([websocket](https://www.github.com/vnpy/vnpy_websocket)): High-performance Websocket API client based on coroutine process asynchronous IO, supports sharing event loops with REST Client to avoid multi-threaded performance loss caused by GIL


5. :arrow_up: Simple and easy-to-use event-driven engine (vnpy.event), which is the core of event-driven trading programs

6. Standardized management client (vnpy.database) interfacing with various databases:

    * SQL class

        * :arrow_up: SQLite ([sqlite](https://www.github.com/vnpy/vnpy_sqlite)): Lightweight single file database, no need to install and configure data service programs, default option of VeighNa, suitable for novice users

        * MySQL ([mysql](https://www.github.com/vnpy/vnpy_mysql)): The world's most popular open source relational database, extremely rich documentation, and can replace other high NewSQL compatible implementations (such as TiDB)

        * PostgreSQL ([postgresql](https://www.github.com/vnpy/vnpy_postgresql)): More feature-rich open source relational database, support for new features through extension plug-ins, only recommended for skilled users

    * NoSQL classes

        * DolphinDB ([dolphindb](https://www.github.com/vnpy/vnpy_dolphindb)): A high-performance distributed temporal database especially suitable for low latency or real-time tasks with high speed requirements
        
        * Arctic ([arctic](https://www.github.com/vnpy/vnpy_arctic)): High-performance financial temporal database developed by quantitative hedge fund Man AHL based on MongoDB, adopts performance optimization schemes such as partitioned storage and lz4 compression

        * TDengine ([taos](https://www.github.com/vnpy/vnpy_taos)): Distributed, high-performance, SQL-supporting time-series database with built-in caching, stream computing, data subscription and other system functions that greatly reduce development and maintenance complexity

        * TimescaleDB ([timescaledb](https://www.github.com/vnpy/vnpy_timescaledb)): Time-series database developed based on PostgreSQL, installed as a plugin extension, supports automatic data partitioning by space and time

        * MongoDB ([mongodb](https://www.github.com/vnpy/vnpy_mongodb)): Non-relational database based on distributed file storage (bson format), built-in memory cache of hot data provides faster read and write speeds
        
        * InfluxDB ([influxdb](https://www.github.com/vnpy/vnpy_influxdb)): Non-relational database specially designed for time-series data, columnar data storage provides high read/write efficiency and peripheral analysis applications
        
        * LevelDB ([leveldb](https://www.github.com/vnpy/vnpy_leveldb)): High-performance key/value database launched by Google which implements a process memory storage engine based on LSM algorithm, and supports billions of levels of massive data

7. Adapter interfaces for various data services (datafeed):

    * XtQuant ([xt](https://www.github.com/vnpy/vnpy_xt)): Stocks, futures, options, funds, bonds

    * :arrow_up: RQData ([rqdata](https://www.github.com/vnpy/vnpy_rqdata)): Stocks, futures, options, funds, bonds, Gold TD

    * VoltTrader ([voltrader](https://www.github.com/vnpy/vnpy_voltrader)): Futures, options
    
    * UData ([udata](https://www.github.com/vnpy/vnpy_udata)): Stocks, futures, options
    
    * TuShare ([tushare](https://www.github.com/vnpy/vnpy_tushare)): Stocks, futures, options, funds
    
    * Wind ([wind](https://www.github.com/vnpy/vnpy_wind)): Stocks, futures, funds, bonds
    
    * Tinysoft ([tinysoft](https://www.github.com/vnpy/vnpy_tinysoft)): Stocks, futures, funds, bonds
    
    * iFinD ([ifind](https://www.github.com/vnpy/vnpy_ifind)): Stocks, futures, funds, bonds
    
    * TQSDK ([tqsdk](https://www.github.com/vnpy/vnpy_tqsdk)): Futures


8. :arrow_up: Standard component for inter-process communication (vnpy.rpc) for implementing complex trading systems in distributed deployments

9. :arrow_up: Python high-performance K-line charts (vnpy.chart), supporting large data volume chart display and real-time data update functions

10. [Community Forum](http://www.vnpy.com/forum) and [Zhihu Blog](http://zhuanlan.zhihu.com/vn-py), which include the development tutorial of VeighNa project and the research on the application of Python in the field of quantitative trading, etc.

11. The official communication group 262656087 (QQ), with strict management (regular purging of long-term inactive members), and the membership fee will be donated to the VeighNa community fund.

Note: The above description of functional features is based on the documentation at the time of publication, and subsequent updates or adjustments may exist. If there are discrepancies between the function description and the actual situation, please contact us through Issue for adjustments.

## Environment preparation

* We recommend using the Python distribution [VeighNa Studio-4.0.0](https://download.vnpy.com/veighna_studio-4.0.0.exe), which is built with the latest version of VeighNa framework and VeighNa Station quantitative management platform, specifically created by the VeighNa team for quantitative trading. No manual installation required.
* Supported system versions: Windows 11 or above / Windows Server 2022 or above / Ubuntu 22.04 LTS or above
* Supported Python version: Python 3.10 or above (64-bit), **Python 3.13 recommended**

## Installation steps

Download the latest version from [here](https://github.com/vnpy/vnpy/releases), unzip it and run the following command to install it.

**Windows**

```
install.bat
```

**Ubuntu**

```
bash install.sh
```

**Macos**

```
bash install_osx.sh
```

**Note: setup.cfg lists the dependency libraries required for VeighNa framework installation, and requirements.txt provides the recommended installation versions of these dependencies.**

## User's Guide

1. Register a CTP Demo account at [SimNow](http://www.simnow.com.cn/) and get the broker code and the trading quotes server address at [this page](http://www.simnow.com.cn/product.action).

2. Register at [VeighNa community forum](https://www.vnpy.com/forum/) to get the VeighNa Station account password (the forum account password is used)

3. Launch VeighNa Station (a shortcut will be created automatically on your desktop after installing VeighNa Studio), enter the account password from the previous step and login

4. Click on the **VeighNa Trader** button at the bottom and start your trading!

Attention:

* Please do not close VeighNa Station during the running of VeighNa Trader (it will exit automatically)

## Script Run

In addition to the graphical start-up method based on VeighNa Station, you can also create run.py in any directory and write the following sample code:

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp

from vnpy_ctp import CtpGateway
from vnpy_ctastrategy import CtaStrategyApp
from vnpy_ctabacktester import CtaBacktesterApp


def main():
    """Start VeighNa Trader"""
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

Open CMD in that directory (hold Shift->click right mouse button->open command window/PowerShell here) and then run the following command to start VeighNa Trader:

    python run.py
    
## Contributing code

VeighNa uses Github to host its source code, if you wish to contribute code please use the PR (Pull Request) process of github:

1. [Create Issue](https://github.com/vnpy/vnpy/issues/new) - For larger changes (such as new features, large refactoring, etc.) it is best to first open an issue to discuss, and smaller improvements (such as document improvements, bugfixes, etc.) can be sent directly to PR

2. Fork [VeighNa](https://github.com/vnpy/vnpy) - Click the **Fork** button in the upper right corner

3. Clone your own fork: ```git clone https://github.com/$userid/vnpy.git```

	* If your fork is out of date, you need to manually sync: [Synchronization method](https://help.github.com/articles/syncing-a-fork/)

4. Create your own feature branch from **dev**: ```git checkout -b $my_feature_branch dev```

5. Make changes on $my_feature_branch and push the changes to your fork

6. Create a [Pull Request] from your fork's $my_feature_branch branch to the main project's **dev** branch - [here](https://github.com/vnpy/vnpy/compare?expand=1) Click on **compare across forks** and select the required fork and branch to create the PR

7. Waiting for review, need to continue to improve, or be Merge!

When submitting code, please observe the following rules to improve the quality of the code:

  * Use [ruff](https://github.com/astral-sh/ruff) to check your code style, ensuring there are no errors and warnings. Just run ``ruff check .`` in the project root directory.
  * Use [mypy](https://github.com/python/mypy) for static type checking, ensuring type annotations are correct. Just run ``mypy vnpy`` in the project root directory.


## Other content

* [Getting Help](https://github.com/vnpy/vnpy/blob/dev/.github/SUPPORT.md)
* [Community Conduct Guidelines](https://github.com/vnpy/vnpy/blob/dev/.github/CODE_OF_CONDUCT.md)
* [Issue templates](https://github.com/vnpy/vnpy/blob/dev/.github/ISSUE_TEMPLATE.md)
* [PR templates](https://github.com/vnpy/vnpy/blob/dev/.github/PULL_REQUEST_TEMPLATE.md)


## Copyright statement

MIT

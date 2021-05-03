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

## Features

1. Full-featured quantitative trading platform（vnpy.trader），It integrates multiple transaction interface，And provides a simple and easy to use for a particular strategy algorithm and feature developmentAPI，Rapid construction required for traders quantitative trading application。

2. All transactions covering domestic and foreign varieties of the transaction interface（vnpy.gateway）：

    * Domestic market

        * CTP（ctp）：Domestic futures、Options

        * CTP Mini（mini）：Domestic futures、Options

        * CTPSecurities（sopt）：ETFOptions

        * Pegasus（femas）：Domestic futures

        * Core Width（oes）：Domestic securities（Ashare）

        * NakaYasushiXTP（xtp）：Domestic securities（Ashare）

        * 华鑫奇 point（tora）：Domestic securities（Ashare）

        * Xin housekeeper（xgj）：Futures and information management

        * Rong Hang（rohon）：Futures and information management

    * overseas market

        * Fu passers securities（futu）：Hong Kong stocks、US stocks

        * Tiger Securities（tiger）：Global Securities、futures、Options、Foreign exchange

        * Interactive Brokers（ib）：Global Securities、futures、Options、Foreign exchange

        * Yi Sheng9.0External disk（tap）：Global Futures

        * Direct Futures（da）：Global Futures

    * Digital Currency

        * BitMEX（bitmex）：Digital currency futures、Options、Sustainable contracts

        * OKEXSustainable（okexs）：Sustainable digital currency contracts

        * OKEXcontract（okexf）：Digital currency futures

        * Fire currency contracts（hbdm）：Digital currency futures

        * An coins（binance）：Digital currency spot

        * OKEX（okex）：Digital currency spot

        * Fire currency（huobi）：Digital currency spot

        * Bitfinex（bitfinex）：Digital currency spot

        * Coinbase（coinbase）：Digital currency spot

        * 1Token（onetoken）：Digital currency broker（Stock、futures）

    * Special Applications
    
        * RPCservice（rpc）：Cross-process communication interface，For distributed architecture

3. All kinds of quantitative strategies trading applications out of the box（vnpy.app）：

    * cta_strategy：CTAPolicy engine module，While maintaining the ease of use，To allow for usersCTAProcess class policy to run in the report commissioned by the withdrawal behavior of fine-grained control（Reduce transaction Slippage、High frequency strategies）

    * cta_backtester：CTAStrategy Backtesting module，Without the use ofJupyter Notebook，Direct use graphical interface directly strategy backtesting analysis、Parameter optimization and other related work

    * spread_trading：Spread trading module，Support for custom spreads，Real-time quotes and to calculate the spread positions，Support for semi-automatic and fully automatic algorithmic trading spreads spread trading strategies two modes

    * algo_trading：Algorithmic trading module，It offers a variety of commonly used smart trading algorithms：TWAP、Sniper、Iceberg、BestLimitand many more，Support for common algorithm configuration is saved

    * script_trader：Scripts policy module，For multi-target combination class trading strategy design，At the same time can also be implemented directly on the command lineREPLInstruction in the form of transaction，Backtesting feature is not supported

    * rpc_service：RPCService Module，Allows aVN TraderProcess starts for the server，As a unified market and transaction routing channel，It allows multiple simultaneous client connections，Multi-process distributed systems

    * csv_loader：CSVHistorical Data Loader，For loadingCSVHistorical data format file into the database platform，Backtesting for strategy and research firm initialization function，Support for custom data format header

    * data_recorder：Quotes recording module，Be configured based graphical interface，According to the needs of real-time recordingTickorKQuotes line into the database，Backtesting for strategy or firm initialization

    * risk_manager：Risk Management Module，Including transaction provides flow control、Under a single number、Principal activities、Statistics and limit the total number of regular withdrawals，Effective to achieve the control function of the front end of the wind

4. PythontransactionAPIInterface Package（vnpy.api），The deal provides an interface to achieve the underlying docking。

5. Simple and easy to use event-driven engine（vnpy.event），As the core of event-driven trading programs。

6. Inter-process communication standard components（vnpy.rpc），System implementation for complex transactions distributed deployment。

7. Pythonhigh performanceKLine chart（vnpy.chart），Support large amount of data in the chart display and real-time data updates。

8. [Community Forum](http://www.vnpy.com)with[Know almost Column](http://zhuanlan.zhihu.com/vn-py)，content includevn.pyTutorials and project developmentPythonThe contents of applied research in the field of quantitative trading。

9.  The official exchange group262656087（QQ），Strict management（Periodically clear long-term member of diving），The fee will be donated to the groupvn.pyCommunity Fund。

## Preparing the Environment

* Recommended Usevn.pyQuantitative trading team built specificallyPythonRelease[VNStudio-2.0.7](https://download.vnpy.com/vnstudio-2.0.7.exe)，Built with the latest version of thevn.pyFramework andVN StationQuantitative Management Platform，No need to manually install
* Support system version：Windows 7the above/Windows Server 2008the above/Ubuntu 18.04 LTS
* SupportedPythonversion：Python 3.7 64Place（**Note must bePython 3.7 64Bit versions**）

## installation steps

in[Here](https://github.com/vnpy/vnpy/releases)Download the latest version，After extracting run the following command to install：

**Windows**

    install.bat

**Ubuntu**

    bash install.sh


## user's guidance

1. in[SimNow](http://www.simnow.com.cn/)registeredCTPSimulation account，And[This page](http://www.simnow.com.cn/product.action)Get the code and brokers trading market server address。

2. in[vn.pyCommunity Forum](https://www.vnpy.com/forum/)Register forVN Stationaccount password（Forum account password that is）

3. start upVN Station（installationVNCondaAfter automatically create a shortcut on the desktop），Enter your login account and password on step

4. Click the bottom**VN Trader Lite**Push button，Start your transaction！！！

note：

* inVN TraderDo not turn off the process of runningVN Station（It will automatically exit）
* If you need the flexibility to configure quantitative trading application components，please use**VN Trader Pro**


## Script

In addition to onVN StationGraphical way outside to start，You can also create any directoryrun.py，The following sample code is written：

```Python
from vnpy.event import EventEngine
from vnpy.trader.engine import MainEngine
from vnpy.trader.ui import MainWindow, create_qapp
from vnpy.gateway.ctp import CtpGateway
from vnpy.app.cta_strategy import CtaStrategyApp
from vnpy.app.cta_backtester import CtaBacktesterApp

def main（）:
    """Start VN Trader"""
    qapp = create_qapp（）

    event_engine = EventEngine（）
    main_engine = MainEngine（event_engine）
    
    main_engine.add_gateway（CtpGateway）
    main_engine.add_app（CtaStrategyApp）
    main_engine.add_app（CtaBacktesterApp）

    main_window = MainWindow（main_engine, event_engine）
    main_window.showMaximized（）

    qapp.exec（）

if __name__ == "__main__":
    main（）
```

Open in the directoryCMD（Press and holdShift->right click->Open a command window here/PowerShell）After you run the following command to startVN Trader：

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
  




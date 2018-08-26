# vn.py - By Traders, For Traders.

---

### Brief Introduction

The vn.py project is an open-source quantitative trading framework that is developed by traders, for traders. The project is mainly written in Python and uses C++ for low-layer and performance sensitive infrastructure. 

Using the vn.py project, institutional investors and professional traders, such as hedge funds, prop trading firms and investment banks, can easily develop complex trading strategies with the Event Engine Strategy Module, and automatically route their orders to the most desired destinations, including equity, commodity, forex, cryptocurrency and many other financial markets. 

---
### Quick Start

1. Prepare a computer with Windows 7/8/10/Server 2008 (64-bit) installed.

2. Install [Anaconda 5.2.0](http://www.continuum.io/downloads), please make sure you download **Python 2.7 (32-bit)**.

3. Install [MongoDB](https://www.mongodb.org/downloads#production), please register MongoDB as Windows Service.

4. Install [Visual C++  Redistributable Packages for VS2013 (32-bit)](https://www.microsoft.com/en-gb/download/details.aspx?id=40784).

5. Run **install.bat** to install vn.py and all dependencies.

6. Go to folder **examples/CryptoTrader/** and edit those **ABC_connect.json** files with your exchange config. Taking BitMEX_connect.json as an example:
	* apiKey: the API Key of your account provided by BitMEX
	* secretKey: the Secret Key of your account provide by BitMEX 
	* sessionCount: number of sessions and threads you would like to use for RESTFul request
	* symbols: symbols of contract you would like to receive data update from Websocket API 

7. Change the "language" setting in **VT_setting.json** to "english" (otherwise you will see the GUI in Chinese).

8. Start CryptoTrader by running "python run.py", connect to BitMEX and then you are ready to trade!

### Project Structure

1. A large number of Broker and Market Data APIs, all in Python (vnpy.api):

	**Cryptocurrency Market**

    - BitMEX (bitmex)

    - OKEX（okex)

    - Huobi Pro（huobi)

    - Binance（binance)

    - Bitfinex (bitfinex)

    - Coinbase Pro (coinbase)

    - FCoin (fcoin)

    - BigOne (bigone)

    - LBank（lbank）

    - CCXT (ccxt)

	**International Financial Markets**

	- Interactive Brokers（ib）
	
	- Shanghai Zhida Futures（shzd）

	- Futu Securities (futu)

	**Chinese Futures Market**

	- CTP（ctp）

	- Femas（femas）

	- Kingstar Option（ksotp）

	- XSpeed（xspeed）

	**Chinese Equity Market**

	- LTS（lts）
	
	- QDP（qdp）

	- CSHSHLP（cshshlp）	

	- XSpeed Securities (sec)

	**Chinese Precious Metal Market**

	- SGIT（sgit）

	- Kingstar Gold（ksgold）


2. Simple but powerful event engine module (vnpy.event), which can be used for developing complex quantitative trading strategies

3. RPC framework (vnpy.rpc) which also supports pushing data from server to client, aimed at implementing distributed trading systems.

4. Ready to use trading platform (vnpy.trader), which has integrated all the trading APIs in vnpy.api, and provides easy to use strategy engines for developing different types of quantitative strategies and trading algorithms.

5. Examples about how to use vn.py framework for solving real world trading issues (vnpy.examples).

6. [Official Forum](http://www.vnpie.org) and [Github Repository](http://www.github.com/vnpy/vnpy)

---
### Contact

If you have any questions about how to use the project or any suggestions about improving it, please feel free to email vn.py@foxmail.com.

---
### License
MIT


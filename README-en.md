# vn.py - By Traders, For Traders.

---

### Brief Introduction

The vn.py project is an open-source quantitative trading framework that is developed by traders, for traders. The project is mainly written in Python and uses C++ for low-layer and performance sensitive infrastructure. 

Using the vn.py project, institutional investors and professional traders, such as hedge funds, prop trading firms and investment banks, can easily develop complex trading strategies with the Event Engine Strategy Module, and automatically route their orders to the most desired destinations, including equity, commodity, forex and many other financial markets. 


### Project Structure

1. A large number of Broker and Market Data APIs, all in Python (vn.api):

	**International Financial Markets**

	- Interactive Brokers（vn.ib）

	- OANDA（vn.oanda）
	
	- Shanghai Zhida Futures（vn.shzd）

	**Chinese Futures Market**

	- CTP（vn.ctp）

	- Femas（vn.femas）

	- Kingstar Option（vn.ksotp）

	- XSpeed（vn.xspeed）


	**Chinese Equity Market**

	- LTS（vn.lts）
	
	- QDP（vn.qdp）

	- CSHSHLP（vn.cshshlp）	

	**Chinese Precious Metal Market**

	- SGIT（vn.sgit）

	- Kingstar Gold（vn.ksgold）


	**Cryptocurrency Market**

	- OKCOIN（vn.okcoin）
	
	- Huobi（vn.huobi）

	- Lhang（vn.lhang）

	**Market Data**

	- Datayes（vn.datayes）

2. Simple but powerful event engine module (vn.event), which can be used for developing complex quantitative trading strategies

3. RPC framework (vn.rpc) which also supports pushing data from server to client, aimed at implementing distributed trading systems.

4. Ready to use trading platform (vn.trader), which has integrated all the trading APIs in vn.api, and provides easy to use strategy engines for developing different types of quantitative strategies and trading algorithms.

5. Tutorials about how to use vn.py to solve real world trading issues.

6. [Official Website](http://vnpy.org) and [Github Repository](http://www.github.com/vnpy/vnpy)


---
### Quick Start

1. Prepare a computer with Windows 7 (64-bit) installed.

2. Install [Anaconda](http://www.continuum.io/downloads), please make sure you download **Anaconda 4.0.0 Python 2.7 (32-bit)**.

3. Install [MongoDB](https://www.mongodb.org/downloads#production)

4. Install pymongo, just run "pip install pymongo" in cmd.

5. Register MongoDB as Windows Service and start it.

6. Install [Visual C++  Redistributable Packages for VS2013 (32-bit)](https://www.microsoft.com/en-gb/download/details.aspx?id=40784).

7. Click the "Download ZIP" button on this page to download the project source code, assume you unzip to C:\vnpy.

8. Install the IB TWS software and configure it to allow trading API connection.

9. Use sublime text or any other text editors you like, to change related details in C:\vnpy\vn.trader\gateway\ibGateway\IB_connect.json to your data.

10. Start IB TWS software and run C:\vnpy\vn.trader\vtMain.py, enjoy trading!

---
### Contact

If you have any questions about how to use the project or any suggestions about improving it, please feel free to email vn.py@foxmail.com.

---
### License
MIT


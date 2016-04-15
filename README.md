# vn.py - 基于python的开源交易平台开发框架

---
### Quick Start

对于大部分用户来说，无需自行编译API接口，可以直接使用vn.trader进行交易和策略开发：

1. 准备一台Windows 7 64位系统的电脑**32位系统单进程有2G限制**

2. 安装[Anaconda](http://www.continuum.io/downloads)：下载Python 2.7 32位版本，**一次装完大部份包，注意必须是32位，稳定少坑**

3. 安装[MongoDB](https://www.mongodb.org/downloads#production)：下载Windows 64-bit 2008 R2+版本 **注：需用firefox浏览器，不然会看不到下载链接，网站兼容性不好。**

4. 安装pymongo：在cmd中运行pip install pymongo  **python下的MongoDB的驱动**

5. 参考[这里](http://jingyan.baidu.com/article/6b97984dbeef881ca2b0bf3e.html)，将MongoDB注册为Windows服务并启动
     **管理员身份的CMD界面进入：C:\MongoDB目录\bin ，运行Mongod -dbpath "C:\MongoDB目录\Data\db" -logpath "C:\MongoDB目录\Data\log\MongoDB.log"  -install -serviceName  "MongoDB" （Data及下面的db,log目录有时需要自己添加）**
     **此时服务已经安装成功，运行>net start mongodb (开启服务)**

6. 安装[Visual C++  Redistributable Packages for VS2013](https://www.microsoft.com/en-gb/download/details.aspx?id=40784)，中英文随意

7. 在本页面选择Download ZIP下载项目代码，并解压到C:\vnpy

8. 获取交易帐号、BrokerID与交易和行情服务器地址
           对于仿真交易者：
在[SimNow](http://simnow.com.cn/)注册CTP仿真账号，记下你的**账号、密码**
参考：http://www.simnow.com.cn/product.action
BrokerID统一为：9999
第一套：
    标准CTP：
        第一组：Trade Front：180.168.146.187:10000，Market Front：180.168.146.187:10010；【电信】
        第二组：Trade Front：180.168.146.187:10001，Market Front：180.168.146.187:10011；【电信】
        第三组：Trade Front：218.202.237.33 :10002，Market Front：218.202.237.33 :10012；【移动】
        交易阶段(服务时间)：与实际生产环境保持一致
    CTPMini1：
        第一组：Trade Front：180.168.146.187:10003，Market Front：180.168.146.187:10013；【电信】
第二套：
    交易前置：180.168.146.187:10030，行情前置：180.168.146.187:10031；【7x24】
    第二套环境仅服务于CTP API开发爱好者，仅为用户提供CTP API测试需求，不提供结算等其它服务。
    新注册用户，需要等到第二个交易日才能使用第二套环境。
    账户、钱、仓跟第一套环境上一个交易日保持一致。
    交易阶段(服务时间)：交易日，16：00～次日09：00；非交易日，16：00～次日15：00。
    用户通过SimNow的账户（上一个交易日之前注册的账户都有效）接入环境，建议通过商业终端进行模拟交易的用户使用第一套环境。

 对于实盘交易者：
      下载快期，找到安装目录，用文本文件打开broker.xml
           查询你的**交易帐号、BrokerID、交易和行情服务器地址**（注：每家期货公司的ctp前置地址都不一样，有的公司还有盘后查询服务器地址）

9. 把C:\vnpy\vn.trader\ctpGateway\CTP_connect.json中的账号、密码、服务器等修改为上一步注册完成后你的信息（注意使用专门的编程编辑器，如Sublime Text等，防止json编码出错）
{
    "brokerID": "9999", 
    "tdAddress": "tcp://前置交易服务器地址", 
    "password": "密码", 
    "mdAddress": "tcp://前置行情服务器地址", 
    "userID": "帐号"
}


10. 双击运行C:\vnpy\vn.trader\vtMain.py，开始交易！

对于想研究API封装的用户，可以参考[vnpy.org](http://vnpy.org)上面的教程一步步操作。

其他作者建议使用的软件工具：
* [WingIDE](http://wingware.com/)：非常好用的Python集成开发环境（作者就是用它写的vn.py）

* [Robomongo](https://robomongo.org/)：MongoDB的图形化客户端，方便监控和修改数据

* [Sublime Text](http://www.sublimetext.com/)：针对编程的文本编辑器，当然你也可以使用Vim或者Emacs

* [PyQtGraph](http://www.pyqtgraph.org/)：适用于开发实时更新数据的图表，如Tick图、K线图、期权波动率曲线等（Matplotlib渲染开销太大，用于实盘绘图可能拖慢整个程序）

* [Visual Studio 2013](https://www.visualstudio.com/en-us/downloads/download-visual-studio-vs.aspx)：这个就不多说了（作者编译API封装用的是2013版本）

---
### 2016年vn.py项目计划

首先要感谢所有vn.py用户，是你们的热情让vn.py项目在2015年从最初单纯的交易API接口Python封装一步步成长为现在较为全面的交易程序开发框架。

截止2016年2月15日，vn.py项目在Github上收获了583个Star和362个Fork，且已有6位贡献者提交了代码。项目的用户包括：私募基金，证券自营、资管，期货公司，高校的金融研究院系，个人投资者等，机构用户加起来至少20多家（和作者交流过的）。

**总结一下项目当前取得的进展**

1. 较为丰富的Python交易和数据API接口，基本覆盖了国内所有常规交易品种（股票、期货、期权），具体包括：
	
	* CTP（vn.ctp）
	
	* 飞马（vn.femas）
	
	* LTS（vn.lts）
	
	* 金仕达黄金（vn.ksgold）
	
	* 金仕达期权（vn.ksotp）
	
	* 通联数据（vn.datayes）

2. 简洁易用的事件驱动引擎（vn.event），作为事件驱动型交易程序的核心

3. 针对如何使用API和事件驱动引擎开发交易程序的示例（vn.demo）

4. 开箱即用的实盘交易平台vn.trader（相比之下vn.demo仅建议学习用），整合了多种交易接口，并针对具体策略算法和功能开发提供了简洁易用的API，功能应用举例：
	
	* 同时登录多个交易接口，在一套界面上监控多种市场的行情和多种资产账户的资金、持仓、委托、成交情况
	
	* 支持跨市场套利（CTP期货和LTS证券）、境内外套利（CTP期货和IB外盘）、多市场数据整合实时预测走势（CTP的股指期货数据、IB的外盘A50数据、Wind的行业指数数据）等策略应用
	
	* CTA策略引擎模块，在保持易用性的同时，允许用户针对CTA类策略运行过程中委托的报撤行为进行细粒度控制（降低交易滑点、实现高频策略）

5. [官网](http://vnpy.org)和[知乎专栏](http://zhuanlan.zhihu.com/vn-py)，内容目前主要是《Python量化交易平台开发教程系列》，以及vn.py项目进展的更新

6. 官方交流QQ群262656087，管理较严格（定期清除长期潜水的成员）

**展望一下项目2016年的计划**

代码方面：

1. 完善飞创、易盛等相对小众接口的添加，这块将由社区驱动，作者主要负责代码检查和管理

2. 整理vn.py项目中API的具体版本号，保证封装接口的对应，这点已经有多位用户提起过，项目初期没有做详细记录所以很多API的版本号一时都较难对上

3. Linux上API的编译以及vn.trader支持

4. 基于VirtualBox的vn.py开发环境镜像，解决部分用户反映项目初期不知该如何搭建开发环境的问题，这个镜像会由官方长期维护下去

文章方面：

1.作者自己作为交易员的成长经历（这一年来收到好多人关于如何成为Quant、建议看什么书、怎么选学校等类似的问题，与其零散的回答不如介绍下自己的一些经历给大家参考可能更有帮助）

2. vn.trader的使用教程（目前基本除了代码里的注释什么都没有...）

3. 将ta-lib（技术分析）和quantlib（金融工程和量化）整合到vn.trader中应用的教程，解决目前策略开发过程中技术指标和量化函数缺乏的问题

4. 一套关于开发基于股指交易ETF期权的CTA策略的教程（股指期货短时间内还看不到恢复的希望，咱得另谋出路）

社区方面：

1. 重新建设官方网站，目前使用的是托管在Github Pages上的Hexo静态博客，一来功能比较有限，二来有些用户反映Github时不时会被墙，考虑基于Flask重建一个托管在国内的官网

2. 有用户提出建设互动性更强的网站作为交流平台（如论坛或者知乎Q&A类似的模式），这点在考虑中，主要制约因素是作者参与的时间，可能考虑和更多的资深用户合作是个好主意？

**最后，2016年，Happy Trading!!!**

---
### 联系作者
作者知乎名：用python的交易员，想要联系作者可以通过知乎私信

---
### License
MIT


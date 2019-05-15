# vn.py文档


* [项目简介](introduction.md)

* [安装指南](install.md)
  * [Windows](install.md#Windows)
    * [使用VNConda](install.md#使用VNConda)
    * [手动安装](install.md#手动安装) 
  * [Ubuntu](install.md#Ubuntu)

* [基本使用](quickstart.md)
  * [启动程序](quickstart.md#启动程序)
    * [图形模式](quickstart.md#图形模式)
    * [脚本模式](quickstart.md#脚本模式)
  * [连接接口](quickstart.md#连接接口)
  * [订阅行情](quickstart.md#订阅行情)
  * [委托交易](quickstart.md#委托交易)
  * [数据监控](quickstart.md#数据监控)
  * [应用模块](quickstart.md#应用模块)


* [CSV载入](csv_loader.md)
  * [初始化配置](csv_loader.md#初始化配置)
  * [数据载入](csv_loader.md#数据载入)

* [CTA策略](cta_strategy.md)
  * [模块构成](cta_strategy.md#模块构成)
  * [历史数据](cta_strategy.md#历史数据)
  * [策略开发](cta_strategy.md#策略开发)
  * [回测研究](cta_strategy.md#回测研究)
  * [参数优化](cta_strategy.md#参数优化)
  * [实盘运行](cta_strategy.md#实盘运行)


* [CTA回测](cta_backtester.md)
    * [加载启动](cta_backtester.md#加载启动)
    * [下载数据](cta_backtester.md#下载数据)
    * [策略回测](cta_backtester.md#策略回测)
      * [统计数据](cta_backtester.md#统计数据)
      * [图表分析](cta_backtester.md#图表分析)
    * [参数优化](cta_backtester.md#参数优化)
      * [穷举算法](cta_backtester.md#穷举算法)
      * [遗传算法](cta_backtester.md#遗传算法)

* [行情记录](datarecoder.md)
  * [加载启动](datarecoder.md#加载启动)
  * [开始收录](datarecoder.md#开始收录)
  * [移除记录](datarecoder.md#移除记录)
  * [停止记录](datarecoder.md#停止记录)


* [交易接口](gateway.md)
  * [如何连接](gateway.md#如何连接)
    * [加载需要用的接口](gateway.md#加载需要用的接口)
    * [配置和连接](gateway.md#配置和连接)
    * [修改json配置文件](gateway.md#修改json配置文件)
    * [查看可交易的合约](gateway.md#查看可交易的合约)
  * [接口分类](gateway.md#接口分类)
  * [接口详解](gateway.md#接口详解)
    * [CTP](gateway.md#CTP)
    * [宽睿柜台(OES)](gateway.md#宽睿柜台(OES))
    * [盈透证券(IB)](gateway.md#盈透证券(IB))
    * [富途证券(FUTU)](gateway.md#富途证券(FUTU))
    * [老虎证券(TIGER)](gateway.md#老虎证券(TIGER))
    * [BITMEX](gateway.md#BITMEX)
    * [OKEX](gateway.md#OKEX)
  
* [配置数据库](database.md)
  * [SQLite](database.md#sqlite)
  * [SQL(MySQL,PostgreSQL)](database.md#SQL(MySQL,PostgreSQL))
  * [MongoDB](database.md#mongodb)

* [RPC应用](rpc.md)

* [贡献代码](contribution.md)
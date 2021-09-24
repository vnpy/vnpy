# 2.6.0版本

## 新增
1. 增加双边报价业务的发送和撤销函数功能
2. 增加双边报价监控UI组件
3. 增加用于对接数据服务的抽象接口vnpy.trader.datafeed
4. 新增基于Arctic的MongoDB数据库接口项目vnpy_arctic
5. 新增LevelDB数据库接口项目vnpy_leveldb
6. 新增DolphinDB数据库接口项目vnpy_dolphindb

## 调整
1. 移除批量委托和批量撤单相关的函数功能
2. 移除老虎证券交易接口TigerGateway
3. 移除鑫管家交易接口XgjGateway
4. 移除AlgoTrading算法交易模块对于金纳算法服务的支持


## 剥离
1. 将米筐数据接口剥离到vnpy_rqdata项目中，并升级到2.9.38版本
2. 将行情录制模块剥离到vnpy_datarecorder项目中
3. 将K线图表模块剥离到vnpy_chartwizard项目中
4. 将SQLite数据库接口剥离到vnpy_sqlite项目中
5. 将MySQL数据库接口剥离到vnpy_mysql项目中
6. 将PostgreSQL数据库接口剥离到vnpy_postgresql项目中
7. 将MongoDB数据库接口剥离到vnpy_mongodb项目中
8. 将InfluxDB数据库接口剥离到vnpy_influxdb项目中
9. 将火币交易所相关接口剥离到vnpy_huobi项目中
10. 将Bitstamp交易所相关接口剥离到vnpy_bitstamp项目中


# 2.5.0版本
## 新增
1. 新增TTS交易系统（兼容CTP的仿真交易环境）的接口vnpy_tts（6.5.1）
2. 新增易盛启明星/北斗星兼容交易API的接口vnpy_esunny（1.0.2.2）
3. 新增BarData和TickData的成交额turnover字段

## 调整
1. 将SpreadTrading模块策略初始化时的K线价差数据加载，改为优先通过RQData查询数据
2. 在MainWindow的AboutDialog中，基于importlib_metadata模块来获取版本信息
3. 隐藏所有对话框右上角的【？】按钮
4. 将易盛外盘TapGateway的合约信息，从行情接口获取改为交易接口获取（避免外盘合约size为0的问题）
5. 改进VN Trader的异常捕捉对话框弹出方式，避免多次重复报错情况下的程序卡死崩溃

## 修复
1. 修复Linux下安装时，对于已经剥离的XTP API的自动编译操作
2. 修复PortfolioManager的UI组件，对于成交事件监听类型错误的BUG
3. 修复vnpy_rest下的Response对象缺乏text字段导致的BUG
4. 修复数字货币类接口，代理端口信息传空时，导致底层连接出错的BUG
5. 修复BitstampGateway，由于_process_request函数参数数量不匹配导致的BUG
6. 修复ArrayManager的Aroon指标计算输出结果顺序错误的BUG
7. 修复数据库管理器读写TickData时，由于缺少对localtime字段处理导致的BUG
8. 修复币安现货接口，对于不支持类型的委托（停止单等）收到推送后导致的BUG

## 剥离
1. 将融航接口剥离到vnpy_rohon项目中，并升级到6.5.1版本
2. 将CTP MINI接口剥离到vnpy_mini项目中，并升级到1.5.6版本
3. 将CTP期权接口剥离到vnpy_sopt项目中
4. 将恒生UFT柜台极速API接口剥离到vnpy_uft项目中


# 2.4.0版本

## 新增
1. 新增TickData的本地时间戳字段local_time（不带时区信息）
2. 新增基于asyncio和aiohttp实现的协程异步REST API客户端vnpy_rest项目
3. 新增基于asyncio和aiohttp实现的协程异步Websocket API客户端vnpy_websocket项目
4. 新增基于多进程模式的遗传算法优化功能
5. 新增XTP的API封装中，行情登录函数对于本地网卡地址的参数支持

## 调整
1. 将Deribit接口剥离到vnpy_deribit项目中，并升级到2.0.1版本
2. 剥离CTA策略模块下的穷举和遗传优化算法到vnpy.trader.optimize模块下
3. 遗传算法优化完成后，输出所有回测过的参数对应结果（而不只是最优结果）
4. CTA策略引擎加载策略文件时，增加模块重载的操作，使得任何策略文件修改可以立即生效
5. CTA策略引擎扫描特定目录下的策略文件时，使用glob函数（替换原有的os.walk），避免对子目录中文件的错误加载
6. 将CTA策略模块剥离到vnpy_ctastrategy项目中
7. 将CTA回测模块剥离到vnpy_ctabacktester项目中
8. 将XTP接口剥离到vnpy_xtp项目中，并升级到2.2.27.4版本
9. 将事前风控模块剥离到vnpy_riskmanager项目中
10. 将数据管理模块剥离到vnpy_datamanager项目中
11. 将Deribit接口剥离到vnpy_bybit项目中，并升级到2021.6.21版本

## 修复
1. 修复BinancesGateway由于撤单请求失败，导致委托持续处于【提交中】状态的问题
2. 修复MySQL和PostgreSQL数据库管理器删除K线数据时出错的问题
3. 修复基于aiohttp的RestClient和WebsocketClient，事件循环停止后重新启动失败的问题
4. 修复BinancesGateway由于保持会话流超时失败，导致的系统卡死问题
5. 修复HuobisGateway，订阅O3-USDT（代码中有数字）合约行情失败的问题
6. 修复BinanceGateway，使用市价下单报错的问题
7. 修复CtaBacktester基于Tick级别数据进行参数优化时，启动优化失败的问题
8. 修复ToraStockGateway和ToraOptionGateway，调用下单函数时没有返回委托号的问题
9. 修复InfluxDB数据管理器，导入数据时时间字段解析错误的问题

# 2.3.0版本

## 修复
1. 修复IbGateway断线重连后，没有自动订阅之前已订阅的合约行情问题
2. 修复CTA模块的净仓交易模式中，部分平仓部分开仓时，开仓部分下单错误的问题
3. 修复OkexfGateway，某个合约全部平仓后，持仓数量不更新为0的问题
4. 修复HuobisGateway，当行情盘口不足5档时，TickData对象初始化出错的问题
5. 修复HuobifGateway，查询历史数据时由于请求超过1999个数据点导致的失败问题
6. 修复CtpGateway对于FAK和FOK委托指令的处理错误问题
7. 修复HuobiGateway的成交数量为浮点数时，浮点数精度导致上层应用仓位计算偏差问题
8. 修复BinancesGateway，U本位合约查询历史数据失败的问题
9. 修复BinanceGateway，账户资金收不到推送更新的问题
10. 修复IbGateway，查询历史数据由于传参错误导致的查询失败问题
11. 修复IbGateway，当要查询的合约历史数据不存在时卡死的问题
12. 修复IbGateway，查询返回的合约乘数（字符串）未作转换导致的上层应用问题
13. 修复BitfinexGateway，查询的历史数据OHLC字段取值错误问题
14. 修复BarGenerator，在合成小时K线时部分情况下遗漏分钟K线收盘价更新的问题
15. 修复UftGateway，在连接ETF期权服务器时无法订阅行情的问题
16. 修复UftGateway，在连接ETF期权服务器时，对于包含毫秒的委托时间戳处理错误的问题

## 调整
1. 修改CTA模块的净仓交易模式，支持上期所和能交所的今昨仓拆分下单
2. 调整组合策略模块的回测引擎K线回放逻辑，当某个时间点K线数据缺失时，推送给策略的K线字典中不对其进行向前补齐
3. 将CTP接口和API封装，剥离到vnpy_ctp项目中
4. 将CTP穿透式测试接口和API封装，剥离到vnpy_ctptest项目中

## 新增
1. 新增DataManager在导入CSV文件时，对于时间戳时区的选择功能
2. 新增CtaStrategy模块的策略移仓助手功能，实现一键式期货换月移仓支持
3. 新增OKEX V5 API接口支持，通过vnpy_okex项目进行加载


# 2.2.0版本

## 修复
1. 修复DataManager查询数据库中K线数据范围时，开始和结束日期相反的问题
2. 修复CoinbaseGateway的行情订单簿在更新时，已经撤单的档位不删除的问题
3. 修复BybitGateway对于USDT本位永续合约，浮点数委托量会被转换为0的问题
4. 修复BinanceGateway/BinancesGateway的ConnectionResetError问题，通过关闭HTTP连接的keep-alive功能实现
5. 修复HuobisGateway在USDT本位模式下时，浮点数合约乘数转换出错的问题
6. 修复PostgreSQL数据库对接层中，save_tick_data函数由于访问interval导致保存出错的问题
7. 修复DataRecorder模块中add_bar_recording下保存录制用合约配置错误的问题
8. 修复PostgreSQL数据库对接层中，由于事务执行失败导致的后续报错问题，创建数据库对象时设置自动回滚模式（autorollback=True）
9. 修复DataManager自动更新数据时，查询数据范围由于调用老版本函数导致的错误
10. 修复RQData下载获取的历史数据浮点数精度问题
11. 修复BarGenerator在合成N小时K线时，收盘价、成交量、持仓量字段缺失的问题
12. 修复K线图表底层组件ChartWidget当绘制数据较少时，坐标轴时间点显示重复的问题
13. 修复SpreadTrading模块生成的价差盘口数据的时区信息缺失问题
14. 修复IbGateway的现货贵金属行情数据缺失最新价和时间戳的问题
15. 修复BarGenerator在合成小时级别K线时，成交量字段部分缺失的问题
16. 修复vnpy.rpc模块启用非对称加密后无法正常退出的问题
17. 修复BinancesGateway持仓更新时由于包含多条方向记录导致的持仓错误问题

## 调整
1. 修改vnpy.chart下ChartItem为按需绘制，大幅缩短图表第一次显示出来的耗时
2. 修改IbGateway的历史数据查询功能，包括所有可用时间（即欧美晚上的电子交易时段）
3. 修改DataRecorder的数据入库为定时批量写入，提高录制大量合约数据时的写入性能

## 新增
1. 新增IbGateway连接断开后的自动重连功能（每10秒检查）
2. 新增双边报价业务相关的底层数据结构和功能函数
3. 新增开平转换器OffsetConverter的净仓交易模式
4. 新增CtaStrategy模块策略模板的委托时的净仓交易可选参数
5. 新增CtaStrategy模块回测引擎中的全年交易日可选参数
6. 新增ChartWizard模块对于价差行情图表的显示支持
7. 新增MarketRadar模块的雷达信号条件提醒功能

# 2.1.9.1版本

## 修复
1. 修复RestClient中，因为pyopenssl.extract_from_urllib3引起的兼容性问题

## 调整
1. 调整OptionMaster模块中，期权链数据结构搜索平值行权价的算法，不再依赖标的物合约

## 新增
1. 新增OptionMaster模块使用合成期货作为定价标的合约的功能


# 2.1.9版本

## 修复
1. 修复BarGenerator的小时线合成时，出现同一个小时的K线重复推送两次的问题
2. 修复遗传算法优化时，因为lru_cache缓存导致的新一轮优化结果不变的问题
3. 修复RestClient发起请求时，由于requests库底层使用OpenSSL导致的WinError 10054 WSAECONNRESET的问题
4. 修复okexf、okexs、okexo三个接口收取TICK行情时，盘口数据解析错误的问题
5. 修复程序中频繁捕捉到异常时，异常捕捉对话框反复执行导致卡死的问题
6. 修复币安的现货和合约接口请求抛出SSLError异常时，未捕捉导致程序卡死的问题
7. 修复活动委托监控组件ActiveOrderMonitor，保存CSV时会将所有委托数据一起保存的问题
8. 修复XtpGateway重复发起登录操作时，出现的系统崩溃问题
9. 修复XtpGateway的股票市价委托类型映射错误问题
10. 修复DeribitGateway中对于Stop Market类型委托的支持问题，同时过滤掉Stop Limit类型委托
11. 修复BinancesGateway中，由于成交数量浮点数精度问题导致的上层应用模块（CtaStrategy）数据计算错误
12. 修复BinancesGateway中，由于合约持仓类型（应该是净仓，而非多空仓）错误，导致的上层应用模块（SpreadTrading）数据计算错误
13. 修复HuobisGateway中，初始化查询活动委托时，由于请求过快导致的限流错误

## 调整
1. 对XTP接口的行情价格数据基于合约最小价格跳动进行取整，资金保留2位小数
2. BaseMonitor保存CSV文件时，表头改为图形界面显示的中文（之前是数据的字段名英文）
3. 初始化TWAP算法时，对每轮委托数量取整到合约最小交易数量
4. 将原vnpy.trader.database中的数据库客户端拆分到独立的vnpy.database模块下
5. 对SQLite/MySQL/PostgreSQL/MongoDB/InfluxDB客户端进行代码重构优化，增加K线数据整体情况BarOverview查询功能

## 新增
1. 新增BaseMonitor数据监控UI组件（以及其子类），自动保存列宽的功能
2. 增加华鑫奇点ToraGateway对于FENS服务器连接和资金账户登录的支持，之前只支持前置机连接和用户代码登录 
3. 增加火币永续合约HuobisGateway对于USDT本位合约的支持
4. 增加InfluxDB数据库客户端vnpy.database.influx对于Tick数据储存和加载的支持
# 4.0.0版本

## 新增

1. 新增面向机器学习多因子策略的vnpy.alpha模块

## 调整

1. 核心支持版本升级到Python 3.13
2. 使用pyproject.toml统一项目配置
3. 日志功能使用loguru替代logging
4. 使用mypy优化静态类型声明
5. 使用ruff优化代码细节质量
6. 使用uv作为开发环境管理工具
7. 升级扩展模块适配4.0版本：vnpy_ctp/vnpy_ctastrategy/vnpy_sqlite/vnpy_rqdata

## 修复

1. 修复PySide6中单元格排序可能出现的乱序问题

# 3.9.4版本

## 新增

1. vnpy_tora增加登录时终端动态密钥支持
2. vnpy_taos升级支持TDengine的3.0版本

## 调整

1. vnpy_xt行情接口增加实时行情中的涨跌停价字段
2. vnpy_taos移除不必要的时区转换提高性能
3. vnpy_dolphindb优化写入大量数据时候的内存占用
4. vnpy_portfoliostrategy简化回测引擎的calculate_pnl每日盈亏计算函数
5. vnpy_tap/vnpy_tts升级pybind11封装工具库的版本，支持Python 3.12编译
6. EmailEngine发送邮件失败后，捕捉异常并输出日志

## 修复

1. vnpy_optionmaster移除不必要的价格缓存代码
2. vnpy_dolphindb修复保存overview的时区不正确问题


# 3.9.3版本

## 新增

1. 利星资管交易接口vnpy_lstar
2. 咏春大师数据服务vnpy_voltrader
3. vnpy_rpcservice增加数据服务代理工具RpcDatafeed

## 调整

1. 适配6.3.0版本以上的PySide6模块：vnpy/vnpy_ctastrategy/vnpy_ctabacktester/vnpy_portfoliostrategy/vnpy_spreadtrading/vnpy_datamanager/vnpy_algotrading/vnpy_portfoliomananger/vnpy_optionmaster
2. vnpy_uft升级3.7.4.1004版本API
3. vnpy_ib的execDetails成交回报使用本地缓存的委托记录填充交易所，解决SMART交易所字段可能发生变化的问题
4. vnpy_ib的openOrder委托回报优先使用本地缓存的委托记录，解决交易所字段可能发生变化的问题
5. vnpy_ib的查询历史数据时，使用UTC时间戳传参
6. vnpy_ib的查询历史数据时，异步返回最长等待时间延长为600秒
7. vnpy_ib的增加期权链合约数据更新结束回报
8. vnpy_ib的合约乘数支持浮点数
9. 合约信息ContractData数据类，增加单笔最大委托数量max_volume

## 修复

1. 修复vnpy_spreadtrading回测引擎clear_data时，没有清空价差仓位的问题
2. 修复vnpy_ib查询历史数据失败时的日志输出错误


# 3.9.2版本

## 新增

1. vnpy_xt增加实时行情接口XtGateway
2. vnpy_xt增加基于文件锁实现的xtdc单例运行
3. vnpy_ib增加行情退订功能
4. vnpy_ib的合约乘数支持浮点数
5. vnpy_ib增加期权链合约数据更新结束回报
6. vnpy_ctabacktester、vnpy_ctastrategy、vnpy_portfoliostrategy增加i18n国际化支持

## 调整

1. vnpy_algotrading增加委托/成交推送时，对于算法状态的过滤
2. vnpy_tushare模块的to_ts_asset函数增加ETF基金支持
3. vnpy_xt更新适配xtquant的240613.1.1版本
4. vnpy_xt开启使用期货真实夜盘时间，增加期货历史数据集合竞价K线合成支持
5. vnpy_tts更新API版本到6.7.2
6. vnpy_rohon更新API版本：行情1.4.1.3，交易30.4.1.24
7. vnpy_tap完善API日志输出功能
8. vnpy_rest发送REST请求时，增加对于json参数的支持
9. vnpy_excelrtd优化PyXLL启动时加载模块的方式
10. vnpy_spreadtrading使用线程池实现策略初始化的异步执行
11. vnpy_ib移除期权合约的自动查询功能
12. vnpy_ib缓存查询返回的IB合约数据，简化行情切片查询函数
13. vnpy_ib查询历史数据时，使用UTC时间戳传参，并将最长等待时间延长为600秒
14. vnpy_ctastrategy的绩效统计值增加基于指数移动平均计算的EWM Sharpe比率
15. vnpy_ctastrategy回测引擎的show_chart函数直接返回图表对象

## 修复

1. 修复vnpy_rhon行情登录失败时的判断逻辑问题
2. 修复vnpy_datarecorder记录价差数据时缺失的localtime字段
3. 修复vnpy_spreadtraidng从datafeed加载数据时，时间戳传参缺失时区信息的问题
4. 修复vnpy_paperaccount委托数量为0撮合之后导致的ZeroDivisionError问题
5. 修复vnpy_portoliostrategy停止策略时，没有自动撤销策略委托的功能

# 3.9.1版本

## 新增

1. 增加i18n国际化支持，以及对应的英文翻译
2. 增加CFD和SWAP品种类型枚举值
3. vnpy_ib增加COMEX、Eurex交易所支持
4. vnpy_ib增加CFD品种支持

## 调整

1. vnpy_rqdata完善对于周五夜盘数据查询的支持
2. vnpy_ib订阅行情和委托下单时，检查代码字符串是否包含空格
3. vnpy_ib解析合约对象时，增加对于ConId是否包含非数字字符的检查
4. vnpy_ib查询历史K线数据，支持更长时间段跨度（不再限制半年）
5. vnpy_da更新API版本到1.18.2.0
6. vnpy_da移除历史数据查询功能
7. vnpy_tora调整期权接口的委托号生成规则，支持上限10万数量委托
8. vnpy_xtp调整账户冻结资金的计算逻辑
9. vnpy_optionmaster增加对IB的股票期权品种支持
10. vnpy_optionmaster定价模型改为计算理论希腊值
11. vnpy_optionmaster调整对象希腊值为理论模式
12. vnpy_optionmaster调整中值隐波动的计算方法
13. vnpy_spreadtrading使用线程池实现策略初始化的异步执行
14. vnpy_postgresql支持自动重用已经打开的数据库连接
15. vnpy_ctptest更新API版本至6.7.2
16. 接口封装升级更新pybind11到2.11.1版本：vnpy_ctptest、vnpy_sopttest
17. vnpy_ctp更新API版本到6.7.2
18. 调整extract_vt_symbol函数，兼容代码中带有"."的情况，如HHI.HK-HKD-FUT.HKFE
19. 更新vnpy框架的核心依赖模块到2024年较新的版本

## 修复

1. 修复vnpy_portfoliostrategy调用stop_strategy没有撤销活动委托的问题
2. 修复vnpy_xtp的API封装中queryTickersPriceInfo底层调用错误
3. 修复RpcClient中_last_received_ping变量的类型问题


# 3.9.0版本

## 新增

1. 迅投研数据服务vnpy_xt，支持股票、期货、期权、债券、基金历史数据获取
2. vnpy_ib增加对CBOE和CBOT交易所的支持、对指数期权的支持
3. vnpy_rqdata增加对于88A2连续次主力合约的支持
4. vnpy_wind增加广期所和上期能源交易所的数据支持

## 调整

1. vnpy_sopt升级3.7.0版本API
2. vnpy_portfoliostrategy回测引擎支持交易日参数annual_days
3. K线合成器（BarGenerator）移除对于Tick时间戳的检查过滤逻辑，交由用户层负责控制过滤
4. vnpy_ib收到期权合约数据后，自动查询其切片行情数据
5. vnpy_paperaccount实现对于IB接口合约的特殊路由处理
6. 接口封装升级更新pybind11到2.11.1版本：vnpy_ctp、vnpy_sopt、vnpy_tora
7. vnpy_ctp过滤不支持的委托状态推送
8. vnpy_mysql兼容无数据库写入权限情况下的数据表初始化
9. vnpy_chartwizard支持关闭单个图表标签页
10. vnpy_portfoliostrategy移除策略后同时清除对应的策略状态缓存数据
11. vnpy_portfoliostrategy调整每日盈亏清算对象开盘持仓数据的初始化方式
12. 策略模块遗传优化函数增加ngen_size和max_workers参数


## 修复

1. 修复vnpy_tora接口中的委托部分撤单状态映射缺失
2. 修复vnpy_wind查询日线历史数据时数值存在NaN的问题
3. 修复vnpy_mongodb的Tick汇总数据的条数统计错误
4. 修复vnpy_chartwizard对于升级后的vnpy_spreadtrading价差行情显示问题
5. 修复vnpy_ctastrategy回测成交记录为空时的报错
6. 修复vnpy_ctastrategy策略初始化时，历史数据重复推送调用on_bar的问题


# 3.8.0版本

## 新增

1. K线合成器（BarGenerator）增加对日K线的合成支持
2. 基于华鑫奇点柜台的C++ API重构vnpy_tora，实现VeighNa Station加载支持
3. 新增vnpy_ib对于期权合约查询、波动率和希腊值等扩展行情数据的支持

## 调整

1. vnpy_rest/vnpy_websocket限制在Windows上改为必须使用Selector事件循环
2. vnpy_rest/vnpy_websocket客户端关闭时确保所有会话结束，并等待有异步任务完成后安全退出
3. vnpy_ctp升级6.6.9版本API
4. vnpy_ctp支持大商所的1毫秒级别行情时间戳
5. vnpy_tqsdk过滤不支持的K线频率查询并输出日志
6. vnpy_datamanager增加数据频率下按交易所显示支持，优化数据加载显示速度
7. vnpy_ctabacktester如果加载的历史数据为空，则不执行后续回测
8. vnpy_spreadtrading采用轻量级数据结构，优化图形界面更新机制
9. vnpy_spreadtrading价差子引擎之间的事件推送，不再经过事件引擎，降低延迟水平
10. vnpy_rpcservice增加对下单返回委托号的gateway_name替换处理
11. vnpy_portfoliostrategy策略模板增加引擎类型查询函数get_engine_type
12. vnpy_sec更新行情API至1.6.45.0版本，更新交易API版本至1.6.88.18版本
13. vnpy_ib更新10.19.1版本的API，恢复对于数字格式代码（ConId）的支持
14. 没有配置数据服务或者加载模块失败的情况下，使用BaseDatafeed作为数据服务
15. 遗传优化算法运行时，子进程指定使用spawn方式启动，避免数据库连接对象异常
16. 合约管理控件，增加对于期权合约的特有数据字段显示

## 修复

1. 修复vnpy_datarecorder对于新版本vnpy_spreadtrading价差数据的录制支持
2. 修复vnpy_algotrading条件委托算法StopAlgo全部成交后状态更新可能缺失的问题
3. 修复vnpy_ctastrategy策略初始化时，历史数据重复推送调用on_bar的问题
4. 修复vnpy_wind查询日线历史数据时，数值存在NaN的问题


# 3.7.0版本

## 新增

1. 新增沪股通和深股通交易所枚举值
2. 增加vnpy_tap对于Linux系统的支持
3. 增加vnpy_rqdata对于新型主力合约数据支持（切换前一日收盘价比例复权）

## 调整

1. vnpy_ctastrategy/vnpy_ctabacktester加载策略类时，过滤TargetPosTemplate模板
2. vnpy_ctp连接登录过程中，只有在授权码错误的情况下，才禁止再次发起认证
3. vnpy_uft增加对广期所GFEX的支持
4. vnpy_tqsdk增加对于output日志输出功能的支持
5. vnpy_dolphindb允许指定用户自行配置具体的数据库实例
6. vnpy_rqdata优化对于郑商所期货和期权合约的查询代码转换规则
7. vnpy_rqdata增加对广期所GFEX的支持
8. vnpy_portfoliostrategy增加回测爆仓检查
9. vnpy_portfoliostrategy策略模板增加合约乘数查询函数get_size
10. vnpy_portfoliostrategy回测加载日线和小时线数据时，不使用分段加载

## 修复

1. 修复vnpy_rpcservice中，RPC接口对于推送数据的vt前缀相关字段错误问题
2. 修复vnpy_mini中，对于INE交易所今昨仓位的特殊处理
3. 修复vnpy_datamanager中，批量数据更新时缺失output函数的问题
4. 修复vnpy_spreadtrading中，回测加载数据时优先从数据服务获取历史数据的问题，改为优先从本地数据库加载


# 3.6.0版本

## 新增

1. 新增vnpy_ctp的Mac系统支持（M1/M2）

## 调整

1. BaseDatafeed的相关功能函数增加output入参用于输出日志
2. 修改相关数据服务模块适配output参数：vnpy_rqdata/vnpy_ifind/vnpy_wind/vnpy_tushare
3. 修改相关策略应用模块适配output参数：vnpy_ctastrategy/vnpy_ctabacktester/vnpy_portfoliostrategy/vnpy_spreadtrading/vnpy_datamanager
3. OffsetConverter增加对于SHFE/INE合约的锁仓模式支持
4. 在OmsEngine中添加全局的OffsetConverter功能，不再需要各AppEngine自行维护
5. 添加CTA策略模块在执行参数优化时的最大进程数量限制参数：vnpy_ctastrategy/vnpy_ctabacktester
6. 增加穷举优化算法运行过程中基于tqdm的进度条输出
7. 增加遗传优化算法运行过程中的迭代次数进度输出
8. 增加vnpy_optionmaster模块的期权产品对应标的合约的匹配函数，不再限制产品范围
9.  升级vnpy_tts的dll链接库，解决openctp升级导致的资金不显示的问题
10. 修改vnpy_ctastrategy使用vnpy.trader.database中统一定义的时区来加载数据
11. 增加vnpy_ctastrategy策略模板的合约乘数查询函数get_size
12. 增加vnpy_spreadtrading回测中统计绩效时对于爆仓情况的检查
13. 增加vnpy_scripttrader基于vt_symbol和direction查询持仓数据的函数
14. 修改vt_positionid的字符串内容，增加gateway_name前缀标识

## 修复

1. 修复异常捕捉钩子threading_excepthook的参数错误问题
2. 修复vnpy_ib获取历史数据时的异常失败问题
3. 修复vnpy_rest/vnpy_websocket中aiohttp的代理参数proxy传空时必须为None的问题
4. 修复vnpy_optionmaster模块的Greeks监控表行数设置不足的问题
5. 修复vnpy_rqdata查询股票期权数据报错的问题
6. 修复vnpy_rqdata中RqdataGateway获取期货指数和连续合约信息时错误的问题
7. 修复vnpy_portfoliostrategy中，从缓存文件恢复数据，导致defaultdict变成dict的问题


# 3.5.0版本

## 新增

1. 新增基于米筐RQData的跨市场行情数据接口RqdataGateway
2. 新增东方财富证券EMT柜台交易接口vnpy_emt

## 调整

1. 调整vnpy_algotrading模块设计（模板、引擎），只支持单合约算法执行交易
2. 优化vnpy_algotrading的算法状态控制，增加状态枚举值，算法支持暂停和恢复运行
3. 升级vnpy_hft接口支持HFT国君统一交易网关的2.0版本API
4. 优化vnpy_portfoliostrategy的策略模板，支持持仓目标调仓交易模式

## 修复

1. 修复后台线程异常捕捉钩子函数，对于Python 3.7的语法兼容性问题
2. 修复vnpy_mysql加载历史数据时存在时段重复的问题
3. 修复vnpy_ib由于TWS客户端升级导致的委托失败问题
4. 修复vnpy_rest/vnpy_websocket对Python 3.10后asyncio的支持
5. 修复vnpy_sopt由于流控导致的委托失败时，返回【提交中】状态委托的问题


# 3.4.0版本

## 新增

1. 新增杰宜斯资管系统交易接口vnpy_jees

## 调整

1. 开启vnpy.rpc的pyzmq连接keepalive机制，避免在复杂网络环境下闲置连接的断开
2. 移除vnpy_rpcservice中服务端的EVENT_TIMER定时事件推送
3. 调整vnpy_postgresql采用批量方式写入数据，提高效率
4. 添加VeighNa Trader中的子线程异常捕捉（需要Python>=3.8）
5. 调整vnpy_ib接口查询历史K线数据时，对外汇和贵金属均采用中间价（而非成交价）
6. 增加vnpy_ctastrategy对于回测过程中资金爆仓（小于等于0）情况的检查
7. 优化vnpy_webtrader模块的加密鉴权，支持web进程关闭重启

## 修复

1. 修复vnpy.rpc模块对于23.0以上版本pyzmq的NOBLOCK兼容性问题
2. 修复vnpy_taos由于TDengine版本升级，出现d的一系列兼容问题
3. 修复vnpy_datamanager刷新数据汇总信息显示时，老数据点移除失败的问题



# 3.3.0版本

## 新增
1. 新增数据库组件vnpy.trader.database中的TickOverview对象
2. 新增掘金仿真环境交易接口vnpy_gm
3. BaseData基础数据类型增加extra字段（字典类型），用于传送任意相关数据

## 调整
1. 使用Python内置的zoneinfo库替换三方的pytz库
2. 调整相关交易接口、数据服务接口、数据库适配器、应用模块，使用新的ZoneInfo对象来标识时区信息
3. 数据库适配器接口vnpy.trader.database写入数据时，新增流式写入参数stream，提高行情录制性能


# 3.2.0版本

## 新增
1. 添加广州期货交易所枚举值字段GFEX
2. 新增CTP期权（ETF）穿透式测试接口vnpy_sopttest
3. 新增Currency.CAD（加元）枚举值
4. 新增Exchange.TSE（多伦多交易所）和Exchange.AMEX（美洲交易所）枚举值
5. 新增vnpy_taos，涛思数据TDengine时序数据库适配器
5. 新增vnpy_timescaledb，TimescaleDB时序数据库适配器

## 调整
1. 更新vnpy_ctp/vnpy_ctptest支持广州期货交易所
2. 更新vnpy_tora的现货API接口到最新版本：API_Python3.7_交易_v4.0.3_20220222
3. 更新vnpy_tora的期权API接口到最新版本：API_Python3.7_v1.3.2_20211201
4. 更新vnpy_esunny/vnpy_tap添加关闭接口时对于API退出函数的调用
5. 移除vnpy_ctastrategy/vnpy_ctabacktester/vnpy_optionmaster的反向合约支持
6. 增加vnpy_ib对于沪股通、深股通、多伦多交易所、美洲交易所的支持
7. 增加vnpy_ib对于指数行情数据的支持
8. 添加vnpy_ctastrategy策略交易管理界面的策略实例查找功能

## 修复

1. 修复vnpy_mongodb中K线数据量统计的问题（使用新的count_documents函数）
2. 修复由于PySide6对象销毁先于__del__调用，导致的BaseMonitor衍生组件无法自动保存界面状态的问题



# 3.1.0版本

## 新增
1. 新增恒生云UF2.0证券仿真环境交易接口vnpy_uf
2. 新增火象投教仿真环境交易接口vnpy_hx

## 调整
1. 升级tzlocal库的版本到4.2，消除get_localzone()函数的warning
2. 完善代码中函数和变量类型提示
3. 使用QtCore.Signal代替老的QtCore.pyqtSignal
4. 优化vnpy_rohon接口的委托成交相关细节功能
5. 更新vnpy_xtp到2.2.32.2.0版本XTP API，支持上交所新债系统
6. 优化vnpy_mongodb的数据写入速度，基于pymongo 4.0版本的批量写入功能
7. 增加vnpy_ctp对于委托函数返回值为非0（请求发送失败）状态的处理
8. 对vnpy_ctastrategy和vnpy_ctabacktester的策略模板下拉框中内容，改为基于首字母排序

## 修复
1. 修复vnpy_optionmaster模块希腊值监控组件的数据刷新问题
2. 修复vnpy_mongodb由于时间戳的时区信息确实，导致的数据加载范围问题
3. 修复vnpy_tts的sdist源代码打包缺失lib文件的问题
4. 修复vnpy_rqdata由于查询返回数据为NaN导致的解析问题


# 3.0.0版本

## 调整
1. 移除api、gateway、app子模块的目录
2. 移除requirements.txt对于插件的默认依赖
3. 简化重构rpc子模块，定位于可靠环境下跨进程通讯（本机、局域网）
4. 移除rpc子模块对于鉴权的支持
5. 调整rpc子模块中的心跳机制的实现方式
6. 移除基于QScintilla开发的代码编辑器，改用VSCode打开代码
7. 优化MainWindow主窗口中，对于QAction按钮图标的加载逻辑
8. MainEngine添加交易接口时，支持自定义接口名称

## 修复
1. 使用非原生窗口菜单栏，修复Linux/Mac下【配置】按钮不显示的问题


# 2.9.0版本

## 新增
1. 新增顶点HTS柜台交易接口vnpy_hts

## 调整
1. 移除恒生期权hsoption接口
2. vnpy_webtrader增加对于自定义监听地址和端口的支持
3. vnpy_mongodb锁定pymongo的依赖版本为3.12.3
4. vnpy_udata安装脚本中添加hs_udata库的依赖
5. vnpy_uft升级使用3.7.2.4版本的恒生API接口

## 剥离
2. 将国泰君安证券统一接入网关交易接口剥离到vnpy_hft项目中
3. 将顶点飞创交易接口剥离到vnpy_sec项目中
4. 将RPC服务和接口剥离到vnpy_rpcservice项目中

## 修复
1. 修复vnpy_tora撤单时，由于撤单编号和委托编号冲突导致的撤单失败问题
2. 修复vnpy_tora股票委托状态中【未成交】状态的错误映射问题
3. 修复vnpy_ctabacktester中，回测开始日期编辑框的数据缓存问题
4. 修复vnpy_udata中，分段下载数据时，可能进入死循环的问题
5. 修复vnpy_udata中，修复下载的数据量为空时，出现的异常报错问题
6. 修复vnpy_dolphindb中，合约名带有符号时数据无法读取问题


# 2.8.0版本

## 新增
1. 新增东证OST柜台交易接口vnpy_ost
2. 增加投资组合策略模块的策略参数优化功能

## 修复
1. 修复部分C++接口模块剥离后，遗留的安装脚本编译代码导致的报错问题
2. 修复vnpy_xtp订阅深交所行情后，可能出现的闪退问题
3. 修复vnpy_tushare部分数据字段为None时，导致的数据错误
4. 修复vnpy_mini，在夜盘换日时上期所行情时间戳的日期字段误差问题
5. 修复vnpy_uft的ETF期权合约信息解析缺失的问题
6. 修复vnpy_wind下载数据存在缺失时的N/A解析问题
7. 修复vnpy_webtrader的html静态文件缺失的问题
8. 修复vnpy_dolphindb存储Tick数据时的数据类型问题
9. 修复vnpy_dolphindb读取数据为空时的BUG
10. 修复vnpy_esunny查询黄金TD合约的合约乘数为0的问题
11. 修复vnpy_ctastrategy策略初始化读取布尔值false失败的问题
12. 修复vnpy_rohon的期权合约字段赋值错误的问题
13. 修复vnpy_leveldb的Linux安装依赖库问题

## 调整
1. 移除老版本基于requests库的RestClient客户端
2. 移除老版本基于websocket-client库的WebsocketClient客户端
3. vnpy_tts增加对上交所和深交所股票模拟交易的支持
4. 移除vnpy_ctp的期权询价指令支持
5. 增加vnpy_ctp的授权码验证失败后，避免重复操作的功能
6. 优化vnpy_uft的断线重连行情订阅逻辑
7. 增加vnpy_arctic对于用户名和密码的鉴权功能
8. 增加vnpy_mini对于股指期权的支持

## 剥离
1. 将华鑫奇点交易接口剥离到vnpy_tora项目中，并升级到4.0版本
2. 将飞马交易接口剥离到vnpy_femas项目中
3. 将金仕达黄金接口剥离到vnpy_ksgold项目中
4. 将投资组合策略模块剥离到vnpy_portfoliostrategy项目中
5. 将Excel RTD模块剥离到vnpy_excelrtd项目中
6. 将本地仿真模拟交易模块剥离到vnpy_paperaccount项目中

# 2.7.0版本

## 新增
1. 新增天软数据服务项目vnpy_tinysoft
2. 新增同花顺iFinD数据服务项目vnpy_ifind
3. 新增dYdx交易接口vnpy_dydx
4. 新增万得Wind数据服务项目vnpy_wind
5. 新增PortfolioStrategy专用的PortfolioBarGenerator

## 调整
1. 移除KasiaGateway
4. 移除MarketRadarApp
5. 算法交易模块中移除套利和网格两个非执行类算法
6. vnpy_tushare数据服务，增加持仓量和成交额字段
8. vnpy_datamanager数据管理器，查询的K线信息按合约代码排序显示
13. vnpy_dolphindb优化数据的加载解析速度
14. vnpy_influxdb采用pandas解析CSV数据，提高整体速度

## 修复
1. 修复vnpy_ctp的CtpGateway，在夜盘换日时上期所行情时间戳的日期字段误差问题
2. 修复vnpy_arctic的数据重复写入时出现的错误覆盖问题

## 剥离
1. 将InteractiveBrokers交易接口剥离到vnpy_ib项目中
2. 将飞鼠交易接口剥离到vnpy_sgit项目中
3. 将易盛外盘交易接口剥离到vnpy_tap项目中
4. 将直达期货交易接口剥离到vnpy_da项目中
5. 将算法交易模块剥离到vnpy_algotrading项目中
6. 将脚本交易模块剥离到vnpy_scripttrader项目中
7. 将交易组合管理模块剥离到vnpy_portfoliomanager项目中


# 2.6.0版本

## 新增
1. 增加双边报价业务的发送和撤销函数功能
2. 增加双边报价监控UI组件
3. 增加用于对接数据库的抽象接口vnpy.trader.database
4. 新增基于Arctic的MongoDB数据库接口项目vnpy_arctic
5. 新增LevelDB数据库接口项目vnpy_leveldb
6. 新增DolphinDB数据库接口项目vnpy_dolphindb
7. 增加用于对接数据服务的抽象接口vnpy.trader.datafeed
8. 新增TuShare数据服务项目vnpy_tushare
8. 新增恒生UData数据服务项目vnpy_udata
8. 新增天勤TQSDK数据服务项目vnpy_tqsdk
8. 新增CoinAPI数据服务项目vnpy_coinapi

## 调整
1. 移除批量委托和批量撤单相关的函数功能
2. 移除老虎证券交易接口TigerGateway
3. 移除鑫管家交易接口XgjGateway
4. 移除AlgoTrading算法交易模块对于金纳算法服务的支持
5. RestClient增加对操作系统代理配置的支持
6. RestClient和WebsocketClient的默认异常处理逻辑由抛出异常修改为打印输出
7. 价差交易模块移除对反向合约、线性价差、开平字段的支持
8. 价差交易模块优化对灵活价差的支持，优化价差行情推送过滤判断
9. 价差交易算法停止时，等待全部委托结束、各条腿平衡后，再结束算法

## 修复
1. 修复在Linux/Mac系统上，运行多进程优化时的进程启动错误
2. 修复WebsocketClient由于心跳机制不完善，导致的频繁断线问题

## 剥离
1. 将米筐数据接口剥离到vnpy_rqdata项目中，并升级到2.9.38版本
2. 将行情录制模块剥离到vnpy_datarecorder项目中
3. 将K线图表模块剥离到vnpy_chartwizard项目中
4. 将SQLite数据库接口剥离到vnpy_sqlite项目中
5. 将MySQL数据库接口剥离到vnpy_mysql项目中
6. 将PostgreSQL数据库接口剥离到vnpy_postgresql项目中
7. 将MongoDB数据库接口剥离到vnpy_mongodb项目中
8. 将InfluxDB数据库接口剥离到vnpy_influxdb项目中
13. 将期权波动率交易模块剥离到vnpy_optionmaster项目中


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
5. 改进VeighNa Trader的异常捕捉对话框弹出方式，避免多次重复报错情况下的程序卡死崩溃

## 修复
1. 修复Linux下安装时，对于已经剥离的XTP API的自动编译操作
2. 修复PortfolioManager的UI组件，对于成交事件监听类型错误的BUG
3. 修复vnpy_rest下的Response对象缺乏text字段导致的BUG
4. 修复RestClient，代理端口信息传空时，导致底层连接出错的BUG
6. 修复ArrayManager的Aroon指标计算输出结果顺序错误的BUG
7. 修复数据库管理器读写TickData时，由于缺少对localtime字段处理导致的BUG

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
2. 剥离CTA策略模块下的穷举和遗传优化算法到vnpy.trader.optimize模块下
3. 遗传算法优化完成后，输出所有回测过的参数对应结果（而不只是最优结果）
4. CTA策略引擎加载策略文件时，增加模块重载的操作，使得任何策略文件修改可以立即生效
5. CTA策略引擎扫描特定目录下的策略文件时，使用glob函数（替换原有的os.walk），避免对子目录中文件的错误加载
6. 将CTA策略模块剥离到vnpy_ctastrategy项目中
7. 将CTA回测模块剥离到vnpy_ctabacktester项目中
8. 将XTP接口剥离到vnpy_xtp项目中，并升级到2.2.27.4版本
9. 将事前风控模块剥离到vnpy_riskmanager项目中
10. 将数据管理模块剥离到vnpy_datamanager项目中

## 修复
2. 修复MySQL和PostgreSQL数据库管理器删除K线数据时出错的问题
3. 修复基于aiohttp的RestClient和WebsocketClient，事件循环停止后重新启动失败的问题
7. 修复CtaBacktester基于Tick级别数据进行参数优化时，启动优化失败的问题
8. 修复ToraStockGateway和ToraOptionGateway，调用下单函数时没有返回委托号的问题
9. 修复InfluxDB数据管理器，导入数据时时间字段解析错误的问题

# 2.3.0版本

## 修复
1. 修复IbGateway断线重连后，没有自动订阅之前已订阅的合约行情问题
2. 修复CTA模块的净仓交易模式中，部分平仓部分开仓时，开仓部分下单错误的问题
6. 修复CtpGateway对于FAK和FOK委托指令的处理错误问题
10. 修复IbGateway，查询历史数据由于传参错误导致的查询失败问题
11. 修复IbGateway，当要查询的合约历史数据不存在时卡死的问题
12. 修复IbGateway，查询返回的合约乘数（字符串）未作转换导致的上层应用问题
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


# 2.2.0版本

## 修复
1. 修复DataManager查询数据库中K线数据范围时，开始和结束日期相反的问题
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
5. 修复程序中频繁捕捉到异常时，异常捕捉对话框反复执行导致卡死的问题
7. 修复活动委托监控组件ActiveOrderMonitor，保存CSV时会将所有委托数据一起保存的问题
8. 修复XtpGateway重复发起登录操作时，出现的系统崩溃问题
9. 修复XtpGateway的股票市价委托类型映射错误问题

## 调整
1. 对XTP接口的行情价格数据基于合约最小价格跳动进行取整，资金保留2位小数
2. BaseMonitor保存CSV文件时，表头改为图形界面显示的中文（之前是数据的字段名英文）
3. 初始化TWAP算法时，对每轮委托数量取整到合约最小交易数量
4. 将原vnpy.trader.database中的数据库客户端拆分到独立的vnpy.database模块下
5. 对SQLite/MySQL/PostgreSQL/MongoDB/InfluxDB客户端进行代码重构优化，增加K线数据整体情况BarOverview查询功能

## 新增
1. 新增BaseMonitor数据监控UI组件（以及其子类），自动保存列宽的功能
2. 增加华鑫奇点ToraGateway对于FENS服务器连接和资金账户登录的支持，之前只支持前置机连接和用户代码登录 
4. 增加InfluxDB数据库客户端vnpy.database.influx对于Tick数据储存和加载的支持
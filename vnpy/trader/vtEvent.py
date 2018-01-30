# encoding: UTF-8

'''
本文件仅用于存放对于事件类型常量的定义。

由于python中不存在真正的常量概念，因此选择使用全大写的变量名来代替常量。
这里设计的命名规则以EVENT_前缀开头。

常量的内容通常选择一个能够代表真实意义的字符串（便于理解）。

建议将所有的常量定义放在该文件中，便于检查是否存在重复的现象。
'''
print( 'load vtEvent.py')

# 导入基础模块vnpy.event.EventEngine等
from vnpy.event import *

# 系统相关
EVENT_TIMER = 'eTimer'                  # 计时器事件，每隔1秒发送一次
EVENT_LOG = 'eLog'                      # 日志事件，全局通用

# Gateway相关
EVENT_TICK = 'eTick.'                   # TICK行情事件，可后接具体的vtSymbol
EVENT_TRADE = 'eTrade.'                 # 成交回报事件
EVENT_ORDER = 'eOrder.'                 # 报单回报事件
EVENT_POSITION = 'ePosition.'           # 持仓回报事件
EVENT_ACCOUNT = 'eAccount.'             # 账户回报事件
EVENT_CONTRACT = 'eContract.'           # 合约基础信息回报事件
EVENT_ERROR = 'eError.'                 # 错误回报事件

# add by incenselee
EVENT_ACCOUNT_LOSS = 'eAccountLoss'     # 账户亏损事件
EVENT_FULL_MONITOR = 'eFullMonitor'     # 全周期监控
EVENT_ON_BAR = 'eOnBar'                 # OnBar事件
EVENT_WARNING = 'eWarning'              # 全局告警信息
EVENT_CRITICAL = 'eCritical'            # 全局严重信息
EVENT_NOTIFICATION = 'eNotification'    # 全局通知
EVENT_SIGNAL = 'eSignal'                # 信号通知
EVENT_STATUS = 'eStatus'                # 服务状态

# CTA模块相关
EVENT_CTA_LOG = 'eCtaLog'               # CTA相关的日志事件
EVENT_CTA_STRATEGY = 'eCtaStrategy.'    # CTA策略状态变化事件

# 行情记录模块相关
EVENT_DATARECORDER_LOG = 'eDataRecorderLog' # 行情记录日志更新事件

# Wind接口相关
EVENT_WIND_CONNECTREQ = 'eWindConnectReq'   # Wind接口请求连接事件

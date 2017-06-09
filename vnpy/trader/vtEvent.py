# encoding: UTF-8

'''
本文件基于vnpy.event.eventType，并添加更多字段
'''

from vnpy.event.eventType import *

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

# CTA模块相关
EVENT_CTA_LOG = 'eCtaLog'               # CTA相关的日志事件
EVENT_CTA_STRATEGY = 'eCtaStrategy.'    # CTA策略状态变化事件

# 行情记录模块相关
EVENT_DATARECORDER_LOG = 'eDataRecorderLog' # 行情记录日志更新事件

# Wind接口相关
EVENT_WIND_CONNECTREQ = 'eWindConnectReq'   # Wind接口请求连接事件
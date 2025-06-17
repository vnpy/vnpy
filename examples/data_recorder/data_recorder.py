"""
该程序使用VeighNa框架通过CTP接口连接到期货市场，并自动录制指定交易所和品种的行情数据。

适合初学者了解VeighNa框架的基本用法和数据录制流程。
"""

# 加载Python标准库
from logging import INFO
from time import sleep

# 加载VeighNa核心框架
from vnpy.event import EventEngine, Event
from vnpy.trader.setting import SETTINGS
from vnpy.trader.engine import MainEngine, LogEngine
from vnpy.trader.object import ContractData
from vnpy.trader.constant import Exchange, Product
from vnpy.trader.event import EVENT_CONTRACT

# 加载VeighNa插件模块
from vnpy_ctp import CtpGateway
from vnpy_datarecorder import DataRecorderApp, RecorderEngine
from vnpy_datarecorder.engine import EVENT_RECORDER_LOG


# 开启日志记录功能
# 日志对于排查问题和监控系统运行状态非常重要
SETTINGS["log.active"] = True       # 激活日志功能
SETTINGS["log.level"] = INFO        # 设置日志级别为INFO，输出详细信息
SETTINGS["log.console"] = True      # 在控制台显示日志，方便实时查看


# CTP接口登录信息
# 以下使用的是SimNow模拟账户信息，初学者可以在SimNow官网申请
ctp_setting: dict[str, str] = {
    "用户名": "888888",                       # SimNow账户名
    "密码": "123456",                         # SimNow密码
    "经纪商代码": "9999",                     # SimNow经纪商代码固定为9999
    "交易服务器": "180.168.146.187:10201",    # SimNow交易服务器地址和端口
    "行情服务器": "180.168.146.187:10211",    # SimNow行情服务器地址和端口
    "产品名称": "simnow_client_test",         # 产品名称，用于区分不同的客户端
    "授权编码": "0000000000000000"            # 授权编码，SimNow模拟账户使用默认值即可
}


# 要录制数据的交易所列表
# 可以根据需要取消注释来添加更多交易所
recording_exchanges: list[Exchange] = [
    Exchange.CFFEX,          # 中国金融期货交易所
    # Exchange.SHFE,         # 上海期货交易所
    # Exchange.DCE,          # 大连商品交易所
    # Exchange.CZCE,         # 郑州商品交易所
    # Exchange.GFEX,         # 广州期货交易所
    # Exchange.INE,          # 上海国际能源交易中心
]


# 要录制数据的品种类型
# 可以根据需要取消注释来添加更多品种
recording_products: list[Product] = [
    Product.FUTURES,        # 期货品种
    # Product.OPTION,       # 期权品种
]


def run_recorder() -> None:
    """
    运行行情录制程序

    该函数是程序的主体，按照以下步骤工作：
    1. 创建VeighNa核心组件（事件引擎、主引擎）
    2. 添加交易接口和应用模块
    3. 设置数据录制规则
    4. 连接到交易所并开始录制数据
    """
    # 创建事件引擎，负责系统内各模块间的通信
    event_engine: EventEngine = EventEngine()

    # 创建主引擎，管理系统功能模块，包括底层接口、上层应用等
    main_engine: MainEngine = MainEngine(event_engine)

    # 添加CTP接口，连接到期货市场
    main_engine.add_gateway(CtpGateway)

    # 添加数据录制引擎，用于录制Tick行情入库
    recorder_engine: RecorderEngine = main_engine.add_app(DataRecorderApp)

    # 定义合约订阅函数
    def subscribe_data(event: Event) -> None:
        """
        处理合约推送并订阅行情

        当系统接收到合约信息后，根据预设的交易所和品种过滤条件，
        自动为符合条件的合约添加行情录制任务。

        参数:
            event: 包含合约信息的事件对象
        """
        # 从事件对象中获取合约数据
        contract: ContractData = event.data

        # 判断合约是否符合录制条件
        if (
            contract.exchange in recording_exchanges    # 检查合约所属交易所是否在预设列表中
            and contract.product in recording_products  # 检查合约品种类型是否在预设列表中
        ):
            # 添加该合约的行情录制任务，vt_symbol是VeighNa中的唯一标识符，格式为"代码.交易所"
            recorder_engine.add_tick_recording(contract.vt_symbol)      # 录制Tick数据
            recorder_engine.add_bar_recording(contract.vt_symbol)       # 录制分钟K线

    # 注册合约事件处理函数，当有新合约信息推送时，会自动调用subscribe_data函数
    event_engine.register(EVENT_CONTRACT, subscribe_data)

    # 获取日志引擎并设置日志处理
    log_engine: LogEngine = main_engine.get_engine("log")

    def print_log(event: Event) -> None:
        """
        处理数据录制模块的日志事件

        将数据录制模块产生的日志信息输出到控制台和日志文件中，
        便于监控录制过程和排查问题。

        参数:
            event: 包含日志信息的事件对象
        """
        log_engine.logger.log(INFO, event.data)

    # 注册日志事件处理函数，当有新的日志推送时，会自动调用print_log函数
    event_engine.register(EVENT_RECORDER_LOG, print_log)

    # 连接CTP接口并登录，第一个参数是接口设置，第二个参数是接口名称
    main_engine.connect(ctp_setting, CtpGateway.default_name)

    # 等待30秒，CTP接口连接后需要一段时间来完成初始化
    sleep(30)

    # 提示用户程序已经开始运行，用户可以根据需要随时退出
    input(">>>>>> 高频行情数据录制已启动，正在记录数据。按回车键退出程序 <<<<<<")

    # 关闭主引擎实现安全退出，避免出现内存中未入库数据的丢失
    main_engine.close()


# Python程序的标准入口写法，直接运行此脚本时会执行run_recorder函数
if __name__ == "__main__":
    run_recorder()

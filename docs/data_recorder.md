# DataRecorder - 行情记录模块

DataRecorder是用于**实时行情收录**的模块，用户可以利用该模块记录实时Tick数据和K线数据，并载入到数据库中。

## 加载启动

### VN Station加载

启动登录VN Station后，点击【VN Trader Pro】按钮，在配置对话框中的【上层应用】栏勾选【DataRecorder】。

### 脚本加载

在启动脚本中添加如下代码：

```
# 写在顶部
from vnpy.app.data_recorder import DataRecorderApp

# 写在创建main_engine对象后
main_engine.add_app(DataRecorderApp)
```

## 启动模块

在启动模块之前，请先连接交易接口（连接方法详见基本使用篇的连接接口部分）。看到VN Trader主界面【日志栏】输出“合约信息查询成功”之后再启动模块：


请注意，目前vn.py支持的数据库为SQLite (默认数据库)/ MySQL/ PostgreSQL/ MongoDB。如果用户需要配置数据库，具体方法详见项目文档的数据库配置部分。如果用户使用MongoDB，则行情记录数据直接载入到MongoDB中。


成功连接交易接口后，在菜单栏中点击【功能】-> 【行情记录】，或者点击左侧按钮栏的图标：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_recorder/1.png)

即可启动DataRecorder，并弹出DataRecorder的UI界面，如下图所示：

![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_recorder/2.png)
  
启动DataRecorder后，模块状态为True，run()函数的while循环会被执行，可以通过添加任务实现实时行情记录。
```
def start(self):
    """"""
    self.active = True
    self.thread.start()

def run(self):
    """"""
    while self.active:
        try:
            task = self.queue.get(timeout=1)
            task_type, data = task

            if task_type == "tick":
                database_manager.save_tick_data([data])
            elif task_type == "bar":
                database_manager.save_bar_data([data])

        except Empty:
            continue

        except Exception:
            self.active = False

            info = sys.exc_info()
            event = Event(EVENT_RECORDER_EXCEPTION, info)
            self.event_engine.put(event)
```


## 开始收录

 开始收录操作：在【本地代码】栏输入需要订阅的品种，格式为vt_symbol（合约代码 + 交易所名称），如rb2112.SHFE。  然后点击右侧【K线记录】或者【Tick记录】中的【添加】选项，该品种会显示在在【K线记录列表】或者【Tick记录列表】中，如下图所示。


![](https://vnpy-doc.oss-cn-shanghai.aliyuncs.com/data_recorder/3.png)


下面介绍行情收录的具体原理：

若无合约记录的历史，用户需要先添加行情记录任务，以添加tick数据为例，add_tick_recording()函数将被调用，并依次执行下面工作：

 - 先创建tick_recordings字典；
 - 调用接口的suscribe()函数订阅行情；
 - 保存该tick_recordings字典到json文件上；
 - 推送行情记录事件。

```
def add_tick_recording(self, vt_symbol: str):
    """"""
    if vt_symbol in self.tick_recordings:
        self.write_log(f"已在Tick记录列表中：{vt_symbol}")
        return

    # For normal contract
    if Exchange.LOCAL.value not in vt_symbol:
        contract = self.main_engine.get_contract(vt_symbol)
        if not contract:
            self.write_log(f"找不到合约：{vt_symbol}")
            return

        self.tick_recordings[vt_symbol] = {
            "symbol": contract.symbol,
            "exchange": contract.exchange.value,
            "gateway_name": contract.gateway_name
        }

        self.subscribe(contract)
    # No need to subscribe for spread data
    else:
        self.tick_recordings[vt_symbol] = {}

    self.save_setting()
    self.put_event()

    self.write_log(f"添加Tick记录成功：{vt_symbol}")
```

下面对add_tick_recording()函数里面调用的子函数进行扩展：

### 订阅行情

 - 调用main_engine的suscribe()函数来订阅行情，需要填入的信息为symbol、exchange、gateway_name
```
def subscribe(self, contract: ContractData):
    """"""
    req = SubscribeRequest(
        symbol=contract.symbol,
        exchange=contract.exchange
    )
    self.main_engine.subscribe(req, contract.gateway_name)
```


### 将订阅信息保存到json文件

- 主要把tick_recordings或者bar_recordings通过save_json()函数保存到C:\Users\Administrator\\.vntrader文件夹内的data_recorder_setting.json上。
- 该json文件用于存放行情记录的任务，当每次启动行情模块后，会调用load_setting()函数来得到tick_recordings和bar_recordings字典，进而开始记录的任务。
```
setting_filename = "data_recorder_setting.json"
    def save_setting(self):
        """"""
        setting = {
            "tick": self.tick_recordings,
            "bar": self.bar_recordings
        }
        save_json(self.setting_filename, setting)

    def load_setting(self):
        """"""
        setting = load_json(self.setting_filename)
        self.tick_recordings = setting.get("tick", {})
        self.bar_recordings = setting.get("bar", {})        
```
### 推送行情记录事件

- 创建行情记录列表tick_symbols和bar_symbols，并且缓存在data字典里；
- 创建evnte对象，其类型是EVENT_RECORDER_UPDATE，内容是data字典；
- 调用event_engine的put()函数推送event事件。

```
def put_event(self):
    """"""
    tick_symbols = list(self.tick_recordings.keys())
    tick_symbols.sort()

    bar_symbols = list(self.bar_recordings.keys())
    bar_symbols.sort()

    data = {
        "tick": tick_symbols,
        "bar": bar_symbols
    }

    event = Event(
        EVENT_RECORDER_UPDATE,
        data
    )
    self.event_engine.put(event)
```

&nbsp;

### 注册行情记录事件

register_event()函数分别注册2种事件：EVENT_CONTRACT、EVENT_TICK
- EVENT_CONTRACT事件，调用process_contract_event()函数: 从tick_recordings和bar_recordings字典获取需要订阅的合约品种；然后使用subscribe()函数进行订阅行情。
- EVENT_TICK事件，调用的是process_tick_event()函数：从tick_recordings和bar_recordings字典获取需要订阅的合约品种；然后使用record_tick()和record_bar()函数，把行情记录任务推送到queue队列中等待执行。

```
def register_event(self):
    """"""
    self.event_engine.register(EVENT_TICK, self.process_tick_event)
    self.event_engine.register(EVENT_CONTRACT, self.process_contract_event)

def process_tick_event(self, event: Event):
    """"""
    tick = event.data

    if tick.vt_symbol in self.tick_recordings:
        self.record_tick(tick)

    if tick.vt_symbol in self.bar_recordings:
        bg = self.get_bar_generator(tick.vt_symbol)
        bg.update_tick(tick)

def process_contract_event(self, event: Event):
    """"""
    contract = event.data
    vt_symbol = contract.vt_symbol

    if (vt_symbol in self.tick_recordings or vt_symbol in self.bar_recordings):
        self.subscribe(contract)

def record_tick(self, tick: TickData):
    """"""
    task = ("tick", copy(tick))
    self.queue.put(task)

def record_bar(self, bar: BarData):
    """"""
    task = ("bar", copy(bar))
    self.queue.put(task)

def get_bar_generator(self, vt_symbol: str):
    """"""
    bg = self.bar_generators.get(vt_symbol, None)

    if not bg:
        bg = BarGenerator(self.record_bar)
        self.bar_generators[vt_symbol] = bg

    return bg
```



### 执行记录行情任务

 - 在while循环中，从queue队列读取任务，调用save_tick_data()或者save_bar_data()函数来记录数据，并且载入到数据库中。
```
def run(self):
    """"""
    while self.active:
        try:
            task = self.queue.get(timeout=1)
            task_type, data = task

            if task_type == "tick":
                database_manager.save_tick_data([data])
            elif task_type == "bar":
                database_manager.save_bar_data([data])

        except Empty:
            continue
```

## 移除记录

移除记录操作：首先输入需要移除合约品种的本地代码，如rb1905.SHFE。该本地代码必须在【Tick记录】栏或者【K线记录】栏中。随后在对应的栏右侧点击【移除】按钮即可，如下图所示：

下面展示代码运作原理：
- 从tick_recordings字典移除vt_symbol
- 调用save_setting()函数保存json配置文件
- 推送最新的tick_recordings字典来继续记录行情，原来移除合约品种不再记录。
```
def remove_tick_recording(self, vt_symbol: str):
    """"""
    if vt_symbol not in self.tick_recordings:
        self.write_log(f"不在Tick记录列表中：{vt_symbol}")
        return

    self.tick_recordings.pop(vt_symbol)
    self.save_setting()
    self.put_event()

    self.write_log(f"移除Tick记录成功：{vt_symbol}")
```

## 停止记录

停止记录操作：只需手动关闭行情记录模块窗口就停止记录行情。

下面展示代码运作原理：
- 记录行情状态改为False, 停止while循环；
- 调用join()函数关掉线程。

```
def close(self):
    """"""
    self.active = False

    if self.thread.isAlive():
        self.thread.join()
```
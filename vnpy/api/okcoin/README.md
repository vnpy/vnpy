# vn.okcoin

贡献者：量衍投资

### 简介
OkCoin的比特币交易接口，基于Websocket API开发，实现了以下功能：

1. 发送、撤销委托

2. 查询委托、持仓、资金、成交历史

3. 实时行情、成交、资金更新的推送

### 特点
相比较于[OkCoin官方](http://github.com/OKCoin/websocket/tree/master/python)给出的Python API实现，vn.okcoin的一些特点：

1. 同时支持OkCoin的中国站和国际站交易，根据用户连接的站点会在内部自动切换结算货币（CNY、USD）

2. 采用面向对象的接口设计模式，接近国内CTP接口的风格，并对主动函数的调用参数做了大幅简化

3. 数据解包和签名生成两个热点函数使用了更加高效的实现方式

### 参数命名
函数的参数命名针对金融领域用户的习惯做了一些修改，具体对应如下：

* expiry：原生命名的contract_type
* order: 原生命名的match_price
* leverage：原生命名的lever_rate
* page：原生命名的current_page
* length：原生命名的page_length

### API版本
日期：2016-06-29

链接：[http://www.okcoin.com/about/ws_getStarted.do](http://www.okcoin.com/about/ws_getStarted.do)


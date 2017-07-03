# encoding: UTF-8

from vnshcifco import ShcifcoApi, PERIOD_1MIN


if __name__ == "__main__":
    ip = '101.231.179.199'
    port  = '10102'
    token = 'testd2cda34b2d317779e812eb84ee4224a6_qpweqf1'
    symbol = 'cu1709'
    
    # 创建API对象
    api = ShcifcoApi(ip, port, token)
    
    # 获取最新tick
    print api.getLastTick(symbol)
    
    # 获取最新价格
    print api.getLastPrice(symbol)
    
    # 获取最新分钟线
    print api.getLastBar(symbol)
    
    # 获取历史分钟线
    print api.getHisBar(symbol, 502, period=PERIOD_1MIN)
    
    
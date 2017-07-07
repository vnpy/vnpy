# encoding: UTF-8

from vnshcifco import ShcifcoApi, PERIOD_1MIN


if __name__ == "__main__":
    ip = '180.169.126.123'
    port  = '45065'
    token = '请联系上海中期申请'
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
    print api.getHisBar(symbol, 500, period=PERIOD_1MIN)
    
    
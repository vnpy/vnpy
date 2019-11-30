# encoding: UTF-8

from uuid import uuid1
import json
from vnpy.amqp.producer import task_creator
from vnpy.trader.constant import Direction

if __name__ == '__main__':
    import datetime
    import time
    p = task_creator(host='192.168.0.202')
    while True:
        time.sleep(10)
        mission = {}
        mission.update({'id':str(uuid1())})
        mission.update({'templateName': u'TWAP 时间加权平均'})
        mission.update({'direction': Direction.LONG})
        mission.update({'vtSymbol': '518880'})
        mission.update({'is_stock': True})
        mission.update({'totalVolume': 300})
        mission.update({'target_price': 3.20})
        mission.update({'minVolume': 100})
        mission.update({'orderTime': datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')})
        msg = json.dumps(mission)
        print(u'[x] create task :{}'.format(msg))
        p.pub(msg)
        break

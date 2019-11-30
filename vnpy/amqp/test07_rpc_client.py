# encoding: UTF-8

from .producer import rpc_client
from uuid import uuid1
import json
import argparse


def cb_function(*args):
    print('resp call back')
    for arg in args:
        if isinstance(arg, bytes):
            print(u'{}'.format(arg.decode('utf-8')))
        else:
            print(u'{}'.format(arg))


if __name__ == '__main__':
    # 参数分析
    parser = argparse.ArgumentParser()

    parser.add_argument('-s', '--host', type=str, default='localhost',
                        help='rabbit mq host')
    parser.add_argument('-p', '--port', type=int, default=5672,
                        help='rabbit mq port')
    parser.add_argument('-U', '--user', type=str, default='admin',
                        help='rabbit mq user')
    parser.add_argument('-P', '--password', type=str, default='admin',
                        help='rabbit mq password')
    parser.add_argument('-x', '--exchange', type=str, default='exchange',
                        help='rabbit mq exchange')
    parser.add_argument('-r', '--routing_key', type=str, default='default',
                        help='rabbit mq routing_key')
    args = parser.parse_args()

    import time

    c = rpc_client(host=args.host, port=args.port, user=args.user,
                   password=args.password, exchange=args.exchange,
                   routing_key=args.routing_key)

    counter = 0
    while True:
        time.sleep(10)
        mission = {'method': 'get_strategy_names'}
        params = {}
        mission.update({'params': params})
        msg = json.dumps(mission)
        print(u'[x] rpc call :{}'.format(msg))
        c.call(msg, str(uuid1()), cb_function)
        counter += 1

        if counter > 1:
            break

    print('exit')
    c.exit()

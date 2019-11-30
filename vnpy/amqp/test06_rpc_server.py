import os, sys, copy
# 将repostory的目录i，作为根目录，添加到系统环境中。
ROOT_PATH = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))
sys.path.append(ROOT_PATH)

routing_key = 'default'

from vnpy.amqp.consumer import rpc_server

import argparse

def test_func01(p1,p2,p3):
    print('test_func01:', p1, p2, p3)
    return p1+p2+p3

def test_func02(p1, p2=0):
    print('test_func02:', p1, p2)
    return str(p1 + p2)

def get_strategy_names():
    print(u'{}'.format(routing_key))
    return ['stratege_name_01', 'strategy_name_02']


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
    parser.add_argument('-q', '--queue', type=str, default='queue',
                        help='rabbit mq queue')
    parser.add_argument('-r', '--routing_key', type=str, default='default',
                        help='rabbit mq routing_key')
    args = parser.parse_args()

    routing_key = copy.copy(args.routing_key)

    from time import sleep
    s = rpc_server(host=args.host,
                   port=args.port,
                   user=args.user,
                   password=args.password,
                   exchange=args.exchange,
                   queue=args.queue,
                   routing_key=args.routing_key)

    s.register_method('test_01', test_func01)
    s.register_method('test_02', test_func02)
    s.register_method('get_strategy_names', get_strategy_names)

    s.start()
    while True:
        sleep(1)

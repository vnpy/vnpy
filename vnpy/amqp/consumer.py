# encoding: UTF-8
# 消息消费者类（集合）
import json
import pika
import random
import traceback
from vnpy.amqp.base import base_broker


#   模式1：接收者
class receiver(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin', exchange='x',
                 queue='recv.{}'.format(random.randint(0, 1000000)), routing_key='default'):
        super().__init__(host=host, port=port, user=user,
                         password=password)

        # 唯一匹配
        self.routing_key = routing_key

        self.queue = queue
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

        self.queue = self.channel.queue_declare(
            queue='', auto_delete=True, exclusive=True).method.queue
        self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                routing_key=self.routing_key)          # 队列名采用服务端分配的临时队列
        # self.channel.basic_qos(prefetch_count=1)

    def callback(self, chan, method_frame, _header_frame, body, userdata=None):
        print(1)
        print(" [x] received: %r" % body)

    def subscribe(self):
        # 消息接收
        self.channel.basic_consume(self.queue, self.callback, auto_ack=True)
        self.channel.start_consuming()

    def start(self):
        try:
            self.subscribe()
        except Exception as e:
            print(e)
            self.start()


#  模式2：（执行）接收者
class worker(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin', exchange='x_work_queue',
                 queue='task_queue', routing_key='default'):
        super().__init__(host=host, port=port, user=user, password=password)

        # 唯一匹配
        self.routing_key = routing_key
        self.exchange = exchange

        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      durable=True)

        self.queue = self.channel.queue_declare(queue=queue, durable=True).method.queue
        print('worker use exchange:{},queue:{}'.format(exchange, self.queue))
        self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                routing_key=self.routing_key)          # 队列名采用服务端分配的临时队列

        # 每个worker只执行一个
        self.channel.basic_qos(prefetch_count=1)

    def callback(self, chan, method_frame, _header_frame, body, userdata=None):
        print(1)
        print(" [x] received task: %r" % body)
        chan.basic_ack(delivery_tag=method_frame.delivery_tag)
        print(" [x] task finished ")

    def subscribe(self):
        print('worker subscribed')
        # 消息接收
        self.channel.basic_consume(self.queue, self.callback, auto_ack=False)
        self.channel.start_consuming()

    def start(self):
        print('worker start')
        try:
            self.subscribe()
        except Exception as e:
            print(str(e))
            traceback.print_exc()


# 模式3：发布 / 订阅（Pub/Sub）模式, 订阅者
class subscriber(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 exchange='x_fanout', queue='sub.{}'.format(random.randint(0, 1000000)),
                 routing_key='default'):
        super().__init__(host=host, port=port, user=user, password=password)
        self.queue = queue
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='fanout',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)
        self.routing_key = routing_key

        # 队列名采用服务端分配的临时队列
        self.queue = self.channel.queue_declare(
            queue='', auto_delete=True, exclusive=True).method.queue
        self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                routing_key=self.routing_key)

        # 缺省回调函数地址
        self.cb_func = self.callback

    def set_callback(self, cb_func):
        self.cb_func = cb_func

    def callback(self, chan, method_frame, _header_frame, body, userdata=None):
        print(1)
        print(" [x] %r" % body)

    def subscribe(self):
        self.channel.basic_consume(self.queue, self.cb_func, auto_ack=True)
        self.channel.start_consuming()
        # self.channel.basic_consume(
        #     self.callback, queue=self.queue_name, no_ack=True)  # 消息接收

    def start(self):
        try:
            self.subscribe()
        except Exception as ex:
            print('subscriber exception:{}'.format(str(ex)))
            traceback.print_exc()


# 模式4： 路由模式
class subscriber_routing(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 exchange='x_direct', queue='sub_r.{}'.format(random.randint(0, 1000000)), routing_keys=['default']):
        super().__init__(host=host, port=port, user=user,
                         password=password)
        self.queue = queue
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)
        # 队列名采用服务端分配的临时队列
        self.queue = self.channel.queue_declare(
            queue='', auto_delete=True, exclusive=True).method.queue

        # 逐一绑定所有的routing 标签
        for routing_key in routing_keys:
            self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                    routing_key=routing_key)

    def callback(self, chan, method_frame, _header_frame, body, userdata=None):
        print(1)
        print(" [x] %r" % body)

    def subscribe(self):
        self.channel.basic_consume(self.queue, self.callback, auto_ack=True)
        self.channel.start_consuming()

    def start(self):
        try:
            self.subscribe()
        except Exception as e:
            print(e)
            self.start()


#  模式5：主题模式
class subscriber_topic(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 exchange='x_topic', queue='sub_t.{}'.format(random.randint(0, 1000000)), routing_keys=['default']):
        super().__init__(host=host, port=port, user=user,
                         password=password)
        self.queue = queue
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='topic',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)
        # 队列名采用服务端分配的临时队列
        self.queue = self.channel.queue_declare(
            queue='', auto_delete=True, exclusive=True).method.queue

        # 逐一绑定所有的routing 标签
        for routing_key in routing_keys:
            self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                    routing_key=routing_key)

    def callback(self, chan, method_frame, _header_frame, body, userdata=None):
        print(1)
        print(" [x] %r" % body)

    def subscribe(self):
        self.channel.basic_consume(self.queue, self.callback, auto_ack=True)
        self.channel.start_consuming()

    def start(self):
        try:
            self.subscribe()
        except Exception as e:
            print(e)
            self.start()


# 模式6：RPC模式 （服务端)
class rpc_server(base_broker):
    # 接收:
    #  exchange: x_rpc
    #  queue: rpc_queue
    #  routing_key: gateway_name
    # 发送执行结果:
    #
    def __init__(self, host='localhost', port=5672, user='admin', password='admin', exchange='x_rpc',
                 queue='rpc_queue', routing_key='default'):
        super().__init__(host=host, port=port, user=user,
                         password=password)

        self.exchange = exchange
        # 唯一匹配
        self.routing_key = routing_key

        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

        # 队列名采用指定队列( 若建立多个server方式随机分配任务，使用指定queue）
        self.queue = queue
        self.channel.queue_declare(queue=self.queue, auto_delete=True)

        # 绑定 exchange->queue->channel,指定routing_key
        self.channel.queue_bind(queue=self.queue, exchange=exchange,
                                routing_key=self.routing_key)
        # 支持多个订阅
        self.channel.basic_qos(prefetch_count=1)
        # method
        self.method_dict = {}

    def register_method(self, method_name, func):
        """登记方法名称与调用函数"""
        self.method_dict.update({method_name: func})

    def on_request(self, chan, method_frame, _header_frame, body, userdata=None):
        """
        响应rpc请求得处理函数
        :param chan:
        :param method_frame:
        :param _header_frame:
        :param body:
        :param userdata:
        :return:
        """
        if isinstance(body, bytes):
            body = body.decode('utf-8')
        if isinstance(body, str):
            body = json.loads(body)
        print(" [RPC Server] on_request: %r" % body)
        # 判断body内容类型
        if not isinstance(body, dict):
            print(u'请求不是dict格式')
            resp_data = {'ret_code': -1, 'err_msg': u'请求不是dict格式'}
            self.reply(chan, resp_data, _header_frame.reply_to, _header_frame.correlation_id, method_frame.delivery_tag)
            return

        method = body.get('method', None)
        params = body.get('params', {})
        if method is None or method not in self.method_dict:
            print(u'请求方法:{}不在配置中'.format(method))
            resp_data = {'ret_code': -1, 'err_msg': u'请求方法:{}不在配置中'.format(method)}
            self.reply(chan, resp_data, _header_frame.reply_to, _header_frame.correlation_id,
                       method_frame.delivery_tag)
            return

        function = self.method_dict.get(method)
        try:
            ret = function(**params)
            resp_data = {'ret_code': 0, 'data': ret}
            self.reply(chan, resp_data, _header_frame.reply_to, _header_frame.correlation_id,
                       method_frame.delivery_tag)
        except Exception as ex:
            print(u'mq rpc server exception:{}'.format(str(ex)))
            traceback.print_exc()
            resp_data = {'ret_code': -1, 'err_msg': '执行异常:{}'.format(str(ex))}
            self.reply(chan, resp_data, _header_frame.reply_to, _header_frame.correlation_id,
                       method_frame.delivery_tag)

    def reply(self, chan, reply_data, reply_to, reply_id, delivery_tag):
        """返回调用结果"""
        # data => string
        reply_msg = json.dumps(reply_data)
        # 发送返回消息
        chan.basic_publish(exchange=self.exchange,
                           routing_key=reply_to,
                           properties=pika.BasicProperties(content_type='application/json',
                                                           correlation_id=reply_id),
                           body=reply_msg)
        # 确认标识
        chan.basic_ack(delivery_tag=delivery_tag)

    def subscribe(self):
        print(' consuming queue:{}'.format(self.queue))
        # 绑定消息接收，指定当前queue得处理函数为on_request
        self.channel.basic_consume(self.queue, self.on_request)

        # 进入死循环，不断接收
        self.channel.start_consuming()

    def start(self):
        """启动接收"""
        try:
            self.subscribe()
        except Exception as e:
            print(e)
            self.start()


if __name__ == '__main__':

    import sys
    if len(sys.argv) >= 2:
        print(sys.argv)
    from time import sleep
    c = subscriber(user='admin', password='admin')

    c.subscribe()

    while True:
        sleep(1)

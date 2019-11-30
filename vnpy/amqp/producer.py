# encoding: UTF-8
# 消息生产者类（集合）
import sys
import json
import pika
import random
import traceback
from threading import Thread
from uuid import uuid1
from vnpy.amqp.base import base_broker

#########  模式1：发送者 #########
class sender(base_broker):
    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 exchange='x', queue_name='', routing_key='default'):

        # 通过基类，创建connection & channel
        super().__init__(host, port, user, password, channel_number=1)

        self.exchange = exchange
        self.queue_name = queue_name
        self.routing_key = routing_key

        # 通过channel，创建/使用一个queue。
        # auto_delete： 当所有已绑定在queue的consumer不使用此queue时，自动删除此queue
        # exclusive： private queue,它是True时，auto_delete也是True
        self.channel.queue_declare(self.queue_name, auto_delete=True, exclusive=True)

        # 通过channel，创建/使用一个网关
        # exchange_type: direct 点对点
        # passive: 只是检查其是否存在
        # durable: 是否需要queue持久化消息。开启将降低性能至1/10
        # auto_delete: 当没有queue绑定时，就自动删除
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

    def pub(self, text):
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        content_type = 'application/json' if isinstance(text, dict) else 'text/plain'
        try:
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=self.routing_key,
                                       body=text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       delivery_mode=1))
        except Exception as e:
            print(e)
            # 重连一次，继续发送
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=self.routing_key,
                                                   body=text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   delivery_mode=1))

    def exit(self):
        self.connection.close()

#########  模式2：工作队列,任务发布者 #########
class task_creator(base_broker):
    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 channel_number=1, queue_name='task_queue', routing_key='default',
                 exchange='x_work_queue'):

        # 通过基类，创建connection & channel
        super().__init__(host, port, user, password, channel_number)

        self.queue_name = queue_name
        self.exchange = exchange
        self.routing_key = routing_key

        # 通过channel，创建/使用一个queue。
        queue = self.channel.queue_declare(self.queue_name, durable=True).method.queue
        print(u'create/use queue:{}')
        # 通过channel，创建/使用一个网关
        # exchange_type: direct
        # passive: 只是检查其是否存在
        # durable: 是否需要queue持久化消息。开启将降低性能至1/10
        # auto_delete: 当没有queue绑定时，就自动删除
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      durable=True)

    def pub(self, text):
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        content_type = 'application/json' if isinstance(text, dict) else 'text/plain'
        try:
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=self.routing_key,
                                       body=text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       delivery_mode=2))
        except Exception as e:
            print(e)
            # 重连一次，继续发送
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=self.routing_key,
                                                   body=text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   delivery_mode=2))

    def exit(self):
        self.connection.close()

#########  3、发布 / 订阅（Pub/Sub）模式，发布者 #########
class publisher(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 channel_number=1, queue_name='', routing_key='default',
                 exchange='x_fanout'):

        # 通过基类，创建connection & channel
        super().__init__(host, port, user, password, channel_number)

        self.queue_name = queue_name
        self.exchange = exchange
        self.routing_key = routing_key

        # 通过channel，创建/使用一个queue。
        # auto_delete： 当所有已绑定在queue的consumer不使用此queue时，自动删除此queue
        # exclusive： private queue,它是True时，auto_delete也是True
        self.channel.queue_declare(self.queue_name,
                                   auto_delete=True, exclusive=True)

        # 通过channel，创建/使用一个网关
        # exchange_type: fanout，1对多的广播式， topic: 主题匹配
        # passive: 只是检查其是否存在
        # durable: 是否需要queue持久化消息。开启将降低性能至1/10
        # auto_delete: 当没有queue绑定时，就自动删除
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='fanout',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

    def pub(self, text, routing_key=None):
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        content_type = 'application/json' if isinstance(text, dict) else 'text/plain'
        if routing_key is None:
            routing_key = self.routing_key
        try:
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=routing_key,
                                       body=text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       delivery_mode=1))
        except Exception as e:
            print(e)
            # 重连一次，继续发送
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=routing_key,
                                                   body=text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   delivery_mode=1))

    def exit(self):
        self.connection.close()

#########  4、路由模式：发布者 #########
class publisher_routing(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 channel_number=1, queue_name='', routing_key='default',  exchange='x_direct'):
        super().__init__(host, port, user, password, channel_number)

        self.queue_name = queue_name
        self.exchange = exchange
        self.routing_key = routing_key

        self.channel.queue_declare(
            self.queue_name, auto_delete=True, exclusive=True)
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

    def pub(self, text, routing_key):
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        content_type = 'application/json' if isinstance(text, dict) else 'text/plain'
        try:
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=routing_key,
                                       body=text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       delivery_mode=1))
        except Exception as e:
            print(e)
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=routing_key,
                                                   body=text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   delivery_mode=1))

    def exit(self):
        self.connection.close()

#########  5、主题模式：发布者 #########
class publisher_topic(base_broker):

    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 channel_number=1, queue_name='', routing_key='default', exchange='x_topic'):
        super().__init__(host, port, user, password, channel_number)

        self.queue_name = queue_name
        self.exchange = exchange
        self.routing_key = routing_key

        self.channel.queue_declare(
            self.queue_name, auto_delete=True, exclusive=True)
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='topic',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

    def pub(self, text, routing_key):
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        content_type = 'application/json' if isinstance(text, dict) else 'text/plain'
        try:
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=routing_key,
                                       body=text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       delivery_mode=1))
        except Exception as e:
            print(e)
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=routing_key,
                                                   body=text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   delivery_mode=1))

    def exit(self):
        self.connection.close()


#########  6、RPC模式（调用者) #########
class rpc_client(base_broker):
    # 发送：
    #   exchange: x_rpc
    #   queue: rpc_queue
    # 接收结果:
    #   exchange: x_rpc
    #   queue: 动态生成 cb_queue_name
    # 执行结果回调:
    # 暂时无用得 queue_name='rpc_queue',
    def __init__(self, host='localhost', port=5672, user='admin', password='admin',
                 exchange='x_rpc', routing_key='default'):

        # 通过基类，创建connection & channel
        super().__init__(host, port, user, password, channel_number=1)

        self.exchange = exchange
        #self.queue_name = queue_name
        self.routing_key = routing_key

        # 通过channel，创建/使用一个网关
        # exchange_type: direct 点对点
        # passive: 只是检查其是否存在
        # durable: 是否需要queue持久化消息。开启将降低性能至1/10
        # auto_delete: 当没有queue绑定时，就自动删除
        self.channel.exchange_declare(exchange=exchange,
                                      exchange_type='direct',
                                      passive=False,
                                      durable=False,
                                      auto_delete=False)

        # 创建/声明rpc结果消息队列
        result = self.channel.queue_declare(queue='', exclusive=True)
        self.cb_queue_name = result.method.queue
        print('call back queue name:{}'.format(self.cb_queue_name))

        # 绑定 回调消息队列，exchange和channnel
        self.channel.queue_bind(queue=self.cb_queue_name, exchange=exchange)

        # 绑定 回调消息队列得接受处理函数为on_respone
        self.channel.basic_consume(queue=self.cb_queue_name,
                                   on_message_callback=self.on_respone,
                                   auto_ack=True)
        # 回调函数字典
        self.cb_dict = {}

        self.thread = Thread(target=self.start)
        self.thread.start()

    def on_respone(self, ch, method, props, body):
        """
        相应 cb_queue返回的结果处理信息
        :param ch:
        :param method:
        :param props:
        :param body:
        :return:
        """
        if isinstance(body, bytes):
            body = body.decode('utf-8')
        if isinstance(body, str):
            body = json.loads(body)

        cb = self.cb_dict.pop(props.correlation_id, None)
        if cb:
            try:
               cb(body)
            except Exception as ex:
                print('on_respone exception when call cb.{}'.format(str(ex)))
                traceback.print_exc()

    def call(self, req_text, correlation_id=None, cb_func=None):
        """
        远程调用
        :param req_text: 调用指令及内容
        :param cb_func: 回调函数地址
        :return:
        """
        # channel.basic_publish向队列中发送信息
        # exchange -- 它使我们能够确切地指定消息应该到哪个队列去。
        # routing_key 指定向哪个队列中发送消息
        # body是要插入的内容, 字符串格式
        #
        content_type = 'application/json' if isinstance(req_text, dict) else 'text/plain'
        if correlation_id is None:
            correlation_id = str(uuid1())
        try:
            print(u'sending request message, exchange:{},routing_key:{},body:{},reply_queue:{}'
                  .format(self.exchange, self.routing_key, req_text, self.cb_queue_name))
            self.channel.basic_publish(exchange=self.exchange,
                                       routing_key=self.routing_key,
                                       body=req_text,
                                       properties=pika.BasicProperties(content_type=content_type,
                                                                       reply_to=self.cb_queue_name,
                                                                       correlation_id=correlation_id
                                                                       ))
        except Exception as e:
            print(e)
            # 重连一次，继续发送
            self.reconnect().channel.basic_publish(exchange=self.exchange,
                                                   routing_key=self.routing_key,
                                                   body=req_text,
                                                   properties=pika.BasicProperties(content_type=content_type,
                                                                                   reply_to=self.cb_queue_name,
                                                                                   correlation_id=correlation_id
                                                                                   ))
        # 登记参照id和回调函数
        if cb_func:
            self.cb_dict.update({correlation_id: cb_func})

    def start(self):
        try:
            self.channel.start_consuming()
        except Exception as ex:
            print('rpc_client consuming exception:{}'.format(str(ex)))
            traceback.print_exc()
            self.channel.start_consuming()

    def exit(self):
        try:
            self.channel.stop_consuming()
            self.channel.close()
            self.connection.close()
            if self.thread:
                self.thread.join()
        except:
            pass

if __name__ == '__main__':
    import datetime
    import time
    p = publisher()
    while True:
        time.sleep(1)
        msg = '{}'.format(datetime.datetime.now())
        print(msg)
        p.pub(msg)

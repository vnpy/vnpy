# encoding: UTF-8
import pika


class base_broker():
    def __init__(self, host='localhost', port=5672, user='guest', password='guest',
                 channel_number=1):
        """
        :param host: 连接rabbitmq的服务器地址（或者群集地址）
        :param port: 端口
        :param user: 用户名
        :param password: 密码
        :param channel_number: 频道的数字（大于1）
        """
        self.host = host
        self.port = port
        self.user = user
        self.password = password

        self.channel_number = channel_number

        # 身份鉴权
        self.credentials = pika.PlainCredentials(self.user, self.password, erase_on_connect=True)

        # 创建连接
        self.connection = pika.BlockingConnection(
            pika.ConnectionParameters(host=self.host, port=self.port,
                                      credentials=self.credentials,
                                      heartbeat=0, socket_timeout=5))

        # 创建一个频道，或者指定频段数字编号
        self.channel = self.connection.channel(
            channel_number=self.channel_number)

    def reconnect(self):
        """
        重新连接
        :return:
        """
        try:
            self.connection.close()
        except Exception:
            pass

        self.connection = pika.BlockingConnection(
            pika.ConnectionParameters(host=self.host, port=self.port,
                                      credentials=self.credentials,
                                      heartbeat=0, socket_timeout=5,))

        self.channel = self.connection.channel(
            channel_number=self.channel_number)
        return self

    def close(self):
        if self.connection:
            self.connection.close()

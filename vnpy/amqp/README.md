代码源自余总得 https://github.com/yutiansut/QAPUBSUB/

**RabbitMQ and AMQP**

RabbitMQ 是采用 Erlang 语言实现的 AMQP 协议的消息中间件，
最初起源于金融系统，用于在分布式系统中存储转发消息。
RabbitMQ 发展到今天，被越来越多的人认可，
这和它在可靠性、可用性、扩展性、功能丰富等方面的卓越表现是分不开的。

消息支持多种传递模式，详细见案例https://www.rabbitmq.com/getstarted.html
RabbitMQ 是一种典型的点对点模式,也可以通过设置交换器类型来实现发布订阅模式而达到广播消费的效果

**1、点对点**
   
    发布者：只需要定义queue的名称
    接收者：只需要定义queue的名称。 隐含上，auto_ack=True，即收到消息后，自动确认，就会从Queue中删除
    
**2、工作队列**
    
    （任务）发布者：指定queue名称，durable=True。发送任务时，发送到指定的queue，设置delivery_mode=2(持久化该任务)
    （执行）接收者：指定queue名称，durable=True。执行任务后，才确认. ch.basic_ack(delivery_tag=method.delivery_tag
    
**3、发布 / 订阅（Pub/Sub）模式**
   
    发布者：创建channel时，指定Exchange名称，类型为fanout。
            发布时，指定Exchange名称，无routing_key。
    订阅者：创建channel时，指定Exchagne名称，类型为fanout。
            创建动态queue名，绑定私有。
            绑定channel与queue，指定Exchange和queue名。

**4、路由模式**  

    发布者：发布者：创建channel时，指定Exchange名称，类型为direct。
            发布时，指定Exchange名称，打上route_key作为标签
    订阅者：创建channel时，指定Exchagne名称，类型为direct。
            创建动态queue名，绑定私有。
            绑定channel与queue，指定Exchange、queue名和期望获取的标签
            如订阅多个标签，绑定多次即可。
    
**5、主题模式**  

    发布者：创建channel时，指定Exchange名称，类型为topic。
            发布时，指定Exchange名称，打上route_key作为标签
    订阅者：创建channel时，指定Exchagne名称，类型为topic。
            创建动态queue名，绑定私有。
            绑定channel与queue，指定Exchange、queue名和期望获取的标签匹配符
            如订阅多个标签匹配符，绑定多次即可。
            匹配有两个关键字:
                * 1~多个字母
                # 0~多个字母
            
**6、远程调用模式**

    服务端（响应）：创建channel时，指定queue，定义basic_qos为只有一个执行，
                   定义消息的响应执行方法。
                   消息执行方法：执行完毕后，发布结果消息，使用指定routing_key标签为回复的queue
                   推送属性包含参照ID，确认ACK.
    客户端（请求）：创建2个queue，一个是接收执行结果的queue，并绑定执行结果回调响应，自动ack。
                    另一个是推送请求的queue，推送时，增加reply_to 和 参照ID。
            

**consumer.py 提供两种消费者：**

    1. 订阅模式下得subscriber
    2. 点对点/路由/主题模式下得subscriber_routing
    
**producter.py，提供两种生产者:**

    1. 订阅模式下得publisher
    2. 点对点/路由/主题模式下得publisher_routing

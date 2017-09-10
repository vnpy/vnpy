# encoding: UTF-8

import threading
import traceback
import signal

import zmq
from msgpack import packb, unpackb
from json import dumps, loads

import cPickle
pDumps = cPickle.dumps
pLoads = cPickle.loads


# 实现Ctrl-c中断recv
signal.signal(signal.SIGINT, signal.SIG_DFL)


########################################################################
class RpcObject(object):
    """
    RPC对象
    
    提供对数据的序列化打包和解包接口，目前提供了json、msgpack、cPickle三种工具。
    
    msgpack：性能更高，但通常需要安装msgpack相关工具；
    json：性能略低但通用性更好，大部分编程语言都内置了相关的库。
    cPickle：性能一般且仅能用于Python，但是可以直接传送Python对象，非常方便。
    
    因此建议尽量使用msgpack，如果要和某些语言通讯没有提供msgpack时再使用json，
    当传送的数据包含很多自定义的Python对象时建议使用cPickle。
    
    如果希望使用其他的序列化工具也可以在这里添加。
    """

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        # 默认使用msgpack作为序列化工具
        #self.useMsgpack()
        self.usePickle()
    
    #----------------------------------------------------------------------
    def pack(self, data):
        """打包"""
        pass
    
    #----------------------------------------------------------------------
    def unpack(self, data):
        """解包"""
        pass
    
    #----------------------------------------------------------------------
    def __jsonPack(self, data):
        """使用json打包"""
        return dumps(data)
    
    #----------------------------------------------------------------------
    def __jsonUnpack(self, data):
        """使用json解包"""
        return loads(data)
    
    #----------------------------------------------------------------------
    def __msgpackPack(self, data):
        """使用msgpack打包"""
        return packb(data)
    
    #----------------------------------------------------------------------
    def __msgpackUnpack(self, data):
        """使用msgpack解包"""
        return unpackb(data)
    
    #----------------------------------------------------------------------
    def __picklePack(self, data):
        """使用cPickle打包"""
        return pDumps(data)
    
    #----------------------------------------------------------------------
    def __pickleUnpack(self, data):
        """使用cPickle解包"""
        return pLoads(data)
        
    #----------------------------------------------------------------------
    def useJson(self):
        """使用json作为序列化工具"""
        self.pack = self.__jsonPack
        self.unpack = self.__jsonUnpack
        
    #----------------------------------------------------------------------
    def useMsgpack(self):
        """使用msgpack作为序列化工具"""
        self.pack = self.__msgpackPack
        self.unpack = self.__msgpackUnpack
        
    #----------------------------------------------------------------------
    def usePickle(self):
        """使用cPickle作为序列化工具"""
        self.pack = self.__picklePack
        self.unpack = self.__pickleUnpack


########################################################################
class RpcServer(RpcObject):
    """RPC服务器"""

    #----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
        super(RpcServer, self).__init__()
        
        # 保存功能函数的字典，key是函数名，value是函数对象
        self.__functions = {}     

        # zmq端口相关
        self.__context = zmq.Context()
        
        self.__socketREP = self.__context.socket(zmq.REP)   # 请求回应socket
        self.__socketREP.bind(repAddress)
        
        self.__socketPUB = self.__context.socket(zmq.PUB)   # 数据广播socket
        self.__socketPUB.bind(pubAddress)
        
        # 工作线程相关
        self.__active = False                             # 服务器的工作状态
        self.__thread = threading.Thread(target=self.run) # 服务器的工作线程
        
    #----------------------------------------------------------------------
    def start(self):
        """启动服务器"""
        # 将服务器设为启动
        self.__active = True
        
        # 启动工作线程
        if not self.__thread.isAlive():
            self.__thread.start()
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止服务器"""
        # 将服务器设为停止
        self.__active = False
        
        # 等待工作线程退出
        if self.__thread.isAlive():
            self.__thread.join()
    
    #----------------------------------------------------------------------
    def run(self):
        """服务器运行函数"""
        while self.__active:
            # 使用poll来等待事件到达，等待1秒（1000毫秒）
            if not self.__socketREP.poll(1000):
                continue
            
            # 从请求响应socket收取请求数据
            reqb = self.__socketREP.recv()
            
            # 序列化解包
            req = self.unpack(reqb)
            
            # 获取函数名和参数
            name, args, kwargs = req
            
            # 获取引擎中对应的函数对象，并执行调用，如果有异常则捕捉后返回
            try:
                func = self.__functions[name]
                r = func(*args, **kwargs)
                rep = [True, r]
            except Exception as e:
                rep = [False, traceback.format_exc()]
            
            # 序列化打包
            repb = self.pack(rep)
            
            # 通过请求响应socket返回调用结果
            self.__socketREP.send(repb)
        
    #----------------------------------------------------------------------
    def publish(self, topic, data):
        """
        广播推送数据
        topic：主题内容（注意必须是ascii编码）
        data：具体的数据
        """
        # 序列化数据
        datab = self.pack(data)
        
        # 通过广播socket发送数据
        self.__socketPUB.send_multipart([topic, datab])
        
    #----------------------------------------------------------------------
    def register(self, func):
        """注册函数"""
        self.__functions[func.__name__] = func


########################################################################
class RpcClient(RpcObject):
    """RPC客户端"""
    
    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        super(RpcClient, self).__init__()
        
        # zmq端口相关
        self.__reqAddress = reqAddress
        self.__subAddress = subAddress
        
        self.__context = zmq.Context()
        self.__socketREQ = self.__context.socket(zmq.REQ)   # 请求发出socket
        self.__socketSUB = self.__context.socket(zmq.SUB)   # 广播订阅socket        

        # 工作线程相关，用于处理服务器推送的数据
        self.__active = False                                   # 客户端的工作状态
        self.__thread = threading.Thread(target=self.run)       # 客户端的工作线程
        
    #----------------------------------------------------------------------
    def __getattr__(self, name):
        """实现远程调用功能"""
        # 执行远程调用任务
        def dorpc(*args, **kwargs):
            # 生成请求
            req = [name, args, kwargs]
            
            # 序列化打包请求
            reqb = self.pack(req)
            
            # 发送请求并等待回应
            self.__socketREQ.send(reqb)
            repb = self.__socketREQ.recv()
            
            # 序列化解包回应
            rep = self.unpack(repb)
            
            # 若正常则返回结果，调用失败则触发异常
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException(rep[1])
        
        return dorpc
    
    #----------------------------------------------------------------------
    def start(self):
        """启动客户端"""
        # 连接端口
        self.__socketREQ.connect(self.__reqAddress)
        self.__socketSUB.connect(self.__subAddress)
    
        # 将服务器设为启动
        self.__active = True
        
        # 启动工作线程
        if not self.__thread.isAlive():
            self.__thread.start()
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止客户端"""
        # 将客户端设为停止
        self.__active = False
        
        # 等待工作线程退出
        if self.__thread.isAlive():
            self.__thread.join()
        
    #----------------------------------------------------------------------
    def run(self):
        """客户端运行函数"""
        while self.__active:
            # 使用poll来等待事件到达，等待1秒（1000毫秒）
            if not self.__socketSUB.poll(1000):
                continue
            
            # 从订阅socket收取广播数据
            topic, datab = self.__socketSUB.recv_multipart()
            
            # 序列化解包
            data = self.unpack(datab)

            # 调用回调函数处理
            self.callback(topic, data)
            
    #----------------------------------------------------------------------
    def callback(self, topic, data):
        """回调函数，必须由用户实现"""
        raise NotImplementedError
    
    #----------------------------------------------------------------------
    def subscribeTopic(self, topic):
        """
        订阅特定主题的广播数据
        
        可以使用topic=''来订阅所有的主题
        
        注意topic必须是ascii编码
        """
        self.__socketSUB.setsockopt(zmq.SUBSCRIBE, topic)
        
    

########################################################################
class RemoteException(Exception):
    """RPC远程异常"""

    #----------------------------------------------------------------------
    def __init__(self, value):
        """Constructor"""
        self.__value = value
        
    #----------------------------------------------------------------------
    def __str__(self):
        """输出错误信息"""
        return self.__value

    
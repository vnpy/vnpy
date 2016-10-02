# encoding: UTF-8

import threading
import traceback

import zmq
from msgpack import packb, unpackb


########################################################################
class RpcServer(object):
    """RPC服务器"""

    #----------------------------------------------------------------------
    def __init__(self, repAddress, pubAddress):
        """Constructor"""
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
        self.__thread = threading.Thread(target=self.__run) # 服务器的工作线程
        
    #----------------------------------------------------------------------
    def start(self):
        """启动服务器"""
        # 将服务器设为启动
        self.__active = True
        
        # 启动工作线程
        self.__thread.start()
        
    #----------------------------------------------------------------------
    def stop(self):
        """停止服务器"""
        # 将服务器设为停止
        self.__active = False
        
        # 等待工作线程退出
        self.__thread.join()
    
    #----------------------------------------------------------------------
    def __run(self):
        """连续运行函数"""
        while self.__active:
            # 从请求响应socket收取请求数据
            reqb = self.__socketREP.recv()
            
            # 用msgpack解包
            req = unpackb(reqb)
            
            # 获取函数名和参数
            name, args, kwargs = req
            
            # 获取引擎中对应的函数对象，并执行调用，如果有异常则捕捉后返回
            try:
                func = self.__functions[name]
                r = func(*args, **kwargs)
                rep = [True, r]
            except Exception as e:
                rep = [False, traceback.format_exc()]
            
            # 用msgpack打包
            repb = packb(rep)
            
            # 通过请求响应socket返回调用结果
            self.__socketREP.send(repb)
        
    #----------------------------------------------------------------------
    def publish(self, data):
        """广播推送数据"""
        # 使用msgpack序列化数据
        datab = packb(data)
        
        # 通过广播socket发送数据
        self.__socketPUB.send(datab)
        
    #----------------------------------------------------------------------
    def register(self, func):
        """注册函数"""
        self.__functions[func.__name__] = func


########################################################################
class RpcClient(object):
    """RPC客户端"""

    #----------------------------------------------------------------------
    def __init__(self, reqAddress, subAddress):
        """Constructor"""
        # zmq端口相关
        self.__reqAddress = reqAddress
        self.__subAddress = subAddress
        
        self.__context = zmq.Context()
        self.__socketREQ = self.__context.socket(zmq.REQ)   # 请求发出socket
        self.__socketSUB = self.__context.socket(zmq.SUB)   # 广播订阅socket        

        # 工作线程相关，用于处理服务器推送的数据
        self.__active = False                                   # 客户端的工作状态
        self.__thread = threading.Thread(target=self.__run)     # 客户端的工作线程
        
    #----------------------------------------------------------------------
    def __getattr__(self, name):
        """实现远程调用功能"""
        # 执行远程调用任务
        def dorpc(*args, **kwargs):
            # 生成请求
            req = [name, args, kwargs]
            
            # 用msgpack打包请求
            reqb = packb(req)
            
            # 发送请求并等待回应
            self.__socketREQ.send(reqb)
            repb = self.__socketREQ.recv()
            
            # 用msgpack解包回应
            rep = unpackb(repb)
            
            # 若正常则返回结果，调用失败则触发异常
            if rep[0]:
                return rep[1]
            else:
                raise RemoteException, rep[1]
        
        return dorpc
    
    #----------------------------------------------------------------------
    def start(self):
        """启动客户端"""
        # 连接端口
        self.__socketREQ.connect(self.__reqAddress)
        
        self.__socketSUB.connect(self.__subAddress)
        self.__socketSUB.setsockopt(zmq.SUBSCRIBE, '')    # 订阅全部数据，不做过滤
    
        # 将服务器设为启动
        self.__active = True
        
        # 启动工作线程
        self.__thread.start()
    
    #----------------------------------------------------------------------
    def stop(self):
        """停止客户端"""
        # 将客户端设为停止
        self.__active = False
        
        # 等待工作线程退出
        self.__thread.join()
        
    #----------------------------------------------------------------------
    def __run(self):
        """连续运行函数"""
        while self.__active:
            # 从订阅socket收取广播数据
            datab = self.__socketSUB.recv()
            
            # 用msgpack解包
            data = unpackb(datab)

            # 调用回调函数处理
            self.callback(data)
            
    #----------------------------------------------------------------------
    def callback(self, data):
        """回调函数，必须由用户实现"""
        raise NotImplementedError
    

########################################################################
class RemoteException(Exception):
    """RPC远程异常"""

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        pass

    
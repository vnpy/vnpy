# encoding: UTF-8

'''一个简单的通联数据客户端，主要使用requests开发，比通联官网的python例子更为简洁。'''

import os
import requests
import json


HTTP_OK = 200


########################################################################
class DatayesApi(object):
    """通联数据API"""

    #----------------------------------------------------------------------
    def __init__(self, token, 
                 domain="http://api.wmcloud.com/data",
                 version="v1"):
        """Constructor"""
        self.domain = domain        # 主域名
        self.version = version      # API版本
        self.token = token          # 授权码
        
        self.header = {}            # http请求头部
        self.header['Connection'] = 'keep_alive'
        self.header['Authorization'] = 'Bearer ' + self.token                
    
    #----------------------------------------------------------------------
    def downloadData(self, path, params):
        """下载数据"""
        url = '/'.join([self.domain, self.version, path])
        r = requests.get(url=url, headers=self.header, params=params)
        
        if r.status_code != HTTP_OK:
            print u'http请求失败，状态代码%s' %r.status_code
            return None
        else:
            result = r.json()
            if 'retMsg' in result and result['retMsg'] == 'Success':
                return result['data']
            else:
                if 'retMsg' in result:
                    print u'查询失败，返回信息%s' %result['retMsg']
                elif 'message' in result:
                    print u'查询失败，返回信息%s' %result['message']
                return None
                    
                    
    
    
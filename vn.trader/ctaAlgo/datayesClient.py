# encoding: UTF-8

'''一个简单的通联数据客户端，主要使用requests开发，比通联官网的python例子更为简洁。'''


import requests
import json

FILENAME = 'datayes.json'
HTTP_OK = 200


########################################################################
class DatayesClient(object):
    """通联数据客户端"""
    
    name = u'通联数据客户端'

    #----------------------------------------------------------------------
    def __init__(self):
        """Constructor"""
        self.domain = ''    # 主域名
        self.version = ''   # API版本
        self.token = ''     # 授权码
        self.header = {}    # http请求头部
        self.settingLoaded = False  # 配置是否已经读取
        
        self.loadSetting()
        
    #----------------------------------------------------------------------
    def loadSetting(self):
        """载入配置"""
        try:
            f = file(FILENAME)
        except IOError:
            print u'%s无法打开配置文件' % self.name
            return
        
        setting = json.load(f)
        try:
            self.domain = str(setting['domain'])
            self.version = str(setting['version'])
            self.token = str(setting['token'])
        except KeyError:
            print u'%s配置文件字段缺失' % self.name
            return
        
        self.header['Connection'] = 'keep_alive'
        self.header['Authorization'] = 'Bearer ' + self.token
        self.settingLoaded = True
        
        print u'%s配置载入完成' % self.name
        
    
    #----------------------------------------------------------------------
    def downloadData(self, path, params):
        """下载数据"""
        if not self.settingLoaded:
            print u'%s配置未载入' % self.name
            return None
        else:
            url = '/'.join([self.domain, self.version, path])
            r = requests.get(url=url, headers=self.header, params=params)
            
            if r.status_code != HTTP_OK:
                print u'%shttp请求失败，状态代码%s' %(self.name, r.status_code)
                return None
            else:
                result = r.json()
                if 'retMsg' in result and result['retMsg'] == 'Success':
                    return result['data']
                else:
                    if 'retMsg' in result:
                        print u'%s查询失败，返回信息%s' %(self.name, result['retMsg'])
                    elif 'message' in result:
                        print u'%s查询失败，返回信息%s' %(self.name, result['message'])
                    return None
                    
                    
    
    
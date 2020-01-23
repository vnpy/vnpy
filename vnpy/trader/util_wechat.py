# -*- coding:utf-8 -*-
'''
通过wxpusher发送Weixin的消息
http://wxpusher.zjiecode.com/
开通步骤：
1、关注公众号，注册
2、通过公众号，获取UID
3、通过网站=》应用列表=》新建应用，如vnpy2，并获得APP_TOOKEN
4、应用列表=》应用（vnpy2）=》 关注.
'''

from threading import Lock, Thread
import requests
import json
import sys
import traceback
from urllib.parse import urlencode
from datetime import datetime

global wechat_lock
wechat_lock = Lock()

# 这里可以设置UID
UID = 'UID_kZguGPBQPWn41Ni9FK4CgPts2Kj'
APP_TOKEN = 'AT_aDuiQu41dmAQV2vUMXOaaTDrWyhKJN2'


class wechat_thread(Thread):
    """
    采用线程方式，不阻塞
    """

    def __init__(self, uid: str, content: str, topic_ids: list = [], url: str = ''):

        # text：消息标题，最长为256，必填。
        # desp：消息内容，最长64Kb，可空，支持MarkDown。

        super(wechat_thread, self).__init__(name="wechat_thread")
        self.request_url = "http://wxpusher.zjiecode.com/api/send/message"
        self.uid = uid
        self.content = content
        self.topic_ids = topic_ids
        self.url = url
        self.lock = wechat_lock

    def run(self):
        if self.content is None or len(self.content) == 0:
            return
        params = {}
        params['appToken'] = APP_TOKEN
        params['content'] = self.content
        params['contentType'] = 1
        params['topicIds'] = self.topic_ids
        params['uids'] = [self.uid]
        params['url'] = self.url

        # 发送请求
        try:
            response = requests.post(self.request_url, json=params).json()
            if not response.get('success', False):
             print(response)
        except Exception as e:
            print("{} wechat_thread sent failed! ex:{},trace:{}".format(datetime.now(), str(e), traceback.format_exc()),
                  file=sys.stderr)
            return

        print("wechat_thread sent successful!")


def send_wx_msg(content=''):
    """
    发送微信Msg
    :param content:   发送内容

    :return:
    """
    if len(text) == 0:
        return

    t = wechat_thread(uid=UID, content=content)
    t.daemon = False
    # t.run()
    t.start()


if __name__ == '__main__':
    text = u'微信测试标题!!!!\n第二行'

    send_wx_msg(text)

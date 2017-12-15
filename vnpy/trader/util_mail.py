# -*- coding:utf-8 -*-
'''
发送带附件邮件
'''

from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
import smtplib
from threading import *
import time

# 创建一个带附件的实例

global maillock
maillock = Lock()


class mail_thread(Thread):
    def __init__(self, to_list, subject, msgcontent, attachlist):
        super(mail_thread, self).__init__(name="mail_thread")
        self.to_list = to_list
        self.subject = subject
        self.msgcontent = msgcontent
        self.attachlist = attachlist
        self.mailfrom = ''  #  xxxxx@163.com
        self.mailpwd = 'xxxxxx' # 密码
        self.lock = maillock

    def run(self):

        if len(self.mailfrom) == 0:
            print (" pls config email sending address")
            return

        print("sendmail run!")
        self.lock.acquire()
        print("lock acquire %s" % time.ctime())

        msg = MIMEMultipart()
        # 文本肉容
        content = MIMEText(self.msgcontent, _subtype='plain', _charset='gb2312')
        msg.attach(content)

        # 添加附件
        for attachfile in self.attachlist:
            # 构造附件
            att = MIMEText(open(attachfile, 'rb').read(), 'base64', 'gb2312')
            att["Content-Type"] = 'application/octet-stream'
            att["Content-Disposition"] = "attachment; filename='" + attachfile + "'"  # 这里的filename可以任意写，写什么名字，邮件中显示什么名字
            msg.attach(att)

        # 加邮件头
        msg['to'] = ";".join(self.to_list)
        msg['from'] = self.mailfrom
        msg['subject'] = self.subject
        # 发送邮件
        try:
            server = smtplib.SMTP()
            server.connect('smtp.' + self.mailfrom.split('@')[1])
            server.login(self.mailfrom.split('@')[0], self.mailpwd)  # XXX为用户名，XXXXX为密码
            server.sendmail(msg['from'], msg['to'], msg.as_string())
            server.quit()
            # print '发送成功'
        except Exception as e:
            #pass
            print str(e)
        print("mail sent successful!")

        time.sleep(5)
        print("lock release %s" % time.ctime())
        self.lock.release()


def sendmail(subject, msgcontent, attachlist=[], to_list=['xxxxx@xxxxx.com']):
    t = mail_thread(to_list, subject, msgcontent, attachlist)
    t.daemon = False
    t.start()


if __name__ == '__main__':
    to_list = ['xxxxx@xxxxx.com']
    subject = '测试邮件!!!!'
    msgcontent = u'测试邮件!!!!\n测试邮件!!!!\n测试邮件!!!!\n测试邮件!!!!\n测试邮件!!!!\n'
    attachlist = []

    sendmail(subject, msgcontent, attachlist, to_list)

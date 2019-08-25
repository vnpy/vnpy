from vnpy.amqp.producer import sender

if __name__ == '__main__':
    import datetime
    import time
    p = sender()
    while True:
        time.sleep(1)
        msg = '{}'.format(datetime.datetime.now())
        print(u'[x] send :{}'.format(msg))
        p.pub(msg)

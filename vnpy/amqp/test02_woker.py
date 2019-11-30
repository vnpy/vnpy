# encoding: UTF-8

from vnpy.amqp.consumer import worker

if __name__ == '__main__':

    import sys

    from time import sleep
    c = worker(host='192.168.0.202', user='admin', password='admin')
    c.start()
    while True:
        sleep(1)

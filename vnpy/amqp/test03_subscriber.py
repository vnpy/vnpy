# encoding: UTF-8

from vnpy.amqp.consumer import subscriber

if __name__ == '__main__':

    import sys

    from time import sleep
    c = subscriber(user='admin', password='admin', exchange='x_fanout_md_tick')

    c.subscribe()

    while True:
        sleep(1)

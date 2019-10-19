from vnpy.event import EventEngine
EVENT_TIMER = "eTimer"

def even_test():
    """测试函数"""
    import sys
    from datetime import datetime
    # from PyQt5.QtCore import QCoreApplication

    def simpletest(event):
        print('处理每秒触发的计时器事件：%s' % str(datetime.now()))

    # app = QCoreApplication(sys.argv)

    ee = EventEngine(2)
    ee.register(EVENT_TIMER, simpletest)
    ee.start()

    # app.exec_()


# 直接运行脚本可以进行测试
if __name__ == '__main__':
    even_test()
    ####
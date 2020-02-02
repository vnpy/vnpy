# encoding: UTF-8

# Celery app
# 该py脚本，为启动celery worker app
# 在项目根目录下，运行 celery -A vnpy.task.celery worker
from celery import Celery

import sys
import os
import traceback

from vnpy.trader.utility import import_module_by_str
from celery.utils.log import get_task_logger

logger = get_task_logger(__name__)

# 添加项目目录
vnpy_root = os.path.abspath(os.path.join(os.path.dirname(__file__), '..', '..'))

if vnpy_root not in sys.path:
    print('append {} into sys.path'.format(vnpy_root))
    sys.path.append(vnpy_root)

# 使用本地配置的
from vnpy.trader.utility import load_json  # noqa

file_path = os.path.abspath(os.path.join(os.path.dirname(__file__), 'celery_config.json'))
celery_config = load_json(file_path)

# 使用 redis
# broker = celery_config.get('celery_broker','redis://192.168.0.202:6379')
# backend = celery_config.get('celery_backend','redis://192.168.0.202:6379/0')

# 使用rabbitMQ
broker = celery_config.get('celery_broker', 'amqp://admin:admin@192.168.0.202:5672//')
backend = celery_config.get('celery_backend', 'amqp://admin:admin@192.168.0.202:5672//')

print(u'Celery 使用redis配置:\nbroker:{}\nbackend:{}'.format(broker, backend))

app = Celery('vnpy_task', broker=broker)

# 动态导入task目录下子任务
app.conf.CELERY_IMPORTS = ['vnpy.task.celery_app.worker_started']


def worker_started():
    """发送worker启动的通知"""
    try:
        import socket
        from vnpy.trader.util_wechat import send_wx_msg
        send_wx_msg(u'{} Celery Worker 启动'.format(socket.gethostname()))
    except:  # noqa
        pass


@app.task(bind=True)
def execute(self, func, *args, **kwargs):
    """
    通用的执行任务方法
    :param func: 函数方法在绝对路径字符串，mod.sub_mod.func
    :param args: 参数
    :param kwargs: 扩展参数
    :return:
    """
    try:
        logger.info('working folder:{}'.format(os.getcwd()))
        logger.info('task id:{}'.format(self.request.id))
        logger.info('celery will execute:{}'.format(func))
        logger.info('args:{}'.format(args))
        logger.info('kwargs:{}'.format(kwargs))

        # Str =》 加载 模块（ 模块如果修改代码，会加载新得代码）
        f = import_module_by_str(func)

        # 加载不成功得话，告警
        if f is None:
            msg = 'celery can not load function :{}'.format(func)
            print(msg, file=sys.stderr)
            return False

        # 真正执行任务
        ret = f(*args, **kwargs)

        # 返回执行结果给celery
        return ret

    except Exception as ex:
        msg = 'celery execute func:{} exception:{},{}'.format(func, str(ex), traceback.format_exc())
        logger.error(msg)
        return False

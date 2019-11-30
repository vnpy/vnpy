#!/usr/bin/env python
# coding=utf8

import os
import sys
import re
import logging
import threading
import multiprocessing
from datetime import datetime


RECORD_FORMAT = "%(levelname)s  [%(asctime)s][%(filename)s:%(lineno)d] %(message)s"
BACKTEST_FORMAT = "%(levelname)s  %(message)s"
DATE_FORMAT = "%Y-%m-%d %H:%M:%S"

_logger = None
_fileHandler = None
_logger_filename = None

thread_data = threading.local()


class MultiprocessHandler(logging. FileHandler):
    """支持多进程的TimedRotatingFileHandler"""
    def __init__(self, filename: str,
                 interval: str = 'D',
                 backup_count: int = 0,
                 encoding: str = None,
                 delay: bool = False):
        """filename 日志文件名,
        interval 时间间隔的单位,
        backup_count 保留文件个数,0表示不删除
        delay 是否开启 OutSteam缓存
            True 表示开启缓存，OutStream输出到缓存，待缓存区满后，刷新缓存区，并输出缓存数据到文件。
            False表示不缓存，OutStrea直接输出到文件"""
        self.prefix = filename
        self.backup_count = backup_count
        self.interval = interval.upper()
        # 正则匹配 年-月-日
        self.re_match = r"^\d{4}-\d{2}-\d{2}"

        # S 每秒建立一个新文件
        # M 每分钟建立一个新文件
        # H 每天建立一个新文件
        # D 每天建立一个新文件
        self.interval_formater_dict = {
            'S': "%Y-%m-%d-%H-%M-%S",
            'M': "%Y-%m-%d-%H-%M",
            'H': "%Y-%m-%d-%H",
            'D': "%Y-%m-%d"
        }

        # 日志文件日期后缀
        self.formater = self.interval_formater_dict.get(interval)
        if not self.formater:
            raise ValueError(u"指定的日期间隔单位无效: %s" % self.interval)

        # 使用当前时间，格式化文件格式化字符串
        self.file_path = u'{}_{}.log'.format(self.prefix, datetime.now().strftime(self.formater))
        # 获得文件夹路径
        _dir = os.path.dirname(self.file_path)
        try:
            # 如果日志文件夹不存在，则创建文件夹
            if not os.path.exists(_dir):
                os.makedirs(_dir)
        except Exception as ex:
            print(f'创建log文件夹{self.file_path}失败:{str(ex)}', file=sys.stderr)
            pass

        print(u'MultiprocessHandler create logger:{}'.format(self.file_path))

        logging.FileHandler.__init__(self, self.file_path, 'a+', encoding, delay)

    def should_change_file(self):
        """更改日志写入目的写入文件
        :return True 表示已更改，False 表示未更改"""
        # 以当前时间获得新日志文件路径
        _filePath = u'{}_{}.log'.format(self.prefix, datetime.now().strftime(self.formater))
        # 新日志文件日期 不等于 旧日志文件日期，则表示 已经到了日志切分的时候
        # 更换日志写入目的为新日志文件。
        # 例如 按 天 （D）来切分日志
        #   当前新日志日期等于旧日志日期，则表示在同一天内，还不到日志切分的时候
        #   当前新日志日期不等于旧日志日期，则表示不在
        # 同一天内，进行日志切分，将日志内容写入新日志内。
        if _filePath != self.file_path:
            self.file_path = _filePath
            return True
        return False

    def do_change_file(self):
        """输出信息到日志文件，并删除多于保留个数的所有日志文件"""
        # 日志文件的绝对路径
        self.baseFilename = os.path.abspath(self.file_path)
        # stream == OutStream
        # stream is not None 表示 OutStream中还有未输出完的缓存数据
        if self.stream:
            # flush close 都会刷新缓冲区，flush不会关闭stream，close则关闭stream
            # self.stream.flush()
            self.stream.close()
            # 关闭stream后必须重新设置stream为None，否则会造成对已关闭文件进行IO操作。
            self.stream = None
        # delay 为False 表示 不OutStream不缓存数据 直接输出
        #  所有，只需要关闭OutStream即可
        if not self.delay:
            # 这个地方如果关闭colse那么就会造成进程往已关闭的文件中写数据，从而造成IO错误
            # delay == False 表示的就是 不缓存直接写入磁盘
            # 我们需要重新在打开一次stream
            # self.stream.close()
            self.stream = self._open()
        # 删除多于保留个数的所有日志文件
        if self.backup_count > 0:
            print('删除日志')
            for s in self.get_expired_files():
                print(s)
                os.remove(s)

    def get_expired_files(self):
        """获得过期需要删除的日志文件"""
        # 分离出日志文件夹绝对路径
        # split返回一个元组（absFilePath,fileName)
        # 例如：split('I:\ScripPython\char4\mybook\util\logs\mylog.2017-03-19）
        # 返回（I:\ScripPython\char4\mybook\util\logs， mylog.2017-03-19）
        # _ 表示占位符，没什么实际意义，
        dir_name, _ = os.path.split(self.baseFilename)
        file_names = os.listdir(dir_name)
        result = []
        # self.prefix 为日志文件名 列如：mylog.2017-03-19 中的 mylog
        # 加上 点号 . 方便获取点号后面的日期
        prefix = self.prefix + '.'
        plen = len(prefix)
        for file_name in file_names:
            if file_name[:plen] == prefix:
                # 日期后缀 mylog.2017-03-19 中的 2017-03-19
                suffix = file_name[plen:]
                # 匹配符合规则的日志文件，添加到result列表中
                if re.compile(self.re_match).match(suffix):
                    result.append(os.path.join(dir_name, file_name))
        result.sort()

        # 返回  待删除的日志文件
        # 多于 保留文件个数 backupCount的所有前面的日志文件。
        if len(result) < self.backup_count:
            result = []
        else:
            result = result[:len(result) - self.backup_count]
        return result

    def emit(self, record):
        """发送一个日志记录
        覆盖FileHandler中的emit方法，logging会自动调用此方法"""
        try:
            if self.should_change_file():
                self.do_change_file()
            logging.FileHandler.emit(self, record)
        except (KeyboardInterrupt, SystemExit):
            raise
        except Exception:
            self.handleError(record)


def setup_logger(filename, name=None, debug=False, force=False, backtesing=False):
    """
    设置日志文件，包括路径
    自动在后面添加 "_日期.log"
    :param logger_file_name:
    :return:
    """

    global _logger
    global _fileHandler
    global _logger_filename

    if _logger is not None and _logger_filename == filename and not force:
        return _logger

    if _logger_filename != filename or force:
        if force:
            _logger_filename = filename

        # 定义日志输出格式
        fmt = logging.Formatter(RECORD_FORMAT if not backtesing else BACKTEST_FORMAT)
        if name is None:
            names = filename.replace('.log', '').split('/')
            name = names[-1]

        logger = logging.getLogger(name)
        if debug:
            logger.setLevel(logging.DEBUG)
            stream_handler = logging.StreamHandler(sys.stdout)
            stream_handler.setLevel(logging.DEBUG)
            stream_handler.setFormatter(fmt)
            if not logger.hasHandlers():
                logger.addHandler(stream_handler)

        fileHandler = MultiprocessHandler(filename, encoding='utf8', interval='D')
        if debug:
            fileHandler.setLevel(logging.DEBUG)
        else:
            fileHandler.setLevel(logging.WARNING)

        fileHandler.setFormatter(fmt)
        logger.addHandler(fileHandler)

        if debug:
            logger.setLevel(logging.DEBUG)
        else:
            logger.setLevel(logging.WARNING)

        return logger

    return _logger


def get_logger(name=None):
    global _logger

    if _logger is None:
        _logger = logging.getLogger(name)
        return _logger

    if _logger.name != name:
        return logging.getLogger(name)

    return _logger


# -------------------测试代码------------
def single_func(para):
    setup_logger('logs/MyLog{}'.format(para))
    logger = get_logger()
    if para > 5:
        # print u'more than 5'
        logger.info(u'{}大于 More than 5'.format(para))
        return True
    else:
        # print 'less'
        logger.info('{}Less than 5'.format(para))
        return False


def multi_func():
    # 启动多进程
    pool = multiprocessing.Pool(multiprocessing.cpu_count())
    setup_logger('logs/MyLog')
    logger = get_logger()
    logger.info('main process')
    task_list = []

    for i in range(0, 10):
        task_list.append(pool.apply_async(single_func, (i,)))

    [res.get() for res in task_list]

    pool.close()
    pool.join()


if __name__ == '__main__':

    # 创建启动主进程日志
    setup_logger('logs/MyLog')
    logger = get_logger()
    logger.info("info into multiprocessing")

    # 测试所有多进程日志
    multi_func()

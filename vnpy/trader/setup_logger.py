#!/usr/bin/env python
# coding=utf8
import logging
import threading
import logging.config
import os.path
import uuid
from logging import handlers
import os,sys
import re
from datetime import datetime
import multiprocessing

SIMPLE_FORMAT = "[%(asctime)s] %(message)s"
RECORD_FORMAT = "%(levelname)s  [%(asctime)s.%(msecs)d][%(filename)s:%(lineno)d][%(process)d:%(threadName)s] %(message)s"
COLOR_FORMAT = {
    'DEBUG': "\033[1;34m%(levelname)s\033[0m: ",
    'INFO': "\033[1;32m%(levelname)s\033[0m: ",
    'WARNING': "\033[1;33m%(levelname)s\033[0m: ",
    'ERROR': "\033[1;31m%(levelname)s\033[0m: ",
}
DATE_FORMAT = "%Y-%m-%d %H:%M:%S"

_logger = None
_fileHandler = None
_logger_filename = None

class ExtFormatter(logging.Formatter):

    def __init__(self, colorful=False, simple=False):
        self._colorful = colorful
        self._simple = simple
        logging.Formatter.__init__(self, datefmt=DATE_FORMAT)

    def format(self, record):
        fmt = SIMPLE_FORMAT if self._simple else RECORD_FORMAT
        if self._colorful:
            self._fmt = COLOR_FORMAT[record.levelname] + fmt
        else:
            self._fmt = "%(levelname)s: " + fmt
        return logging.Formatter.format(self, record)


class BasicFormatter(ExtFormatter):

    def __init__(self):
        super(BasicFormatter, self).__init__()


class SimpleFormatter(ExtFormatter):

    def __init__(self):
        super(SimpleFormatter, self).__init__(simple=True)


class ColorFormatter(ExtFormatter):

    def __init__(self):
        super(ColorFormatter, self).__init__(colorful=True)


thread_data = threading.local()



class StreamHandler(logging.StreamHandler):
    def acquire(self):
        pass

    def release(self):
        pass

class FileHandler(handlers.TimedRotatingFileHandler):
    def acquire(self):
        pass

    def release(self):
        pass


def setup_logger2(filename=None, debug=False):
    handlers = []
    LOGGING = {
        'version': 1,
        'disable_existing_loggers': True,
        'formatters': {
            'color': {
                '()': ColorFormatter,
            },
            'basic': {
                '()': BasicFormatter,
            },
        },
        'handlers': {
            'std_debug': {
                'level': 'DEBUG',
                '()': StreamHandler,
                'formatter': 'basic',
            },
            'std_info': {
                'level': 'INFO',
                '()': StreamHandler,
                'formatter': 'basic',
            }
        },
        'loggers': {
            '': {
                'level': 'DEBUG',
                'handlers': [],
                'propagate': True,
            },
            'tornado.access': {
                'level': 'DEBUG',
                'handlers': [],
                'propagate': False,
            },
            'tornado.application': {
                'level': 'DEBUG',
                'handlers': [],
                'propagate': False,
            },
            'tornado.gen_log': {
                'level': 'DEBUG',
                'handlers': [],
                'propagate': False,
            },
            'django': {
                'handlers': [],
                'propagate': True,
                'level': 'INFO',
            },
            'django.request': {
                'handlers': [],
                'level': 'INFO',
                'propagate': False,
            },
        },
    }

    if filename:
        base_name, ext = os.path.splitext(filename)
        debug_filename = '%s-debug%s' % (base_name, ext)
        warning_filename = '%s-warning%s' % (base_name, ext)
        error_filename = '%s-error%s' % (base_name, ext)
        critical_filename = '%s-critical%s' % (base_name, ext)
        local = {
            'local_debug': {
                'level': 'DEBUG',
                '()': FileHandler,
                'filename': debug_filename,
                'formatter': 'basic',
                'interval': 1,
                'when': 'D',
            },
            'local_info': {
                'level': 'INFO',
                '()': FileHandler,
                'filename': filename,
                'formatter': 'basic',
                'interval': 1,
                'when': 'D',
            },
            'local_error': {
                'level': 'ERROR',
                '()': FileHandler,
                'filename': error_filename,
                'formatter': 'basic',
                'interval': 1,
                'when': 'D',
            },
            'local_warning': {
                'level': 'WARNING',
                '()': FileHandler,
                'filename': warning_filename,
                'formatter': 'basic',
                'interval': 1,
                'when': 'D',
            },
            'local_critical': {
                'level': 'CRITICAL',
                '()': FileHandler,
                'filename': critical_filename,
                'formatter': 'basic',
                'interval': 1,
                'when': 'D',
            },

        }

        LOGGING['handlers'].update(local)
        handlers.append('local_info')
        if debug:
            handlers.append('local_debug')
        #handlers.append('local_error')
        #handlers.append('local_warning')
        #handlers.append('local_critical')

    else:
        if debug:
            handlers.append('std_debug')
        else:
            handlers.append('std_info')

    for k, v in LOGGING['loggers'].items():
        v['handlers'] = handlers

    logging.config.dictConfig(LOGGING)
    return LOGGING

try:
    import codecs
except ImportError:
    codecs = None

class MultiprocessHandler(logging.FileHandler):
    """支持多进程的TimedRotatingFileHandler"""
    def __init__(self,filename,when='D',backupCount=0,encoding=None,delay=False):
        """filename 日志文件名,
        when 时间间隔的单位,
        backupCount 保留文件个数,0表示不删除
        delay 是否开启 OutSteam缓存
            True 表示开启缓存，OutStream输出到缓存，待缓存区满后，刷新缓存区，并输出缓存数据到文件。
            False表示不缓存，OutStrea直接输出到文件"""
        self.prefix = filename
        self.backupCount = backupCount
        self.when = when.upper()
        # 正则匹配 年-月-日
        self.extMath = r"^\d{4}-\d{2}-\d{2}"

        # S 每秒建立一个新文件
        # M 每分钟建立一个新文件
        # H 每天建立一个新文件
        # D 每天建立一个新文件
        self.when_dict = {
            'S':"%Y-%m-%d-%H-%M-%S",
            'M':"%Y-%m-%d-%H-%M",
            'H':"%Y-%m-%d-%H",
            'D':"%Y-%m-%d"
        }
        #日志文件日期后缀
        self.suffix = self.when_dict.get(when)
        if not self.suffix:
            raise ValueError(u"指定的日期间隔单位无效: %s" % self.when)
        #拼接文件路径 格式化字符串
        self.filefmt = "%s_%s.log" % (self.prefix,self.suffix)
        #使用当前时间，格式化文件格式化字符串
        self.filePath = datetime.now().strftime(self.filefmt)
        #获得文件夹路径
        _dir = os.path.dirname(self.filefmt)
        try:
            #如果日志文件夹不存在，则创建文件夹
            if not os.path.exists(_dir):
                os.makedirs(_dir)
        except Exception:
            print( u"创建文件夹失败")
            print( u"文件夹路径：" + self.filePath)
            pass

        if codecs is None:
            encoding = None

        logging.FileHandler.__init__(self,self.filePath,'a+',encoding,delay)

    def shouldChangeFileToWrite(self):
        """更改日志写入目的写入文件
        :return True 表示已更改，False 表示未更改"""
        #以当前时间获得新日志文件路径
        _filePath = datetime.now().strftime(self.filefmt)
        #新日志文件日期 不等于 旧日志文件日期，则表示 已经到了日志切分的时候
        #   更换日志写入目的为新日志文件。
        #例如 按 天 （D）来切分日志
        #   当前新日志日期等于旧日志日期，则表示在同一天内，还不到日志切分的时候
        #   当前新日志日期不等于旧日志日期，则表示不在
        #同一天内，进行日志切分，将日志内容写入新日志内。
        if _filePath != self.filePath:
            self.filePath = _filePath
            return True
        return False

    def doChangeFile(self):
        """输出信息到日志文件，并删除多于保留个数的所有日志文件"""
        #日志文件的绝对路径
        self.baseFilename = os.path.abspath(self.filePath)
        #stream == OutStream
        #stream is not None 表示 OutStream中还有未输出完的缓存数据
        if self.stream:
            #flush close 都会刷新缓冲区，flush不会关闭stream，close则关闭stream
            #self.stream.flush()
            self.stream.close()
            #关闭stream后必须重新设置stream为None，否则会造成对已关闭文件进行IO操作。
            self.stream = None
        #delay 为False 表示 不OutStream不缓存数据 直接输出
        #   所有，只需要关闭OutStream即可
        if not self.delay:
            #这个地方如果关闭colse那么就会造成进程往已关闭的文件中写数据，从而造成IO错误
            #delay == False 表示的就是 不缓存直接写入磁盘
            #我们需要重新在打开一次stream
            #self.stream.close()
            self.stream = self._open()
        #删除多于保留个数的所有日志文件
        if self.backupCount > 0:
            print('删除日志')
            for s in self.getFilesToDelete():
                print(s)
                os.remove(s)

    def getFilesToDelete(self):
        """获得过期需要删除的日志文件"""
        #分离出日志文件夹绝对路径
        #split返回一个元组（absFilePath,fileName)
        #例如：split('I:\ScripPython\char4\mybook\util\logs\mylog.2017-03-19）
        #返回（I:\ScripPython\char4\mybook\util\logs， mylog.2017-03-19）
        # _ 表示占位符，没什么实际意义，
        dirName,_ = os.path.split(self.baseFilename)
        fileNames = os.listdir(dirName)
        result = []
        #self.prefix 为日志文件名 列如：mylog.2017-03-19 中的 mylog
        #加上 点号 . 方便获取点号后面的日期
        prefix = self.prefix + '.'
        plen = len(prefix)
        for fileName in fileNames:
            if fileName[:plen] == prefix:
                #日期后缀 mylog.2017-03-19 中的 2017-03-19
                suffix = fileName[plen:]
                #匹配符合规则的日志文件，添加到result列表中
                if re.compile(self.extMath).match(suffix):
                    result.append(os.path.join(dirName,fileName))
        result.sort()

        #返回  待删除的日志文件
        #   多于 保留文件个数 backupCount的所有前面的日志文件。
        if len(result) < self.backupCount:
            result = []
        else:
            result = result[:len(result) - self.backupCount]
        return result

    def emit(self, record):
        """发送一个日志记录
        覆盖FileHandler中的emit方法，logging会自动调用此方法"""
        try:
            if self.shouldChangeFileToWrite():
                self.doChangeFile()
            logging.FileHandler.emit(self,record)
        except (KeyboardInterrupt,SystemExit):
            raise
        except:
            self.handleError(record)

def setup_logger(filename, name=None, debug=False):
    """
    设置日志文件，包括路径
    自动在后面添加 "_日期.log"
    :param logger_file_name: 
    :return: 
    """

    global _logger
    global _fileHandler
    global _logger_filename

    if _logger is not None and _logger_filename == filename:
        return _logger

    if _logger_filename != filename:
        _logger_filename = filename
        # 定义日志输出格式
        fmt = logging.Formatter(RECORD_FORMAT)
        if name is None:
            names = filename.replace('.log','').split('/')
            name = names[-1]

        _logger = logging.getLogger(name)
        if debug:
            _logger.setLevel(logging.DEBUG)
            stream_handler = logging.StreamHandler(sys.stdout)
            stream_handler.setLevel(logging.DEBUG)
            stream_handler.setFormatter(fmt)
            _logger.addHandler(stream_handler)

        _fileHandler = MultiprocessHandler(filename, when='D')
        if debug:
            _fileHandler.setLevel(logging.DEBUG)
        else:
            _fileHandler.setLevel(logging.INFO)
            _fileHandler.setFormatter(fmt)

        _logger.addHandler(_fileHandler)

        if debug:
            _logger.setLevel(logging.DEBUG)
        else:
            _logger.setLevel(logging.INFO)

    return _logger

def get_logger(name=None):
    global _logger

    if _logger is None:
        _logger = logging.getLogger(name)
        return _logger

    if _logger.name !=name:
        return logging.getLogger(name)

    return _logger

def single_func(para):
    setup_logger('logs/MyLog{}'.format(para))
    logger = get_logger()
    if para > 5:
        #print u'more than 5'
        logger.info(u'{}大于 More than 5'.format(para))
        return True
    else:
        #print 'less'
        logger.info('{}Less than 5'.format(para))
        return False

def multi_func():

    # 启动多进程
    pool = multiprocessing.Pool(multiprocessing.cpu_count())

    setup_logger('logs/MyLog')
    logger = get_logger()
    logger.info('main process')
    l = []

    for i in range(0,10):
        l.append(pool.apply_async(single_func,(i,)))

    results = [res.get() for res in l]

    pool.close()
    pool.join()

if __name__ == '__main__':

    #logging_config = setup_logger('aaa.log', debug=True)
    # logging.info("aaaa")

    setup_logger('logs/MyLog')
    logger = get_logger()
    logger.info("info into multiprocessing")

    multi_func()
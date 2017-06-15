#!/usr/bin/env python
# coding=utf8
import logging
import threading
import logging.config
import os.path
import uuid
from logging import handlers

SIMPLE_FORMAT = "[%(asctime)s] %(message)s"
RECORD_FORMAT = "[%(asctime)s.%(msecs)d][%(filename)s:%(lineno)d][%(process)d:%(threadName)s] %(message)s"
COLOR_FORMAT = {
    'DEBUG': "\033[1;34m%(levelname)s\033[0m: ",
    'INFO': "\033[1;32m%(levelname)s\033[0m: ",
    'WARNING': "\033[1;33m%(levelname)s\033[0m: ",
    'ERROR': "\033[1;31m%(levelname)s\033[0m: ",
}
DATE_FORMAT = "%Y-%m-%d %H:%M:%S"


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


def setup_logger(filename=None, debug=False):
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

        }

        LOGGING['handlers'].update(local)
        handlers.append('local_info')
        if debug:
            handlers.append('local_debug')
    else:
        if debug:
            handlers.append('std_debug')
        else:
            handlers.append('std_info')

    for k, v in LOGGING['loggers'].items():
        v['handlers'] = handlers

    logging.config.dictConfig(LOGGING)
    return LOGGING

if __name__ == '__main__':
    setup_logger('aaa.log', debug=True)
    logging.info("aaaa")
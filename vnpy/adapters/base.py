# -*- coding=utf-8 -*-
# @Project  : crypto_backtrader
# @FilePath : adapters
# @File     : base.py
# @Time     : 2024/2/27 21:19
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description:
from __future__ import annotations

import os
from abc import ABC, abstractmethod
from enum import Enum
from typing import Optional, Literal


class DataSource(Enum):
    unknown = 0

    # file like
    csv = 1.1
    txt = 1.2
    json = 1.3

    # database like
    sqlite = 2.1
    mysql = 2.2
    clickhouse = 2.3  # clickhouse
    duckdb = 2.4  # duckdb比sqlite更快的数据库，且能较好的适配polars

    # memory like
    np_memmap = 3.1
    py_dict = 3.2

    # network like
    websock_binance = 4.1

    # destinations
    backtrader = 5.1


class StatusCode(Enum):
    success = 0
    failed = 900  # group 9 means failed


class BaseSchema(object):

    def to_sql(cls):
        return ','.join([f'`{k}` {v}' for k, v in cls.__dict__.items()])


class BaseAdapter(ABC):
    """
    可以用来连接系统的各种源，如文件、数据库、网络等
    """
    __from__: Optional[DataSource] = None
    __to__: Optional[DataSource] = None

    def __init__(self, tz='UTC', *args, **kwargs):
        os.environ['TZ'] = tz


class BaseDataAdapter(BaseAdapter):
    """
    Attributes
    ----------
    __reader_cls__ : BaseDataAdapter,
        to specify the reader class
    __writer_cls__ : BaseDataAdapter,
        to specify the writer class
    """
    __reader_cls__ = None
    __writer_cls__ = None

    def __init__(self, from_: Optional[DataSource] = None, to_: Optional[DataSource] = None, *args, **kwargs):
        """

        Parameters
        ----------
        from_ : DataSource
        to_ : DataSource
        args :
        kwargs :
        """
        super().__init__(tz=kwargs.get('tz', 'UTC'))
        self.__from__ = from_
        self.__to__ = to_
        self.__reader_cls__ = from_  # todo: 落实到具体class
        self.__writer_cls__ = to_  # todo: 落实到具体class

    @classmethod
    def _pre_read_(cls, path):
        """
        check if the file exists
        """
        if not os.path.exists(path):
            raise FileExistsError(f'file does not exist: {path}')

    @classmethod
    def _pre_write_(cls, path, not_exists: Literal['raise', 'create'] = 'raise'):
        """
        check if the dir exists, if not, create it when not_exists=='create'
        """
        if not_exists == 'raise' and not os.path.exists(path):
            raise FileExistsError(f'dir does not exist: {path}')
        os.makedirs(os.path.dirname(path), exist_ok=True)

    @classmethod
    def _sort_data_polars_(cls, data, by='open_time', descending: bool = False):
        """
        sort the data by 'open_time'
        """
        return data.sort(by, descending=descending)

    @classmethod
    def _set_sorted_polars_(cls, data, by='open_time'):
        """
        set the data by 'open_time'
        """
        return data.set_sorted(by)

    # @abstractmethod
    # def write(self, *args, **kwargs):
    #     """
    #     write all the data
    #     Parameters
    #     ----------
    #     args :
    #     kwargs :
    #
    #     Returns
    #     -------
    #
    #     """
    #     pass

    # def process(self, *args, **kwargs):
    #     # data = self.read()
    #     # self.write(data)
    #     pass

    # @abstractmethod
    # def read(self, *args, **kwargs):
    #     """
    #     read all the data
    #     Parameters
    #     ----------
    #     args :
    #     kwargs :
    #
    #     Returns
    #     -------
    #
    #     """
    #     pass


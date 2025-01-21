# -*- coding=utf-8 -*-
# @Project  : crypto_backtrader
# @FilePath : adapters
# @File     : core.py
# @Time     : 2024/3/13 13:35
# @Author   : EvanHong
# @Email    : 939778128@qq.com
# @Description: initialize both reader and writer and this class will be the main api for data requirements.

from typing import Optional, Union, TypeVar, Type

import polars as pl

from .base import BaseDataAdapter, DataSource

T_reader = TypeVar('T_reader', bound=BaseDataAdapter)
T_writer = TypeVar('T_writer', bound=BaseDataAdapter)


class DataAdapter(BaseDataAdapter):
    """initialize both reader and writer and this class will be the main api for data requirements.
    主要有两种数据
    1. 市场行情，即kline数据
    2. factor数据，即用于生成信号的数据
    """

    def __init__(self,
                 from_: Optional[DataSource] = None,
                 to_: Optional[DataSource] = None,
                 reader: Type[T_reader,] = None,
                 writer: Type[T_writer,] = None,
                 *args, **kwargs):
        super().__init__(from_=from_, to_=to_, *args, **kwargs)
        self.reader = reader
        self.writer = writer
        self.__reader_cls__ = reader.__class__ if reader else None
        self.__writer_cls__ = writer.__class__ if writer else None

    def read(self, path: str, *args, **kwargs) -> pl.DataFrame:
        df = self.reader.read(path, *args, **kwargs)
        return df

    def write(self, data: Union[pl.DataFrame], path: str, *args, **kwargs):
        self.writer.write(data, path, *args, **kwargs)

    def process(self, *args, **kwargs):
        pass

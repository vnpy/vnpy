# encoding: UTF-8

'''
vn.py - By Traders, For Traders.

The vn.py project is an open-source quantitative trading framework 
that is developed by traders, for traders. 

The project is mainly written in Python and uses C++ for low-layer 
and performance sensitive infrastructure.

Using the vn.py project, institutional investors and professional 
traders, such as hedge funds, prop trading firms and investment banks, 
can easily develop complex trading strategies with the Event Engine 
Strategy Module, and automatically route their orders to the most 
desired destinations, including equity, commodity, forex and many 
other financial markets.
'''


import os
from setuptools import setup

import vnpy


def getSubpackages(name):
    """获取该模块下所有的子模块名称"""
    splist = []

    for dirpath, _dirnames, _filenames in os.walk(name):
        if os.path.isfile(os.path.join(dirpath, '__init__.py')):
            splist.append(".".join(dirpath.split(os.sep)))
    
    return splist


setup(
    name='vnpy',
    version=vnpy.__version__,
    author=vnpy.__author__,
    author_email='vn.py@foxmail.com',
    license='MIT',
    url='http://www.vnpy.org',
    description='A framework for developing Quantitative Trading programmes',
    long_description = __doc__,    
    keywords='quant quantitative investment trading algotrading',
    classifiers=['Development Status :: 4 - Beta',
                 'Operating System :: Microsoft :: Windows :: Windows 7',
                 'Operating System :: Microsoft :: Windows :: Windows 8',
                 'Operating System :: Microsoft :: Windows :: Windows 10',
                 'Operating System :: Microsoft :: Windows :: Windows Server 2008',
                 'Programming Language :: Python :: 2',
                 'Programming Language :: Python :: 2.7',
                 'Topic :: Office/Business :: Financial :: Investment',
                 'Programming Language :: Python :: Implementation :: CPython',
                 'License :: OSI Approved :: MIT License'],
    packages=getSubpackages('vnpy'),
    package_data={'': ['*.json', '*.md', '*.ico',
                       '*.h', '*.cpp', '*.bash', '*.txt',
                       '*.dll', '*.lib', '*.so', '*.pyd',
                       '*.dat', '*.ini', '*.pfx', '*.scc', '*.crt', '*.key']},
    extras_require={
        'tq': ["tornado>=4.5.1", "sortedcontainers>=1.5.7"],
    }
)
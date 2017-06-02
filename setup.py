# encoding: UTF-8

import os
from setuptools import setup

import vnpy


long_desc = """   
"""

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
    description='A framework for developing quantitative trading strategy',
    long_description = long_desc,
    author=vnpy.__author__,
    author_email='vn.py@foxmail.com',
    license='MIT',
    url='http://www.vnpy.org',
    keywords='Python quantitative trading framework',
    classifiers=['Development Status :: 4 - Beta',
                 'Programming Language :: Python :: 2.7',
                 'License :: OSI Approved :: MIT License'],
    packages=getSubpackages('vnpy'),
    package_data={'': ['*.json', '*.md', '*.ico',
                       '*.dll', '*.lib', '*.so', '*.pyd',
                       '*.dat', '*.ini', '*.pfx', '*.scc', '*.crt', '*.key']},
)
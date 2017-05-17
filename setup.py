# encoding: UTF-8

from setuptools import setup
import vnpy


long_desc = """   
"""


setup(
    name='vnpy',
    version=vnpy.__version__,
    description='A utility for crawling historical and Real-time Quotes data of China stocks',
    long_description = long_desc,
    author=vnpy.__author__,
    author_email='vn.py@foxmail.com',
    license='MIT',
    url='http://www.vnpy.org',
    keywords='Python quantitative trading framework',
    classifiers=['Development Status :: 4 - Beta',
    'Programming Language :: Python :: 2.7'
    'License :: OSI Approved :: MIT License'],
    packages=['vnpy','vnpy.api', 'vnpy.event', 'vnpy.rpc', 'vnpy.trader'],
    package_data={'': ['*.json']},
)
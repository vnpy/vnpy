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


import os, sys, glob, shutil, platform

# Require Python 2.6+
if sys.version_info < (2, 6):
    raise RuntimeError('Python 2.6 or higher required')

from setuptools import setup, find_packages, Extension

import vnpy

here = os.path.abspath(os.path.dirname(__file__))

# Sample
# module1 = Extension('demo',
#     define_macros = [('MAJOR_VERSION', '1'),
#                      ('MINOR_VERSION', '0')],
#     include_dirs = ['/usr/local/include'],
#     libraries = ['tcl83'],
#     library_dirs = ['/usr/local/lib'],
#     sources = ['demo.c'])

BOOST_INC = os.environ['BOOST_INC']
BOOST_LIB = os.environ['BOOST_LIB']

system = platform.system()
is_64bits = sys.maxsize > 2**32

ctp_path = 'vnpy/api/ctp/'
ctpapi_path = os.path.join(ctp_path, 'ctpapi')

if system == 'Linux':
    if is_64bits:
        CTP_API_INC = os.path.join(ctpapi_path, 'linux64')
        CTP_API_LIB = os.path.join(ctpapi_path, 'linux64')
        DEPENDS = glob.glob(os.path.join(ctpapi_path, 'linux64', '*.so'))
    else:
        raise RuntimeError('Unsupport Linux 32bit.')
elif system == 'Windows':
    if is_64bits:
        CTP_API_INC = os.path.join(ctpapi_path, 'win64')
        CTP_API_LIB = os.path.join(ctpapi_path, 'win64')
        DEPENDS = glob.glob(os.path.join(ctpapi_path, 'win64', '*.dll'))
    else:
        CTP_API_INC = os.path.join(ctpapi_path, 'win32')
        CTP_API_LIB = os.path.join(ctpapi_path, 'win32')
        DEPENDS = glob.glob(os.path.join(ctpapi_path, 'win32', '*.dll'))
else:
    raise RuntimeError('Unsupport Platform.')


vnctpmd_module = Extension('vnpy.api.ctp.vnctpmd',
    include_dirs = [BOOST_INC, CTP_API_INC],
    library_dirs = [BOOST_LIB, CTP_API_INC],
    libraries = ['thostmduserapi', 'thosttraderapi'],
    sources = ['vnpy/api/ctp/vnctpmd/vnctpmd.cpp'],
    extra_compile_args=['-EHsc'], # boost exception support
    # extra_compile_args=['-DBOOST_PYTHON_STATIC_LIB'],
    )

vnctptd_module = Extension('vnpy.api.ctp.vnctptd',
    include_dirs = [BOOST_INC, CTP_API_INC],
    library_dirs = [BOOST_LIB, CTP_API_INC],
    libraries = ['thostmduserapi', 'thosttraderapi'],
    sources = ['./vnpy/api/ctp/vnctptd/vnctptd.cpp'],
    extra_compile_args=['-EHsc'], # boost exception support
    # extra_compile_args=['-DBOOST_PYTHON_STATIC_LIB'],
    )

# hotfix
# copy depends(dll/so) to ctp folder
# BUG: duplicate copy or co-exist (dll and so)
for f in DEPENDS:
    shutil.copy2(f, ctp_path)

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
    packages=find_packages(exclude=['docker', 'docs', 'examples', 'tutorial', 'test']),
    package_data={'': ['*.json', '*.md', '*.ico',
                       '*.h', '*.cpp', '*.bash', '*.txt',
                       '*.dll', '*.lib', '*.so', '*.pyd',
                       '*.dat', '*.ini', '*.pfx', '*.scc', '*.crt', '*.key']
                 },
    # data_files=[('', ['vnpy/api/ctp/ctpapi/win64/thostmduserapi.dll', 'vnpy/api/ctp/ctpapi/win64/thostmduserapi.dll'])],
    extras_require={
        'tq': ["tornado>=4.5.1", "sortedcontainers>=1.5.7"],
    },
    ext_modules = [vnctpmd_module, vnctptd_module]
)
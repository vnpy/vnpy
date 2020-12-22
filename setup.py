"""
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
"""

import ast
import os
import platform
import re
import sys

from setuptools import Extension, find_packages, setup


def gather_autocxxpy_generated_files(root: str):
    fs = [os.path.join(root, "module.cpp")]
    for root, dirs, filenames in os.walk(root):
        for filename in filenames:
            filebase, ext = os.path.splitext(filename)
            if ext == ".cpp" and filebase.startswith("generated_functions_"):
                path = os.path.join(root, filename)
                fs.append(path)
    return fs


def check_extension_build_flag(ext_modules, key: str, module: Extension):
    value = os.environ.get(key, None)
    if value is not None:
        if value == '1':
            ext_modules = list(set(ext_modules) | {module})
        elif value == '0':
            ext_modules = list(set(ext_modules) - {module})
        else:
            raise ValueError(
                f"Flag {key} should be '0' or '1', but {repr(value)} got.")
    return ext_modules


def is_psycopg2_exists():
    try:
        import psycopg2  # noqa
        return True
    except ImportError:
        return False


def get_install_requires():
    install_requires = [
        "PyQt5",
        "qdarkstyle",
        "requests",
        "websocket-client",
        "peewee",
        "numpy",
        "pandas",
        "matplotlib",
        "seaborn",
        "rqdatac",
        "ta-lib",
        "deap",
        "pyzmq",
        "QScintilla"
    ]
    if not is_psycopg2_exists():
        install_requires.append("psycopg2-binary")

    if sys.version_info.minor < 7:
        install_requires.append("dataclasses")
    return install_requires


def get_version_string():
    global version
    with open("vnpy/__init__.py", "rb") as f:
        version_line = re.search(
            r"__version__\s+=\s+(.*)", f.read().decode("utf-8")
        ).group(1)
        return str(ast.literal_eval(version_line))


def get_ext_modules():
    if platform.uname().system == "Windows":
        compiler_flags = [
            "/MP", "/std:c++17",  # standard
            "/O2", "/Ob2", "/Oi", "/Ot", "/Oy", "/GL",  # Optimization
            "/bigobj",  # Better compatibility
            "/wd4819",  # 936 code page
            "/D_CRT_SECURE_NO_WARNINGS",
            # suppress warning of unsafe functions like fopen, strcpy, etc
        ]
        extra_link_args = []
        runtime_library_dirs = None
    else:
        compiler_flags = [
            "-std=c++17",  # standard
            "-O3",  # Optimization
            "-Wno-delete-incomplete", "-Wno-sign-compare",
        ]
        extra_link_args = ["-lstdc++"]
        runtime_library_dirs = ["$ORIGIN"]

    vnctpmd = Extension(
        "vnpy.api.ctp.vnctpmd",
        [
            "vnpy/api/ctp/vnctp/vnctpmd/vnctpmd.cpp",
        ],
        include_dirs=["vnpy/api/ctp/include",
                      "vnpy/api/ctp/vnctp"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/ctp/libs", "vnpy/api/ctp"],
        libraries=["thostmduserapi_se", "thosttraderapi_se"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnctptd = Extension(
        "vnpy.api.ctp.vnctptd",
        [
            "vnpy/api/ctp/vnctp/vnctptd/vnctptd.cpp",
        ],
        include_dirs=["vnpy/api/ctp/include",
                      "vnpy/api/ctp/vnctp"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/ctp/libs", "vnpy/api/ctp"],
        libraries=["thostmduserapi_se", "thosttraderapi_se"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnxtpmd = Extension(
        "vnpy.api.xtp.vnxtpmd",
        [
            "vnpy/api/xtp/vnxtp/vnxtpmd/vnxtpmd.cpp",
        ],
        include_dirs=["vnpy/api/xtp/include",
                      "vnpy/api/xtp/vnxtp"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/xtp/libs", "vnpy/api/xtp"],
        libraries=["xtptraderapi", "xtpquoteapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnxtptd = Extension(
        "vnpy.api.xtp.vnxtptd",
        [
            "vnpy/api/xtp/vnxtp/vnxtptd/vnxtptd.cpp",
        ],
        include_dirs=["vnpy/api/xtp/include",
                      "vnpy/api/xtp/vnxtp"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/xtp/libs", "vnpy/api/xtp"],
        libraries=["xtptraderapi", "xtpquoteapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnksgoldmd = Extension(
        "vnpy.api.ksgold.vnksgoldmd",
        [
            "vnpy/api/ksgold/vnksgold/vnksgoldmd/vnksgoldmd.cpp",
        ],
        include_dirs=["vnpy/api/ksgold/include",
                      "vnpy/api/ksgold/vnksgold"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/ksgold/libs", "vnpy/api/ksgold"],
        libraries=["ksgoldquotmarketdataapi", "ksgoldtraderapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnksgoldtd = Extension(
        "vnpy.api.ksgold.vnksgoldtd",
        [
            "vnpy/api/ksgold/vnksgold/vnksgoldtd/vnksgoldtd.cpp",
        ],
        include_dirs=["vnpy/api/ksgold/include",
                      "vnpy/api/ksgold/vnksgold"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/ksgold/libs", "vnpy/api/ksgold"],
        libraries=["ksgoldquotmarketdataapi", "ksgoldtraderapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnsgitmd = Extension(
        "vnpy.api.sgit.vnsgitmd",
        [
            "vnpy/api/sgit/vnsgit/vnsgitmd/vnsgitmd.cpp",
        ],
        include_dirs=["vnpy/api/sgit/include",
                      "vnpy/api/sgit/vnsgit"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/sgit/libs", "vnpy/api/sgit"],
        libraries=["crypto", "sgitquotapi", "sgittradeapi", "ssl"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnsgittd = Extension(
        "vnpy.api.sgit.vnsgittd",
        [
            "vnpy/api/sgit/vnsgit/vnsgittd/vnsgittd.cpp",
        ],
        include_dirs=["vnpy/api/sgit/include",
                      "vnpy/api/sgit/vnsgit"],
        define_macros=[],
        undef_macros=[],
        library_dirs=["vnpy/api/sgit/libs", "vnpy/api/sgit"],
        libraries=["crypto", "sgitquotapi", "sgittradeapi", "ssl"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        depends=[],
        language="cpp",
    )

    vnnhmd = Extension(
        "vnpy.api.nh.vnnhmd",
        [
            "vnpy/api/nh/vnnh/vnnhmd/vnnhmd.cpp",
        ],
        include_dirs=["vnpy/api/nh/include", "vnpy/api/nh/vnnh"],
        library_dirs=["vnpy/api/nh/libs", "vnpy/api/nh"],
        libraries=["nhmdapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        language="cpp",
    )

    vnnhfutures = Extension(
        "vnpy.api.nh.vnnhfutures",
        [
            "vnpy/api/nh/vnnh/vnnhfutures/vnnhfutures.cpp",
        ],
        include_dirs=["vnpy/api/nh/include", "vnpy/api/nh/vnnh"],
        library_dirs=["vnpy/api/nh/libs", "vnpy/api/nh"],
        libraries=["nhtd2traderapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        language="cpp",
    )

    vnnhstock = Extension(
        "vnpy.api.nh.vnnhstock",
        [
            "vnpy/api/nh/vnnh/vnnhstock/vnnhstock.cpp",
        ],
        include_dirs=["vnpy/api/nh/include", "vnpy/api/nh/vnnh"],
        library_dirs=["vnpy/api/nh/libs", "vnpy/api/nh"],
        libraries=["nhtdstockapi"],
        extra_compile_args=compiler_flags,
        extra_link_args=extra_link_args,
        runtime_library_dirs=runtime_library_dirs,
        language="cpp",
    )

    if platform.system() == "Windows":
        # use pre-built pyd for windows ( support python 3.7 only )
        ext_modules = []
    elif platform.system() == "Darwin":
        ext_modules = []
    else:
        ext_modules = [
            vnctptd, vnctpmd,
            vnxtptd, vnxtpmd,
            vnsgittd, vnsgitmd,
            vnksgoldmd, vnksgoldtd,
            vnnhmd, vnnhfutures, vnnhstock
        ]

    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_CTP", vnctptd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_CTP", vnctpmd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_XTP", vnxtptd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_XTP", vnxtpmd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_sgit", vnsgittd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_sgit", vnsgitmd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_ksgold", vnksgoldmd)
    ext_modules = check_extension_build_flag(
        ext_modules, "VNPY_BUILD_ksgold", vnksgoldtd)

    return ext_modules


parallel = os.environ.get('VNPY_BUILD_PARALLEL', None)
if parallel:
    if parallel == 'auto':
        parallel = os.cpu_count()
    if parallel != 'no':
        from ci.parallel_build_distutils import patch_distutils

        patch_distutils(int(parallel))

setup(
    name="vnpy",
    version=get_version_string(),
    author="vn.py team",
    author_email="vn.py@foxmail.com",
    license="MIT",
    url="https://www.vnpy.com",
    description="A framework for developing quant trading systems.",
    long_description=__doc__,
    keywords='quant quantitative investment trading algotrading',
    include_package_data=True,
    packages=find_packages(exclude=["tests", "ci", "tests.*"]),
    package_data={"": [
        "*.ico",
        "*.ini",
        "*.dll",
        "*.so",
        "*.pyd",
    ]},
    install_requires=get_install_requires(),
    classifiers=[
        "Development Status :: 5 - Production/Stable",
        "Operating System :: Microsoft :: Windows :: Windows 7",
        "Operating System :: Microsoft :: Windows :: Windows 8",
        "Operating System :: Microsoft :: Windows :: Windows 10",
        "Operating System :: Microsoft :: Windows :: Windows Server 2008",
        "Operating System :: Microsoft :: Windows :: Windows Server 2012",
        "Operating System :: Microsoft :: Windows :: Windows Server 2019",
        "Operating System :: POSIX :: Linux"
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.7",
        "Topic :: Office/Business :: Financial :: Investment",
        "Programming Language :: Python :: Implementation :: CPython",
        "License :: OSI Approved :: MIT License",
        "Natural Language :: Chinese (Simplified)"
    ],
    ext_modules=get_ext_modules(),
)

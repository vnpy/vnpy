import platform

from setuptools import Extension, setup

# 编译前
#  pip install -U setuptools,pybind11
# 在ctp目录下,
#  activate py37
#  python setup.py build
dir_path = "ctp"
runtime_library_dirs = []
if platform.uname().system == "Windows":
    compiler_flags = [
        "/MP", "/std:c++17",  # standard
        "/O2", "/Ob2", "/Oi", "/Ot", "/Oy", "/GL",  # Optimization
        "/wd4819"  # 936 code page
    ]
    extra_link_args = []

else:
    compiler_flags = [
        "-std=c++17",  # standard
        "-O3",  # Optimization
        "-Wno-delete-incomplete", "-Wno-sign-compare", "-pthread"
    ]
    extra_link_args = ["-lstdc++"]
    runtime_library_dirs = ["$ORIGIN"]

vnctpmd = Extension(
    # 编译对象
    "vnctpmd",
    # 指定 vnctpmd 的位置
    [
        f"vnctp/vnctpmd/vnctpmd.cpp",
    ],
    # 编译需要的头文件
    include_dirs=[
        f"include",
        f"vnctp",
    ],
    # 指定为c plus plus
    language="cpp",
    define_macros=[],
    undef_macros=[],
    # 依赖目录
    library_dirs=[f"libs", f"."],
    # 依赖项
    libraries=["thostmduserapi_se", "thosttraderapi_se", ],
    extra_compile_args=compiler_flags,
    extra_link_args=extra_link_args,
    depends=[],
    runtime_library_dirs=runtime_library_dirs,
)
vnctptd = Extension(
    "vnctptd",
    [
        f"vnctp/vnctptd/vnctptd.cpp",
    ],
    include_dirs=[
        f"include",
        f"vnctp",
    ],
    define_macros=[],
    undef_macros=[],
    library_dirs=[f"libs", f"."],
    libraries=["thostmduserapi_se", "thosttraderapi_se"],
    extra_compile_args=compiler_flags,
    extra_link_args=extra_link_args,
    runtime_library_dirs=runtime_library_dirs,
    depends=[],
    language="cpp",
)

if platform.system() == "Windows":
    # use pre-built pyd for windows ( support python 3.7 only )
    ext_modules = [vnctptd, vnctpmd]
elif platform.system() == "Darwin":
    ext_modules = []
else:
    ext_modules = [vnctptd, vnctpmd]

pkgs = ['']
install_requires = []
setup(
    name='ctp',
    version='1.0',
    description="good luck",
    author='incenselee',
    author_email='incenselee@hotmail.com',
    license="MIT",
    packages=pkgs,
    install_requires=install_requires,
    platforms=["Windows", "Linux", "Mac OS-X"],
    package_dir={'ctp': 'ctp'},
    package_data={'ctp': ['*', ]},
    ext_modules=ext_modules,
    classifiers=[
        'Development Status :: 4 - Beta',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3.7',
    ]
)

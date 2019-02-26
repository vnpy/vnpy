import platform
import ast
import re
from setuptools import Extension, find_packages, setup

with open("vnpy/__init__.py", "rb") as f:
    version_line = re.search(
        r"__version__\s+=\s+(.*)", f.read().decode("utf-8")
    ).group(1)
    version = str(ast.literal_eval(version_line))

if platform.uname().system == "Windows":
    compiler_flags = []
else:
    compiler_flags = ["-std=c++11", "-Wno-delete-incomplete"]

vnctpmd = Extension("vnpy.api.ctp.vnctpmd",
                    [
                        "vnpy/api/ctp/vnctp/vnctpmd/vnctpmd.cpp",
                    ],
                    include_dirs=["vnpy/api/ctp/include", "vnpy/api/ctp/vnctp", ],
                    define_macros=[],
                    undef_macros=[],
                    library_dirs=["vnpy/api/ctp/libs"],
                    libraries=["thostmduserapi", "thosttraderapi", ],
                    extra_compile_args=compiler_flags,
                    extra_link_args=[],
                    depends=[],
                    language="cpp",
                    )
vnctptd = Extension("vnpy.api.ctp.vnctptd",
                    [
                        "vnpy/api/ctp/vnctp/vnctptd/vnctptd.cpp",
                    ],
                    include_dirs=["vnpy/api/ctp/include", "vnpy/api/ctp/vnctp", ],
                    define_macros=[],
                    undef_macros=[],
                    library_dirs=["vnpy/api/ctp/libs"],
                    libraries=["thostmduserapi", "thosttraderapi", ],
                    extra_compile_args=compiler_flags,
                    extra_link_args=[],
                    depends=[],
                    language="cpp",
                    )

# use built in pyd for windows
if platform.uname().system == "Windows":
    ext_modules = []
else:
    ext_modules = [vnctptd, vnctpmd],

pkgs = find_packages()

s = setup(
    name="vnpy",
    version=version,
    include_package_data=True,
    packages=pkgs,
    package_data={"": [
        "*.json", "*.md", "*.ico",
        "*.dll", "*.so",
    ]},
    install_requires=[],
    ext_modules=ext_modules
)

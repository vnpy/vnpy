import platform

from setuptools import Extension, find_packages, setup

if platform.uname().system == "Windows":
    compiler_flags = []
else:
    compiler_flags = ['-std=c++11', '-Wno-delete-incomplete']

vnctpmd = Extension('vnpy.api.ctp.vnctpmd',
                    [
                        "vnpy/api/ctp/vnctp/vnctpmd/vnctpmd.cpp",
                    ],
                    include_dirs=["vnpy/api/ctp/include", "vnpy/api/ctp/vnctp", ],
                    define_macros=[],
                    undef_macros=[],
                    library_dirs=["vnpy/api/ctp/libs"],
                    libraries=["thostmduserapi", "thosttraderapi", ],
                    # runtime_library_dirs=["vnpy/api/ctp/libs", ],
                    extra_compile_args=compiler_flags,
                    extra_link_args=[],
                    depends=[],
                    language="cpp",
                    )
vnctptd = Extension('vnpy.api.ctp.vnctptd',
                    [
                        "vnpy/api/ctp/vnctp/vnctptd/vnctptd.cpp",
                    ],
                    include_dirs=["vnpy/api/ctp/include", "vnpy/api/ctp/vnctp", ],
                    define_macros=[],
                    undef_macros=[],
                    library_dirs=["vnpy/api/ctp/libs"],
                    libraries=["thostmduserapi", "thosttraderapi", ],
                    # runtime_library_dirs=["vnpy/api/ctp/libs", ],
                    extra_compile_args=compiler_flags,
                    extra_link_args=[],
                    depends=[],
                    language="cpp",
                    )

pkgs = find_packages()

s = setup(
    name="vnpy",
    version="2.0.dev0",
    include_package_data=True,
    packages=pkgs,
    package_data={'': [
        '*.json', '*.md', '*.ico',
        '*.dll', '*.so',
    ]},
    ext_modules=[vnctptd, vnctpmd],
)

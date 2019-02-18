from setuptools import Extension, find_packages, setup

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
                    extra_compile_args=[],
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
                    extra_compile_args=[],
                    extra_link_args=[],
                    depends=[],
                    language="cpp",
                    )

setup(
    name="vnpy",
    version="2.0.dev0",
    packages=find_packages(exclude=["tests", "tests.*", "*.tests.*"]),
    ext_modules=[vnctptd, vnctpmd],
)

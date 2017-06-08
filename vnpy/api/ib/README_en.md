# vn.ib

`vn.ib` is still under developing, encapsulation is partially done, further
contributions are warmly welcome : )

### Introduction

`vn.ib` is a Python encapsulation of IB POSIX C++ API with full functionality of
the original C++ API. The name of functions and classes is consistent with original
C++ API.

### Difference between vn.py and IbPy

1. `vn.ib` is a Python encapsulation of POSIX C++ API based on Boost.Python, which
provides higher efficiency than IbPy.
2. `vn.ib` integrates exception handling function inside the encapsulation, which
avoids the disconnection to the IB server when exception is triggered.
3. `vn.ib` needs to be compiled before calling (by default, .pyd file is compiled
under Windows 7 32bit environment), while IbPy is a pure Python library.
4. `vn.ib` is based on 9.72 beta API, while IbPy is based on old 9.70 stable API.

### Changes from original API

Object comparison functions are added into `shared_ptr.h` and `SoftDollerTier.h`
in order to automaticall encapsulate `vector` object to Python.

### Linux version

Currently, revision is needed to deploy `vn.ib` in Linux environment:

1. Object comparison functions are added into `shared_ptr.h` and `SoftDollerTier.h`
in order to automaticall encapsulate `vector` object to Python.
2. `EReader.cpp`: EReader::bufferedRead, change `min` to `std::min` (No revision
needed in Windows environment)
3. `EClient.cpp`: Add `EncodeField<const char*>` in order to partially characterize
`EncodeField<T>` (If you use GCC to compile, you need to do this, otherwise you
will get `underfined symbol` error. MSVC is free from the error).

We suspect that IB development team is developing and testing the API under Windows
environment, here is the compiling process:

1. cd `vn.ib/ibapi/linux`, run `bash build.sh` to generate twsapi.so
2. cd `vn.ib/`, run `bash build.sh` to generate vnib.so

### API version

Version: IB API for Windows beta 9.72.18

Date: 2016-09-14

Link: [http://interactivebrokers.github.io/](http://interactivebrokers.github.io/)

from distutils.core import setup
from Cython.Build import cythonize

setup(
    name='black_76_cython',
    ext_modules=cythonize("black_76_cython.pyx"),
)

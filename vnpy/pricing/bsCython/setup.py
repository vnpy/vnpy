from distutils.core import setup
from Cython.Build import cythonize

setup(
  name = 'bsCython',
  ext_modules = cythonize("bsCython.pyx"),
)

from distutils.core import setup
from Cython.Build import cythonize

setup(
  name = 'cython test',
  ext_modules = cythonize("test.pyx"),
)
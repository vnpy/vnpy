# encoding: UTF-8
from distutils.core import setup
from Cython.Build import cythonize
import numpy


setup(
  name = 'crrCython',
  ext_modules = cythonize("crrCython.pyx"),
  include_dirs = [numpy.get_include()]
)

from distutils.core import setup
from Cython.Build import cythonize
import numpy

setup(
    name='binomial_tree_cython',
    ext_modules=cythonize("binomial_tree_cython.pyx"),
    include_dirs=[numpy.get_include()]
)

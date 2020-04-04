#from distutils.core import setup, Extension
from distutils.core import setup 
from distutils.extension import Extension 
from Cython.Distutils import build_ext
from Cython.Build import cythonize

setup(
  name='py_t2sdk',
  version='1.0.0',
  author='rdc@hundsun',
  author_email='',
  url='',
  ext_modules = cythonize(Extension(
    'py_t2sdk',
    sources=['py_t2sdk.pyx','ufx_interface.cpp'],
    language='c++',
    include_dirs=[],
    library_dirs=[],
    libraries=['t2sdk'],
    extra_compile_args=[],
    extra_link_args=[]
)))
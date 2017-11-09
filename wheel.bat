
# step 1: setup boost library path

# sample: windows 64bit + python2.7.X 64bit
set BOOST_INC=C:\local\boost_1_65_1
set BOOST_LIB=C:\local\boost_1_65_1\lib64-msvc-9.0

# step 2: run build script

python setup.py bdist_wheel


# TODO cshshlp/shzd...
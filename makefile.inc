CXX = g++
LIBRARIES = -lboost_thread -lboost_python -lpython2.7
COMMON_FLAGS = -D__GNU__ -fPIC
INCLUDE = -I/usr/include/python2.7/
ROOTPATH = $(dir $(abspath $(lastword $(MAKEFILE_LIST))))

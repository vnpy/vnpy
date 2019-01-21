cmake_minimum_required(VERSION 2.8)

project(vnpy_binding)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(cmake/flags.cmake)
include(cmake/py.cmake)

include_directories(third_party/include)

add_subdirectory(source)

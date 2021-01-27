# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_DA C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vndafuture_sources 
    "vnda/vndafuture/vndafuture.cpp")
message(STATUS "vndafuture_sources ${vndafuture_sources}")
add_library(vndafuture MODULE ${vndafuture_sources})
target_include_directories(vndafuture
    PRIVATE include
    PRIVATE vnda
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnda/vndafuture )
target_link_directories(vndafuture PRIVATE . PRIVATE libs)
target_link_libraries(vndafuture DAApi_x64)
python_extension_module(vndafuture)


file(GLOB vndamarket_sources 
    "vnda/vndamarket/vndamarket.cpp")
message(STATUS "vndamarket_sources ${vndamarket_sources}")
add_library(vndamarket MODULE ${vndamarket_sources})
target_include_directories(vndamarket
    PRIVATE include
    PRIVATE vnda
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnda/vndamarket )
target_link_directories(vndamarket PRIVATE . PRIVATE libs)
target_link_libraries(vndamarket DAApi_x64)
python_extension_module(vndamarket)

file(GLOB vndastock_sources 
    "vnda/vndastock/vndastock.cpp")
message(STATUS "vndastock_sources ${vndastock_sources}")
add_library(vndastock MODULE ${vndastock_sources})
target_include_directories(vndastock
    PRIVATE include
    PRIVATE vnda
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnda/vndastock )
target_link_directories(vndastock PRIVATE . PRIVATE libs)
target_link_libraries(vndastock DAApi_x64)
python_extension_module(vndastock)


set_target_properties(vndastock vndamarket vndafuture
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vndastock vndamarket vndafuture LIBRARY DESTINATION vnpy/api/da)


# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_NH C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnnhfutures_sources 
    "vnnh/vnnhfutures/vnnhfutures.cpp")
message(STATUS "vnnhfutures_sources ${vnnhfutures_sources}")
add_library(vnnhfutures MODULE ${vnnhfutures_sources})
target_include_directories(vnnhfutures
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnnh
    PRIVATE include
    PRIVATE vnnh/vnnhfutures )
target_link_directories(vnnhfutures PRIVATE . PRIVATE libs)
target_link_libraries(vnnhfutures nhmdapi nhtd2traderapi nhtdstockapi)
python_extension_module(vnnhfutures)


file(GLOB vnnhmd_sources 
    "vnnh/vnnhmd/vnnhmd.cpp")
message(STATUS "vnnhmd_sources ${vnnhmd_sources}")
add_library(vnnhmd MODULE ${vnnhmd_sources})
target_include_directories(vnnhmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnnh
    PRIVATE vnnh/vnnhmd )
target_link_directories(vnnhmd PRIVATE . PRIVATE libs)
target_link_libraries(vnnhmd nhmdapi nhtd2traderapi nhtdstockapi)
python_extension_module(vnnhmd)

file(GLOB vhnhstock_sources 
    "vnnh/vnnhstock/vnnhstock.cpp")
message(STATUS "vhnhstock_sources ${vhnhstock_sources}")
add_library(vnnhstock MODULE ${vhnhstock_sources})
target_include_directories(vnnhstock
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnnh
    PRIVATE vnnh/vnnhstock )
target_link_directories(vnnhstock PRIVATE . PRIVATE libs)
target_link_libraries(vnnhstock nhmdapi nhtd2traderapi nhtdstockapi nhtd2traderapi_rdma nhtd2traderapi_tcpdirect)
python_extension_module(vnnhstock)


set_target_properties(vnnhfutures vnnhmd vnnhstock
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnnhfutures vnnhmd vnnhstock LIBRARY DESTINATION vnpy/api/nh)


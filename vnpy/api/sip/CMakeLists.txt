# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_SIP C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnsipmd_sources 
    "vnsip/vnsipmd/vnsipmd.cpp")
message(STATUS "vnsipmd_sources ${vnsipmd_sources}")
add_library(vnsipmd MODULE ${vnsipmd_sources})
target_include_directories(vnsipmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsip
    PRIVATE vnsip/vnsipmd )
target_link_directories(vnsipmd PRIVATE . PRIVATE libs)
target_link_libraries(vnsipmd sipuix_x64)
python_extension_module(vnsipmd)


set_target_properties(vnsipmd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnsipmd LIBRARY DESTINATION vnpy/api/sip)


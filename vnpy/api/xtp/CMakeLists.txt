# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_XTP C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnxtpmd_sources 
    "vnxtp/vnxtpmd/vnxtpmd.cpp")
message(STATUS "vnxtpmd_sources ${vnxtpmd_sources}")
add_library(vnxtpmd MODULE ${vnxtpmd_sources})
target_include_directories(vnxtpmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnxtp
    PRIVATE vnxtp/vnxtpmd )
target_link_directories(vnxtpmd PRIVATE . PRIVATE libs)
target_link_libraries(vnxtpmd xtpquoteapi xtptraderapi)
python_extension_module(vnxtpmd)


file(GLOB vnxtptd_sources 
    "vnxtp/vnxtptd/vnxtptd.cpp")
message(STATUS "vnxtptd_sources ${vnxtptd_sources}")
add_library(vnxtptd MODULE ${vnxtptd_sources})
target_include_directories(vnxtptd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnxtp
    PRIVATE vnxtp/vnxtptd )
target_link_directories(vnxtptd PRIVATE . PRIVATE libs)
target_link_libraries(vnxtptd xtpquoteapi xtptraderapi)
python_extension_module(vnxtptd)


set_target_properties(vnxtpmd vnxtptd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnxtpmd vnxtptd LIBRARY DESTINATION vnpy/api/xtp)


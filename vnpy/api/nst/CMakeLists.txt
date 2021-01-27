# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_NST C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnnsttd_sources 
    "vnnst/vnnsttd/vnnsttd.cpp")
message(STATUS "vnnsttd_sources ${vnnsttd_sources}")
add_library(vnnsttd MODULE ${vnnsttd_sources})
target_include_directories(vnnsttd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnnst
    PRIVATE vnnst/vnnsttd )
target_link_directories(vnnsttd PRIVATE . PRIVATE libs)
target_link_libraries(vnnsttd uft4tradeapi)
python_extension_module(vnnsttd)


set_target_properties(vnnsttd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnnsttd LIBRARY DESTINATION vnpy/api/nst)


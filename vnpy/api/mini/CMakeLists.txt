# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_MINI C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnminimd_sources 
    "vnmini/vnminimd/vnminimd.cpp")
message(STATUS "vnminimd_sources ${vnminimd_sources}")
add_library(vnminimd MODULE ${vnminimd_sources})
target_include_directories(vnminimd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnmini
    PRIVATE vnmini/vnminimd )
target_link_directories(vnminimd PRIVATE . PRIVATE libs)
target_link_libraries(vnminimd thostmduserapi thosttraderapi)
python_extension_module(vnminimd)

file(GLOB vnminitd_sources 
    "vnmini/vnminitd/vnminitd.cpp")
message(STATUS "vnminitd_sources ${vnminitd_sources}")
add_library(vnminitd MODULE ${vnminitd_sources})
target_include_directories(vnminitd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnmini
    PRIVATE vnmini/vnminitd )
target_link_directories(vnminitd PRIVATE . PRIVATE libs)
target_link_libraries(vnminitd thostmduserapi thosttraderapi)
python_extension_module(vnminitd)


set_target_properties(vnminimd vnminitd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnminimd vnminitd LIBRARY DESTINATION vnpy/api/mini)


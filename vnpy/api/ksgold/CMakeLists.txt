# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_KSGOLD C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnksgoldmd_sources 
    "vnksgold/vnksgoldmd/vnksgoldmd.cpp")
message(STATUS "vnksgoldmd_sources ${vnksgoldmd_sources}")
add_library(vnksgoldmd MODULE ${vnksgoldmd_sources})
target_include_directories(vnksgoldmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnksgold
    PRIVATE vnksgold/vnksgoldmd )
target_link_directories(vnksgoldmd PRIVATE . PRIVATE libs)
target_link_libraries(vnksgoldmd ksgoldtraderapi ksgoldquotmarketdataapi)
python_extension_module(vnksgoldmd)

file(GLOB vnksgoldtd_sources 
    "vnksgold/vnksgoldtd/vnksgoldtd.cpp")
message(STATUS "vnksgoldtd_sources ${vnksgoldtd_sources}")
add_library(vnksgoldtd MODULE ${vnksgoldtd_sources})
target_include_directories(vnksgoldtd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnksgold
    PRIVATE vnksgold/vnksgoldtd )
target_link_directories(vnksgoldtd PRIVATE . PRIVATE libs)
target_link_libraries(vnksgoldtd ksgoldtraderapi ksgoldquotmarketdataapi)
python_extension_module(vnksgoldtd)


set_target_properties(vnksgoldmd vnksgoldtd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnksgoldmd vnksgoldtd LIBRARY DESTINATION vnpy/api/ksgold)


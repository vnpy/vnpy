# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_IHQ C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vhihqmd_sources 
    "vnihq/vnihqmd/vnihqmd.cpp")
message(STATUS "vhihqmd_sources ${vhihqmd_sources}")
add_library(vnihqmd MODULE ${vhihqmd_sources})
target_include_directories(vnihqmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnihq
    PRIVATE vnihq/vnihqmd )
target_link_directories(vnihqmd PRIVATE . PRIVATE libs)
target_link_libraries(vnihqmd ISMdApi)
python_extension_module(vnihqmd)


set_target_properties(vnihqmd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnihqmd LIBRARY DESTINATION vnpy/api/ihq)


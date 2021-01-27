# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_UFT C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnuftmd_sources 
    "vnuft/vnuftmd/vnuftmd.cpp")
message(STATUS "vnuftmd_sources ${vnuftmd_sources}")
add_library(vnuftmd MODULE ${vnuftmd_sources})
target_include_directories(vnuftmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnuft
    PRIVATE vnuft/vnuftmd )
target_link_directories(vnuftmd PRIVATE . PRIVATE libs)
target_link_libraries(vnuftmd HsFutuSystemInfo HSMdApi HSTradeApi t2sdk)
python_extension_module(vnuftmd)


file(GLOB vnufttd_sources 
    "vnuft/vnufttd/vnufttd.cpp")
message(STATUS "vnufttd_sources ${vnufttd_sources}")
add_library(vnufttd MODULE ${vnufttd_sources})
target_include_directories(vnufttd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnuft
    PRIVATE vnuft/vnufttd )
target_link_directories(vnufttd PRIVATE . PRIVATE libs)
target_link_libraries(vnufttd HsFutuSystemInfo HSMdApi HSTradeApi t2sdk)
python_extension_module(vnufttd)


set_target_properties(vnuftmd vnufttd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnuftmd vnufttd LIBRARY DESTINATION vnpy/api/uft)


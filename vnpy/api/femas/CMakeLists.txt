# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_FEMAS C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnfemasmd_sources 
    "vnfemas/vnfemasmd/vnfemasmd.cpp")
message(STATUS "vnfemasmd_sources ${vnfemasmd_sources}")
add_library(vnfemasmd MODULE ${vnfemasmd_sources})
target_include_directories(vnfemasmd
    PRIVATE include
    PRIVATE vnfemas
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnfemas/vnfemasmd )
target_link_directories(vnfemasmd PRIVATE . PRIVATE libs)
target_link_libraries(vnfemasmd USTPmduserapiAF USTPtraderapiAF)
python_extension_module(vnfemasmd)


file(GLOB vnfemastd_sources 
    "vnfemas/vnfemastd/vnfemastd.cpp")
message(STATUS "vnfemastd_sources ${vnfemastd_sources}")
add_library(vnfemastd MODULE ${vnfemastd_sources})
target_include_directories(vnfemastd
    PRIVATE include
    PRIVATE vnfemas
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnfemas/vnfemastd )
target_link_directories(vnfemastd PRIVATE . PRIVATE libs)
target_link_libraries(vnfemastd USTPmduserapiAF USTPtraderapiAF)
python_extension_module(vnfemastd)


set_target_properties(vnfemastd vnfemasmd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnfemastd vnfemasmd LIBRARY DESTINATION vnpy/api/femas)


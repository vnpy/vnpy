# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_HFT C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnhfttd_sources 
    "vnhft/vnhfttd/vnhfttd.cpp")
message(STATUS "vnhfttd_sources ${vnhfttd_sources}")
add_library(vnhfttd MODULE ${vnhfttd_sources})
target_include_directories(vnhfttd
    PRIVATE include
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnhft
    PRIVATE vnhft/vnhfttd )
target_link_directories(vnhfttd PRIVATE . PRIVATE libs)
target_link_libraries(vnhfttd hft_trader_api)
python_extension_module(vnhfttd)


set_target_properties(vnhfttd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnhfttd LIBRARY DESTINATION vnpy/api/hft)


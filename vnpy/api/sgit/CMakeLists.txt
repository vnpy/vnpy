# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_SGIT C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnsgitmd_sources 
    "vnsgit/vnsgitmd/vnsgitmd.cpp")
message(STATUS "vnsgitmd_sources ${vnsgitmd_sources}")
add_library(vnsgitmd MODULE ${vnsgitmd_sources})
target_include_directories(vnsgitmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsgit
    PRIVATE vnsgit/vnsgitmd )
target_link_directories(vnsgitmd PRIVATE . PRIVATE libs)
target_link_libraries(vnsgitmd crypto ssl sgitquotapi sgittradeapi)
python_extension_module(vnsgitmd)


file(GLOB vnsgittd_sources 
    "vnsgit/vnsgittd/vnsgittd.cpp")
message(STATUS "vnsgittd_sources ${vnsgittd_sources}")
add_library(vnsgittd MODULE ${vnsgittd_sources})
target_include_directories(vnsgittd
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsgit
    PRIVATE vnsgit/vnsgittd )
target_link_directories(vnsgittd PRIVATE . PRIVATE libs)
target_link_libraries(vnsgittd crypto ssl sgitquotapi sgittradeapi)
python_extension_module(vnsgittd)


set_target_properties(vnsgitmd vnsgittd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnsgitmd vnsgittd LIBRARY DESTINATION vnpy/api/sgit)


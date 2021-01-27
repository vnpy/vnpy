# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_OES C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnoesmd_sources 
    "vnoes/vnoesmd/vnoesmd.cpp")
message(STATUS "vnoesmd_sources ${vnoesmd_sources}")
add_library(vnoesmd MODULE ${vnoesmd_sources})
target_include_directories(vnoesmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE include/oes
    PRIVATE include_for_generator
    PRIVATE vnoes
    PRIVATE vnoes/vnoesmd )
target_link_directories(vnoesmd PRIVATE . PRIVATE libs)
target_link_libraries(vnoesmd oes_api)
python_extension_module(vnoesmd)


file(GLOB vnoestd_sources 
    "vnoes/vnoestd/vnoestd.cpp")
message(STATUS "vnoestd_sources ${vnoestd_sources}")
add_library(vnoestd MODULE ${vnoestd_sources})
target_include_directories(vnoestd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE include/oes
    PRIVATE include_for_generator
    PRIVATE vnoes
    PRIVATE vnoes/vnoestd )
target_link_directories(vnoestd PRIVATE . PRIVATE libs)
target_link_libraries(vnoestd oes_api)
python_extension_module(vnoestd)


set_target_properties(vnoesmd vnoestd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnoesmd vnoestd LIBRARY DESTINATION vnpy/api/oes)


# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_SOPT C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnsoptmd_sources 
    "vnsopt/vnsoptmd/vnsoptmd.cpp")
message(STATUS "vnsoptmd_sources ${vnsoptmd_sources}")
add_library(vnsoptmd MODULE ${vnsoptmd_sources})
target_include_directories(vnsoptmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsopt
    PRIVATE vnsopt/vnsoptmd )
target_link_directories(vnsoptmd PRIVATE . PRIVATE libs)
target_link_libraries(vnsoptmd soptthostmduserapi_se soptthosttraderapi_se)
python_extension_module(vnsoptmd)


file(GLOB vnsopttd_sources 
    "vnsopt/vnsopttd/vnsopttd.cpp")
message(STATUS "vnsopttd_sources ${vnsopttd_sources}")
add_library(vnsopttd MODULE ${vnsopttd_sources})
target_include_directories(vnsopttd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsopt
    PRIVATE vnsopt/vnsopttd )
target_link_directories(vnsopttd PRIVATE . PRIVATE libs)
target_link_libraries(vnsopttd soptthostmduserapi_se soptthosttraderapi_se)
python_extension_module(vnsopttd)


set_target_properties(vnsoptmd vnsopttd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnsoptmd vnsopttd LIBRARY DESTINATION vnpy/api/sopt)


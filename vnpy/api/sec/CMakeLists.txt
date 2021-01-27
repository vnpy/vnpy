# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_SEC C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnsecmd_sources 
    "vnsec/vnsecmd/vnsecmd.cpp")
message(STATUS "vnsecmd_sources ${vnsecmd_sources}")
add_library(vnsecmd MODULE ${vnsecmd_sources})
target_include_directories(vnsecmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsec
    PRIVATE vnsec/vnsecmd )
target_link_directories(vnsecmd PRIVATE . PRIVATE libs)
target_link_libraries(vnsecmd DFITCSECMdApi DFITCSECTraderApi HsFutuSystemInfo InformationCollect)
python_extension_module(vnsecmd)


file(GLOB vnsectd_sources 
    "vnsec/vnsectd/vnsectd.cpp")
message(STATUS "vnsectd_sources ${vnsectd_sources}")
add_library(vnsectd MODULE ${vnsectd_sources})
target_include_directories(vnsectd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnsec
    PRIVATE vnsec/vnsectd )
target_link_directories(vnsectd PRIVATE . PRIVATE libs)
target_link_libraries(vnsectd DFITCSECMdApi DFITCSECTraderApi HsFutuSystemInfo InformationCollect)
python_extension_module(vnsectd)


set_target_properties(vnsecmd vnsectd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnsecmd vnsectd LIBRARY DESTINATION vnpy/api/sec)


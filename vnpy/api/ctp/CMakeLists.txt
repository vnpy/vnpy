# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_CTP_PRD_6_3_15 C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnctpmd_sources 
    "vnctp/vnctpmd/vnctpmd.cpp")
message(STATUS "vnctpmd_sources ${vnctpmd_sources}")
add_library(vnctpmd MODULE ${vnctpmd_sources})
target_include_directories(vnctpmd
    PRIVATE include
    PRIVATE vnctp
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnctp/vnctpmd )
target_link_directories(vnctpmd PRIVATE . PRIVATE libs)
target_link_libraries(vnctpmd thostmduserapi_se thosttraderapi_se)
python_extension_module(vnctpmd)


file(GLOB vnctptd_sources
    "vnctp/vnctptd/vnctptd.cpp")
message(STATUS "vnctptd_sources ${vnctptd_sources}")
add_library(vnctptd MODULE ${vnctptd_sources})
target_include_directories(vnctptd
    PRIVATE include
    PRIVATE vnctp
    PRIvATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE vnctp/vnctptd )
target_link_directories(vnctptd PRIVATE . PRIVATE libs)
target_link_libraries(vnctptd thostmduserapi_se thosttraderapi_se)
python_extension_module(vnctptd)


set_target_properties(vnctptd vnctpmd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnctptd vnctpmd LIBRARY DESTINATION vnpy/api/ctp)


# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_XGJ C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnxgjmd_sources 
    "vnxgj/vnxgjmd/vnxgjmd.cpp")
message(STATUS "vnxgjmd_sources ${vnxgjmd_sources}")
add_library(vnxgjmd MODULE ${vnxgjmd_sources})
target_include_directories(vnxgjmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnxgj
    PRIVATE vnxgj/vnxgjmd )
target_link_directories(vnxgjmd PRIVATE . PRIVATE libs)
target_link_libraries(vnxgjmd thostmduserapi_se thosttraderapi_se)
python_extension_module(vnxgjmd)


file(GLOB vnxgjtd_sources 
    "vnxgj/vnxgjtd/vnxgjtd.cpp")
message(STATUS "vnxgjtd_sources ${vnxgjtd_sources}")
add_library(vnxgjtd MODULE ${vnxgjtd_sources})
target_include_directories(vnxgjtd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vnxgj
    PRIVATE vnxgj/vnxgjtd )
target_link_directories(vnxgjtd PRIVATE . PRIVATE libs)
target_link_libraries(vnxgjtd thostmduserapi_se thosttraderapi_se)
python_extension_module(vnxgjtd)


set_target_properties(vnxgjmd vnxgjtd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnxgjmd vnxgjtd LIBRARY DESTINATION vnpy/api/xgj)


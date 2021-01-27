# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_TAP C CXX)

find_package(PythonExtensions REQUIRED)

message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vntapmd_sources 
    "vntap/vntapmd/vntapmd.cpp")
message(STATUS "vntapmd_sources ${vntapmd_sources}")
add_library(vntapmd MODULE ${vntapmd_sources})
target_include_directories(vntapmd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vntap
    PRIVATE vntap/vntapmd )
target_link_directories(vntapmd PRIVATE . PRIVATE libs)
target_link_libraries(vntapmd iTapTradeAPI_64 TapQuoteAPI)
python_extension_module(vntapmd)


file(GLOB vntaptd_sources 
    "vntap/vntaptd/vntaptd.cpp")
message(STATUS "vntaptd_sources ${vntaptd_sources}")
add_library(vntaptd MODULE ${vntaptd_sources})
target_include_directories(vntaptd
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE include
    PRIVATE vntap
    PRIVATE vntap/vntaptd )
target_link_directories(vntaptd PRIVATE . PRIVATE libs)
target_link_libraries(vntaptd iTapTradeAPI_64 TapQuoteAPI)
python_extension_module(vntaptd)


set_target_properties(vntapmd vntaptd
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vntapmd vntaptd LIBRARY DESTINATION vnpy/api/tap)


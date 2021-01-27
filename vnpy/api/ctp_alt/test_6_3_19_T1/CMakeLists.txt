# 指定 cmake 最低编译版本
CMAKE_MINIMUM_REQUIRED(VERSION 3.14)

PROJECT (VNPY_CTP_TEST_6_3_19_T1 C CXX)

find_package(PythonExtensions REQUIRED)

if(WIN32)
    set(build_platform "windows-amd64")
else()
    set(build_platform "linux-amd64")
endif()


message(STATUS "CMAKE_SOURCE_DIR ${CMAKE_SOURCE_DIR}")
message(STATUS "PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message(STATUS "PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message(STATUS "CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message(STATUS "CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message(STATUS "CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message(STATUS "CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX}")

file(GLOB vnctpmd_sources 
    "src/${build_platform}/vnctpmd/*.cpp")
message(STATUS "vnctpmd_sources ${vnctpmd_sources}")
add_library(vnctpmd_test_6_3_19_T1 MODULE ${vnctpmd_sources})
target_include_directories(vnctpmd_test_6_3_19_T1 
    PRIVATE include/${build_platform}
    PRIVATE src/${build_platform}
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE src/${build_platform}/vnctpmd )
target_link_directories(vnctpmd_test_6_3_19_T1 PRIVATE .)
target_link_libraries(vnctpmd_test_6_3_19_T1 thostmduserapi_se thosttraderapi_se)
python_extension_module(vnctpmd_test_6_3_19_T1)


file(GLOB vnctptd_sources
    "src/${build_platform}/vnctptd/*.cpp")
message(STATUS "vnctptd_sources ${vnctptd_sources}")
add_library(vnctptd_test_6_3_19_T1 MODULE ${vnctptd_sources})
target_include_directories(vnctptd_test_6_3_19_T1 
    PRIVATE include/${build_platform}
    PRIVATE src/${build_platform}
    PRIVATE ${CMAKE_SOURCE_DIR}/external/include
    PRIVATE src/${build_platform}/vnctptd )
target_link_directories(vnctptd_test_6_3_19_T1 PRIVATE .)
target_link_libraries(vnctptd_test_6_3_19_T1 thostmduserapi_se thosttraderapi_se)
python_extension_module(vnctptd_test_6_3_19_T1)


set_target_properties(vnctptd_test_6_3_19_T1 vnctpmd_test_6_3_19_T1
    PROPERTIES INSTALL_RPATH $ORIGIN
)

install(TARGETS vnctptd_test_6_3_19_T1 vnctpmd_test_6_3_19_T1 LIBRARY DESTINATION vnpy/api/ctp_alt/test_6_3_19_T1)


cmake_minimum_required(VERSION 2.8)
project(vn_lts_api)

set(CMAKE_BUILD_TYPE "Release")
if (CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
endif ()

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

option(USE_64BITS "comiple 64bits" ON)
if (USE_64BITS)
  add_definitions(-DUSE_64BITS)
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

if (WIN32)
    set(LTSAPI_PATH ltsapi)
elseif (UNIX)
    message("Under unix: " ${CMAKE_SIZEOF_VOID_P})
    #if (CMAKE_SIZEOF_VOID_P MATCHES "8")
    set(LTSAPI_PATH ltsapi)
    #endif()
endif()
include_directories(${LTSAPI_PATH})
message(${LTSAPI_PATH})
set(LTSAPI_LIBRARY )
find_library(LTSAPI_MD_LIBRARY
  NAMES securitymduserapi
  PATHS ${LTSAPI_PATH}) 
message(${LTSAPI_MD_LIBRARY})
find_library(LTSAPI_TD_LIBRARY
  NAMES securitytraderapi
  PATHS ${LTSAPI_PATH})
find_library(LTSAPI_QRY_LIBRARY
  NAMES securityqueryapi
  PATHS ${LTSAPI_PATH})

set (vnltsmd )
set (vnltstd )
set (vnltsqry )
  
option(BUILD_LTS_MD "build lts md" ON)
if (BUILD_LTS_MD)
  add_definitions(-DBUILD_LTS_MD)
  set(LTS_MD_PATH vnltsmd/vnltsmd)
  include_directories(LTS_MD_PATH)
  set(VN_LTS_MD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnltsmd/vnltsmd/vnltsmd.cpp)
  add_library(vnltsmd SHARED ${VN_LTS_MD_SOURCE})
endif()
option(BUILD_LTS_TD "build lts td" ON)
if (BUILD_LTS_TD)
  add_definitions(-DBUILD_LTS_TD)
  set(LTS_TD_PATH vnltstd/vnltstd)
  include_directories(LTS_TD_PATH)
  set(VN_LTS_TD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnltstd/vnltstd/vnltstd.cpp)
  add_library(vnltstd SHARED ${VN_LTS_TD_SOURCE})  
endif()
option(BUILD_LTS_QRY "build lts qry" ON)
if (BUILD_LTS_QRY)
  add_definitions(-DBUILD_LTS_QRY)
  set(LTS_QRY_PATH vnltsqry/vnltsqry)
  include_directories(LTS_QRY_PATH)
  set(VN_LTS_QRY_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnltsqry/vnltsqry/vnltsqry.cpp)
  add_library(vnltsqry SHARED ${VN_LTS_QRY_SOURCE})  
endif()

set(PYTHON_LIBRARY )
if (WIN32)
set(PYTHON_INCLUDE_PATH C:/Python27/include)
find_library(PYTHON_LIBRARY
  NAMES python27
  PATHS C:/Python27/libs)
include_directories(${PYTHON_INCLUDE_PATH})
else()
set(PYTHON_INCLUDE_PATH /usr/include/python2.7/)
find_library(PYTHON_LIBRARY
  NAMES python2.7
  PATHS /usr/lib/x86_64-linux-gnu)
include_directories(${PYTHON_INCLUDE_PATH})
endif()

# 链接boost库，anaconda
if (WIN32)
    set(Boost_USE_STATIC_LIBS        ON)    #链接boost静态库
endif()
set(Boost_USE_MULTITHREADED      ON)
find_package(Boost 1.55.0 COMPONENTS python thread date_time system chrono REQUIRED) # 如果boost库没有完全编译，需要将编译的库明确地指出，否者message(${Boost_LIBRARIES})会出错
if(Boost_FOUND)
  include_directories(${Boost_INCLUDE_DIRS})
endif()

# 去掉生成的so文件名中前缀的lib
set_target_properties(vnltsmd PROPERTIES PREFIX "")
target_link_libraries(vnltsmd  ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${LTSAPI_MD_LIBRARY})
set(MD_DLL "${LIBRARY_OUTPUT_PATH}/Release/vnltsmd.dll")
if (EXISTS ${MD_DLL})
  file(RENAME ${MD_DLL} ${LIBRARY_OUTPUT_PATH}/Release/vnltsmd.pyd)
endif()
set_target_properties(vnltstd PROPERTIES PREFIX "")
target_link_libraries(vnltstd  ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${LTSAPI_TD_LIBRARY})
set(TD_DLL ${LIBRARY_OUTPUT_PATH}/Release/vnltstd.dll)
if (EXISTS ${TD_DLL})
  file(RENAME  ${TD_DLL} ${LIBRARY_OUTPUT_PATH}/Release/vnltstd.pyd)
endif()
set_target_properties(vnltsqry PROPERTIES PREFIX "")
target_link_libraries(vnltsqry  ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${LTSAPI_QRY_LIBRARY})
set(QRY_DLL ${LIBRARY_OUTPUT_PATH}/Release/vnltsqry.dll)
if (EXISTS ${QRY_DLL})
  file(RENAME  ${QRY_DLL} ${LIBRARY_OUTPUT_PATH}/Release/vnltsqry.pyd)
endif()

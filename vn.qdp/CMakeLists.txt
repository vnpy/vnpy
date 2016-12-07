cmake_minimum_required(VERSION 2.8)
project(vn_qdp_api)

# 设置使用的编译器
set(CMAKE_BUILD_TYPE "Release")
if (CMAKE_COMPILER_IS_GNUC OR CMAKE_COMPILER_IS_GNUCXX) 
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -std=c++11")
endif ()

# 设置输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# 使用64位编译
option(USE_64BITS "comiple 64bits" ON)
if (USE_64BITS)
  add_definitions(-DUSE_64BITS)
  #set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m32")
  #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m32")
endif()

# 设置C++ API源文件的所在目录
if (WIN32)
    set(QDPAPI_PATH qdpapi)
elseif (UNIX)
    message("Under unix: " ${CMAKE_SIZEOF_VOID_P})
    if (CMAKE_SIZEOF_VOID_P MATCHES "8")
        set(QDPAPI_PATH qdpapi/x64_linux)
    endif()
endif()
include_directories(${QDPAPI_PATH})
set(QDPAPI_LIBRARY )
find_library(QDPAPI_MD_LIBRARY
  NAMES qdpmdapi
  PATHS ${QDPAPI_PATH}) 
find_library(QDPAPI_TD_LIBRARY
  NAMES qdptraderapi
  PATHS ${QDPAPI_PATH})


# 设置编译源文件
set (vnqdpmd )
set (vnqdptd )

option(BUILD_QDP_MD "build qdp md" ON)
if (BUILD_QDP_MD)
  add_definitions(-DBUILD_QDP_MD)
  set(QDP_MD_PATH vnqdpmd/vnqdpmd)
  include_directories(QDP_MD_PATH)
  set(VN_QDP_MD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnqdpmd/vnqdpmd/vnqdpmd.cpp)
  add_library(vnqdpmd SHARED ${VN_QDP_MD_SOURCE})
endif()
option(BUILD_QDP_TD "build qdp td" ON)
if (BUILD_QDP_TD)
  add_definitions(-DBUILD_QDP_TD)
  set(QDP_TD_PATH vnqdptd/vnqdptd)
  include_directories(QDP_TD_PATH)
  set(VN_QDP_TD_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnqdptd/vnqdptd/vnqdptd.cpp)
  add_library(vnqdptd SHARED ${VN_QDP_TD_SOURCE})  
endif()

# 设置Python所在的目录
set(PYTHON_LIBRARY )
if (WIN32)
set(PYTHON_INCLUDE_PATH D:/Anaconda2/include)
find_library(PYTHON_LIBRARY
  NAMES python27
  PATHS D:/Anaconda2/libs)
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
set_target_properties(vnqdpmd PROPERTIES PREFIX "")

# 链接生成.so文件
target_link_libraries(vnqdpmd  ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${QDPAPI_MD_LIBRARY})

# 将生成的dll文件后缀名修改为pyd（仅在windows下）
set(MD_DLL "${LIBRARY_OUTPUT_PATH}/Release/vnqdpmd.dll")
if (EXISTS ${MD_DLL})
  file(RENAME ${MD_DLL} ${LIBRARY_OUTPUT_PATH}/Release/vnqdpmd.pyd)
endif()

# 和上面的MD相同
set_target_properties(vnqdptd PROPERTIES PREFIX "")
target_link_libraries(vnqdptd  ${Boost_LIBRARIES} ${PYTHON_LIBRARY} ${QDPAPI_TD_LIBRARY})
set(TD_DLL ${LIBRARY_OUTPUT_PATH}/Release/vnqdptd.dll)
if (EXISTS ${TD_DLL})
  file(RENAME  ${TD_DLL} ${LIBRARY_OUTPUT_PATH}/Release/vnqdptd.pyd)
endif()

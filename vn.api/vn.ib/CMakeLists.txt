cmake_minimum_required(VERSION 2.8)
project(vn_ib_api CXX)

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
endif()

# 设置C++ API源文件的所在目录
set(IBAPI_PATH ./ibapi/linux)
include_directories(${IBAPI_PATH}/client)

set(IBAPI_LIBRARY )
find_library(IBAPI_LIBRARY
  NAMES twsapi.so
  PATHS ${IBAPI_PATH}/build/lib) 

# 设置编译源文件
set (vnib )

option(BUILD_IB "build ib" ON)
if (BUILD_IB)
  add_definitions(-DBUILD_IB)
  set(IB_PATH ./vnib/vnib)
  include_directories(IB_PATH)
  set(VN_IB_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/vnib/vnib/vnib.cpp)
  add_library(vnib SHARED ${VN_IB_SOURCE})
endif()

# 设置Python所在的目录
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
set_target_properties(vnib PROPERTIES PREFIX "")
set_target_properties(vnib PROPERTIES LINKER_LANGUAGE CXX)

# 链接生成.so文件
target_link_libraries(vnib ${IBAPI_LIBRARY} ${Boost_LIBRARIES} ${PYTHON_LIBRARY})



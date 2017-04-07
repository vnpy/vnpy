cmake_minimum_required(VERSION 2.8)
project(tws_api CXX)

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

# 设置编译源文件
set (twsapi )

add_definitions(-DBUILD_IB)
set(IB_PATH ./client)
include_directories(IB_PATH)

aux_source_directory(./client IB_SOURCE)
add_library(twsapi SHARED ${IB_SOURCE})

# 去掉生成的so文件名中前缀的lib
set_target_properties(twsapi PROPERTIES PREFIX "")

# 设置链接时用的语言是C++
set_target_properties(twsapi PROPERTIES LINKER_LANGUAGE CXX)



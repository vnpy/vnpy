cmake_minimum_required(VERSION 3.20)

project(vnpy_cpp_matching_engine_demo LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(MATCHING_ENGINE_ENABLE_SANITIZERS "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

add_library(matching_engine
    src/matching_engine.cpp
)

target_include_directories(matching_engine
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(MSVC)
    target_compile_options(matching_engine PRIVATE /W4 /permissive-)
else()
    target_compile_options(matching_engine PRIVATE -Wall -Wextra -Wpedantic -Wshadow)

    if(MATCHING_ENGINE_ENABLE_SANITIZERS)
        target_compile_options(matching_engine PUBLIC -fsanitize=address,undefined -fno-omit-frame-pointer)
        target_link_options(matching_engine PUBLIC -fsanitize=address,undefined)
    endif()
endif()

add_executable(matching_engine_demo
    src/main.cpp
)
target_link_libraries(matching_engine_demo PRIVATE matching_engine)

add_executable(matching_engine_tests
    tests/test_matching_engine.cpp
)
target_link_libraries(matching_engine_tests PRIVATE matching_engine)

add_executable(matching_engine_bench
    benchmarks/benchmark.cpp
)
target_link_libraries(matching_engine_bench PRIVATE matching_engine)

enable_testing()
add_test(NAME matching_engine_tests COMMAND matching_engine_tests)

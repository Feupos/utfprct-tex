cmake_minimum_required(VERSION 3.14)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG master
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
    FetchContent_Populate(googletest)
    FetchContent_MakeAvailable(googletest)
    add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

################################
# GBenchmark
################################
set(BENCHMARK_ENABLE_TESTING OFF)

include(FetchContent)
FetchContent_Declare(googlebenchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG master
)

FetchContent_GetProperties(googlebenchmark)
if(NOT googleLIBNOP_BENCHMARK_POPULATED)
    FetchContent_Populate(googlebenchmark)
    FetchContent_MakeAvailable(googlebenchmark)
    add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
endif()

################################
# Framework PON C++ 2.0
################################
if(LIBNOP_FW2_TEST_ENABLE)
    include(FetchContent)
    FetchContent_Declare(libnop_fw2
        GIT_REPOSITORY http://200.134.10.221/NOP-Server/NOP-Frameworks/Cpp-Framework-2_0.git
        GIT_TAG cmake
    )

    FetchContent_GetProperties(libnop_fw2)
    if(NOT libnop_fw2_POPULATED)
        FetchContent_Populate(libnop_fw2)
        FetchContent_MakeAvailable(libnop_fw2)
        add_subdirectory(${libnop_fw2_SOURCE_DIR} ${libnop_fw2_BINARY_DIR})
    endif()
endif()

################################
# Benchmark Tests
################################
file(GLOB LIBNOP_GTEST_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB LIBNOP_GTEST_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

if(LIBNOP_BENCHMARK_SENSOR_ENABLE)
    add_compile_definitions(LIBNOP_BENCHMARK_SENSOR_ENABLE)
endif()

if(LIBNOP_BENCHMARK_BITONIC_ENABLE)
    add_compile_definitions(LIBNOP_BENCHMARK_BITONIC_ENABLE)
endif()

if(LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE)
    add_compile_definitions(LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE)
endif()

add_executable(libnop_gbench ${LIBNOP_GTEST_SOURCE} ${LIBNOP_GTEST_HEADERS})

set_target_properties(libnop_gbench PROPERTIES
    CXX_STANDARD 20
)

target_include_directories(libnop_gbench
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(LIBNOP_FW2_TEST_ENABLE)
    add_compile_definitions(LIBNOP_FW2_TEST_ENABLE)
    target_link_libraries(libnop_gbench gtest_main benchmark::benchmark ${LIBNAME} libnop_fw2)
else()
    target_link_libraries(libnop_gbench gtest_main benchmark::benchmark ${LIBNAME})
endif()

add_test(NAME libnop_gbench
        COMMAND libnop_gbench)

if (MSVC AND LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE)
    target_compile_options(libnop_gbench PRIVATE /bigobj)
endif()
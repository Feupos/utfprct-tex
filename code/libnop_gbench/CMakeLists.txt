cmake_minimum_required(VERSION 3.14)

################################
# GTest
################################
include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG master
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

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
if(NOT googlebenchmark_POPULATED)
	FetchContent_Populate(googlebenchmark)
	FetchContent_MakeAvailable(googlebenchmark)
	add_subdirectory(${googlebenchmark_SOURCE_DIR} ${googlebenchmark_BINARY_DIR})
endif()

################################
# Unit Tests
################################
add_executable(libnop_gbench test.cpp test.h)

set_target_properties(libnop_gbench PROPERTIES
	CXX_STANDARD 17
)

target_link_libraries(libnop_gbench gtest_main benchmark::benchmark libnop)

add_test(NAME libnop_gbench
		COMMAND libnop_gbench)
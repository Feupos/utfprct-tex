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
# Unit Tests
################################
add_executable(libnop_gtest test.cpp)

set_target_properties(libnop_gtest PROPERTIES
	CXX_STANDARD 20
)

if (LIBNOP_SCHEDULER_ENABLE)
    add_compile_definitions(LIBNOP_SCHEDULER_ENABLE)
endif()

if(LIBNOP_LOG_ENABLE)
    add_compile_definitions(LIBNOP_LOG_ENABLE)
endif()

if(LIBNOP_COVERAGE_ENABLE)
    target_compile_options(libnop_gtest PRIVATE -O0 -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors --coverage)
    target_link_options(libnop_gtest PRIVATE --coverage)
endif()

target_link_libraries(libnop_gtest gtest_main ${LIBNAME})

add_test(NAME libnop_gtest
		COMMAND libnop_gtest)
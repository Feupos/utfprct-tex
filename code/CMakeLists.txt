cmake_minimum_required(VERSION 3.14)

project(libnop VERSION 4.0.0 DESCRIPTION "NOP C++ Framework")

option(LIBNOP_TEST_ENABLE "Build libnop tests" ON)

file(GLOB LIBNOP_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB LIBNOP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h
)

set(LIBNOP_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_library(libnop STATIC ${LIBNOP_SOURCE} ${LIBNOP_HEADERS})

set_target_properties(libnop PROPERTIES
    VERSION ${PROJECT_VERSION}
    PUBLIC_HEADER ${LIBNOP_HEADERS}
	CXX_STANDARD 17
)

target_include_directories(libnop PUBLIC ${LIBNOP_INCLUDE_DIRS})

install(TARGETS libnop
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(LIBNOP_TEST_ENABLE)
    add_subdirectory(libnop_gtest)
    add_subdirectory(libnop_gbench)
endif()

export(TARGETS libnop FILE ${CMAKE_CURRENT_BINARY_DIR}/libnop.cmake)

export(PACKAGE libnop)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/libnop.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/libnop.cmake @ONLY
)

cmake_minimum_required(VERSION 3.14)

# ---------------------------------------------------------------------------------------
# Set default build to release
# ---------------------------------------------------------------------------------------
if (NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "" FORCE)
endif()

set(LIBNAME libnop)

project(${LIBNAME} VERSION 4.0.0 DESCRIPTION "NOP C++ Framework")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 10.0)
        message(FATAL_ERROR "GCC version must be at least 10.0!")
    endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "14.2")
        message(FATAL_ERROR "MSVC version must be at least 14.2!")
    endif()
else()
    message(WARNING "You are using an untested compiler ${CMAKE_CXX_COMPILER_ID}! Compilation has only been tested with GCC and MSVC.")
endif()

option(LIBNOP_SCHEDULER_ENABLE "Enable use of schedluer for executing Rules (reduces performance)" OFF)
option(LIBNOP_TEST_ENABLE "Enable building unity tests" OFF)
option(LIBNOP_COVERAGE_ENABLE "Enable code coverage" OFF)
option(LIBNOP_BENCHMARK_ENABLE "Enable build benchmarks" OFF)
option(LIBNOP_BENCHMARK_SENSOR_ENABLE "Enable build sensor benchmark" OFF)
option(LIBNOP_BENCHMARK_BITONIC_ENABLE "Enable build bitonic benchmark" OFF)
option(LIBNOP_BENCHMARK_RANDOMFOREST_ENABLE "Enable build random forest benchmark" OFF)
option(LIBNOP_FW2_TEST_ENABLE "Enable build Fw. C++ 2.0 tests" OFF)
option(LIBNOP_LOG_ENABLE "Enable using logs (heavy performance hit)" OFF)

if(LIBNOP_LOG_ENABLE)
    add_compile_definitions(LIBNOP_LOG_ENABLE)
    include(FetchContent)
    FetchContent_Declare(
            spdlog
            GIT_REPOSITORY https://github.com/gabime/spdlog.git
            GIT_TAG        v1.x
    )

    set(SPDLOG_INSTALL ON CACHE BOOL "" FORCE)
    set(SPDLOG_BUILD_TESTS OFF CACHE BOOL "" FORCE)

    FetchContent_GetProperties(spdlog)
    if (NOT spdlog_POPULATED)
        FetchContent_Populate(spdlog)
        FetchContent_MakeAvailable(spdlog)
        add_subdirectory(${spdlog_SOURCE_DIR} ${spdlog_BINARY_DIR})
    endif()
endif()

if(LIBNOP_TEST_ENABLE)
    add_subdirectory(libnop_gtest)
endif()

if(LIBNOP_BENCHMARK_ENABLE)
    add_subdirectory(libnop_gbench)
endif()



file(GLOB LIBNOP_SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

file(GLOB LIBNOP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/NOPFramework.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/*/*.h
)

add_library(${LIBNAME} STATIC ${LIBNOP_SOURCE} ${LIBNOP_HEADERS})

set_target_properties(${LIBNAME} PROPERTIES
    CXX_STANDARD 20
    PREFIX ""
)

if (LIBNOP_SCHEDULER_ENABLE)
    add_compile_definitions(LIBNOP_SCHEDULER_ENABLE)
endif()

if (MSVC)
    # warning level 4 and all warnings as errors
    target_compile_options(${LIBNAME} PRIVATE /W4 /WX)
else()
    # lots of warnings and all warnings as errors
    target_compile_options(${LIBNAME} PRIVATE -Wall -Wextra -pedantic -Werror)
endif()

target_include_directories(${LIBNAME} PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/>"
                                             "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(LIBNOP_LOG_ENABLE)
    target_link_libraries(${LIBNAME} spdlog::spdlog)
endif()

if(LIBNOP_COVERAGE_ENABLE)
    target_compile_options(${LIBNAME} PRIVATE -O0 -fno-inline -fno-inline-small-functions -fno-default-inline -fno-elide-constructors --coverage)
    target_link_options(${LIBNAME} PRIVATE --coverage)
endif()

if (UNIX)
    include(GNUInstallDirs)
endif (UNIX)

install(TARGETS ${LIBNAME}
    EXPORT ${LIBNAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIBNAME}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/${LIBNAME}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}")

set(project_config_in "${CMAKE_CURRENT_LIST_DIR}/${LIBNAME}Config.cmake.in")
set(project_config_out "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}Config.cmake")
set(config_targets_file "${LIBNAME}Targets.cmake")
set(version_config_file "${CMAKE_CURRENT_BINARY_DIR}/${LIBNAME}ConfigVersion.cmake")
set(export_dest_dir "${CMAKE_INSTALL_LIBDIR}/cmake/${LIBNAME}")
set(pkgconfig_install_dir "${CMAKE_INSTALL_LIBDIR}/pkgconfig")
set(pkg_config "${CMAKE_BINARY_DIR}/${LIBNAME}.pc")

# ---------------------------------------------------------------------------------------
# Install pkg-config file
# ---------------------------------------------------------------------------------------
get_target_property(PKG_CONFIG_DEFINES ${LIBNAME} INTERFACE_COMPILE_DEFINITIONS)
string(REPLACE ";" " -D" PKG_CONFIG_DEFINES "${PKG_CONFIG_DEFINES}")
string(CONCAT PKG_CONFIG_DEFINES "-D" "${PKG_CONFIG_DEFINES}")
configure_file("${CMAKE_CURRENT_LIST_DIR}/${LIBNAME}.pc.in" "${pkg_config}" @ONLY)
install(FILES "${pkg_config}" DESTINATION "${pkgconfig_install_dir}")

# ---------------------------------------------------------------------------------------
# Install CMake config files
# ---------------------------------------------------------------------------------------
install(EXPORT ${LIBNAME} DESTINATION ${export_dest_dir} FILE ${config_targets_file})
export(PACKAGE ${LIBNAME})

include(CMakePackageConfigHelpers)
configure_file("${project_config_in}" "${project_config_out}" @ONLY)

#write_basic_package_version_file("${version_config_file}" COMPATIBILITY SameMajorVersion)
install(FILES "${project_config_out}" DESTINATION "${export_dest_dir}")

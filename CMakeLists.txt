cmake_minimum_required(VERSION 3.10)

project(quant LANGUAGES CXX)

# General project settings (artifact locations, naming, C++ standard).
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_STATIC_LIBRARY_PREFIX "lib_${CMAKE_PROJECT_NAME}_")
set(CMAKE_SHARED_LIBRARY_PREFIX "lib_${CMAKE_PROJECT_NAME}_")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source")

# Export compile commands for Clang.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    list(APPEND CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}")
endif()

# Dependencies.
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(doctest QUIET)

# Source code.
add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(examples)

export(
    TARGETS
        geometry
        units
        framed_geometry
        framed_units
    NAMESPACE
        quant::
    FILE
        "${PROJECT_BINARY_DIR}/quantTargets.cmake"
)

install(
    TARGETS
        geometry
        units
        framed_geometry
        framed_units
    EXPORT
        quant_export_set
    DESTINATION
        lib
)

export(
    EXPORT
        quant_export_set
    NAMESPACE
        quant::
    FILE
        "${PROJECT_BINARY_DIR}/quantConfig-autogen.cmake"
)

configure_file(
    "${CMAKE_SOURCE_DIR}/cmake/quantConfig.template.cmake"
    "${PROJECT_BINARY_DIR}/quantConfig.cmake"
    @ONLY
)

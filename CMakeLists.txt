cmake_minimum_required(VERSION 3.15)

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
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    list(PREPEND CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}")
endif()

# Dependencies.
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(doctest QUIET)

find_package(Python QUIET COMPONENTS Interpreter Development.Module)
find_package(pybind11 CONFIG QUIET)

option(QUANT_ALLOW_DIFFERENCE_ADDITION "Allow the addition and subtraction of difference" ON)
if (QUANT_ALLOW_DIFFERENCE_ADDITION)
    message(WARNING "Difference addition is enabled. This may lead to unexpected results.")
    add_compile_definitions(QUANT_ALLOW_DIFFERENCE_ADDITION)
endif ()

# Source code.
add_subdirectory(source)
add_subdirectory(tests/quant)
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

if (pybind11_FOUND AND Python_FOUND)
    # The install directory is the output (wheel) directory
    install(TARGETS quantpy
            DESTINATION quantpy)
endif (pybind11_FOUND AND Python_FOUND)
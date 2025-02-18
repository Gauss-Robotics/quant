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
if(CMAKE_EXPORT_COMPILE_COMMANDS)
    list(PREPEND CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES "${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES}")
endif()

# Dependencies.
find_package(Eigen3 REQUIRED)
find_package(Boost REQUIRED)
find_package(doctest QUIET)

# Compile Options
option(QUANT_ENABLE_DIFFERENCE_ADDITION "Allow addition and subtraction of difference types" ON)
if (QUANT_ENABLE_DIFFERENCE_ADDITION)
    message(WARNING "Difference addition is enabled. This may lead to unexpected results.")
    add_compile_definitions(QUANT_ENABLE_DIFFERENCE_ADDITION)
endif()

option(QUANT_ENABLE_EXCEPTIONS "Allow throwing of exceptions" ON)
if (QUANT_ENABLE_EXCEPTIONS)
    add_compile_definitions(QUANT_ENABLE_EXCEPTIONS)
endif()
option(QUANT_ENABLE_TESTS "Enable tests" ON)


# Source code.
add_subdirectory(source)
add_subdirectory(examples)

if (QUANT_ENABLE_TESTS)
    if (doctest_FOUND)
        add_subdirectory(tests)
    else()
        message(WARNING "Tests are enabled but doctest is not found. Tests will not be built.")
    endif()
endif()


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

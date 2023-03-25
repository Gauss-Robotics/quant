cmake_minimum_required(VERSION 3.10)

project(quant LANGUAGES CXX)

find_package(Eigen3 REQUIRED)
find_package(doctest REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib")

add_subdirectory(source)
add_subdirectory(tests)
add_subdirectory(examples)

export(
    TARGETS
        geometry
        units
        #framed_geometry
        #framed_units
    NAMESPACE
        quant::
    FILE
        "${PROJECT_BINARY_DIR}/quantTargets.cmake"
)

install(
    TARGETS
        geometry
        units
        #framed_geometry
        #framed_units
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
        "${PROJECT_BINARY_DIR}/quantConfig.cmake"
)

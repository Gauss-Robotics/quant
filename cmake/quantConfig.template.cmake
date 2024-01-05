cmake_minimum_required(VERSION 3.10)

# Add custom Find*.cmake files to CMAKE_MODULE_PATH.
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "@CMAKE_SOURCE_DIR@/cmake/find_scripts/")

# Perform a find_package for dependencies of quant.
find_package(Eigen3 REQUIRED)

# Include auto-generated cmake Config file.
include("@PROJECT_BINARY_DIR@/quantConfig-autogen.cmake")

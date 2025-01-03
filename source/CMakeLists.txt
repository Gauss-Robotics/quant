add_subdirectory(quant)

if (pybind11_FOUND AND Python_FOUND)
    add_subdirectory(quantpy)
endif (pybind11_FOUND AND Python_FOUND)
add_executable(simple_robot_example
    SimpleRobot.h
    main.cpp
)

set_target_properties(simple_robot_example
    PROPERTIES
        CXX_STANDARD 17
)

target_link_libraries(simple_robot_example
    PRIVATE
        quant::framed_units
)

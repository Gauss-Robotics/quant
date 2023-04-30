add_executable(simple_robot_example
    SimpleRobot.h
    main.cpp
)

target_link_libraries(simple_robot_example
    PUBLIC
        quant::framed_units
)

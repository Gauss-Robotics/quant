add_library(units SHARED
    ../units.h

    time.h
    time_minimal.h
    time/forward_declarations.h
    time/TimePoint.h
    time/TimePoint.cpp
    time/Duration.h
    time/Duration.cpp
    time/TimeInterval.h
    time/Frequency.h
    time/detail/UnitConversions.h

    position.h
    position_minimal.h
    position/forward_declarations.h
    position/Position.h
    position/Position.cpp
    position/Orientation.h
    position/Orientation.cpp
    position/Pose.h
    position/Pose.cpp
    position/Displacement.h

    velocity.h
    #velocity_minimal.h
    #velocity/forward_declarations.h
    velocity/LinearVelocity.h
    velocity/LinearVelocity.cpp
    velocity/AngularVelocity.h
    velocity/AngularVelocity.cpp
    velocity/Twist.h
    velocity/Twist.cpp

    acceleration.h
    #acceleration_minimal.h
    #acceleration/forward_declarations.h
    acceleration/LinearAcceleration.h
    acceleration/LinearAcceleration.cpp
    acceleration/AngularAcceleration.h
    acceleration/AngularAcceleration.cpp

    jerk.h
    jerk/LinearJerk.h
    jerk/LinearJerk.cpp
    jerk/AngularJerk.h
    jerk/AngularJerk.cpp

    distance.h
    distance/Distance.h

    speed.h
    speed/Speed.h

    mass.h
    mass/Mass.h

    force.h
    #force_minimal.h
    #force/forward_declarations.h
    force/Force.h
    force/Force.cpp
    force/Torque.h
    force/Torque.cpp
    force/Wrench.h
    force/Wrench.cpp
)

set_target_properties(units
    PROPERTIES
        LINKER_LANGUAGE CXX
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(units
    PRIVATE
        Eigen3::Eigen
        geometry
)

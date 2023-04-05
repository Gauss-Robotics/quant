add_library(units SHARED
    ../units.h
    Scalar.h
    Vector.h

    time.h
    time_fwd.h
    time_constants.h
    time/TimePoint.h
    time/TimePoint.cpp
    time/Duration.h
    time/Duration.cpp
    time/TimeInterval.h
    time/Frequency.h

    position.h
    position_fwd.h
    position_constants.h
    position/Position.h
    position/Position.cpp
    position/Orientation.h
    position/Pose.h
    position/Pose.cpp
    position/LinearDisplacement.h
    position/AngularDisplacement.h
    position/SpatialDisplacement.h

    velocity.h
    velocity_fwd.h
    velocity_constants.h
    velocity/LinearVelocity.h
    velocity/LinearVelocity.cpp
    velocity/AngularVelocity.h
    velocity/AngularVelocity.cpp
    velocity/Twist.h
    velocity/Twist.cpp
    velocity/LinearVelocityDifference.h
    velocity/AngularVelocityDifference.h

    acceleration.h
    acceleration_fwd.h
    acceleration_constants.h
    acceleration/LinearAcceleration.h
    acceleration/LinearAcceleration.cpp
    acceleration/AngularAcceleration.h
    acceleration/AngularAcceleration.cpp

    jerk.h
    jerk_fwd.h
    jerk_constants.h
    jerk/LinearJerk.h
    jerk/LinearJerk.cpp
    jerk/AngularJerk.h
    jerk/AngularJerk.cpp

    distance.h
    distance_fwd.h
    distance/Distance.h

    speed.h
    speed_fwd.h
    speed/Speed.h
    speed/Speed.cpp

    mass.h
    mass_fwd.h
    mass_constants.h
    mass/Mass.h

    force.h
    force_fwd.h
    force_constants.h
    force/Force.h
    force/Force.cpp
    force/Torque.h
    force/Torque.cpp
    force/Wrench.h
    force/Wrench.cpp
    force/ForceDifference.h
    force/TorqueDifference.h

    temperature.h
    temperature_fwd.h
    temperature/Temperature.h
)

set_target_properties(units
    PROPERTIES
        LINKER_LANGUAGE CXX
)

target_link_libraries(units
    PUBLIC
        quant::geometry
)

add_library(quant::units ALIAS units)

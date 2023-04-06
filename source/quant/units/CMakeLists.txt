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
    velocity/TwistDifference.h

    acceleration.h
    acceleration_fwd.h
    acceleration_constants.h
    acceleration/LinearAcceleration.h
    acceleration/LinearAcceleration.cpp
    acceleration/AngularAcceleration.h
    acceleration/AngularAcceleration.cpp
    acceleration/SpatialAcceleration.h
    acceleration/LinearAccelerationDifference.h
    acceleration/AngularAccelerationDifference.h
    acceleration/SpatialAccelerationDifference.h

    jerk.h
    jerk_fwd.h
    jerk_constants.h
    jerk/LinearJerk.h
    jerk/LinearJerk.cpp
    jerk/AngularJerk.h
    jerk/AngularJerk.cpp
    jerk/SpatialJerk.h
    jerk/LinearJerkDifference.h
    jerk/AngularJerkDifference.h
    jerk/SpatialJerkDifference.h

    distance.h
    distance_fwd.h
    distance_constants.h
    distance/Distance.h

    speed.h
    speed_fwd.h
    speed_constants.h
    speed/Speed.h
    speed/Speed.cpp
    speed/SpeedDifference.h

    mass.h
    mass_fwd.h
    mass_constants.h
    mass/Mass.h
    mass/MassDifference.h

    momentum.h
    momentum_fwd.h
    momentum_constants.h
    momentum/LinearMomentum.h
    momentum/AngularMomentum.h
    momentum/SpatialMomentum.h
    momentum/LinearMomentumDifference.h
    momentum/AngularMomentumDifference.h
    momentum/SpatialMomentumDifference.h

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
    force/WrenchDifference.h

    temperature.h
    temperature_fwd.h
    temperature_constants.h
    temperature/Temperature.h
    temperature/TemperatureDifference.h
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

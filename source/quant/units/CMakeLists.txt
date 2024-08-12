add_library(units SHARED
    ../units.h
    
    Scalar.h
    Vector.h
    AxisAngle.h

    angle.h
    angle/forward_declarations.h
    angle/constants.h
    angle/Angle.h
    angle/AngularDifference.h

    angular_speed.h
    angular_speed/forward_declarations.h
    angular_speed/constants.h
    angular_speed/AngularSpeed.h
    angular_speed/AngularSpeedDifference.h

    time.h
    time/forward_declarations.h
    time/constants.h
    time/TimePoint.h
    time/TimePoint.cpp
    time/Duration.h
    time/Duration.cpp
    time/TimeInterval.h
    time/Frequency.h

    position.h
    position/forward_declarations.h
    position/constants.h
    position/Position.h
    position/Position.cpp
    position/Orientation.h
    position/Pose.h
    position/Pose.cpp
    position/LinearDisplacement.h
    position/AngularDisplacement.h
    position/SpatialDisplacement.h

    velocity.h
    velocity/forward_declarations.h
    velocity/constants.h
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
    acceleration/forward_declarations.h
    acceleration/constants.h
    acceleration/LinearAcceleration.h
    acceleration/LinearAcceleration.cpp
    acceleration/AngularAcceleration.h
    acceleration/AngularAcceleration.cpp
    acceleration/SpatialAcceleration.h
    acceleration/LinearAccelerationDifference.h
    acceleration/AngularAccelerationDifference.h
    acceleration/SpatialAccelerationDifference.h

    jerk.h
    jerk/forward_declarations.h
    jerk/constants.h
    jerk/LinearJerk.h
    jerk/LinearJerk.cpp
    jerk/AngularJerk.h
    jerk/AngularJerk.cpp
    jerk/SpatialJerk.h
    jerk/LinearJerkDifference.h
    jerk/AngularJerkDifference.h
    jerk/SpatialJerkDifference.h

    length.h
    length/forward_declarations.h
    length/constants.h
    length/Length.h
    length/Distance.h

    speed.h
    speed/forward_declarations.h
    speed/constants.h
    speed/Speed.h
    speed/Speed.cpp
    speed/SpeedDifference.h

    mass.h
    mass/forward_declarations.h
    mass/constants.h
    mass/Mass.h
    mass/MassDifference.h

    momentum.h
    momentum/forward_declarations.h
    momentum/constants.h
    momentum/LinearMomentum.h
    momentum/AngularMomentum.h
    momentum/SpatialMomentum.h
    momentum/LinearImpulse.h
    momentum/AngularImpulse.h
    momentum/SpatialImpulse.h

    force.h
    force/forward_declarations.h
    force/constants.h
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
    temperature/forward_declarations.h
    temperature/constants.h
    temperature/Temperature.h
    temperature/TemperatureDifference.h

    electric_current.h
    electric_current/forward_declarations.h
    electric_current/constants.h
    electric_current/Current.h
    electric_current/CurrentDifference.h
)

set_target_properties(units
    PROPERTIES
        LINKER_LANGUAGE CXX
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_SOURCE_DIR}/source"
)

target_link_libraries(units
    PUBLIC
        quant::geometry
)

add_library(quant::units ALIAS units)

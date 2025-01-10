add_library(framed_units SHARED
    ../framed_units.h

        #time.h
    #time/forward_declarations.h
        #time/forward_declarations.h
        #time/TimePoint.h
        #time/TimePoint.cpp
        #time/Duration.h
        #time/Duration.cpp
        #time/DateTime.h
        #time/DateTime.cpp
    #time/TimeInterval.h
        #time/Frequency.h
        #time/Frequency.cpp
    #time/detail/UnitConversions.h
        #time/measurement/ClockInterface.h
        #time/measurement/ClockInterface.cpp
        #time/measurement/Clock.h
        #time/measurement/Clock.cpp

    position.h
    position/forward_declarations.h
    position/FramedPosition.h
    position/FramedOrientation.h
    position/FramedPose.h
    position/FramedLinearDisplacement.h
    position/FramedAngularDisplacement.h
    position/FramedSpatialDisplacement.h

        #velocity.h
    #velocity_fwd.h
    #velocity/LinearVelocity.h
    #velocity/LinearVelocity.cpp
    #velocity/AngularVelocity.h
    #velocity/AngularVelocity.cpp
    #velocity/Twist.h
    #velocity/Twist.cpp

    #acceleration.h
    #acceleration_fwd.h
    #acceleration/LinearAcceleration.h
    #acceleration/LinearAcceleration.cpp
    #acceleration/AngularAcceleration.h
    #acceleration/AngularAcceleration.cpp

    #jerk.h
    #jerk_fwd.h
    #jerk/LinearJerk.h
    #jerk/LinearJerk.cpp
    #jerk/AngularJerk.h
    #jerk/AngularJerk.cpp

    #distance.h
    #distance_fwd.h
    #distance/Distance.h

    #speed.h
    #speed_fwd.h
    #speed/Speed.h

    #mass.h
    #mass_fwd.h
    #mass/Mass.h

    #force.h
    #force_fwd.h
    #force/Force.h
    #force/Force.cpp
    #force/Torque.h
    #force/Torque.cpp
    #force/Wrench.h
    #force/Wrench.cpp

    #temperature.h
    #temperature_fwd.h
    #temperature/Temperature.h
)

set_target_properties(framed_units
    PROPERTIES
        LINKER_LANGUAGE CXX
)

target_link_libraries(framed_units
    PUBLIC
        quant::framed_geometry
        quant::units
    PRIVATE
        Boost::headers
)

add_library(quant::framed_units ALIAS framed_units)

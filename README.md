# quant

Robotics-focused geometry and quantities library with support for reference
frame checking.

Authored by Christian Dreher and Rainer Kartmann. 

[[_TOC_]]

---


## Design Goals

- **State ≠ Operation**: Explicit differentiation between state (e.g., a 
  position, an orientation, or a pose) and an operation (e.g., a translation, 
  a rotation or a transform).
- **Units**: It must be clear what units are used if it is relevant (e.g., 
  during construction or initialization), it should not interfere if it is not 
  relevant (e.g., when calculating).
- **Frames of Reference**: Vectors, quaternions, matrices and even scalar values
  are usually in a frame of reference. Transforming a vector in a certain frame
  using a matrix can be ensured if information about the frames is given to
  avoid logic errors.


### State ≠ Operation

There are dedicated types for states and operations.  Specifically, if two 
states are subtracted, the result will be a difference type.  See the following 
tables.  For some geometric concepts, special names are given.


#### R<sup>3</sup> (3-Dimensional Space)

| Geometric Concept | Position            | Orientation          | Pose                 | Translation                                     | Rotation                                            | Transform                                            |
|------------------:|---------------------|----------------------|----------------------|-------------------------------------------------|-----------------------------------------------------|------------------------------------------------------|
|          Position | Position            | Orientation          | Pose                 | Linear Displacement<br/>(*Position Difference*) | Angular Displacement<br/>(*Orientation Difference*) | Spatial Displacement<br/>(*Pose Difference*)         |
|          Velocity | Linear Velocity     | Angular Velocity     | Twist                | Linear Velocity Difference                      | Angular Velocity Difference                         | Twist Difference<br/>(*Spatial Velocity Difference*) |
|      Acceleration | Linear Acceleration | Angular Acceleration | Spatial Acceleration | Linear Acceleration Difference                  | Angular Acceleration Difference                     | Spatial Acceleration Difference                      |
|              Jerk | Linear Jerk         | Angular Jerk         | Spatial Jerk         | Linear Jerk Difference                          | Angular Jerk Difference                             | Spatial Jerk Difference                              |
|          Momentum | Linear Momentum     | Angular Momentum     | Spatial Momentum     | Linear Momentum Difference                      | Angular Momentum Difference                         | Spatial Momentum Difference                          |
|             Force | Force               | Torque               | Wrench               | Force Difference                                | Torque Difference                                   | Wrench Difference                                    |


#### R (1-Dimensional Space)

| Geometric Concept | Position                             | Translation                                 |
|------------------:|--------------------------------------|---------------------------------------------|
|              Time | Time Point                           | Duration                                    |
|          Distance | -                                    | Distance (Magnitude of Linear Displacement) |
|             Speed | Speed (Magnitude of Linear Velocity) | -                                           |
|              Mass | Mass                                 | -                                           |


### Units

Each quantity is stored as a normalized unit (e.g., Millimeters for Position).  Constructing a 
quantity from any other non-normalized form will result in a run-time conversion (e.g., a 
construction from Meters will result in a conversion to Millimeters). This allows for flexibility
and easier to read and write code at the cost of run-time conversions if non-normalized units are
provided.

It is not possible to construct any quantity in this framework without explicitly specifying the 
unit.  For example, for Position:

```c++
using namespace quant;

Position p1_good;                                           // Ok, will be [0, 0, 0] mm.
Position p2_good == Position::Zero();                       // Ok, will be [0, 0, 0] mm.
Position p3_good == Position::MilliMeters(100, 200, 300);   // Ok, will be [100, 200, 300] mm.
Position p4_good == Position::Meters(0.1, 0.2, 0.3);        // Ok, will be [100, 200, 300] mm.
Position p5_good == Position::Meters({.y = 0.2});           // Ok, will be [0, 200, 0] mm.
Position p6_good == Position::Meters(Vector::FromEigen(e)); // Ok, will be the Eigen vector e converted to mm.

Position p1_bad{0, 0, 0};                                   // Error, constructor not defined.  Unit unclear.
```

This applies to all quantities.  There will be static constructor-like functions specifying the 
unit of the passed numbers.


### Frames of Reference

Usually a quantity (e.g., a position or a velocity) is in a base frame.  For example, the position 
of the tool center point of a robot might be given in the frame of the robot model's root.

Especially in robotics, were several frames of reference have to be taken into account, logic 
errors can quickly occur and are usually just mitigated by specific naming conventions.

This library provides the concept of "Framed" states and "Frame" operations.

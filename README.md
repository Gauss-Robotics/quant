# quant

Robotics-focused geometry and quantities library with support for reference
frame checking.

[[_TOC_]]

---


## Design Goals

- **State ≠ Operation**: Explicit differentiation between state (e.g., a 
  position, an orientation, or a pose) and an operation (e.g., a translation, 
  a rotation or a transform).
- **Units**: It must be clear what units are used if it is relevant (e.g., 
  during construction or initialization), it should not interfere if it is not 
  relevant (e.g., when calculating).

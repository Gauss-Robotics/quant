import pytest
import numpy as np
from quantpy import units

@pytest.fixture
def angle_in_deg():
    return units.angle.Angle.degrees(90)

@pytest.fixture
def angle_in_rad():
    return units.angle.Angle.radians(np.pi / 2)

def test_angle_add(angle_in_deg, angle_in_rad):
    with pytest.raises(TypeError):
        angle = angle_in_deg + angle_in_rad

def test_angle_sub(angle_in_deg, angle_in_rad):
    angle = angle_in_deg - angle_in_rad
    assert type(angle) == units.angle.AngularDifference
    assert angle.to_degrees().value == pytest.approx(0)

def test_angle_mul(angle_in_deg, angle_in_rad):
    angle = angle_in_deg * 2
    assert angle.to_degrees().value == pytest.approx(180)

    angle = angle_in_rad * 2
    assert angle.to_degrees().value == pytest.approx(180)

def test_angle_truediv(angle_in_deg, angle_in_rad):
    angle = angle_in_deg / 2
    assert angle.to_degrees().value == pytest.approx(45)

    angle = angle_in_rad / 2
    assert angle.to_degrees().value == pytest.approx(45)

def test_angle_eq(angle_in_deg, angle_in_rad):
    assert angle_in_rad == units.angle.Angle.degrees(90)
    assert angle_in_deg == units.angle.Angle.radians(np.pi / 2)

def test_angle_neq(angle_in_deg, angle_in_rad):
    assert angle_in_rad != units.angle.Angle.degrees(45)
    assert angle_in_deg != units.angle.Angle.radians(np.pi / 4)

def test_angle_isub(angle_in_deg):
    with pytest.raises(TypeError):
        # Difference between two angles is an AngularDifference
        angle_in_deg -= units.angle.Angle.degrees(45)

    angle_in_deg -= units.angle.AngularDifference.degrees(45)
    assert angle_in_deg.to_degrees().value == pytest.approx(45)
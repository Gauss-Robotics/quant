import pytest
import numpy as np
from quantpy import units

@pytest.fixture
def angle_in_deg():
    return units.angle.Angle.degrees(90)

@pytest.fixture
def angle_in_rad():
    return units.angle.Angle.radians(np.pi / 2)

def test_angle_from_degrees(angle_in_deg):
    angle = angle_in_deg.to_degrees()
    assert angle.value == pytest.approx(90)
    assert angle.unit_symbol == '°'
    assert angle.quantity_name == 'Degrees'

    angle = angle_in_deg.to_radians()
    assert angle.value == pytest.approx(np.pi / 2)
    assert angle.unit_symbol == 'rad'
    assert angle.quantity_name == 'Radians'

def test_angle_from_rad(angle_in_rad):
    angle = angle_in_rad.to_degrees()
    assert angle.value == pytest.approx(90)
    assert angle.unit_symbol == '°'
    assert angle.quantity_name == 'Degrees'

    angle = angle_in_rad.to_radians()
    assert angle.value == pytest.approx(np.pi / 2)
    assert angle.unit_symbol == 'rad'
    assert angle.quantity_name == 'Radians'

def test_angle_repr(angle_in_deg, angle_in_rad):
    assert repr(angle_in_deg) == "Angle(90 °)"
    assert repr(angle_in_rad) == "Angle(90 °)"

def test_angle_str(angle_in_deg, angle_in_rad):
    assert str(angle_in_deg) == "1.5708 rad"
    assert str(angle_in_rad) == "1.5708 rad"
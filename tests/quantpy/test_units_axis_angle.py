import pytest
import numpy as np
from quantpy import units

@pytest.fixture
def axis_angle() -> units.AxisAngle:
    return units.AxisAngle(1, np.array([1.0, 0, 0]), 'quantity', 'quant')

def test_properties(axis_angle):
    assert axis_angle.angle == 1
    assert np.all(axis_angle.axis == np.array([1.0, 0, 0]))
    assert axis_angle.unit_symbol == 'quant'
    assert axis_angle.quantity_name == 'quantity'

def test_set_angle(axis_angle):
    axis_angle.angle = 2
    assert axis_angle.angle == 2

def test_set_axis(axis_angle):
    axis_angle.axis = np.array([0, 1.0, 0])
    assert np.all(axis_angle.axis == np.array([0, 1.0, 0]))

def test_set_unit_fails(axis_angle):
    with pytest.raises(AttributeError):
        axis_angle.unit_symbol = 'm'
    with pytest.raises(AttributeError):
        axis_angle.quantity_name = 'length'
def test_str(axis_angle):
    assert str(axis_angle) == '1 quant around axis [1 0 0]'
def test_repr(axis_angle):
    assert repr(axis_angle) == "AxisAngle(1.00, [1 0 0], 'quantity', 'quant')"


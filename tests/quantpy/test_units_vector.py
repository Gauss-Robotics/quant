import pytest
import numpy as np
from quantpy import units

@pytest.fixture
def vector() -> units.Vector:
    return units.Vector(np.array([1.0, 0, 0]), 'quantity', 'quant')

def test_properties(vector):
    assert vector.x == 1.0
    assert vector.y == 0
    assert vector.z == 0
    assert vector.unit_symbol == 'quant'
    assert vector.quantity_name == 'quantity'

def test_set_properties(vector):
    vector.x = 2
    vector.y = 3
    vector.z = 4
    assert vector.x == 2
    assert vector.y == 3
    assert vector.z == 4

    with pytest.raises(AttributeError):
        vector.unit_symbol = 'm'
    with pytest.raises(AttributeError):
        vector.quantity_name = 'length'
def test_mul(vector):
    result = vector * 2
    assert result.x == 2.0
    assert result.y == 0
    assert result.z == 0
    assert result.unit_symbol == 'quant'
    assert result.quantity_name == 'quantity'

def test_truediv(vector):
    result = vector / 2
    assert result.x == 0.5
    assert result.y == 0
    assert result.z == 0
    assert result.unit_symbol == 'quant'
    assert result.quantity_name == 'quantity'

def test_repr(vector):
    assert repr(vector) == "Vector([1, 0, 0], 'quantity', 'quant')"

def test_str(vector):
    assert str(vector) == '[1 0 0] quant'

def test_norm(vector):
    assert vector.norm() == 1.0

def test_factory_methods():
    vector = units.Vector.unit_x('quantity', 'quant')
    assert vector.x == 1
    assert vector.y == 0
    assert vector.z == 0
    assert vector.unit_symbol == 'quant'
    assert vector.quantity_name == 'quantity'

    vector = units.Vector.unit_y('quantity', 'quant')
    assert vector.x == 0
    assert vector.y == 1
    assert vector.z == 0
    assert vector.unit_symbol == 'quant'
    assert vector.quantity_name == 'quantity'

    vector = units.Vector.unit_z('quantity', 'quant')
    assert vector.x == 0
    assert vector.y == 0
    assert vector.z == 1
    assert vector.unit_symbol == 'quant'
    assert vector.quantity_name == 'quantity'
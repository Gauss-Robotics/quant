import pytest
from quantpy import units

@pytest.fixture
def scalar():
    return units.Scalar(1, 'quantity', 'quant')

def test_properties(scalar):
    assert scalar.value == 1
    assert scalar.unit_symbol == 'quant'
    assert scalar.quantity_name == 'quantity'

def test_set_value(scalar):
    scalar.value = 2
    assert scalar.value == 2

def test_set_unit_fails(scalar):
    with pytest.raises(AttributeError):
        scalar.unit_symbol = 'm'
    with pytest.raises(AttributeError):
        scalar.quantity_name = 'length'
def test_mul(scalar):
    result = scalar * 2
    assert result.value == 2
    assert result.unit_symbol == 'quant'
    assert result.quantity_name == 'quantity'
def test_truediv(scalar):
    result = scalar / 2
    assert result.value == 0.5
    assert result.unit_symbol == 'quant'
    assert result.quantity_name == 'quantity'

def test_float(scalar):
    assert float(scalar) == 1.0

def test_repr(scalar):
    assert repr(scalar) == "Scalar(1.00, 'quantity', 'quant')"

def test_str(scalar):
    assert str(scalar) == '1 quant'

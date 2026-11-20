import numpy as np

from gates import bell, x_on_zero


def test_x_flips_zero_to_one() -> None:
    assert np.isclose(abs(x_on_zero()[1]) ** 2, 1.0)


def test_bell_is_equal_superposition_of_00_and_11() -> None:
    data = bell()
    assert np.isclose(abs(data[0]) ** 2, 0.5)  # |00>
    assert np.isclose(abs(data[3]) ** 2, 0.5)  # |11>

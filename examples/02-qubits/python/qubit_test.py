import numpy as np

from qubit import H, KET0, X, apply_gate, probabilities


def test_hadamard_equal_probabilities() -> None:
    p = probabilities(apply_gate(H, KET0))
    assert np.isclose(p[0], 0.5)
    assert np.isclose(p[1], 0.5)


def test_x_flips_zero_to_one() -> None:
    p = probabilities(apply_gate(X, KET0))
    assert np.isclose(p[0], 0.0)
    assert np.isclose(p[1], 1.0)


def test_apply_gate_is_row_major() -> None:
    # A non-symmetric matrix pins the row/column convention.
    m = np.array([[1, 2], [3, 4]], dtype=complex)
    s = np.array([5, 6], dtype=complex)
    r = apply_gate(m, s)
    assert np.isclose(r[0], 17)  # 1*5 + 2*6
    assert np.isclose(r[1], 39)  # 3*5 + 4*6

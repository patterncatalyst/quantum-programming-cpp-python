from phase_estimation import phase_estimate_value


def test_recovers_exact_phases() -> None:
    t, shots = 3, 1000
    assert phase_estimate_value(0.125, t, shots) == 1  # 0.001
    assert phase_estimate_value(0.25, t, shots) == 2   # 0.010
    assert phase_estimate_value(0.375, t, shots) == 3  # 0.011
    assert phase_estimate_value(0.5, t, shots) == 4    # 0.100

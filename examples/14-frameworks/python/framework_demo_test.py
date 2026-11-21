import math

from framework_demo import outcome_probs


def test_shared_circuit_probabilities() -> None:
    probs = outcome_probs()
    assert set(probs) == {"000", "001", "110", "111"}
    for bits, p in probs.items():
        assert math.isclose(p, 0.25, abs_tol=1e-9), bits

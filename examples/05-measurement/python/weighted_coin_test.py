import math

from weighted_coin import prob_one_exact, weighted_coin_counts


def test_exact_probability_is_one_quarter() -> None:
    assert math.isclose(prob_one_exact(math.pi / 3), 0.25, abs_tol=1e-9)


def test_sampled_fraction_tracks_exact() -> None:
    shots = 20000
    zeros, ones = weighted_coin_counts(math.pi / 3, shots)
    assert zeros + ones == shots
    assert math.isclose(ones / shots, 0.25, abs_tol=0.03)

from qaoa import TRIANGLE, cut_value, qaoa_optimize, qaoa_sample


def test_cut_value() -> None:
    assert cut_value("000", TRIANGLE, 3) == 0
    assert cut_value("111", TRIANGLE, 3) == 0
    assert cut_value("100", TRIANGLE, 3) == 2
    assert cut_value("011", TRIANGLE, 3) == 2


def test_samples_a_max_cut() -> None:
    gamma, beta, exp_cut = qaoa_optimize(TRIANGLE, 3, 40)
    assert exp_cut > 1.0
    _, cut, _ = qaoa_sample(TRIANGLE, 3, gamma, beta, 4000)
    assert cut == 2

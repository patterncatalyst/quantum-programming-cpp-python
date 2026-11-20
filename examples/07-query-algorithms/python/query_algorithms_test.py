from query_algorithms import bernstein_vazirani_recover, deutsch_jozsa_all_zero_count


def test_constant_is_always_all_zero() -> None:
    shots = 1000
    assert deutsch_jozsa_all_zero_count("constant0", 3, shots) == shots
    assert deutsch_jozsa_all_zero_count("constant1", 3, shots) == shots


def test_balanced_is_never_all_zero() -> None:
    assert deutsch_jozsa_all_zero_count("balanced", 3, 1000) == 0


def test_bernstein_vazirani_recovers_hidden_string() -> None:
    shots = 1000
    assert bernstein_vazirani_recover("1011", shots) == "1011"
    assert bernstein_vazirani_recover("0000", shots) == "0000"
    assert bernstein_vazirani_recover("111", shots) == "111"

from coin_flip import coin_flip_counts


def test_coin_flip_splits_roughly_evenly() -> None:
    shots = 1000
    zeros, ones = coin_flip_counts(shots)
    assert zeros + ones == shots
    assert zeros > 350
    assert ones > 350

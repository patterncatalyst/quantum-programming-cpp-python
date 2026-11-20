from shor import order_from_measurement, shor_factor


def test_continued_fraction_recovers_order() -> None:
    assert order_from_measurement(4, 4, 15) == 4   # 4/16 = 1/4
    assert order_from_measurement(12, 4, 15) == 4  # 12/16 = 3/4


def test_classical_shortcut_when_not_coprime() -> None:
    p, q = shor_factor(6, 15, 4, 4, 100)  # gcd(6, 15) = 3
    assert p * q == 15
    assert {p, q} == {3, 5}


def test_factors_fifteen() -> None:
    p, q = shor_factor(7, 15, 4, 4, 2000)
    assert p * q == 15
    assert {p, q} == {3, 5}

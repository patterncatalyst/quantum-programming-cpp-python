import math

from entanglement import bell_counts, ghz_counts, teleport_zero_count


def test_bell_pair_is_correlated() -> None:
    shots = 2000
    counts = bell_counts(shots)
    assert set(counts) <= {"00", "11"}
    assert counts.get("00", 0) + counts.get("11", 0) == shots
    assert counts.get("00", 0) > 700
    assert counts.get("11", 0) > 700


def test_ghz_is_all_or_nothing() -> None:
    shots = 2000
    counts = ghz_counts(shots)
    assert set(counts) <= {"000", "111"}
    assert counts.get("000", 0) + counts.get("111", 0) == shots
    assert counts.get("000", 0) > 700
    assert counts.get("111", 0) > 700


def test_teleportation_is_exact() -> None:
    shots = 2000
    assert teleport_zero_count(math.pi / 3, shots) == shots

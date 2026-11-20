"""Verifies the Bell state's measured distribution: only 00 and 11 appear, each
close to half the shots. Checks the effect, not just that the program ran.
"""

from bell_state import bell_counts


def test_only_00_and_11() -> None:
    counts = bell_counts(shots=2000)
    assert set(counts).issubset({"00", "11"})
    assert counts.get("00", 0) > 700
    assert counts.get("11", 0) > 700

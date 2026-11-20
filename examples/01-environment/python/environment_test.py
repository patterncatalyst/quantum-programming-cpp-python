from environment import hadamard_counts


def test_hadamard_is_superposition() -> None:
    counts = hadamard_counts(shots=2000)
    assert set(counts).issubset({"0", "1"})
    assert counts.get("0", 0) > 700
    assert counts.get("1", 0) > 700

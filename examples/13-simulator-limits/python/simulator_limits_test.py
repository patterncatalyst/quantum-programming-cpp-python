from simulator_limits import ghz_counts, statevector_bytes, statevector_dim


def test_state_vector_grows_exponentially() -> None:
    assert statevector_dim(10) == 1024
    assert statevector_dim(20) == 1048576
    assert statevector_bytes(10) == 1024 * 16
    for n in range(1, 24):
        assert statevector_bytes(n) == 2 * statevector_bytes(n - 1)


def test_ghz_has_two_outcomes_at_any_size() -> None:
    counts = ghz_counts(14, 2000)
    assert set(counts) == {"0" * 14, "1" * 14}
    assert sum(counts.values()) == 2000

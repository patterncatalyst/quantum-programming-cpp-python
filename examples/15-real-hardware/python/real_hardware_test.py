from real_hardware import bell_counts_local

# Only the local simulator path is tested; run_on_ibm needs a free IBM Quantum
# account and is not exercised in CI.


def test_local_bell_is_correlated() -> None:
    counts = bell_counts_local(2000)
    assert set(counts) <= {"00", "11"}
    assert counts.get("00", 0) + counts.get("11", 0) == 2000

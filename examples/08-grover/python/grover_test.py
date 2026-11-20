from grover import grover_iterations, grover_search


def test_finds_marked_item_with_high_probability() -> None:
    found, fraction = grover_search("101", 2000)
    assert found == "101"
    assert fraction > 0.90


def test_works_for_a_different_target() -> None:
    found, fraction = grover_search("011", 2000)
    assert found == "011"
    assert fraction > 0.90


def test_iteration_count_for_three_qubits() -> None:
    assert grover_iterations(3) == 2

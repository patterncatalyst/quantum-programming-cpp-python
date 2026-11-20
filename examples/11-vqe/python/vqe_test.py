import math

from vqe import ground_energy, hamiltonian, vqe_minimize


def test_finds_ground_energy() -> None:
    c1, c2 = 0.5, 1.0
    H = hamiltonian(c1, c2)
    expected = -math.sqrt(c1 * c1 + c2 * c2)
    assert math.isclose(ground_energy(H), expected, abs_tol=1e-9)

    _, e_vqe = vqe_minimize(H, 2000)
    assert math.isclose(e_vqe, expected, abs_tol=1e-3)
    assert e_vqe >= expected - 1e-9  # variational principle


def test_pure_z_hamiltonian() -> None:
    _, e_vqe = vqe_minimize(hamiltonian(0.0, 1.0), 2000)
    assert math.isclose(e_vqe, -1.0, abs_tol=1e-3)

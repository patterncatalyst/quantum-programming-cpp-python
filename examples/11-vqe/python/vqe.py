"""Variational quantum eigensolver (VQE) in Qiskit: minimize the energy of a
parameterized state to find a Hamiltonian's lowest eigenvalue, mirroring the
Quantum++ version. H = c1 X + c2 Z on one qubit, ansatz RY(theta), so the ground
energy is known (-sqrt(c1^2 + c2^2)) and checkable.
"""

from __future__ import annotations

import math

import numpy as np
from qiskit import QuantumCircuit
from qiskit.quantum_info import SparsePauliOp, Statevector


def hamiltonian(c1: float, c2: float) -> SparsePauliOp:
    return SparsePauliOp.from_list([("X", c1), ("Z", c2)])


def energy(theta: float, H: SparsePauliOp) -> float:
    """Expectation <psi(theta)|H|psi(theta)> for the ansatz RY(theta)|0>."""
    qc = QuantumCircuit(1)
    qc.ry(theta, 0)
    return float(Statevector.from_instruction(qc).expectation_value(H).real)


def vqe_minimize(H: SparsePauliOp, grid: int) -> tuple[float, float]:
    """Sweep the single parameter and return (best_theta, min_energy)."""
    best_theta, best_energy = 0.0, energy(0.0, H)
    for i in range(1, grid + 1):
        theta = 2 * math.pi * i / grid
        e = energy(theta, H)
        if e < best_energy:
            best_theta, best_energy = theta, e
    return best_theta, best_energy


def ground_energy(H: SparsePauliOp) -> float:
    return float(np.linalg.eigvalsh(H.to_matrix())[0])


def main() -> None:
    c1, c2 = 0.5, 1.0
    H = hamiltonian(c1, c2)
    theta, e_vqe = vqe_minimize(H, 2000)
    print(f">> VQE for H = {c1} X + {c2} Z")
    print(f"best theta   = {theta:.4f}")
    print(f"VQE energy   = {e_vqe:.4f}")
    print(f"exact ground = {ground_energy(H):.4f}")


if __name__ == "__main__":
    main()

"""The weighted coin in Qiskit: an RY rotation sets the bias, Statevector gives
the exact probability, and Aer sampling estimates it. More shots, tighter
estimate -- the same lesson as the Quantum++ version.
"""

from __future__ import annotations

import math

from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector
from qiskit_aer import AerSimulator


def prob_one_exact(theta: float) -> float:
    """Exact probability of measuring 1 after RY(theta) on |0>."""
    qc = QuantumCircuit(1)
    qc.ry(theta, 0)
    amp_one = Statevector.from_int(0, 2).evolve(qc).data[1]
    return float(abs(amp_one) ** 2)


def weighted_coin_counts(theta: float, shots: int) -> tuple[int, int]:
    """Sample the RY(theta) circuit and return (zeros, ones)."""
    qc = QuantumCircuit(1, 1)
    qc.ry(theta, 0)
    qc.measure(0, 0)
    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    return counts.get("0", 0), counts.get("1", 0)


def main() -> None:
    theta = math.pi / 3  # tilts P(1) to 0.25
    print(">> Weighted coin: RY(pi/3) then measure")
    print(f"exact P(1) = {prob_one_exact(theta):.3f}\n")

    for shots in (100, 10000):
        zeros, ones = weighted_coin_counts(theta, shots)
        print(f"{shots} shots: 0={zeros} 1={ones}  measured P(1) = {ones / shots:.3f}")


if __name__ == "__main__":
    main()

"""Quantum phase estimation in Qiskit: recover the phase phi of a controlled-phase
gate into a t-bit counting register, mirroring the Quantum++ version. We estimate
the phase of P(2 pi phi) on its |1> eigenstate, so phi is known and checkable.

The inverse QFT is built from Hadamards and controlled phases rather than Qiskit's
QFT helper (deprecated in Qiskit 2.1, and Aer does not run it as a single op).
"""

from __future__ import annotations

import math

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def inverse_qft(qc: QuantumCircuit, n: int) -> None:
    """Inverse QFT on qubits 0..n-1, no final swaps."""
    for j in reversed(range(n)):
        for k in reversed(range(j + 1, n)):
            qc.cp(-math.pi / 2 ** (k - j), k, j)
        qc.h(j)


def phase_estimate_value(phi: float, t: int, shots: int) -> int:
    """Return the most-measured integer value; the estimate is value / 2^t."""
    theta = 2 * math.pi * phi
    qc = QuantumCircuit(t + 1, t)
    qc.x(t)  # prepare the |1> eigenstate
    for j in range(t):
        qc.h(j)
    for j in range(t):  # controlled-U^(2^j) is a controlled phase of theta * 2^j
        qc.cp(theta * (2**j), j, t)
    inverse_qft(qc, t)
    qc.measure(range(t), range(t))

    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    top = max(counts, key=counts.get)
    return int(top[::-1], 2)  # reverse the MSB-first key to read the value


def main() -> None:
    t, shots = 3, 1000
    print(f">> Phase estimation with {t} counting qubits, {shots} shots")
    for phi in (0.125, 0.25, 0.375, 0.5):
        value = phase_estimate_value(phi, t, shots)
        print(f"phi = {phi} -> value {value}/{2**t} = {value / 2**t}")


if __name__ == "__main__":
    main()

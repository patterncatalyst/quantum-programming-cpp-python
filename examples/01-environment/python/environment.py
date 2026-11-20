"""Confirms the Python quantum environment: Qiskit imports, and a one-qubit
Hadamard circuit runs on the Aer simulator giving an equal superposition.
"""

from __future__ import annotations

import qiskit
from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def hadamard_counts(shots: int = 1000) -> dict[str, int]:
    qc = QuantumCircuit(1, 1)
    qc.h(0)
    qc.measure(0, 0)
    return AerSimulator().run(qc, shots=shots).result().get_counts()


def main() -> None:
    print(f">> Python quantum environment is ready (Qiskit {qiskit.__version__})")
    print("H|0> measured:", dict(sorted(hadamard_counts().items())))


if __name__ == "__main__":
    main()

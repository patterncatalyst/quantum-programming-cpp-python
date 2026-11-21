"""Qiskit side of the framework comparison: the same three-qubit circuit as the
Quantum++ program, read as an exact probability map. Same numbers, so the choice
between frameworks is about ergonomics, not correctness.
"""

from __future__ import annotations

import math

from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector


def outcome_probs() -> dict[str, float]:
    qc = QuantumCircuit(3)
    qc.h(0)
    qc.cx(0, 1)
    qc.ry(math.pi / 2, 2)
    raw = Statevector(qc).probabilities_dict()
    # Qiskit keys are qubit-2-q1-q0; reverse to qubit 0 first, matching the C++ output.
    return {key[::-1]: p for key, p in raw.items() if p > 1e-12}


def main() -> None:
    print(">> Shared circuit in Qiskit: H q0, CNOT q0->q1, RY(pi/2) q2")
    for bits, p in sorted(outcome_probs().items()):
        print(f"  {bits}: {p:.3f}")


if __name__ == "__main__":
    main()

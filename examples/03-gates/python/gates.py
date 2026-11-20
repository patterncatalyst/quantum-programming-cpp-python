"""Single-qubit gates and a two-qubit circuit with Qiskit, read as exact state
vectors (the Python cross-check for the Quantum++ gates example).
"""

from __future__ import annotations

import numpy as np
from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector


def x_on_zero() -> np.ndarray:
    qc = QuantumCircuit(1)
    qc.x(0)
    return np.asarray(Statevector.from_int(0, 2).evolve(qc).data)


def bell() -> np.ndarray:
    qc = QuantumCircuit(2)
    qc.h(0)
    qc.cx(0, 1)
    return np.asarray(Statevector.from_int(0, 4).evolve(qc).data)


def main() -> None:
    print(">> Single-qubit gates (Qiskit)")
    print("X|0> =", np.round(x_on_zero(), 3))
    print("Bell =", np.round(bell(), 3))


if __name__ == "__main__":
    main()

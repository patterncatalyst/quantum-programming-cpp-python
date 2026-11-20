"""Grover's search in Qiskit: the same oracle-and-diffusion loop as the Quantum++
version, finding a marked item in about (pi/4) * sqrt(2^n) iterations.

A multi-controlled Z is a multi-controlled phase of pi (qc.mcp). Count keys are
most-significant qubit first, so we reverse them to read bit 0 first.
"""

from __future__ import annotations

import math

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def _multi_controlled_z(qc: QuantumCircuit, n: int) -> None:
    if n == 1:
        qc.z(0)
    else:
        qc.mcp(math.pi, list(range(n - 1)), n - 1)


def _oracle(qc: QuantumCircuit, target: str, n: int) -> None:
    for i in range(n):
        if target[i] == "0":
            qc.x(i)
    _multi_controlled_z(qc, n)
    for i in range(n):
        if target[i] == "0":
            qc.x(i)


def _diffusion(qc: QuantumCircuit, n: int) -> None:
    qc.h(range(n))
    qc.x(range(n))
    _multi_controlled_z(qc, n)
    qc.x(range(n))
    qc.h(range(n))


def grover_iterations(n: int) -> int:
    return int(math.floor(math.pi / 4 * math.sqrt(2**n)))


def grover_search(target: str, shots: int) -> tuple[str, float]:
    """Return the most-measured outcome (bit 0 first) and its shot fraction."""
    n = len(target)
    qc = QuantumCircuit(n, n)
    qc.h(range(n))
    for _ in range(grover_iterations(n)):
        _oracle(qc, target, n)
        _diffusion(qc, n)
    qc.measure(range(n), range(n))

    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    top = max(counts, key=counts.get)
    return top[::-1], counts[top] / shots


def main() -> None:
    target, shots = "101", 1000
    print(f">> Grover search for {target} among {2**len(target)} items, {shots} shots")
    print(f"iterations: {grover_iterations(len(target))}")
    found, fraction = grover_search(target, shots)
    print(f"most measured: {found}  fraction = {fraction:.3f}")


if __name__ == "__main__":
    main()

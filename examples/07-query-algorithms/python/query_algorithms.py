"""Deutsch-Jozsa and Bernstein-Vazirani in Qiskit: each decides its question in a
single oracle query, mirroring the Quantum++ versions.

Qiskit count keys are written most-significant qubit first, so we reverse them to
read bit 0 first, matching the C++ output.
"""

from __future__ import annotations

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def deutsch_jozsa_all_zero_count(oracle: str, n: int, shots: int) -> int:
    """Return how many shots measured the input register as all-zeros."""
    qc = QuantumCircuit(n + 1, n)
    qc.x(n)
    qc.h(range(n + 1))
    if oracle == "constant1":
        qc.x(n)
    elif oracle == "balanced":
        for i in range(n):
            qc.cx(i, n)
    # "constant0" adds no oracle gates.
    qc.h(range(n))
    qc.measure(range(n), range(n))
    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    return counts.get("0" * n, 0)


def bernstein_vazirani_recover(secret: str, shots: int) -> str:
    """Recover the hidden string (given bit 0 first) and return it bit 0 first."""
    n = len(secret)
    qc = QuantumCircuit(n + 1, n)
    qc.x(n)
    qc.h(range(n + 1))
    for i, bit in enumerate(secret):
        if bit == "1":
            qc.cx(i, n)
    qc.h(range(n))
    qc.measure(range(n), range(n))
    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    top = max(counts, key=counts.get)
    return top[::-1]  # reverse MSB-first key to bit-0-first


def main() -> None:
    n, shots = 3, 1000
    print(f">> Deutsch-Jozsa on {n} input qubits, {shots} shots")
    print(f"constant oracle: all-zero outcomes = "
          f"{deutsch_jozsa_all_zero_count('constant0', n, shots)}/{shots}")
    print(f"balanced oracle: all-zero outcomes = "
          f"{deutsch_jozsa_all_zero_count('balanced', n, shots)}/{shots}")

    secret = "1011"
    print(f"\n>> Bernstein-Vazirani, hidden string {secret}")
    print(f"recovered: {bernstein_vazirani_recover(secret, shots)}")


if __name__ == "__main__":
    main()

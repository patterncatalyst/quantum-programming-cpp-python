"""Why a CPU simulator caps out around 25-30 qubits: the state vector holds 2^n
complex amplitudes, so memory doubles with each qubit. Mirrors the Quantum++ version.
"""

from __future__ import annotations

import time

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def statevector_dim(n: int) -> int:
    """Number of complex amplitudes in an n-qubit state vector: 2^n."""
    return 1 << n


def statevector_bytes(n: int) -> int:
    """Bytes for the state vector: 2^n times one complex128 (16 bytes)."""
    return statevector_dim(n) * 16


def ghz_counts(n: int, shots: int) -> dict[str, int]:
    """Measured counts of a GHZ state on n qubits (only all-0 and all-1 appear)."""
    qc = QuantumCircuit(n, n)
    qc.h(0)
    for i in range(1, n):
        qc.cx(i - 1, i)
    qc.measure(range(n), range(n))
    return dict(AerSimulator().run(qc, shots=shots).result().get_counts())


def main() -> None:
    print(">> State-vector cost by qubit count (GHZ, 200 shots)")
    print("qubits   amplitudes        memory       sim time")
    for n in (4, 8, 12, 16, 20):
        start = time.perf_counter()
        counts = ghz_counts(n, 200)
        ms = (time.perf_counter() - start) * 1000
        mib = statevector_bytes(n) / (1024 * 1024)
        print(f"{n:>4}   {statevector_dim(n):>12}   {mib:>10.3f} MiB   "
              f"{ms:>8.3f} ms   (outcomes: {len(counts)})")
    print("\nEach qubit doubles the memory: 30 qubits already needs ~16 GiB.")


if __name__ == "__main__":
    main()

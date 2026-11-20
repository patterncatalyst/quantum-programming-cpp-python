"""Bell state in Qiskit: the Python cross-check for the C++ (Quantum++) example.

Build (|00> + |11>)/sqrt(2) with H on qubit 0 then CNOT(0->1), run it on the Aer
CPU simulator, and report measured counts. Measuring gives 00 or 11 with roughly
equal frequency, never 01 or 10.
"""

from __future__ import annotations

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def bell_counts(shots: int = 1000) -> dict[str, int]:
    qc = QuantumCircuit(2, 2)
    qc.h(0)
    qc.cx(0, 1)
    qc.measure([0, 1], [0, 1])
    result = AerSimulator().run(qc, shots=shots).result()
    return result.get_counts()


def main() -> None:
    counts = bell_counts()
    print(">> Bell state measured counts (Qiskit Aer):")
    for key in sorted(counts):
        print(f"  |{key}>: {counts[key]}")


if __name__ == "__main__":
    main()

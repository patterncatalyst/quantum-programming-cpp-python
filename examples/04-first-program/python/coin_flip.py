"""The same first program in Qiskit: a Hadamard, a measurement, and many shots
on the Aer simulator. Where Chapter 3 read an exact state vector, here we sample
the circuit the way a real quantum program does and count the outcomes.
"""

from __future__ import annotations

from qiskit import QuantumCircuit
from qiskit_aer import AerSimulator


def coin_flip_counts(shots: int) -> tuple[int, int]:
    """Run the one-qubit coin-flip circuit and return (zeros, ones)."""
    qc = QuantumCircuit(1, 1)
    qc.h(0)              # equal superposition
    qc.measure(0, 0)     # collapse and record into classical bit 0

    result = AerSimulator().run(qc, shots=shots).result()
    counts = result.get_counts()
    return counts.get("0", 0), counts.get("1", 0)


def main() -> None:
    shots = 1000
    zeros, ones = coin_flip_counts(shots)
    print(f">> Quantum coin flip: H then measure, {shots} shots")
    print(f"0: {zeros}")
    print(f"1: {ones}")


if __name__ == "__main__":
    main()

"""Entanglement in Qiskit: the Bell pair, the GHZ state, and teleportation with
mid-circuit measurement and classically conditioned corrections. Each circuit is
sampled on Aer and reported as counts, mirroring the Quantum++ version.
"""

from __future__ import annotations

import math

from qiskit import ClassicalRegister, QuantumCircuit, QuantumRegister
from qiskit_aer import AerSimulator


def bell_counts(shots: int) -> dict[str, int]:
    qc = QuantumCircuit(2, 2)
    qc.h(0)
    qc.cx(0, 1)
    qc.measure([0, 1], [0, 1])
    return dict(AerSimulator().run(qc, shots=shots).result().get_counts())


def ghz_counts(shots: int) -> dict[str, int]:
    qc = QuantumCircuit(3, 3)
    qc.h(0)
    qc.cx(0, 1)
    qc.cx(1, 2)
    qc.measure([0, 1, 2], [0, 1, 2])
    return dict(AerSimulator().run(qc, shots=shots).result().get_counts())


def teleport_zero_count(theta: float, shots: int) -> int:
    """Teleport RY(theta)|0> to q2, undo the preparation there, measure q2.
    Returns how many shots measured q2 as 0 (should be all of them).
    """
    q = QuantumRegister(3)
    c0 = ClassicalRegister(1, "c0")
    c1 = ClassicalRegister(1, "c1")
    c2 = ClassicalRegister(1, "c2")
    qc = QuantumCircuit(q, c0, c1, c2)

    qc.ry(theta, 0)          # state to teleport
    qc.h(1)                  # Bell pair across q1, q2
    qc.cx(1, 2)
    qc.cx(0, 1)              # Bell measurement on q0, q1
    qc.h(0)
    qc.measure(0, c0)
    qc.measure(1, c1)
    with qc.if_test((c1, 1)):  # correction: X on q2 if c1 set
        qc.x(2)
    with qc.if_test((c0, 1)):  # correction: Z on q2 if c0 set
        qc.z(2)
    qc.ry(-theta, 2)         # undo preparation on the teleported qubit
    qc.measure(2, c2)

    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    # Keys are "c2 c1 c0"; the c2 field (leftmost) must be 0.
    return sum(n for key, n in counts.items() if key.split()[0] == "0")


def main() -> None:
    shots = 1000
    print(f">> Bell pair (H, CNOT), {shots} shots")
    for outcome, count in sorted(bell_counts(shots).items()):
        print(f"  {outcome}: {count}")

    print(f"\n>> GHZ state (3 qubits), {shots} shots")
    for outcome, count in sorted(ghz_counts(shots).items()):
        print(f"  {outcome}: {count}")

    ok = teleport_zero_count(math.pi / 3, shots)
    print(f"\n>> Teleportation of RY(pi/3)|0>, {shots} shots")
    print(f"  target returns to |0> after undo: {ok}/{shots}")


if __name__ == "__main__":
    main()

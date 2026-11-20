"""QAOA for MaxCut in Qiskit, mirroring the Quantum++ version: a p=1 circuit of a
cost layer (ZZ phase per edge) and a mixer (RX per qubit), with the two angles tuned
by a classical grid search to maximize the expected cut. Demonstrated on a triangle
(maximum cut 2).

Qiskit orders bitstrings with the highest-index qubit on the left, so for a key `s`
of length n, qubit q's bit is s[n - 1 - q].
"""

from __future__ import annotations

import math

from qiskit import QuantumCircuit
from qiskit.quantum_info import Statevector
from qiskit_aer import AerSimulator

Edge = tuple[int, int]
TRIANGLE: list[Edge] = [(0, 1), (1, 2), (0, 2)]


def cut_value(key: str, edges: list[Edge], n: int) -> int:
    """Edges whose endpoints get different bits, for a Qiskit bitstring key."""
    bit = {q: int(key[n - 1 - q]) for q in range(n)}
    return sum(1 for u, v in edges if bit[u] != bit[v])


def build_qaoa(edges: list[Edge], n: int, gamma: float, beta: float) -> QuantumCircuit:
    qc = QuantumCircuit(n, n)
    qc.h(range(n))
    for u, v in edges:  # cost layer: exp(-i gamma Z_u Z_v)
        qc.rzz(2 * gamma, u, v)
    for q in range(n):  # mixer: exp(-i beta X)
        qc.rx(2 * beta, q)
    return qc


def expected_cut(edges: list[Edge], n: int, gamma: float, beta: float) -> float:
    probs = Statevector(build_qaoa(edges, n, gamma, beta)).probabilities_dict()
    return sum(p * cut_value(key, edges, n) for key, p in probs.items())


def qaoa_optimize(edges: list[Edge], n: int, grid: int) -> tuple[float, float, float]:
    best = (0.0, 0.0, -1.0)
    for i in range(grid + 1):
        for j in range(grid + 1):
            g, b = math.pi * i / grid, math.pi * j / grid
            e = expected_cut(edges, n, g, b)
            if e > best[2]:
                best = (g, b, e)
    return best


def qaoa_sample(
    edges: list[Edge], n: int, gamma: float, beta: float, shots: int
) -> tuple[str, int, float]:
    qc = build_qaoa(edges, n, gamma, beta)
    qc.measure(range(n), range(n))
    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    top = max(counts, key=counts.get)
    return top, cut_value(top, edges, n), counts[top] / shots


def main() -> None:
    n, shots = 3, 2000
    gamma, beta, exp_cut = qaoa_optimize(TRIANGLE, n, 40)
    bits, cut, fraction = qaoa_sample(TRIANGLE, n, gamma, beta, shots)
    print(">> QAOA MaxCut on a triangle (max cut = 2)")
    print(f"best gamma = {gamma:.3f}, beta = {beta:.3f}")
    print(f"expected cut = {exp_cut:.3f}")
    print(f"most-sampled {bits} with cut {cut} (fraction {fraction:.3f})")


if __name__ == "__main__":
    main()

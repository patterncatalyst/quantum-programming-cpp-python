"""Shor's algorithm in Qiskit: factor N by order-finding, mirroring the Quantum++
version. The quantum step is phase estimation on the modular-multiplication gate
U_a|y> = |a*y mod N>, built here as the explicit permutation unitary (exact, and
tiny on a simulator). Continued fractions then recover the order r, and a classical
gcd splits N. Demonstrated on N = 15, a = 7 (order 4).
"""

from __future__ import annotations

import math
from fractions import Fraction

import numpy as np
from qiskit import QuantumCircuit, transpile
from qiskit.circuit.library import UnitaryGate
from qiskit_aer import AerSimulator


def mul_mod_matrix(mul: int, N: int, m: int) -> np.ndarray:
    """Permutation matrix for |y> -> |(mul*y) mod N> on m qubits (index = value)."""
    dim = 1 << m
    matrix = np.zeros((dim, dim))
    for y in range(dim):
        image = (mul * y) % N if y < N else y
        matrix[image, y] = 1.0
    return matrix


def inverse_qft(qc: QuantumCircuit, n: int) -> None:
    """Inverse QFT on qubits 0..n-1, no final swaps (matches Chapter 9)."""
    for j in reversed(range(n)):
        for k in reversed(range(j + 1, n)):
            qc.cp(-math.pi / 2 ** (k - j), k, j)
        qc.h(j)


def order_from_measurement(value: int, t: int, N: int) -> int:
    """Denominator of the best continued-fraction convergent of value/2^t below N."""
    frac = Fraction(value, 1 << t).limit_denominator(N - 1)
    return frac.denominator


def order_finding_counts(a: int, N: int, t: int, m: int, shots: int) -> dict[int, int]:
    qc = QuantumCircuit(t + m, t)
    qc.x(t)  # target register = |1> (qubit t is the least significant)
    for j in range(t):
        qc.h(j)
    targets = list(range(t, t + m))
    for j in range(t):
        mul = pow(a, 2**j, N)  # a^(2^j) mod N
        controlled = UnitaryGate(mul_mod_matrix(mul, N, m)).control(1)
        qc.append(controlled, [j, *targets])
    inverse_qft(qc, t)
    qc.measure(range(t), range(t))

    sim = AerSimulator()
    compiled = transpile(qc, sim)  # decompose the controlled unitary to basis gates
    raw = sim.run(compiled, shots=shots).result().get_counts()
    values: dict[int, int] = {}
    for key, n in raw.items():
        # The t leftmost characters are the counting register, MSB first; reverse to
        # read qubit 0 as the MSB (matching the C++ value assembly).
        value = int(key.replace(" ", "")[:t][::-1], 2)
        values[value] = values.get(value, 0) + n
    return values


def shor_factor(a: int, N: int, t: int, m: int, shots: int) -> tuple[int, int]:
    # Classical first step: if a and N already share a factor, we are done.
    common = math.gcd(a, N)
    if 1 < common < N:
        return common, N // common

    for value in sorted(order_finding_counts(a, N, t, m, shots)):
        if value == 0:
            continue
        r = order_from_measurement(value, t, N)
        if r == 0 or pow(a, r, N) != 1 or r % 2 != 0:
            continue
        x = pow(a, r // 2, N)
        if x == N - 1:
            continue
        g1, g2 = math.gcd(x - 1, N), math.gcd(x + 1, N)
        if 1 < g1 < N:
            return g1, N // g1
        if 1 < g2 < N:
            return g2, N // g2
    return 1, N


def main() -> None:
    N, a, t, m, shots = 15, 7, 4, 4, 2000
    print(f">> Shor's algorithm: factor {N} with base a = {a}")
    print(f"phase-estimation outcomes (value/{1 << t}):")
    for value, count in sorted(order_finding_counts(a, N, t, m, shots).items()):
        print(f"  {value}/{1 << t}  count={count}")
    p, q = shor_factor(a, N, t, m, shots)
    print(f"{N} = {p} x {q}")


if __name__ == "__main__":
    main()

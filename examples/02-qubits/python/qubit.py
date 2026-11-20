"""A single qubit built from scratch with NumPy: a two-element complex vector and
the gates as 2x2 matrices. The Python cross-check for the C++ from-scratch qubit.
"""

from __future__ import annotations

import numpy as np

INV_SQRT2 = 1.0 / np.sqrt(2.0)
H = np.array([[INV_SQRT2, INV_SQRT2], [INV_SQRT2, -INV_SQRT2]], dtype=complex)
X = np.array([[0, 1], [1, 0]], dtype=complex)
KET0 = np.array([1, 0], dtype=complex)
KET1 = np.array([0, 1], dtype=complex)


def apply_gate(gate: np.ndarray, state: np.ndarray) -> np.ndarray:
    return gate @ state


def probabilities(state: np.ndarray) -> np.ndarray:
    return np.abs(state) ** 2


def main() -> None:
    psi = apply_gate(H, KET0)
    p = probabilities(psi)
    print(">> Single qubit, built from scratch (NumPy)")
    print("state:", psi)
    print(f"P(0) = {p[0]:.3f}, P(1) = {p[1]:.3f}")

    rng = np.random.default_rng(12345)
    shots = 1000
    zeros = int(np.sum(rng.random(shots) < p[0]))
    print(f"measured over {shots} shots: |0>={zeros}, |1>={shots - zeros}")


if __name__ == "__main__":
    main()

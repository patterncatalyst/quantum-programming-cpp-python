---
title: "The variational quantum eigensolver"
order: 11
part: "Hybrid & Variational"
description: "Find a Hamiltonian's lowest energy by tuning a parameterized circuit with a classical optimizer: the variational principle, the energy expectation, and the loop, in Quantum++ and Qiskit."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- State the variational principle and why it makes optimization safe.
- Compute the energy of a parameterized state under a Hamiltonian.
- Run the quantum-classical loop that drives that energy down to the ground state.

## Why this matters

The algorithms in Part 3 need deep, exact circuits that today's noisy hardware cannot
run. Variational algorithms are the response: keep the quantum circuit shallow and let
a classical optimizer do the heavy lifting. VQE, the variational quantum eigensolver,
finds the lowest eigenvalue of a Hamiltonian, which in chemistry is a molecule's
ground-state energy. It is one of the most likely near-term uses of a quantum
computer, and it introduces the hybrid loop that QAOA in the next chapter reuses.

## The variational principle

For any state $|\psi\rangle$, the energy $\langle\psi|H|\psi\rangle$ is at least the
smallest eigenvalue of $H$. So if you can prepare a family of states $|\psi(\theta)\rangle$
and measure their energy, you can never undershoot the ground energy, and driving the
energy down can only move you toward it. That is what makes the optimization safe: the
true answer is a floor you approach from above.

## The loop

VQE alternates a quantum step and a classical step:

- **Quantum:** prepare $|\psi(\theta)\rangle$ with a parameterized circuit (the
  *ansatz*) and measure its energy under $H$.
- **Classical:** adjust $\theta$ to lower the energy, and repeat.

{% include excalidraw.html file="vqe-loop" alt="A loop: a classical optimizer proposes parameters theta, a quantum circuit prepares the ansatz and measures the energy, and the energy is returned to the optimizer to propose better parameters" %}

The worked example is a one-qubit Hamiltonian $H = c_1 X + c_2 Z$ with the ansatz
$R_Y(\theta)|0\rangle$, whose ground energy is exactly $-\sqrt{c_1^2 + c_2^2}$:

```cpp
ket psi = apply(0_ket, gt.RY(theta), {0});          // the ansatz
double e = std::real((psi.adjoint() * H * psi)(0, 0));  // its energy
```

With one parameter the "optimizer" is a sweep of $\theta$; a real VQE uses a
gradient-based optimizer over many parameters.

```text
[cpp]$ ./vqe
>> VQE for H = 0.5000 X + 1.0000 Z
best theta   = 3.6065
VQE energy   = -1.1180
exact ground = -1.1180
```

The energy bottoms out at $-1.118 = -\sqrt{1.25}$, the exact ground energy. On a
simulator the expectation is read from the state vector; on hardware it is estimated
by measuring the state many times in the right bases.

## The same solver in Qiskit

Qiskit represents the Hamiltonian as a `SparsePauliOp` and reads the energy with
`Statevector.expectation_value`:

```python
H = SparsePauliOp.from_list([("X", c1), ("Z", c2)])
qc = QuantumCircuit(1); qc.ry(theta, 0)
e = Statevector.from_instruction(qc).expectation_value(H).real
```

```text
[py]$ python vqe.py
>> VQE for H = 0.5 X + 1.0 Z
best theta   = 3.6065
VQE energy   = -1.1180
exact ground = -1.1180
```

## Cross-check

Both libraries find the same minimum energy, $-1.118$, at the same angle, and both
match the exact smallest eigenvalue computed independently by diagonalizing $H$. The
variational principle holds in the numbers: the swept energy never dips below the true
ground energy, it only reaches it.

## What you learned

VQE finds a Hamiltonian's lowest eigenvalue by minimizing the energy of a
parameterized state, with a quantum step that prepares the state and measures its
energy and a classical step that tunes the parameters. The variational principle keeps
the search honest: the ground energy is a floor. The next chapter applies the same
hybrid loop to combinatorial optimization.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that the solver reaches the exact
ground energy $-\sqrt{c_1^2 + c_2^2}$ within the grid resolution and never dips below
it, for two Hamiltonians, in both GoogleTest and pytest.

## For deeper coverage

- [Variational quantum eigensolver](https://en.wikipedia.org/wiki/Variational_quantum_eigensolver)
  — the method, ansatz choices, and chemistry applications.
- [Variational principle](https://en.wikipedia.org/wiki/Variational_method_(quantum_mechanics))
  — why the energy expectation bounds the ground state from above.

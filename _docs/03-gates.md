---
title: "Gates and circuits"
order: 3
part: "Foundations"
description: "Single-qubit gates as unitary matrices, multi-qubit gates that entangle, and circuits as sequences of gates, shown with Quantum++ and Qiskit."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Say what the X, Z, and H gates do to a qubit.
- Explain why CNOT entangles two qubits and how a circuit composes gates.
- Build and read small circuits with Quantum++ and Qiskit.

## Why this matters

In [Chapter 2]({{ '/docs/02-qubits/' | relative_url }}) you applied a gate by
writing out a matrix-vector product. That is the right mental model, but nobody
wants to hand-multiply matrices for a ten-qubit circuit. From here on the frameworks
do the arithmetic. This chapter introduces the handful of gates the algorithms later
in the book are built from, and shows a circuit as what it is: an ordered list of
gates applied to a register of qubits.

## Single-qubit gates

Every quantum gate is a **unitary** matrix, which is the property that keeps total
probability at one. Three single-qubit gates come up constantly:

- **X** is the quantum NOT. It swaps the amplitudes of `|0>` and `|1>`, so `X|0> =
  |1>`.
- **Z** leaves `|0>` alone and multiplies `|1>` by `-1`. It does nothing you can see
  by measuring one qubit on its own, but that sign matters once the qubit is in
  superposition or entangled.
- **H**, the Hadamard from Chapter 2, creates an equal superposition.

With Quantum++ the gates live in a `gt` object and `apply` runs them:

```cpp
std::cout << disp(apply(0_ket, gt.X, {0})) << "\n";   // X|0>
std::cout << disp(apply(1_ket, gt.Z, {0})) << "\n";   // Z|1>
```

```text
[cpp]$ ./gates
X|0> = |1>:
0
1

Z|1> = -|1>:
 0
-1
```

`X|0>` is `(0, 1)`, which is `|1>`. `Z|1>` is `(0, -1)`: the same basis state with a
flipped sign, the phase that Z introduces.

## Multi-qubit gates and entanglement

Two qubits have four basis states (`|00>`, `|01>`, `|10>`, `|11>`), so their state
is a four-element vector and a two-qubit gate is a $4\times4$ matrix. The key one is
**CNOT** (controlled-NOT): it flips the second qubit only when the first is `1`.

Apply H to the first qubit and then CNOT, and you get the Bell state from Chapter 0.
A **circuit** is just this sequence of gates:

```cpp
ket psi = 00_ket;
psi = apply(psi, gt.H, {0});        // superpose qubit 0
psi = apply(psi, gt.CNOT, {0, 1});  // entangle qubit 1 with it
```

```text
>> Two-qubit circuit: H on q0, then CNOT(0 -> 1)
0.707107
       0
       0
0.707107
```

The state has equal amplitude on `|00>` and `|11>` and zero on the mixed outcomes.
That is entanglement: the two qubits are now correlated, and measuring one tells you
the other.

## The same circuits in Qiskit

Qiskit builds a circuit object and can report the exact state vector with
`Statevector`, which lets us compare amplitudes directly rather than sampling:

```python
def bell():
    qc = QuantumCircuit(2)
    qc.h(0)
    qc.cx(0, 1)
    return Statevector.from_int(0, 4).evolve(qc).data
```

```text
[py]$ python gates.py
>> Single-qubit gates (Qiskit)
X|0> = [0.+0.j 1.+0.j]
Bell = [0.707+0.j 0.   +0.j 0.   +0.j 0.707+0.j]
```

## Cross-check

Quantum++ and Qiskit agree amplitude for amplitude: `X|0>` is `|1>` in both, and the
Bell circuit gives `(0.707, 0, 0, 0.707)` in both. Reading the exact state vector on
each side, rather than sampling, makes the comparison precise: the two libraries
implement the same gates and the same composition rules.

## What you learned

Gates are unitary matrices: X flips, Z adds a phase, H superposes, and CNOT
entangles. A circuit is an ordered sequence of gates on a register, and two
libraries in two languages produce identical state vectors for the same circuit.
These few gates are the vocabulary for the algorithms in the chapters ahead.

## Verification status

Verified on a Fedora 45 workstation: both programs run, and the GoogleTest and
pytest checks assert that `X` flips `|0>` to `|1>` and that H then CNOT produces the
Bell state in both languages.

## For deeper coverage

- [Quantum++ documentation](https://github.com/softwareQinc/qpp/wiki) — the gate set
  and the `apply` interface.
- [Qiskit `Statevector`](https://docs.quantum.ibm.com/api/qiskit/qiskit.quantum_info.Statevector)
  — reading exact states from a circuit.

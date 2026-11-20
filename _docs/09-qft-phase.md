---
title: "The QFT and phase estimation"
order: 9
part: "Algorithms"
description: "The quantum Fourier transform and the phase-estimation routine built on it, recovering the phase of a gate's eigenvalue into a counting register, in Quantum++ and Qiskit."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- Say what the quantum Fourier transform does and where its inverse is used.
- Build the phase-estimation circuit: Hadamards, controlled powers, inverse QFT.
- Recover a known eigenphase into a counting register and read it as a binary fraction.

## Why this matters

Phase estimation is the engine inside the famous exponential-speedup algorithms,
Shor's among them. It answers one question: given a gate $U$ and one of its
eigenvectors $|\psi\rangle$ with $U|\psi\rangle = e^{2\pi i\varphi}|\psi\rangle$,
what is $\varphi$? The answer comes out as the binary digits of $\varphi$ in a
register of counting qubits, and the step that turns accumulated phases into those
digits is the inverse quantum Fourier transform. Get this chapter and the next one,
Shor, is mostly bookkeeping on top of it.

## The quantum Fourier transform

The QFT is the quantum version of the discrete Fourier transform: it maps a basis
state $|x\rangle$ to a uniform superposition whose phases wind at a rate set by $x$.
On its own it is a change of basis; phase estimation uses its **inverse** to read a
phase that has been spread across a register back into plain binary. Quantum++
provides both as circuit operations, `QFT` and `TFQ` (the inverse).

## Phase estimation, step by step

The circuit has a register of $t$ counting qubits and the eigenstate qubit:

- Hadamard the counting qubits into a uniform superposition.
- Counting qubit $j$ controls $U^{2^j}$, so each qubit picks up the eigenphase
  multiplied by a different power of two. This is the array of phases the inverse QFT
  will decode.
- Apply the inverse QFT to the counting register and measure it.

{% include excalidraw.html file="phase-estimation-circuit" alt="A counting register through Hadamards, then each counting qubit controls a power of U acting on the eigenstate qubit, then an inverse QFT on the counting register feeds a measurement" %}

For a test case with a known answer, use the phase gate $P(2\pi\varphi)$, whose
eigenvector is $|1\rangle$ with eigenphase exactly $\varphi$:

```cpp
qc.gate(gt.X, eig);                       // prepare the |1> eigenstate
for (idx j = 0; j < t; ++j) qc.gate(gt.H, j);
for (idx j = 0; j < t; ++j)               // counting qubit j controls U^(2^j)
    qc.CTRL(phase_gate(theta * (1 << j)), j, eig);
qc.TFQ(counting, false);                  // inverse QFT, qubit 0 the MSB
```

```text
[cpp]$ ./phase_estimation
>> Phase estimation with 3 counting qubits, 1000 shots
phi = 0.125 -> value 1/8 = 0.125
phi = 0.25 -> value 2/8 = 0.25
phi = 0.375 -> value 3/8 = 0.375
phi = 0.5 -> value 4/8 = 0.5
```

Each phase that is an exact multiple of $1/2^t$ comes back exactly: three counting
qubits read $\varphi$ to three binary places, so $0.125 = 0.001_2$ reads as the
integer 1 over 8. A phase that is not an exact multiple would land on the nearest
few values instead, with most of the weight on the closest one.

## The same routine in Qiskit

Qiskit builds the inverse QFT from Hadamards and controlled phases (its `QFT` helper
is deprecated and the simulator does not run it as one instruction), then the loop is
the same:

```python
for j in range(t):
    qc.cp(theta * (2**j), j, t)   # controlled-U^(2^j) is a controlled phase
inverse_qft(qc, t)
```

```text
[py]$ python phase_estimation.py
>> Phase estimation with 3 counting qubits, 1000 shots
phi = 0.125 -> value 1/8 = 0.125
phi = 0.25 -> value 2/8 = 0.25
phi = 0.375 -> value 3/8 = 0.375
phi = 0.5 -> value 4/8 = 0.5
```

## Cross-check

Both libraries recover the same values for every phase, and both are exact for phases
that fit in three bits. One subtlety worth naming: the inverse QFT has a bit-ordering
convention (whether it swaps qubits at the end), and the counting-qubit order has to
match the order the controlled powers were applied. Here both sides disable the final
swap and read counting qubit 0 as the most significant bit, which is why the integers
line up across the two implementations.

## What you learned

Phase estimation writes the eigenphase of a gate into a counting register: Hadamards
spread the counting qubits, controlled powers of $U$ stamp the phase at power-of-two
rates, and the inverse QFT decodes those into binary digits. With $t$ counting qubits
you read $\varphi$ to $t$ bits. The next chapter points this exact machinery at a
modular-multiplication gate and factors a number with it.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that the three-bit estimate of
each phase in {0.125, 0.25, 0.375, 0.5} equals the exact value, in both GoogleTest
and pytest.

## For deeper coverage

- [Quantum Fourier transform](https://en.wikipedia.org/wiki/Quantum_Fourier_transform)
  — the transform and its circuit.
- [Quantum phase estimation](https://en.wikipedia.org/wiki/Quantum_phase_estimation_algorithm)
  — the routine, its precision, and the role of the inverse QFT.

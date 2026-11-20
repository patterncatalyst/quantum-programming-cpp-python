---
title: "Grover's search"
order: 8
part: "Algorithms"
description: "Find a marked item in an unstructured space of 2^n in about sqrt(2^n) steps, with a phase oracle and a diffusion operator that rotate amplitude onto the answer, in Quantum++ and Qiskit."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- Explain the two moves of a Grover iteration: the phase oracle and the diffusion operator.
- Say why the optimal number of iterations is about $(\pi/4)\sqrt{2^n}$.
- Run Grover and read the marked item off the measured counts.

## Why this matters

Searching an unsorted space of $N$ items takes $N/2$ tries on average classically.
Grover's algorithm finds the marked item in about $\sqrt{N}$ steps, a quadratic
speed-up that applies to any problem you can phrase as "recognise the answer when you
see it." It is also the clearest illustration of amplitude amplification, the idea of
steering probability toward the states you want, which shows up throughout quantum
computing.

## One Grover iteration

Start in the uniform superposition over all $2^n$ items (a Hadamard on each qubit).
Each iteration then does two things:

- **The oracle** flips the sign of the amplitude on the marked item, leaving every
  other amplitude alone. It recognises the answer without revealing it.
- **The diffusion operator** reflects every amplitude about their average, which turns
  the marked item's lone negative amplitude into a taller positive one.

{% include excalidraw.html file="grover-circuit" alt="A register of qubits through a layer of Hadamards, then a repeated block of oracle followed by diffusion, ending in measurement" %}

Each pair rotates the state a fixed angle toward the marked item, so the success
probability rises, peaks, and would fall again if you over-rotate. The peak is at
about $(\pi/4)\sqrt{2^n}$ iterations; for three qubits that is two.

## Building it with Quantum++

The marked-item oracle and the diffusion operator both end in a multi-controlled Z,
sandwiched between `X` gates (the oracle brackets the zeros of the target; diffusion
brackets all qubits):

```cpp
const idx iters = grover_iterations(n);   // (pi/4) * sqrt(2^n), floored
for (idx r = 0; r < iters; ++r) {
    grover_oracle(qc, target, n);         // flip the phase of |target>
    grover_diffusion(qc, n);              // reflect about the average
}
```

```text
[cpp]$ ./grover
>> Grover search for 101 among 8 items, 1000 shots
iterations: 2
most measured: 101  fraction = 0.967
```

Two iterations put 96.7% of the shots on `101`. The amplitude on the marked item is
now so much larger than the rest that a single measurement almost always returns it.

## The same search in Qiskit

Qiskit expresses the multi-controlled Z as a multi-controlled phase of $\pi$
(`mcp`), and the loop is identical:

```python
for _ in range(grover_iterations(n)):
    _oracle(qc, target, n)
    _diffusion(qc, n)
```

```text
[py]$ python grover.py
>> Grover search for 101 among 8 items, 1000 shots
iterations: 2
most measured: 101  fraction = 0.942
```

## Cross-check

Both libraries mark `101`, run two iterations, and land over 90% of the shots on it:
96.7% in C++ and 94.2% in Python, both close to the analytic optimum of about 94.5%
for three qubits. The small gap between runs is sampling noise; the structure, almost
all of the probability on the marked item, is identical.

## What you learned

Grover's search superposes, marks, and amplifies: the oracle flips the marked item's
phase and the diffusion operator reflects every amplitude about the average, together
rotating the state toward the answer by a fixed angle each round. After about
$(\pi/4)\sqrt{2^n}$ rounds the marked item dominates the measurement. The quadratic
speed-up is modest next to the exponential ones, but it is general, and the
amplitude-amplification idea behind it is everywhere.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that two iterations on three
qubits put over 90% of 2000 shots on the marked item for more than one target, and
that the iteration count for eight items is two, in both GoogleTest and pytest.

## For deeper coverage

- [Grover's algorithm](https://en.wikipedia.org/wiki/Grover%27s_algorithm) — the
  geometry of the rotation and the optimal iteration count.
- [Amplitude amplification](https://en.wikipedia.org/wiki/Amplitude_amplification) —
  the generalisation Grover is a special case of.

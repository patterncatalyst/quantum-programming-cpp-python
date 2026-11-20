---
title: "Your first quantum program"
order: 4
part: "First Programs"
description: "Build a circuit, run it on the simulator for many shots, and read the measured counts, with Quantum++ leading and Qiskit cross-checking."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Build a circuit with Quantum++'s `QCircuit` and run it on a `QEngine`.
- Explain what a shot is and why a quantum program's output is a set of counts.
- Run the same program in Qiskit and get the same distribution.

## Why this matters

Up to now you have read a circuit's exact state vector, amplitude by amplitude.
That is a privilege of simulation. A real quantum computer never hands you the
state; you prepare a circuit, run it, and get one classical outcome per run. Run
it many times and the outcomes pile up into counts that estimate the underlying
probabilities. This chapter writes a complete program in that style: the one you
would run on hardware, not just inspect in memory.

## The circuit

The program is a quantum coin. A Hadamard puts one qubit into an equal
superposition, and a measurement collapses it to 0 or 1 with equal probability.

{% include excalidraw.html file="coin-flip-circuit" alt="A single qubit wire passing through a Hadamard gate labelled H and then a measurement meter that writes to a classical bit" %}

## Building and running it with Quantum++

`QCircuit` holds the gates and measurements; `QEngine` runs the circuit and
accumulates results across many shots:

```cpp
QCircuit qc{1, 1};   // one qubit, one classical bit
qc.gate(gt.H, 0);    // put the qubit in an equal superposition
qc.measure(0, 0);    // collapse it and record the result in bit 0

QEngine engine{qc};
engine.execute(shots);
```

`engine.get_stats().data()` is a map from each outcome to how many times it came
up. Summing the map into zeros and ones and running 1000 shots gives:

```text
[cpp]$ ./coin_flip
>> Quantum coin flip: H then measure, 1000 shots
0: 506
1: 494
```

Close to 500 each, as a fair coin should be. The split is not exactly even, and
that is the point: counts are samples, not the exact probabilities.

## The same program in Qiskit

Qiskit builds the circuit the same way and runs it on the Aer simulator, which
also reports counts:

```python
def coin_flip_counts(shots: int) -> tuple[int, int]:
    qc = QuantumCircuit(1, 1)
    qc.h(0)
    qc.measure(0, 0)
    counts = AerSimulator().run(qc, shots=shots).result().get_counts()
    return counts.get("0", 0), counts.get("1", 0)
```

```text
[py]$ python coin_flip.py
>> Quantum coin flip: H then measure, 1000 shots
0: 495
1: 505
```

## Cross-check

Both programs run the identical circuit and both land near a 500/500 split: 506/494
in C++ and 495/505 in Python. Neither is exactly even, and they disagree in the
details, because each is an independent sample of the same fair coin. What they
agree on is the distribution they are drawn from.

## What you learned

A quantum program is a circuit you run, not a state you read. One run yields one
outcome; many runs yield counts that estimate the probabilities. Quantum++'s
`QCircuit`/`QEngine` and Qiskit's circuit/Aer pair express the same program and
produce the same distribution. The next chapter looks at exactly how those counts
relate to the amplitudes underneath.

## Verification status

Verified on a Fedora 45 workstation: both programs build and run, and the
GoogleTest and pytest checks assert that 1000 shots split with both outcomes above
350, so a circuit stuck on one result would fail.

## For deeper coverage

- [Quantum++ `QCircuit` and `QEngine`](https://github.com/softwareQinc/qpp/wiki) —
  the circuit-and-engine API.
- [Qiskit Aer](https://qiskit.github.io/qiskit-aer/) — the simulator backend and
  its `run`/`get_counts` interface.

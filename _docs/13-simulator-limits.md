---
title: "Simulator limits"
order: 13
part: "Going Further"
description: "Why a CPU simulator stops around 25 to 30 qubits: the state vector holds 2^n amplitudes, so memory doubles with every qubit, measured in Quantum++ and Qiskit."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Explain why simulating n qubits needs memory proportional to $2^n$.
- Estimate the state-vector size for a given qubit count.
- Say what the ceiling is on a workstation, and why specialized simulators can beat it
  for special circuits.

## Why this matters

Every circuit in this book ran on a simulator, and every simulator in this book stored
the full state vector. That is the honest limit of the approach: the state of $n$ qubits
is $2^n$ complex numbers, so the memory doubles with each qubit you add. Knowing where
the wall is keeps your examples runnable and sets expectations for what a laptop can and
cannot do.

## The exponential wall

{% include excalidraw.html file="exponential-wall" alt="Four boxes showing state-vector memory at 10, 20, 30, and 40 qubits (16 KiB, 16 MiB, 16 GiB, 16 TiB), each step multiplying by about 1000" %}

An $n$-qubit state vector has $2^n$ amplitudes, each a complex double of 16 bytes:

```cpp
inline std::uint64_t statevector_bytes(int n) {
    return (static_cast<std::uint64_t>(1) << n) * sizeof(std::complex<double>);
}
```

Measuring a GHZ state at growing sizes shows the memory column doubling each row:

```text
[cpp]$ ./simulator_limits
>> State-vector cost by qubit count (GHZ, 200 shots)
qubits   amplitudes        memory       sim time
   4             16        0.000 MiB      0.211 ms   (outcomes: 2)
   8            256        0.004 MiB      1.465 ms   (outcomes: 2)
  12           4096        0.062 MiB     18.499 ms   (outcomes: 2)
  16          65536        1.000 MiB    454.629 ms   (outcomes: 2)
  20        1048576       16.000 MiB  12419.370 ms   (outcomes: 2)
```

Twenty qubits is 16 MiB; thirty qubits is 16 GiB; forty qubits is 16 TiB. Memory, not
cleverness, is what stops a workstation around 25 to 30 qubits.

## Memory is the wall, time depends on the simulator

The memory doubling is a hard, universal limit for a dense state vector. Runtime is a
softer story: it depends on how the simulator works. Quantum++ above applies gates to
the full dense vector, so its time climbs steeply. The Qiskit run of the identical GHZ
circuit finishes in a few milliseconds even at 20 qubits:

```text
[py]$ python simulator_limits.py
  20        1048576       16.000 MiB      5.787 ms   (outcomes: 2)
```

That is not a contradiction. GHZ is a **Clifford** circuit, and Aer recognises it and
switches to a method that never builds the dense vector. For a general circuit that
trick does not apply and the $2^n$ memory cost returns. The lesson: the memory bound is
fundamental, while a good simulator can dodge the time cost for special structure.

## What you learned

Simulating $n$ qubits needs $2^n$ amplitudes, so memory doubles per qubit and a
workstation tops out near 25 to 30. That ceiling is why every example here stays small.
Runtime, unlike memory, depends on the simulator and the circuit: specialized methods
can be far faster on structured circuits, but none escape the memory wall in general.
That wall is exactly why real quantum hardware is interesting, which the rest of this
part turns to.

## Verification status

Verified on a Fedora 45 workstation: the tests assert the state-vector dimension is
$2^n$, that its byte size doubles with each added qubit, and that a 14-qubit GHZ still
has exactly two outcomes, in both GoogleTest and pytest.

## For deeper coverage

- [Quantum simulator](https://en.wikipedia.org/wiki/Quantum_simulator) — approaches and
  their memory and time trade-offs.
- [Gottesman-Knill theorem](https://en.wikipedia.org/wiki/Gottesman%E2%80%93Knill_theorem)
  — why Clifford circuits (like GHZ) are efficiently simulable.

---
title: "QAOA for optimization"
order: 12
part: "Hybrid & Variational"
description: "Solve a combinatorial problem, MaxCut, by alternating a cost layer and a mixer and tuning their angles with a classical optimizer, then reading the answer from the measured counts, in Quantum++ and Qiskit."
duration: 25 minutes
---

## Learning objectives

By the end of this chapter you can:

- Encode a combinatorial problem (MaxCut) as a cost to maximize.
- Build the QAOA circuit: alternating cost and mixer layers.
- Tune the angles classically, then read the solution from the measured counts.

## Why this matters

QAOA, the quantum approximate optimization algorithm, is the sibling of VQE aimed at
combinatorial optimization: scheduling, routing, portfolio selection, anything you can
write as "maximize this count." It uses the same shallow-circuit, classically-tuned
loop, which makes it another leading candidate for near-term hardware. MaxCut, splitting
a graph's nodes into two groups to cut as many edges as possible, is its standard
proving ground.

## Encoding MaxCut

Give each node a qubit. A bit-string assigns each node to one side, and its **cut** is
the number of edges whose endpoints land on different sides. For a triangle the best
you can do is 2: any split leaves one edge uncut. QAOA searches for a bit-string that
maximizes the cut.

## The QAOA circuit

Start in a uniform superposition, then apply $p$ rounds of two layers:

- **Cost layer:** a $ZZ$ phase on each edge, $e^{-i\gamma Z_u Z_v}$, which rewards
  cut edges.
- **Mixer layer:** an $R_X(2\beta)$ on each qubit, which moves amplitude between
  bit-strings.

{% include excalidraw.html file="qaoa-circuit" alt="A register through Hadamards, then a cost layer of ZZ phases on the graph edges and a mixer layer of RX rotations, with a classical optimizer tuning the two angles, ending in measurement" %}

A classical optimizer tunes $\gamma$ and $\beta$ to maximize the expected cut; here
$p = 1$ and the two angles are found by a grid search:

```cpp
for (const auto& e : edges) {          // cost layer: ZZ phase per edge
    qc.CTRL(gt.X, e.u, e.v);
    qc.gate(gt.RZ(2.0 * gamma), e.v);
    qc.CTRL(gt.X, e.u, e.v);
}
for (idx i = 0; i < n; ++i) qc.gate(gt.RX(2.0 * beta), i);   // mixer
```

```text
[cpp]$ ./qaoa
>> QAOA MaxCut on a triangle (max cut = 2)
best gamma = 1.257, beta = 1.885
expected cut = 1.999
most-sampled 100 with cut 2 (fraction 0.175)
```

The tuned circuit has an expected cut of 1.999 out of 2, and sampling it returns a
bit-string that cuts both available edges. The probability spreads across the six
optimal bit-strings (every assignment except all-same), so no single one dominates, but
each is a maximum cut.

## The same optimizer in Qiskit

Qiskit has an `rzz` gate for the cost layer, and the rest matches:

```python
for u, v in edges:
    qc.rzz(2 * gamma, u, v)      # cost layer
for q in range(n):
    qc.rx(2 * beta, q)           # mixer
```

```text
[py]$ python qaoa.py
>> QAOA MaxCut on a triangle (max cut = 2)
best gamma = 2.827, beta = 1.885
expected cut = 1.999
most-sampled 110 with cut 2 (fraction 0.174)
```

## Cross-check

Both libraries reach an expected cut of 1.999 and sample a maximum cut as the most
likely outcome. The best angles differ between the two runs because the $ZZ$ phase is
periodic and the grid lands on different but equivalent optima; what matters, the
expected cut and the quality of the sampled solution, agrees.

## What you learned

QAOA solves combinatorial problems by encoding them as a cost to maximize, alternating a
cost layer and a mixer, and tuning the layer angles with a classical optimizer. The
answer comes out of the measured counts: the tuned circuit concentrates probability on
good bit-strings. With VQE, it rounds out the hybrid, near-term-friendly style of
quantum computing.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that `cut_value` scores known
bit-strings correctly, that the optimized circuit's expected cut beats a trivial
baseline, and that the most-sampled bit-string is a maximum cut (value 2), in both
GoogleTest and pytest.

## For deeper coverage

- [Quantum approximate optimization algorithm](https://en.wikipedia.org/wiki/Quantum_optimization_algorithms#Quantum_approximate_optimization_algorithm)
  — the general $p$-layer construction and performance.
- [Maximum cut](https://en.wikipedia.org/wiki/Maximum_cut) — the problem QAOA is
  benchmarked on.

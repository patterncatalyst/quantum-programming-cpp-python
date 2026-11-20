---
title: "Measurement and sampling"
order: 5
part: "First Programs"
description: "How amplitudes become counts: a weighted coin shows the measured fraction converging on the squared amplitude as shots increase, in Quantum++ and Qiskit."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- State the Born rule: the probability of an outcome is its squared amplitude.
- Explain why more shots give a tighter estimate of those probabilities.
- Read the exact probability and the sampled fraction side by side and see them agree.

## Why this matters

The fair coin in [Chapter 4]({{ '/docs/04-first-program/' | relative_url }}) hid a
detail by being symmetric: a 50/50 split looks right whether you think in
amplitudes or in counts. Tilt the coin and the two views separate. The exact
probability is fixed by the state; the measured fraction is an estimate that wanders
around it and settles closer as you take more shots. Seeing that gap, and watching
it close, is the whole relationship between a quantum state and the data you get out
of it.

## A weighted coin

An `RY(theta)` rotation turns `|0>` into a superposition whose weights you choose.
After `RY(theta)` the probability of measuring 1 is $\sin^2(\theta/2)$. Picking
$\theta = \pi/3$ puts exactly a quarter of the probability on 1.

{% include excalidraw.html file="weighted-coin-circuit" alt="A single qubit wire through an RY of theta rotation gate and then a measurement meter writing to a classical bit" %}

## Amplitudes and counts in Quantum++

Reading the exact state gives the probability; sampling the circuit estimates it.
Running at two shot counts shows the estimate tightening:

```cpp
const double theta = std::numbers::pi / 3.0;  // tilts P(1) to 0.25
const double p_one = scratch::prob_one_exact(theta);
for (qpp::idx shots : {100, 10000}) {
    auto [zeros, ones] = scratch::weighted_coin_counts(theta, shots);
    // measured P(1) = ones / shots
}
```

```text
[cpp]$ ./weighted_coin
>> Weighted coin: RY(pi/3) then measure
exact P(1) = 0.250

100 shots: 0=75 1=25  measured P(1) = 0.250
10000 shots: 0=7504 1=2496  measured P(1) = 0.250
```

The exact probability is 0.250, and both runs land on it here. Small shot counts
will not always be this kind; the next run in Python shows the noise plainly.

## The same measurement in Qiskit

Qiskit reads the exact probability from `Statevector` and samples with Aer:

```python
def prob_one_exact(theta: float) -> float:
    qc = QuantumCircuit(1)
    qc.ry(theta, 0)
    amp_one = Statevector.from_int(0, 2).evolve(qc).data[1]
    return float(abs(amp_one) ** 2)
```

```text
[py]$ python weighted_coin.py
>> Weighted coin: RY(pi/3) then measure
exact P(1) = 0.250

100 shots: 0=70 1=30  measured P(1) = 0.300
10000 shots: 0=7420 1=2580  measured P(1) = 0.258
```

Here 100 shots overshoot to 0.300 while 10000 shots pull back to 0.258. That is
sampling noise shrinking: the error on a fraction falls roughly as one over the
square root of the shot count, so ten times the data is about three times the
precision.

## Cross-check

Both libraries report the same exact probability, 0.250, because they implement the
same `RY` gate and the same Born rule. Their sampled fractions differ run to run and
differ from each other, exactly as independent estimates of one probability should,
and both close in on 0.250 as the shots grow.

## What you learned

A measurement outcome's probability is the squared amplitude of that outcome in the
state. Sampling estimates those probabilities, with error that shrinks as the square
root of the shot count. The exact value and the sampled fraction are two views of
one state, and they agree in both languages once you take enough shots.

## Verification status

Verified on a Fedora 45 workstation: the exact `P(1)` is asserted equal to 0.25, and
a 20000-shot run is asserted within 0.03 of it, in both GoogleTest and pytest.

## For deeper coverage

- [Qiskit `Statevector`](https://docs.quantum.ibm.com/api/qiskit/qiskit.quantum_info.Statevector)
  — reading exact probabilities from a circuit.
- [Born rule](https://en.wikipedia.org/wiki/Born_rule) — the measurement postulate
  behind squared-amplitude probabilities.

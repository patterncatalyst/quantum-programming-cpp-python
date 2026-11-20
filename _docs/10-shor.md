---
title: "Shor's algorithm"
order: 10
part: "Algorithms"
description: "Factor a number by finding the order of an element modulo N with phase estimation, then a classical gcd, demonstrated on N = 15 in Quantum++ and Qiskit."
duration: 30 minutes
---

## Learning objectives

By the end of this chapter you can:

- Explain how factoring reduces to finding the order of an element modulo N.
- Run phase estimation on the modular-multiplication gate to measure a multiple of 1/r.
- Recover the order with continued fractions and finish the factoring classically.

## Why this matters

Shor's algorithm is the reason quantum computing draws so much attention: it factors
large numbers in polynomial time, which would break RSA. The algorithm is mostly
classical number theory wrapped around a single quantum subroutine, order-finding,
which is phase estimation from the previous chapter applied to one particular gate.
Running it end to end on a small number shows exactly where the quantum speed-up sits
and how modest the quantum part actually is.

## Factoring as order-finding

To factor $N$, pick a base $a$ coprime to $N$ and find its **order** $r$, the smallest
$r$ with $a^r \equiv 1 \pmod N$. If $r$ is even and $a^{r/2} \not\equiv -1$, then
$a^{r/2} \pm 1$ share a non-trivial factor with $N$, which $\gcd$ extracts. Everything
here is classical except finding $r$, and that is the hard part classically.

For $N = 15$ and $a = 7$: the order is 4 (since $7^4 = 2401 \equiv 1 \pmod{15}$), so
$a^{r/2} = 7^2 = 49 \equiv 4$, and $\gcd(4 - 1, 15) = 3$, $\gcd(4 + 1, 15) = 5$.

The code starts with a classical $\gcd(a, N)$ check: if the base already shares a
factor with $N$ you are done, and only a genuinely coprime base needs the quantum
order-finding step below.

## The quantum part: order-finding

The order is the period of the map $y \mapsto a\,y \bmod N$, and periods are what
phase estimation reads. Apply phase estimation to the modular-multiplication gate
$U_a|y\rangle = |a\,y \bmod N\rangle$ with the target register prepared in
$|1\rangle$; the measured counting value is $2^t \cdot s/r$ for a random $s$.

{% include excalidraw.html file="shor-circuit" alt="A counting register through Hadamards drives controlled powers of the modular-multiplication gate on a target register prepared in the one state, then an inverse QFT and measurement feed a classical continued-fraction and gcd step" %}

The modular-multiplication gate is used here as its explicit permutation matrix. That
is the exact operator and it is tiny on a simulator; a scalable circuit built from
adders exists but is not needed to see the algorithm work.

```cpp
qc.gate(gt.X, t + m - 1);                  // target register = |1>
for (idx j = 0; j < t; ++j) qc.gate(gt.H, j);
for (idx j = 0; j < t; ++j)                // controlled-U_a^(2^j)
    qc.CTRL(mul_mod_gate(mod_pow(a, 1 << j, N), N, m), j, target);
qc.TFQ(counting, false);                   // inverse QFT (Chapter 9)
```

```text
[cpp]$ ./shor
>> Shor's algorithm: factor 15 with base a = 7
phase-estimation outcomes (value/16):
  0/16  count=505
  4/16  count=497
  8/16  count=536
  12/16  count=462
15 = 3 x 5
```

The four outcomes are $0, 4, 8, 12$ over 16, which are $0, 1/4, 1/2, 3/4$: exactly the
$s/r$ for $r = 4$. The counting register has measured a multiple of $1/r$.

## From a measurement to a factor

A measured value like $4/16 = 1/4$ goes through continued fractions to recover the
denominator $r = 4$; outcomes that reduce to a smaller denominator (like $8/16 = 1/2$)
or to zero are discarded, and the run uses an informative one:

```cpp
const std::uint64_t r = order_from_measurement(value, t, N);   // continued fractions
if (mod_pow(a, r, N) == 1 && r % 2 == 0) {
    const std::uint64_t x = mod_pow(a, r / 2, N);
    // gcd(x - 1, N) and gcd(x + 1, N) are the factors
}
```

## The same algorithm in Qiskit

Qiskit builds $U_a$ as a `UnitaryGate` from the same permutation matrix, controls it,
and transpiles so the simulator can run it; the continued-fraction step is Python's
`Fraction.limit_denominator`:

```python
controlled = UnitaryGate(mul_mod_matrix(mul, N, m)).control(1)
qc.append(controlled, [j, *targets])
r = Fraction(value, 1 << t).limit_denominator(N - 1).denominator
```

```text
[py]$ python shor.py
>> Shor's algorithm: factor 15 with base a = 7
phase-estimation outcomes (value/16):
  0/16  count=511
  4/16  count=498
  8/16  count=488
  12/16  count=503
15 = 3 x 5
```

## Cross-check

Both libraries measure the same four phases, $0, 1/4, 1/2, 3/4$, recover $r = 4$ from
the informative ones, and factor $15 = 3 \times 5$. The quantum step is identical up to
each framework's qubit-ordering convention; the classical wrapper, continued fractions
and gcd, is the same number theory on both sides.

## What you learned

Shor's algorithm factors by order-finding: phase estimation on the
modular-multiplication gate measures a multiple of $1/r$, continued fractions recover
$r$, and a classical gcd turns an even order into a factor. The quantum subroutine is
exactly the phase estimation of the previous chapter pointed at one specific gate.
Simulating it caps out at small numbers, but the structure is the real algorithm.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that continued fractions recover
the order 4 from the informative measurements and that the full algorithm factors 15
into 3 and 5, in both GoogleTest and pytest.

## For deeper coverage

- [Shor's algorithm](https://en.wikipedia.org/wiki/Shor%27s_algorithm) — the reduction
  to order-finding and the continued-fraction post-processing.
- [Quantum phase estimation](https://en.wikipedia.org/wiki/Quantum_phase_estimation_algorithm)
  — the order-finding subroutine Shor is built on.

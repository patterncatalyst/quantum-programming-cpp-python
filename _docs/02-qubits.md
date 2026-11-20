---
title: "Qubits, state vectors, and measurement"
order: 2
part: "Foundations"
description: "Build a qubit from scratch as a vector of complex amplitudes, apply a gate as a matrix, and measure it by sampling, in C++ and NumPy, before any framework hides the mechanism."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Describe a qubit as a two-element vector of complex amplitudes.
- Turn amplitudes into measurement probabilities with the Born rule.
- Apply a gate as a matrix and sample a measurement, in C++ and NumPy, with no
  quantum library.

## Why this matters

Frameworks like Quantum++ and Qiskit are convenient precisely because they hide the
state vector. That hiding is a problem while you are still building intuition: it is
easy to call `h(0)` without any idea what it does to the numbers. So this chapter
uses no quantum library at all. A qubit is just a short vector, a gate is just a
matrix, and measurement is just sampling from a probability distribution. Once you
have written that by hand, the frameworks stop being magic.

## A qubit is two complex numbers

A classical bit is `0` or `1`. A qubit is a blend of both, written

$|\psi\rangle = \alpha\,|0\rangle + \beta\,|1\rangle$

where the **amplitudes** $\alpha$ and $\beta$ are complex numbers. On their own the
amplitudes are not probabilities. The **Born rule** says the probability of
measuring `0` is $|\alpha|^2$ and of measuring `1` is $|\beta|^2$, and because one
of those outcomes must happen, $|\alpha|^2 + |\beta|^2 = 1$.

So `|0>` is the vector $(1, 0)$ and `|1>` is $(0, 1)$. A gate that acts on one qubit
is a $2\times2$ matrix; applying it is a matrix-vector product.

## From scratch in C++

The whole model fits in a small header. A qubit is a two-element array of
`std::complex<double>`, a gate is a $2\times2$ array, and applying a gate is the
matrix-vector product written out:

```cpp
using Qubit = std::array<Complex, 2>;             // amplitudes of |0> and |1>
using Gate = std::array<std::array<Complex, 2>, 2>;

inline Qubit apply_gate(const Gate& g, const Qubit& s) {
    return {g[0][0] * s[0] + g[0][1] * s[1],
            g[1][0] * s[0] + g[1][1] * s[1]};
}
```

The **Hadamard** gate is the one that creates a superposition. Its matrix has
`1/sqrt(2)` in three corners and `-1/sqrt(2)` in the fourth. Applying it to `|0>`
should give equal amplitudes. The probabilities come straight from the Born rule
(`std::norm` on a complex number is its magnitude squared):

```cpp
Qubit psi = apply_gate(hadamard(), ket0);
double p0 = std::norm(psi[0]);   // |0.707|^2 = 0.5
double p1 = std::norm(psi[1]);
```

Measurement is sampling. Draw a uniform number in `[0, 1)`; if it is below `p0`, the
outcome is `0`, otherwise `1`:

```cpp
std::mt19937 rng(12345);
std::uniform_real_distribution<double> u(0.0, 1.0);
for (int i = 0; i < shots; ++i) {
    if (u(rng) < p0) ++zeros;
}
```

Running it:

```text
[cpp]$ ./qubit
>> Single qubit, built from scratch
state: (0.707107,0) |0> + (0.707107,0) |1>
P(0) = 0.5, P(1) = 0.5
measured over 1000 shots: |0>=517, |1>=483
```

The state is an exact equal superposition; the sampled counts land near 500 each.

## The same thing in NumPy

The Python version is the same math with NumPy doing the matrix-vector product and
`np.abs(state) ** 2` applying the Born rule:

```python
H = np.array([[INV_SQRT2, INV_SQRT2], [INV_SQRT2, -INV_SQRT2]], dtype=complex)
KET0 = np.array([1, 0], dtype=complex)

psi = H @ KET0
p = np.abs(psi) ** 2            # [0.5, 0.5]
```

```text
[py]$ python qubit.py
>> Single qubit, built from scratch (NumPy)
state: [0.70710678+0.j 0.70710678+0.j]
P(0) = 0.500, P(1) = 0.500
measured over 1000 shots: |0>=526, |1>=474
```

## Cross-check

Both languages produce the same state vector `(0.707, 0.707)` and the same
probabilities `0.5, 0.5`. The measured counts differ between the two runs and from
each other, because each samples its own random draws, but both sit near 500. The
amplitudes are exact and reproducible; the counts are a finite-sample estimate of
them. That distinction, exact state versus sampled measurement, is the same one you
met in Chapter 1, now written out by hand on both sides.

## What you learned

A qubit is a two-element complex vector, a gate is a matrix, measurement is sampling
from `|amplitude|^2`, and normalization keeps the probabilities summing to one. You
wrote all of it twice, with nothing but the standard library and NumPy. Every
framework in this book automates exactly these steps.

## Verification status

Verified on a Fedora 45 workstation: both programs run, and the GoogleTest and
pytest checks assert the Hadamard probabilities are `0.5` each and that `X` flips
`|0>` to `|1>`.

## For deeper coverage

- [`std::complex`](https://en.cppreference.com/w/cpp/numeric/complex) and
  [`std::norm`](https://en.cppreference.com/w/cpp/numeric/complex/norm) — the C++
  complex-number tools used here.
- [NumPy linear algebra](https://numpy.org/doc/stable/reference/routines.linalg.html)
  — matrix-vector products and more.

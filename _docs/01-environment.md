---
title: "A tour of the two containers"
order: 1
part: "Foundations"
description: "What lives in the C++ and Python images, why each tool is there, and how the multi-stage build tests the code before it ever becomes an image."
duration: 15 minutes
---

## Learning objectives

By the end of this chapter you can:

- Name what each container provides and why.
- Explain the build-then-runtime shape of a multi-stage image.
- Run the environment check in both languages and read an equal superposition.

## Why this matters

In [Chapter 0]({{ '/docs/00-prerequisites/' | relative_url }}) you built two
containers and ran a Bell state in each. This chapter opens them up. Knowing what
is inside, and why, is the difference between treating the environment as a black
box and being able to change it with confidence when a later chapter needs a new
library.

## Two containers, two jobs

The C++ track and the Python track have different toolchains, so each gets its own
image. They never share a runtime; they only share the repository they are built
from.

### The C++ image

The C++ container (`containers/cpp/Containerfile`) carries a compiler toolchain and
a dependency manager:

- **GCC, CMake, and Ninja** build the code. CMake describes the build, Ninja runs
  it, and GCC compiles it. (Clang works too; the house default is whichever the
  base image makes easy.)
- **Conan** resolves third-party libraries. It fetches **Eigen** (the linear
  algebra library that Quantum++ is built on) and **GoogleTest** (the test
  framework), pinned to exact versions so a rebuild is reproducible.
- **Quantum++** (`qpp`) is the quantum library. It is header-only and not packaged
  on Conan Center, so the build pulls it straight from its release tag with CMake's
  `FetchContent`.

### The Python image

The Python container (`containers/python/Containerfile`) is simpler because the
quantum libraries ship as wheels:

- **uv** installs a managed **CPython 3.14** and resolves the dependencies from
  `pyproject.toml` against the locked `uv.lock`. The host's own Python is never
  touched, and the version is pinned regardless of what the base image ships.
- **Qiskit** and **Qiskit Aer** provide the circuits and the CPU simulator.

## The multi-stage shape

Both images are built in stages. A **build stage** installs the toolchain,
compiles the code, and runs the tests. A **runtime stage** copies only what it
needs to run. Because the tests run inside the build, a broken change fails the
image build instead of producing a broken image. You saw this in Chapter 0: the
C++ stage ends with `100% tests passed` and the Python stage ends with a green
`pytest`.

## Running the environment check

Each track has a tiny program that proves its library is wired up by putting a
single qubit into an equal superposition with a Hadamard gate.

The C++ version uses Quantum++:

```cpp
ket q = 0_ket;             // |0>
q = apply(q, gt.H, {0});   // Hadamard -> (|0> + |1>)/sqrt(2)
std::cout << disp(q) << "\n";
```

```text
[cpp]$ ./environment
>> C++ quantum environment is ready (Quantum++)
H|0> =
0.707107
0.707107
```

The two numbers are the amplitudes of `|0>` and `|1>`. Each is `1/sqrt(2)`, about
`0.707107`.

The Python version builds the same one-qubit circuit in Qiskit and measures it:

```python
qc = QuantumCircuit(1, 1)
qc.h(0)
qc.measure(0, 0)
counts = AerSimulator().run(qc, shots=1000).result().get_counts()
```

```text
[py]$ python environment.py
>> Python quantum environment is ready (Qiskit 2.6.2)
H|0> measured: {'0': 503, '1': 497}
```

## Cross-check

The two outputs look different on purpose. Quantum++ shows the exact **amplitudes**
of the state, while Qiskit **samples** measurements, so its counts land near 500
each and wobble from run to run. Both describe the same qubit: equal weight on `0`
and `1`. Squaring each C++ amplitude gives `0.5`, which is exactly the fraction of
shots Qiskit reports. Seeing the state both ways, exact and sampled, is a habit the
rest of the book leans on.

## What you learned

Each container is a small, explicit toolchain: a C++ build image that compiles and
tests against Eigen, GoogleTest, and Quantum++, and a Python image where uv pins
the interpreter and Qiskit provides the simulator. The multi-stage build tests the
code before the image exists, and both tracks agree on the physics of a single
qubit.

## Verification status

Verified on a Fedora 45 workstation: both environment programs build, run, and the
GoogleTest and pytest checks for the superposition pass.

## For deeper coverage

- [Conan documentation](https://docs.conan.io/) — the C++ dependency manager.
- [CMake FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
  — how the header-only Quantum++ library is pulled in.
- [uv documentation](https://docs.astral.sh/uv/) — managed Python and locking.

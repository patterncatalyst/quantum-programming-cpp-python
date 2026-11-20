---
title: "Setup: the containers and your first Bell state"
order: 0
part: "Prerequisites & Setup"
description: "Get a working C++ and Python quantum environment running in Docker, CPU only, and measure your first Bell state in both languages before writing any more code."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Confirm your Fedora host has the few tools this book needs.
- Build the two toolchain containers (C++ and Python) with one command.
- Run the same Bell state in C++ (Quantum++) and Python (Qiskit) and read the
  measured distribution.
- Explain why the Python track pins 3.14 even on a Fedora 45 host, and why none
  of this needs a GPU or a cloud account.

## Why this matters

Quantum programming material usually assumes a notebook, a cloud account, and
sometimes special hardware. None of that is true for learning. Every example in
this book runs on an ordinary Fedora workstation in a container, on the CPU, with
no account anywhere. Getting that environment right once, here, means every later
chapter is just "edit and run." This chapter is also the free sample, so it stands
on its own.

The shape of the project: **C++ is the primary track** and **Python is the
secondary track**, used to cross-check results and to drive tests. Each algorithm
leads in C++ with Quantum++ and is then shown in Python with Qiskit, producing the
same measured distribution. You read results as counts over a number of shots, and
you check them against what the math predicts, never against the exit code alone.

## Host prerequisites

The toolchains live inside the containers, so the host needs very little: Docker
Engine, the Compose plugin, and git. A helper script checks for them:

```text
[host]$ ./scripts/check-prereqs.sh
Checking host prerequisites...
ok:      docker (Docker version 29.10.0, build ...)
ok:      git (git version 2.56.1)
ok:      docker compose (5.8.0)
ok:      uv (uv 0.13.1 ...) [optional, local Python dev]
All required prerequisites are present.
```

`uv` is optional. You only need it if you want to run the Python examples directly
on the host for fast iteration; the container provides its own Python either way.
If Docker is missing, install Docker Engine for Fedora and add yourself to the
`docker` group, or run the commands with `sudo`.

## The two containers

Both images are **multi-stage** and built from a fully qualified Fedora base. The
containers run Fedora 44 regardless of your host's Fedora version, so the toolchain
is identical for every reader. The build stage compiles and tests; the runtime
stage carries only what it needs to run. Because tests run inside the build, an image is never produced from code that
fails.

- **`containers/cpp/Containerfile`** installs a C++ toolchain (GCC, CMake, Ninja)
  and Conan, resolves Eigen and GoogleTest from Conan, pulls the header-only
  Quantum++ library pinned to a release tag, builds the examples, and runs the
  tests with `ctest`.
- **`containers/python/Containerfile`** uses [uv](https://docs.astral.sh/uv/) to
  install a managed **CPython 3.14** and the Python quantum stack (Qiskit and the
  Aer simulator), then runs the tests with `pytest`.

### Why Python 3.14, not the host's 3.15

Fedora 45 ships Python 3.15 as the system interpreter. The quantum stack is not
fully ready for 3.15 yet (the PennyLane native simulator and CUDA-Q do not publish
3.15 wheels at the time of writing), so the book pins **3.14**. The container gets
3.14 from uv regardless of the host, and your system Python is never touched. When
the ecosystem catches up, this is a one-line change.

## Build and test everything

One command builds both images and runs both test suites:

```text
[host]$ docker compose build
```

The C++ stage ends with `100% tests passed`; the Python stage ends with a green
`pytest`. If either test fails, the build fails, and you see exactly which check
broke.

## Run your first Bell state

A Bell state is the smallest interesting quantum program: two qubits prepared so
that measuring them always gives `00` or `11`, with equal probability, and never
`01` or `10`. It is built by putting qubit 0 into superposition with a Hadamard
gate, then entangling it with qubit 1 through a controlled-NOT.

Run the C++ version:

```text
[host]$ docker compose run --rm cpp
0.707107
       0
       0
0.707107

>> Expected counts over 1000 shots (from the state):
  |00>: 499  (p=0.5)
  |11>: 499  (p=0.5)
```

The four numbers are the state vector: equal amplitude on `|00>` and `|11>`, zero
on the other two basis states. Quantum++ gives you the exact state, so the counts
are read straight from the probabilities.

Now the Python version:

```text
[host]$ docker compose run --rm python
>> Bell state measured counts (Qiskit Aer):
  |00>: 496
  |11>: 504
```

Qiskit's Aer simulator *samples* the circuit, so the counts wobble around 500 from
run to run. That difference is the point of having both tracks: C++ with Quantum++
exposes the underlying state directly, while Qiskit models the shot-by-shot
measurement you would see on real hardware. Both agree on the physics: only `00`
and `11`, each about half the time.

## Cross-check

Never trust "it ran." Each example checks its own result. The C++ test asserts the
amplitudes of `|00>` and `|11>` are each one half and the other two are zero; the
Python test asserts the measured counts contain only `00` and `11`, each near half
the shots. Both ran, and both passed, during `docker compose build`.

## What you learned

You have a reproducible, CPU-only quantum environment: two multi-stage containers,
one for C++ and one for Python, each building and testing itself, and you have run
the same Bell state in both. Everything from here is a variation on this loop: read
the concept, see the C++ first, cross-check in Python, measure, and compare against
the math.

## Teardown

To reclaim the space when you are done:

```text
[host]$ docker compose down --rmi local
[host]$ docker image rm quantum-cpp quantum-python 2>/dev/null || true
```

## Verification status

Verified on a Fedora 45 workstation: `check-prereqs.sh` passes, both images build
with their tests green, and both Bell-state programs produce the distribution
above. A figure for the Bell-state pipeline is planned for a later revision.

## For deeper coverage

- [Quantum++](https://github.com/softwareQinc/qpp) — the C++ quantum computing
  library used throughout the C++ track.
- [Qiskit documentation](https://docs.quantum.ibm.com/) — the Python framework and
  the Aer simulator.
- [uv documentation](https://docs.astral.sh/uv/) — the Python package and version
  manager used in the Python container.

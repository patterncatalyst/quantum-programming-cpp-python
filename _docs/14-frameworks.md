---
title: "Choosing a framework"
order: 14
part: "Going Further"
description: "Quantum++ and Qiskit produce the same results, so the choice is about ergonomics: a comparison of the two, with Cirq and PennyLane noted, plus a shared circuit that agrees across both."
duration: 20 minutes
---

## Learning objectives

By the end of this chapter you can:

- Compare Quantum++ and Qiskit on language, packaging, and intended use.
- Say when a C++ framework fits a project and when Python does.
- Confirm that both produce identical results for the same circuit.

## Why this matters

This book ran every algorithm twice, once in C++ with Quantum++ and once in Python with
Qiskit. They always agreed, because they implement the same mathematics. So the choice
between them is not about correctness; it is about how the tool fits the work around it:
the language your system is written in, how you ship it, and what you need from the
surrounding ecosystem.

## The same circuit, both ways

{% include excalidraw.html file="framework-choice" alt="Quantum++ and Qiskit both feeding into the same result, with a note that the choice is about fit rather than correctness" %}

A three-qubit circuit (H on q0, CNOT to q1, $R_Y(\pi/2)$ on q2) gives four equally
likely outcomes, and both frameworks report them identically:

```text
[cpp]$ ./framework_demo          [py]$ python framework_demo.py
  000: 0.250                       000: 0.250
  001: 0.250                       001: 0.250
  110: 0.250                       110: 0.250
  111: 0.250                       111: 0.250
```

With correctness settled, the difference is everything around the circuit.

## Quantum++ and Qiskit compared

| | Quantum++ (qpp) | Qiskit |
|---|---|---|
| Language | C++23, header-only | Python |
| Dependencies | Eigen, a C++ compiler | pip install, a Python runtime |
| Build | CMake + Conan (this book's setup; qpp is header-only) | none (interpreted) |
| Strengths | speed, embedding in C++ systems, no runtime | huge ecosystem, hardware access, fast to prototype |
| Hardware | simulator only | real devices via IBM Quantum |
| Best when | the system is already C++, or you need a library with no runtime | you want ecosystem, hardware, or quick iteration |

Two more Python options are worth knowing: **Cirq** (Google's framework, strong for
near-term devices) and **PennyLane** (built around differentiable circuits for quantum
machine learning). All of them express the same gate model; they differ in ergonomics
and ecosystem, not in the physics.

## How to choose

- **Already in C++?** Reach for Quantum++. It is header-only, links against Eigen, and
  adds no runtime, so it drops into an existing C++ codebase cleanly, which matters for
  the latency-sensitive, C++-heavy systems common in aerospace and financial services.
- **Prototyping, or need hardware?** Use Qiskit. The ecosystem, documentation, and the
  path to real devices are unmatched, and Python iteration is fast.
- **Teaching or cross-checking?** Use both, as this book does: agreement across two
  independent implementations is strong evidence a result is right.

## What you learned

Quantum++ and Qiskit, along with Cirq and PennyLane, implement the same gate model and
agree on results, so the decision is about fit: C++ for embedding and performance,
Python for ecosystem and hardware. Running a problem in two frameworks is also a
practical correctness check, which is why every chapter here did.

## Verification status

Verified on a Fedora 45 workstation: the tests assert that the shared three-qubit
circuit yields the four outcomes 000, 001, 110, 111 at 0.25 each in both GoogleTest and
pytest, confirming the two frameworks agree.

## For deeper coverage

- [Quantum++](https://github.com/softwareQinc/qpp) — the C++ library used throughout.
- [Qiskit](https://www.ibm.com/quantum/qiskit) — the Python framework and its ecosystem.
- [Cirq](https://quantumai.google/cirq) and
  [PennyLane](https://pennylane.ai/) — the other two Python options mentioned here.

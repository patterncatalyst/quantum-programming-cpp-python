# Quantum Programming in C++ and Python

A hands-on tutorial and book that teaches quantum programming with a **primary
C++ track** and a **secondary Python track** for contrast and testing. It runs
entirely on a normal Fedora workstation in Docker containers, CPU only: no GPU,
no cloud account, and no special hardware.

The material builds intuition from state vectors up before reaching for a
framework, and shows each algorithm in C++ (Quantum++, with CUDA-Q's CPU target
as a second option) cross-checked against Python (Qiskit and Aer, Cirq,
PennyLane).

## Status

Planning and scaffolding. The spike (confirm the toolchains build and run a Bell
state in-container) comes before any chapter prose. See `_plans/`.

## How it runs

- **Containers only**, Docker Engine + Docker Compose, multi-stage builds.
- **C++23** via Clang and CMake. **Python 3.14** managed by `uv` inside the build
  stage (the host system Python is left untouched).
- **CPU-only** simulation, with a qubit ceiling around 25 to 30 on a workstation.

## License

MIT, for both prose and code. See `LICENSE`.

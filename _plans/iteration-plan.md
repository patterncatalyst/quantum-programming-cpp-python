---
title: "Iteration plan"
layout: plan
render_with_liquid: false
---

# Iteration plan

Low-latency-style release rhythm: one `release/rNN` branch and PR per iteration,
squash-merged, tagged `rNN.x` on main. The spike gates all chapter prose.

| Iteration | Scope | Status |
|---|---|---|
| r00 | Site scaffold (Jekyll house style), parts, outline, this plan | in progress |
| r01 | Toolchain + containers: lgtm-cpp (Clang/CMake, Quantum++ via CMake), lgtm-python (uv, Python 3.14), lgtm-docker-stack (Docker Compose, multi-stage); Ch0 setup; `check-prereqs.sh` | planned |
| r02 | The spike: build a qpp Bell state (C++) and a matching Qiskit run (Python) in-container; benchmark the qubit ceiling; record in `spike-results.md` | planned |
| r03 | Part 1 Foundations: Ch1 environment tour, Ch2 qubits/state vectors/measurement, Ch3 gates and circuits | planned |
| r04 | Part 2 First Programs: Ch4 first C++ circuit (qpp), Ch5 same in Qiskit, Ch6 entanglement | planned |
| r05 | Part 3 Algorithms: Ch7 Deutsch-Jozsa/Bernstein-Vazirani, Ch8 Grover, Ch9 QFT/phase estimation, Ch10 Shor | planned |
| r06 | Part 4 Hybrid & Variational: Ch11 VQE, Ch12 QAOA | planned |
| r07 | Part 5 Going Further: Ch13 simulator limits, Ch14 framework comparison, Ch15 optional real hardware | planned |
| r08 | Appendix (linear algebra you need), post-quantum-vs-quantum sidebar, bibliography | planned |
| r09 | Companion deck via lgtm-presentation (decks last) | planned |

## Settled decisions

- C++ primary; Python secondary teaching track and test harness.
- C++ frameworks: Quantum++ (qpp, header-only, MIT) primary; CUDA-Q qpp-cpu second, via its image.
- Python: Qiskit + Aer, Cirq, PennyLane, pinned to Python 3.14 via uv.
- Containers only: Docker Engine + Docker Compose, multi-stage builds, tests in a build stage.
- Base image: Fedora base (fedora:44), fully qualified; uv provides Python 3.14 in the build stage.
- CPU-only simulation; qubit ceiling about 25 to 30; no GPU, no cloud account (except the optional final chapter).

## Open before chapter prose

- Spike must pass (r02): qpp and CUDA-Q build in-container; framework imports on 3.14 confirmed.
- Keep the optional real-QPU (IBM Quantum) chapter, or stay simulator-only.
- Revisit Python 3.15 once pennylane-lightning and CUDA-Q ship 3.15 wheels.
- Diagram pass: paired SVG + Excalidraw figures via lgtm-diagram-generator, including the Ch3 H+CNOT circuit (CLAUDE.md requires circuits as diagram + code), batched from r03.

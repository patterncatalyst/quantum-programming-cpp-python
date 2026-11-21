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
| r00 | Site scaffold (Jekyll house style), parts, outline, this plan | shipped |
| r01 | Toolchain + containers (lgtm-cpp, lgtm-python, lgtm-docker-stack), the verified spike (qpp Bell state + Qiskit cross-check in-container), and Ch0 setup | shipped |
| r02 | Part 1 Foundations: Ch1 environment tour, Ch2 qubits/state vectors/measurement, Ch3 gates and circuits | shipped |
| r03 | Part 2 First Programs: Ch4 first program (shots and counts), Ch5 measurement and sampling, Ch6 entanglement (Bell, GHZ, teleportation); circuit diagrams | shipped |
| r04 | Part 3 Algorithms (first half): Ch7 Deutsch-Jozsa/Bernstein-Vazirani, Ch8 Grover | shipped |
| r05 | Part 3 Algorithms (second half): Ch9 QFT/phase estimation, Ch10 Shor | shipped |
| r06 | Part 4 Hybrid & Variational: Ch11 VQE, Ch12 QAOA | shipped |
| r07 | Part 5 Going Further: Ch13 simulator limits, Ch14 framework comparison, Ch15 optional real hardware | shipped |
| r08 | Appendix (linear algebra you need), post-quantum-vs-quantum sidebar, bibliography | planned |
| r09 | Companion deck via lgtm-presentation (decks last) | planned |

> The spike was folded into r01 rather than taking its own iteration, so the
> numbering runs one ahead of the original outline from r02 on.

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
- Diagram pass: done in r03. Paired SVG + Excalidraw circuit figures (Bell, coin
  flip, weighted coin, teleportation) via `scripts/make_diagrams.py`, embedded in
  Chapters 3 to 6 and on the Diagrams page. Add algorithm-circuit figures as the
  r04+ chapters introduce them.

---
title: "Outline"
order: 0
overview: true
part: "Prerequisites & Setup"
description: "What this book covers and how it is organized: a primary C++ track with Python for contrast and testing, CPU-only and container-first."
---

This book teaches quantum programming with a **primary C++ track** and a
**secondary Python track** used for contrast and testing. Every algorithm leads in
C++ (Quantum++, with CUDA-Q's CPU target as a second option) and is cross-checked
against Python (Qiskit and Aer, Cirq, PennyLane). Everything runs on a normal
Fedora workstation in Docker containers, CPU only: no GPU, no cloud account, and
no special hardware.

Results are always reported as a measured distribution (counts over a stated
number of shots) and checked against the analytic expectation, never asserted. The
qubit ceiling is about 25 to 30 on a workstation, which is enough for every
algorithm in the outline.

The arc is below. Chapters link as they ship.

## Part 0: Prerequisites & Setup
- [Ch0 · Setup]({{ '/docs/00-prerequisites/' | relative_url }}): the Fedora host, Docker and Compose, the C++ and Python containers, uv-managed Python 3.14, `check-prereqs.sh`, and teardown (also the free sample)

## Part 1: Foundations
- [Ch1 · Environment tour]({{ '/docs/01-environment/' | relative_url }}): what is in each container and why
- [Ch2 · Qubits, state vectors and measurement]({{ '/docs/02-qubits/' | relative_url }}), built from scratch (C++ first, NumPy as the cross-check)
- [Ch3 · Quantum gates and circuits]({{ '/docs/03-gates/' | relative_url }})

## Part 2: First Programs
- [Ch4 · Your first quantum program]({{ '/docs/04-first-program/' | relative_url }}): a circuit, shots, and counts, in C++ (Quantum++) and Python (Qiskit)
- [Ch5 · Measurement and sampling]({{ '/docs/05-measurement/' | relative_url }}): the Born rule, and how more shots tighten the estimate
- [Ch6 · Entanglement]({{ '/docs/06-entanglement/' | relative_url }}): Bell states, GHZ, and teleportation

## Part 3: Algorithms
- [Ch7 · Deutsch-Jozsa and Bernstein-Vazirani]({{ '/docs/07-query-algorithms/' | relative_url }})
- [Ch8 · Grover's search]({{ '/docs/08-grover/' | relative_url }})
- [Ch9 · The Quantum Fourier Transform and phase estimation]({{ '/docs/09-qft-phase/' | relative_url }})
- [Ch10 · Shor's algorithm]({{ '/docs/10-shor/' | relative_url }}): a runnable demo that factors 15 by order-finding

## Part 4: Hybrid & Variational
- [Ch11 · VQE: the variational quantum eigensolver]({{ '/docs/11-vqe/' | relative_url }})
- [Ch12 · QAOA for optimization problems]({{ '/docs/12-qaoa/' | relative_url }})

## Part 5: Going Further
- [Ch13 · Simulator limits]({{ '/docs/13-simulator-limits/' | relative_url }}): why about 30 qubits on a CPU
- [Ch14 · Choosing a framework]({{ '/docs/14-frameworks/' | relative_url }}): Quantum++ and Qiskit, with Cirq and PennyLane noted
- [Ch15 · Optional: running on real hardware]({{ '/docs/15-real-hardware/' | relative_url }}) (IBM Quantum, free tier)

## Appendices
- [Appendix A · The linear algebra you need]({{ '/docs/16-appendix-linear-algebra/' | relative_url }})
- [Appendix B · Post-quantum cryptography is not quantum computing]({{ '/docs/17-appendix-post-quantum/' | relative_url }})
- [Appendix C · Glossary]({{ '/docs/18-appendix-glossary/' | relative_url }})
- [Appendix D · A guided demo]({{ '/docs/19-appendix-demo/' | relative_url }}): build the containers and run the Bell pair, Grover, and Shor yourself

## A note on "post-quantum"

Post-quantum cryptography (the ML-KEM and ML-DSA algorithms now shipping in
RHEL 10 and UBI) secures today's systems against a future quantum attacker. That
is a different subject from programming a quantum computer, which is what this book
is about. Appendix B clears up the confusion.

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
- Ch0 · Setup: the Fedora host, Docker and Compose, the C++ and Python containers, uv-managed Python 3.14, `check-prereqs.sh`, and teardown (also the free sample)

## Part 1: Foundations
- Ch1 · Environment tour: what is in each container and why
- Ch2 · Qubits, state vectors and measurement, built from scratch (C++ first, NumPy as the cross-check)
- Ch3 · Quantum gates and circuits

## Part 2: First Programs
- Ch4 · Your first circuit in C++ with Quantum++
- Ch5 · The same circuit in Python with Qiskit and Aer
- Ch6 · Entanglement: Bell states, GHZ, and teleportation

## Part 3: Algorithms
- Ch7 · Deutsch-Jozsa and Bernstein-Vazirani
- Ch8 · Grover's search
- Ch9 · The Quantum Fourier Transform and phase estimation
- Ch10 · Shor's algorithm (conceptual, with a small-number demo)

## Part 4: Hybrid & Variational
- Ch11 · VQE: the variational quantum eigensolver
- Ch12 · QAOA for optimization problems

## Part 5: Going Further
- Ch13 · Noise and simulator limits: why about 30 qubits on a CPU
- Ch14 · Framework comparison: Quantum++, CUDA-Q, Qiskit, Cirq
- Ch15 · Optional: running on real hardware (IBM Quantum, free tier)

## A note on "post-quantum"

Post-quantum cryptography (the ML-KEM and ML-DSA algorithms now shipping in
RHEL 10 and UBI) secures today's systems against a future quantum attacker. That
is a different subject from programming a quantum computer, which is what this book
is about. A short sidebar later in the book clears up the confusion.

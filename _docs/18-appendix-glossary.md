---
title: "Appendix C: Glossary"
order: 18
part: "Appendices"
appendix: "C"
description: "Plain-language definitions of the terms used throughout the book, from qubit and superposition to Hamiltonian, VQE, the Born rule, and post-quantum cryptography."
---

A quick reference for the vocabulary the chapters use. Definitions are deliberately
short and practical; the chapter that introduces each term goes deeper.

## Core ideas

| Term | Definition |
|---|---|
| Quantum | An adjective for the physics of the very small, where quantities like energy come in discrete units ("quanta") and systems can be in combinations of states at once. "Quantum computing" uses that physics to compute. |
| Quantum computing | Computing with qubits and quantum gates to solve problems a classical computer cannot solve efficiently. The subject of this book. |
| Qubit | A quantum bit: the basic unit of quantum information. Unlike a bit, it can be in a superposition of 0 and 1 until measured. |
| Superposition | A state that is a weighted combination of basis states at once, for example part 0 and part 1, rather than one definite value. |
| Amplitude | The (complex) weight of a basis state in a superposition. Its squared magnitude is the probability of that outcome. |
| State vector | The list of amplitudes describing a system. For n qubits it has 2^n entries, which is why simulation cost grows exponentially. |
| Gate | A reversible operation on qubits, represented by a unitary matrix. Examples: X, Z, H, CNOT. |
| Circuit | An ordered sequence of gates applied to a register of qubits, optionally ending in measurements. |
| Unitary | The property every gate has: its conjugate transpose is its inverse, so it preserves total probability and is reversible. A matrix is a legal gate only if it is unitary. See Appendix A. |
| Tensor product | How single-qubit states combine into a multi-qubit state; it is why n qubits need 2^n amplitudes. See Appendix A. |
| Entanglement | A correlation between qubits with no classical counterpart: measuring one instantly constrains the others. A Bell pair is the simplest example. |
| Bell state (Bell pair) | The simplest entangled state of two qubits; measured, it gives only 00 or 11, never 01 or 10. Built with a Hadamard and a CNOT. |
| GHZ state | An entangled state extending the Bell correlation to three or more qubits; measured, it gives only all-zeros or all-ones. |
| Quantum teleportation | Moving a qubit's state to another qubit using a shared Bell pair and two classical bits, without copying the state. |

## Common gates

| Term | Definition |
|---|---|
| Hadamard (H) | The superposition gate: it turns \|0> into an equal mix of 0 and 1. The usual first step in a circuit, and the reason a measured qubit can come out either way. |
| X (NOT) | The quantum NOT: it flips \|0> to \|1> and back. |
| Z | A phase flip: it leaves \|0> alone and flips the sign of \|1>. Invisible on its own, but it matters in superposition and entanglement. |
| CNOT (controlled-NOT) | A two-qubit gate that flips the target qubit when the control qubit is 1. The standard way to create entanglement. |
| Rotation gates (RX, RY, RZ) | Gates that rotate a qubit's state by a chosen angle about an axis. RY sets how much weight lands on 0 versus 1, which is how VQE and QAOA tune their circuits. |

## Measurement

| Term | Definition |
|---|---|
| Measurement | Reading a qubit, which collapses its superposition to a single classical outcome. |
| Born rule | The rule that the probability of an outcome equals the squared magnitude of its amplitude. |
| Shot | One run of a circuit, start to measurement, producing one outcome. |
| Counts | The tally of outcomes over many shots; how a quantum program's answer is reported and estimated. |

## Algorithms

| Term | Definition |
|---|---|
| Oracle | A black-box operation encoding a function the algorithm may query but not inspect; central to Deutsch-Jozsa, Bernstein-Vazirani, and Grover. |
| Phase kickback | The trick where an oracle stamps its answer onto the phase of the input qubits (rather than an output qubit), which a later layer of Hadamards turns into a measurable result. |
| Deutsch-Jozsa | An algorithm that decides in a single query whether a function is constant (same value everywhere) or balanced (0 on half its inputs, 1 on the other half). |
| Bernstein-Vazirani | An algorithm that recovers a hidden bit-string in a single query, where classically one query per bit is needed. |
| Grover's algorithm | A search that finds a marked item among N in about the square root of N steps, via amplitude amplification. |
| Amplitude amplification | Repeatedly steering probability toward the states you want; the engine behind Grover. |
| Diffusion operator | The second half of a Grover iteration: it reflects every amplitude about the average, amplifying the marked item the oracle flagged. |
| Quantum Fourier Transform (QFT) | The quantum analogue of the discrete Fourier transform; a change of basis used inside phase estimation. |
| Phase estimation | A routine that reads the phase of a gate's eigenvalue into a counting register. The core of Shor's algorithm. |
| Eigenphase | The phase φ in a gate's eigenvalue e^(2πiφ); the quantity phase estimation measures. |
| Shor's algorithm | A quantum algorithm that factors integers efficiently by order-finding; the reason post-quantum cryptography is needed. |
| Order-finding | Finding the smallest r with a^r = 1 (mod N); the quantum step inside Shor, solved with phase estimation. |
| Modular exponentiation | Computing a^x mod N; the operation Shor's order-finding is built on, applied here as a modular-multiplication circuit. |

## Hybrid and variational methods

| Term | Definition |
|---|---|
| Hamiltonian | The matrix whose eigenvalues are a system's possible energies. It is Hermitian, so those eigenvalues are real. VQE finds its smallest one. |
| Eigenvalue / eigenvector | For a matrix A, a vector v with A·v = λ·v is an eigenvector and λ its eigenvalue. Phase estimation and VQE both turn on these. |
| Ground state / ground energy | The lowest-energy eigenstate of a Hamiltonian and its energy; what VQE estimates. |
| Variational principle | The fact that the energy of any state is at least the ground energy, so minimizing it can only approach the true answer from above. |
| Ansatz | A parameterized circuit that prepares a family of trial states, tuned by a classical optimizer. |
| Expectation value | The average result of measuring an observable (such as energy) in a given state, written ⟨ψ\|H\|ψ⟩; what VQE minimizes and QAOA maximizes. |
| VQE | The variational quantum eigensolver: find a Hamiltonian's lowest eigenvalue by minimizing the energy of a parameterized state. |
| QAOA | The quantum approximate optimization algorithm: solve a combinatorial problem by alternating a cost layer and a mixer and tuning their angles. |
| Cost layer / mixer | The two layers of a QAOA round: the cost layer rewards good solutions (a phase per problem constraint), and the mixer moves amplitude between candidate solutions. |
| MaxCut | A benchmark optimization problem: split a graph's nodes into two groups to cut as many edges as possible. QAOA's standard demonstration. |

## Hardware and limits

| Term | Definition |
|---|---|
| Simulator | Software that computes a circuit's exact state or samples its outcomes on a classical computer. This book is simulator-first. |
| NISQ | Noisy intermediate-scale quantum: today's hardware, with limited qubits and no error correction, so only shallow circuits run usefully. |
| Clifford circuit | A restricted class of circuits (built from H, S, CNOT) that is efficiently simulable classically; GHZ is one, which is why some simulators run it fast. |
| Qubit ceiling | The practical simulation limit, about 25 to 30 qubits on a workstation, set by the 2^n memory of the state vector. |
| Decoherence | The loss of a qubit's quantum state through interaction with its environment; the main source of error on real hardware. |
| Fault-tolerant | A hardware regime with enough error correction to run deep circuits reliably; not yet achieved, and what a cryptography-breaking Shor run would require. |

## Cryptography (a related but separate subject)

| Term | Definition |
|---|---|
| Post-quantum cryptography (PQC) | Classical cryptography, run on ordinary CPUs, designed to resist attacks by a future quantum computer. Not quantum computing. See Appendix B. |
| RSA | A widely used public-key cryptosystem whose security rests on factoring being hard; broken by a large-enough Shor run, which is why PQC exists. |
| Elliptic-curve cryptography (ECC) | Public-key cryptography based on the discrete-logarithm problem on elliptic curves; like RSA, broken by Shor's algorithm. |
| ML-KEM | The standardized post-quantum key-encapsulation algorithm (NIST FIPS 203, formerly Kyber), lattice-based. |
| ML-DSA | The standardized post-quantum digital-signature algorithm (NIST FIPS 204, formerly Dilithium), lattice-based. |
| Harvest now, decrypt later | The threat of recording encrypted data today to decrypt once a quantum computer can break today's cryptography. |
| Quant | In finance, a quantitative analyst who builds mathematical models; unrelated to "quantum" despite the similar sound. Included here only to head off the confusion. |

## Frameworks and tools

| Term | Definition |
|---|---|
| Quantum++ | The header-only C++ quantum computing library used for this book's primary track. |
| Qiskit | IBM's Python quantum computing framework, used for the book's Python cross-check and for hardware access. |
| Qiskit Aer | Qiskit's high-performance simulator backend, used to sample circuits in the Python track. |
| Cirq | Google's Python quantum computing framework; a noted alternative. |
| PennyLane | A Python framework built around differentiable circuits for quantum machine learning; a noted alternative. |

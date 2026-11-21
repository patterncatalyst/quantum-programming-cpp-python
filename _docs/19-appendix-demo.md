---
title: "Appendix D: A guided demo"
order: 19
part: "Appendices"
appendix: "D"
description: "Run the companion demo yourself: build the containers, watch a Bell pair, a Grover search, and Shor factor 15, then follow the thread from Shor to post-quantum cryptography."
---

This walkthrough is the book in miniature. In four short runs you build the two
toolchains, watch entanglement appear as measured counts, search an unstructured
space faster than any classical loop can, and factor a number with the algorithm
that motivates post-quantum cryptography. Everything runs on a plain workstation
in Docker containers, CPU only, with no GPU and no cloud account.

Each step gives the exact command, the output to expect, and a short note on what
you are looking at and why it matters. The numbers in the sample output are
measured counts over many shots, so your run will differ by a few counts each
time. That variation is the point: a quantum program returns a distribution you
estimate by sampling, not a single value you read.

## Before you start

You need Docker Engine and the Docker Compose plugin on a Linux workstation. Clone
the repository and work from its root. Nothing else is installed on the host: the
C++ toolchain, Quantum++, Python 3.14, Qiskit, and every dependency live inside
the images.

```bash
git clone https://github.com/patterncatalyst/quantum-programming-cpp-python.git
cd quantum-programming-cpp-python
```

## Step 1: Build both toolchains

A single command builds both images. Each is a multi-stage build whose test stage
runs the full suite, so the image is never produced from code that does not pass.

```bash
docker compose build
```

The C++ image compiles every example and runs `ctest`; the Python image syncs the
locked environment and runs `pytest`. If either suite fails, the build fails and
no image is produced. This is the book's core discipline made mechanical: a
circuit that runs without error but produces the wrong distribution is still
broken, so correctness is checked against the analytic expectation, never
assumed.

The first build pulls base images and compiles Quantum++, so it takes a few
minutes. Later builds are cached and quick.

## Step 2: A Bell pair, in two languages

This is the "hello world" of entanglement. A Hadamard puts the first qubit into a
superposition, a controlled-NOT entangles the second with it, and measuring the
pair many times yields only `00` or `11`, never `01` or `10`. The two qubits are
perfectly correlated.

Run the C++ track first:

```bash
docker compose run --rm cpp
```

```text
>> Bell state |psi> = (|00> + |11>)/sqrt(2)
0.707107
       0
       0
0.707107

>> Expected counts over 1000 shots (from the state):
  |00>: 499  (p=0.5)
  |11>: 499  (p=0.5)
```

Then the same circuit in Python, cross-checked with Qiskit and the Aer simulator:

```bash
docker compose run --rm python
```

```text
>> Bell state measured counts (Qiskit Aer):
  |00>: 474
  |11>: 526
```

Two independent implementations, one measured distribution. When a C++ build and a
Python build agree on the counts, you trust the result. The outcomes `01` and `10`
never appear, which is the signature of entanglement: the qubits cannot be
described independently. Chapter 6 builds this up from the state vector.

## Step 3: Grover's search

Grover's algorithm finds a marked item in an unstructured space of size *N* in
about the square root of *N* steps. Here the space is the eight three-bit strings
and the marked item is `101`. Two Grover iterations concentrate almost all of the
probability on the target.

The runtime C++ image ships only the Bell binary, so to run the other algorithms
build the C++ **build stage**, which carries every compiled example:

```bash
docker build -t quantum-cpp-build --target build -f containers/cpp/Containerfile .
docker run --rm quantum-cpp-build /work/examples/build/08-grover/cpp/grover
```

```text
>> Grover search for 101 among 8 items, 1000 shots
iterations: 2
most measured: 101  fraction = 0.953
```

The Python image already carries the full environment, so run its Grover directly:

```bash
docker run --rm --entrypoint uv quantum-python \
  run --no-sync python examples/08-grover/python/grover.py
```

```text
>> Grover search for 101 among 8 items, 1000 shots
iterations: 2
most measured: 101  fraction = 0.936
```

About 94 to 95 percent of the shots land on `101`. A classical search of an
unstructured space of eight items has no better strategy than checking entries one
at a time; Grover gets there in two iterations. The speed-up is quadratic, and it
generalizes to any search you can phrase as marking the item you want. Chapter 8
builds the oracle and the diffusion operator.

## Step 4: Shor factors 15, and the thread to cryptography

Shor's algorithm factors an integer by finding the period of modular
exponentiation, a job phase estimation does on a quantum computer. Here it factors
15 using base *a* = 7, whose order is 4. The quantum step returns phase estimates,
and continued fractions plus a classical greatest-common-divisor turn those into
the factors.

```bash
docker run --rm quantum-cpp-build /work/examples/build/10-shor/cpp/shor
```

```text
>> Shor's algorithm: factor 15 with base a = 7
phase-estimation outcomes (value/16):
  0/16  count=474
  4/16  count=526
  8/16  count=498
  12/16  count=502
15 = 3 x 5
```

The same run in Python:

```bash
docker run --rm --entrypoint uv quantum-python \
  run --no-sync python examples/10-shor/python/shor.py
```

```text
>> Shor's algorithm: factor 15 with base a = 7
phase-estimation outcomes (value/16):
  0/16  count=535
  4/16  count=500
  8/16  count=504
  12/16  count=461
15 = 3 x 5
```

The counting register reports four peaks at 0, 4, 8, and 12 out of 16, the
multiples of 16 / 4 that reveal the order 4. From the order a classical step
recovers 3 and 5.

This small factoring is why the book spends a chapter on Shor beyond its fame.
RSA and elliptic-curve cryptography rest on factoring and discrete logarithms
being hard for classical computers. Shor makes both tractable on a large enough
quantum computer. No such machine exists yet, but data captured today can be
stored and decrypted once one does, so any secret that must stay secret for years
is already exposed. That is the harvest-now, decrypt-later problem.

## Step 5: The two tracks

The demo ends where strategy begins. A quantum program you can run on a laptop
today is the same algorithm driving a global cryptographic migration, so there are
two timelines to manage in parallel:

- **Learn quantum programming.** Prototype on CPU simulators now, with no hardware,
  and find where optimization or quantum simulation could pay off. The variational
  methods in Chapters 11 and 12 are the near-term candidates.
- **Adopt post-quantum cryptography.** Inventory long-lived secrets, enable the
  standardized post-quantum algorithms the platform already ships, and plan the
  migration before any code-breaking machine arrives.

Post-quantum cryptography is classical software that resists a quantum attacker.
It never touches a qubit, so it is a different subject from everything else in this
book, and Appendix B draws the line in full.

## Where to go deeper

- Chapter 6 for entanglement, Chapter 8 for Grover, Chapter 10 for Shor.
- Appendix B for post-quantum cryptography and why it is a separate subject.
- Appendix C for any term above you want defined in one line.

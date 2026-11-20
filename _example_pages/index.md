---
title: "Examples"
layout: plan
permalink: /examples/
description: "Every runnable example in this repo, mapped to the chapter it supports."
---

Every hands-on chapter has a matching runnable example under
[`examples/`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples)
in the repo, with a C++ (Quantum++) program and a Python (Qiskit) cross-check,
each with tests. See the [outline]({{ '/docs/00-outline/' | relative_url }}) for
the full arc.

| Example | Chapter | What it shows |
|---|---|---|
| [`00-setup`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/00-setup) | Setup | Bell state, the end-to-end toolchain check |
| [`01-environment`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/01-environment) | Chapter 1 | A first run in each container |
| [`02-qubits`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/02-qubits) | Chapter 2 | Qubits, state vectors, and measurement from scratch |
| [`03-gates`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/03-gates) | Chapter 3 | Single- and multi-qubit gates as state vectors |
| [`04-first-program`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/04-first-program) | Chapter 4 | A full program: circuit, shots, measured counts |
| [`05-measurement`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/05-measurement) | Chapter 5 | A weighted coin: amplitudes versus sampled counts |
| [`06-entanglement`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/06-entanglement) | Chapter 6 | Bell, GHZ, and teleportation in counts |
| [`07-query-algorithms`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/07-query-algorithms) | Chapter 7 | Deutsch-Jozsa and Bernstein-Vazirani in one query |
| [`08-grover`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/08-grover) | Chapter 8 | Grover's search by amplitude amplification |
| [`09-qft-phase`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/09-qft-phase) | Chapter 9 | Phase estimation with the inverse QFT |
| [`10-shor`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/10-shor) | Chapter 10 | Shor's algorithm factoring 15 |
| [`11-vqe`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/11-vqe) | Chapter 11 | VQE finding a ground-state energy |
| [`12-qaoa`](https://github.com/{{ site.github_username }}/{{ site.github_repo }}/tree/main/examples/12-qaoa) | Chapter 12 | QAOA solving MaxCut |

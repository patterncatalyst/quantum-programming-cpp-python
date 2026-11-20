---
title: "Spike results"
layout: plan
render_with_liquid: false
---

# Spike results

Dated 2026-11-19. Host: Fedora 45 workstation, x86_64. The spike gates chapter
prose: confirm both toolchains build and run a Bell state before writing.

## Verdict

Both tracks build and run, producing the same Bell state. The project's two
headline risks are cleared:

- **C++ quantum framework builds on Fedora** (the PRD's #1 risk): yes.
- **Python frameworks install on 3.14** (the PRD's highest risk): yes, live-confirmed.

## C++ track (primary)

- Toolchain: Clang 23.1.5, CMake 4.3.0, Ninja 1.13.2, Conan 2.31.2, C++23,
  warnings-as-errors.
- Dependencies: Eigen 3.4.1 and GoogleTest 1.18.0 via Conan; **Quantum++ v7.1.1**
  header-only via CMake FetchContent.
- Result: `examples/00-setup/cpp/bell_state` prints statevector
  `(0.707107, 0, 0, 0.707107)` = (|00> + |11>)/sqrt(2); the GoogleTest check on the
  amplitudes passes under `ctest`.

Findings worth keeping:

- qpp v7's umbrella header is `qpp/qpp.hpp` (not `.h`).
- qpp bundles qasmtools; a consumer must add both `include/` and
  `qasmtools/include/` to the include path. We mark both SYSTEM so qpp and Eigen
  headers never trip our warnings-as-errors.
- qpp is not on Conan Center, so FetchContent (pinned tag) is the right path.

## Python track (secondary, cross-check and tests)

- uv-managed **CPython 3.14.8** (the host system Python stays 3.15.2, untouched).
- `uv sync` installed **Qiskit 2.6.2** and **Qiskit Aer 0.18.4** cleanly on 3.14,
  plus rustworkx 0.18.1, scipy 1.18.1, numpy (transitive).
- Result: `examples/00-setup/python/bell_state.py` on the Aer CPU simulator gives
  counts near 510/490 for 00/11 and nothing else; pytest passes.

## Still open (not blocking chapter prose)

- Qubit-ceiling benchmark (time and RSS by qubit count) on this box.
- Cirq and PennyLane install check on 3.14 (web-confirmed available; not yet run here).
- CUDA-Q `qpp-cpu` build (secondary C++ option; lean on its published image).
- The same builds inside the Docker multi-stage images (r01 containers).
